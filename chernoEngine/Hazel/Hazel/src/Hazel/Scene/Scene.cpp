#include "hzpch.h"
#include "Scene.h"
#include "ScriptableEntity.h"

#include "Entity.h"
#include "Component.h"
#include "Hazel/Renderer/Renderer2D.h"
#include "glm/glm.hpp"

#include "box2d/b2_world.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h" //fixture �̶���
#include "box2d/b2_polygon_shape.h" //colliderBox shape �������ײ��

namespace Hazel
{

	static b2BodyType RigidBodyType2b2BodyType(const Hazel::Rigidbody2DComponent::RigidBodyType& bodytype)
	{
		switch (bodytype)
		{
			case Rigidbody2DComponent::RigidBodyType::Static:	return b2BodyType::b2_staticBody;
			case Rigidbody2DComponent::RigidBodyType::Kinematic: return b2BodyType::b2_kinematicBody;
			case Rigidbody2DComponent::RigidBodyType::Dynamic:	return b2BodyType::b2_dynamicBody;
		}

		HZ_CORE_WARN("UnKonw hazel RigidBodyType:{0}",(int)bodytype);
		HZ_CORE_ASSERT(false, "UnKonw hazel RigidBodyType");

		return b2BodyType::b2_staticBody;

	}

	//��װ��.......... entt��ĺ�������

	Scene::Scene()
	{


	}


	Scene::~Scene()
	{
		//delete m_mainCamera;
	}

	template<typename T>
	static void CopyComponent(entt::registry& dst , entt::registry& src,const std::unordered_map<UUID, entt::entity>& enttMap)
		//ͨ��ID���dst,��src ���Ǽǵ�entt��Ӧ��ϵ,���˶�Ӧ��ϵ�Ϳ��Զ�Ӧʵ�忽����ӵ�е������
	{
		auto view = src.view<T>();

		for (auto& e : view)
		{
			UUID uuid = src.get<IDComponent>(e).ID;
			HZ_CORE_ASSERT(enttMap.find(uuid) != enttMap.end(), "Doesn't find uuid when copyComponent");
			entt::entity dstEnttID =  enttMap.at(uuid); //enttMap is of dstRegistry

			auto& component = src.get<T>(e);
			dst.emplace_or_replace<T>(dstEnttID, component);//����transform���û���� ������replace

			//for (auto de: dstIdView)
				//���ֱ�������̫������,������unorderedMap��¼UUID,�ռ任ʱ��
		}

	}


	template<typename T>
	static void CopyComponentIfExists(Entity& dst, Entity& src)
	{

		if (src.HasComponent<T>())
		{
			dst.AddOrReplaceComponent<T>(src.GetComponent<T>());
		}


	}


	Ref<Scene> Scene::Copy(Ref<Scene> other)
	{
		Ref<Scene> newScene = CreateRef<Scene>();
		newScene->m_viewportWidth = other->m_viewportWidth;
		newScene->m_viewportHeight= other->m_viewportHeight;
		

		auto& srcSceneRegistry = other->m_registry;
		auto& dstSceneRegistry = newScene->m_registry;
		std::unordered_map<UUID, entt::entity> enttMap;

		//CreateEntity 
		auto idView = srcSceneRegistry.view<IDComponent>();
		for (auto e : idView)
		{
			UUID uuid = srcSceneRegistry.get<IDComponent>(e).ID;
			const std::string& tag = srcSceneRegistry.get<TagComponent>(e).Tag;
			auto entity =  newScene->CreateEntityWithUUID(uuid, tag);
			enttMap[uuid] = entt::entity (entity);
		}

		//CopyComponent (except ID,tag ,tansform(need accept parameter))

		CopyComponent<TransformComponent>(dstSceneRegistry,srcSceneRegistry,enttMap);
		CopyComponent<SpriteRendererComponent>(dstSceneRegistry,srcSceneRegistry,enttMap);
		CopyComponent<CircleRendererComponent>(dstSceneRegistry,srcSceneRegistry,enttMap);
		CopyComponent<CameraComponent>(dstSceneRegistry,srcSceneRegistry,enttMap);
		CopyComponent<NativeScripComponent>(dstSceneRegistry,srcSceneRegistry,enttMap);
		CopyComponent<Rigidbody2DComponent>(dstSceneRegistry,srcSceneRegistry,enttMap);
		CopyComponent<BoxCollider2DComponent>(dstSceneRegistry,srcSceneRegistry,enttMap);

		return newScene;
	}

	void Scene::DuplicateEntity(Entity entity)
	{
		Entity newEntity = CreateEntity(entity.GetTag());
		CopyComponentIfExists<TransformComponent>		(newEntity, entity);
		CopyComponentIfExists<SpriteRendererComponent>	(newEntity, entity);
		CopyComponentIfExists<CircleRendererComponent>	(newEntity, entity);
		CopyComponentIfExists<CameraComponent>			(newEntity, entity);
		CopyComponentIfExists<NativeScripComponent>		(newEntity, entity);
		CopyComponentIfExists<Rigidbody2DComponent>		(newEntity, entity);
		CopyComponentIfExists<BoxCollider2DComponent>	(newEntity, entity);
	}


	void Scene::OnUpdateEditor(Timestep ts, EditorCamera& camera)
	{


		Renderer2D::BeginScene(camera);
		//DrawSprite
		{
			auto group = m_registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto& [transC, spriteC] = m_registry.get<TransformComponent, SpriteRendererComponent>(entity);
				Renderer2D::DrawQuad(transC.GetTransform(), spriteC.Color, (int)entity);
			}

		}

		//DrawCircle
		{
			auto view = m_registry.view<TransformComponent, CircleRendererComponent>();
			for (auto entity : view)
			{
				auto& [transC, CircleC] = view.get<TransformComponent, CircleRendererComponent>(entity);
				Renderer2D::DrawCircle(transC.GetTransform(), CircleC.Color, CircleC.Thickness, CircleC.Fade, (int)entity);
			}

		}

		Renderer2D::EndScene();

	}

	void Scene::OnUpdateRuntime(Timestep ts)
	{
		//Update Script ... you should bind an specific NativeScriptcomponent before it enter Scene's Update
		//Script
		{
			m_registry.view<NativeScripComponent>().each([=](auto entity ,NativeScripComponent& nsc)  // auto entity ,&nsc : view 
			{
				if(!nsc.Instance)
				{ 
					nsc.Instance = nsc.InstantiateScript();
					nsc.Instance->m_entity = { entity,this };
					nsc.Instance->OnCreate();	
				}

				
				nsc.Instance->OnUpdate(ts);	
			
			}); // nsc: native script component


		}

		//physics
		{
			const int32_t velocityIteration = 6; // ->ÿ���������
			const int32_t positionIteration = 2; //λ���������������
			
			//����
			m_physicsWorld->Step(ts, velocityIteration, positionIteration);

			m_registry.view<Rigidbody2DComponent>().each([=](auto e, Rigidbody2DComponent& rb2d)  // auto entity ,&nsc : view 
				{
					Entity entity = { e,this };
					auto& transform = entity.GetComponent<TransformComponent>();
					
					b2Body* body = (b2Body*)rb2d.RuntimeBody;
					//�����˶�����Ȩ�Ѿ��ƽ�����rigidBody , rigidBody -> transform
					const auto& position = body->GetPosition();
					transform.Translation.x = position.x;
					transform.Translation.y = position.y;
					transform.Rotation.z = body->GetAngle();

				}); 


		}



		//render
		Camera* main_Camera = nullptr;
		TransformComponent* main_Camrea_transform = nullptr;
		{

			auto view = m_registry.view<CameraComponent,TransformComponent>();
			for (auto entity : view)
			{
				auto[camera,trans] = view.get<CameraComponent, TransformComponent>(entity); //ok.. view.get��������Ԫ��,����ֱ��auto[] ����.�������ò�������Ϊauto ����[]�Ľṹ����
				if (camera.Primary)	
				{

					main_Camera = & camera.Camera;
					main_Camrea_transform = &trans;
					break;
				}
				
			}
		}

		if (main_Camera)
		{

			Renderer2D::BeginScene(main_Camera->GetProjection(),*main_Camrea_transform);
			{
				auto group = m_registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
				for (auto entity : group)
				{
					auto& [transC, spriteC] = m_registry.get<TransformComponent, SpriteRendererComponent>(entity);
					Renderer2D::DrawQuad(transC.GetTransform(), spriteC.Color, (int)entity);
				}

			} 
			
			{
				auto view = m_registry.view<TransformComponent, CircleRendererComponent>();
				for (auto entity : view)
				{
					auto& [transC, CircleC] = view.get<TransformComponent, CircleRendererComponent>(entity);
					Renderer2D::DrawCircle(transC.GetTransform(), CircleC.Color,CircleC.Thickness,CircleC.Fade, (int)entity);
				}

			}

			Renderer2D::EndScene();
		}


	}

	Entity Scene::CreateEntity(const std::string& tag)
	{
		return CreateEntityWithUUID(UUID(), tag);
	}

	Entity Scene::CreateEntityWithUUID(UUID uuid, const std::string& tag /* = std::string("Entity") */)
	{
		Entity e{ m_registry.create(),this };
		e.AddComponent<IDComponent>(uuid);
		e.AddComponent<TransformComponent>();
		e.AddComponent<TagComponent>(tag);
		return e;
	}

	void Scene::OnViewportResize(const uint32_t& width, const uint32_t& height)
	{
		m_viewportWidth = width;
		m_viewportHeight = height;

		//fix our camera aspectratio
		auto view = m_registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& camera = view.get<CameraComponent>(entity);//���Ƕ��ڵ��������get����..��������Ҫ& �н�...�Լ�ȥ���������Ͱ�!
			if (!camera.FixedAspectRatio) //camera size change with viewPort -> change ProjectionMatrix
			{
				camera.Camera.SetViewPortSize(width,height);
			}

		}

	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_registry.destroy(entity);

	}


	template <typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		//static_assert(false); //��̬���� -> �޶�Ӧ�ػ�ģ�� ->�ж�
		//ɾ�˾�̬���� - 
	}
	//ģ���ػ�
	template <>
	void Hazel::Scene::OnComponentAdded<IDComponent>(Entity entity, IDComponent& component)
	{

	}
	template <>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{

	}

	template <>
	void Hazel::Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
	{

	}	
	template <>
	void Hazel::Scene::OnComponentAdded<CircleRendererComponent>(Entity entity, CircleRendererComponent& component)
	{

	}

	template <>
	void Hazel::Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		component.Camera.SetViewPortSize(m_viewportWidth, m_viewportHeight);
	}
	template <>
	void Hazel::Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{

	}

	template <>
	void Hazel::Scene::OnComponentAdded<NativeScripComponent>(Entity entity, NativeScripComponent& component)
	{

	}
	template <>
	void Hazel::Scene::OnComponentAdded<Rigidbody2DComponent>(Entity entity, Rigidbody2DComponent& component)
	{

	}	
	template <>
	void Hazel::Scene::OnComponentAdded<BoxCollider2DComponent>(Entity entity, BoxCollider2DComponent& component)
	{

	}

	Entity Scene::GetPrimaryCamera()
	{
		auto view = m_registry.view<CameraComponent>();
		if(view.empty())
		{
			return {entt::null,this};
		}
		for (auto entity : view)
		{
			auto& camera= view.get<CameraComponent>(entity); //ok.. view.get��������Ԫ��,����ֱ��auto[] ����.�������ò�������Ϊauto ����[]�Ľṹ����
			if (camera.Primary)
			{
				return {entity,this};
			}

		}
		return { entt::null,this };
	}

	void Scene::OnRuntimeStart()
	{
		b2Vec2 gravity(0.f, -9.8f);
		m_physicsWorld = new b2World(gravity);


		//begin simulation
		auto& view = m_registry.view<Rigidbody2DComponent>();
		for (auto& e: view)
		{
			Entity entity = { e,this };
			auto& transform = entity.GetComponent<TransformComponent>();
			auto& rb2d= entity.GetComponent<Rigidbody2DComponent>();
			
			//��ʼ�����ýṹ��
			b2BodyDef bodyDef;
			bodyDef.type = RigidBodyType2b2BodyType(rb2d.BodyType);
			bodyDef.fixedRotation = rb2d.FixedRotation;
			//������λ�õĿ���ȨӦ�����ƽ������ǹ���
			bodyDef.position.Set(transform.Translation.x, transform.Translation.y);
			bodyDef.angle = transform.Rotation.z;
			
			b2Body* body = m_physicsWorld->CreateBody(&bodyDef);
			//body->SetFixedRotation(rb2d.FixedRotation)
			rb2d.RuntimeBody = body;

			if (entity.HasComponent<BoxCollider2DComponent>())
			{
				auto& bc2d = entity.GetComponent<BoxCollider2DComponent>();
				b2PolygonShape shape;
				shape.SetAsBox(transform.Scale.x*bc2d.Size.x, transform.Scale.y * bc2d.Size.y);//hx , hy  h:half
				
				b2FixtureDef fixtureDef;
				fixtureDef.shape = &shape;
				fixtureDef.density = bc2d.Density;
				fixtureDef.friction = bc2d.Friction;
				fixtureDef.restitution= bc2d.Restitution;
				fixtureDef.restitutionThreshold = bc2d.RestitutionThreshold;
						
				body->CreateFixture(&fixtureDef);
			}
		}


	}

	void Scene::OnRuntimeStop()
	{
		delete m_physicsWorld;
		m_physicsWorld = nullptr;
	}






}


// entt example:
// 		//�����Լ���wiki
// 		transform trans;
// 		Stmath((const glm::mat4&)trans);
// 
// 		entt::entity entity =   m_registry.create(); //entity is std::uint32_t
// 		m_registry.emplace<transform>(entity, glm::mat4(1.f));//Ϊentity�������
// 		m_registry.remove<transform>(entity);
// 
// 		m_registry.get<transform>(entity);
// 
// 		//��ʹ�� any_of / all_of ���� has() ��̽�� ʵ���Ƿ���м����е���������������κ�һ�����
// 		m_registry.any_of<transform>(entity);
// 		//����ʵ��û�е���� get����� :auto vec2 = m_registry.get<glm::vec2>(entity);
// 
// 		auto view = m_registry.view<transform>(); //̽�����к���ģ���������ʵ�岢���� view: һ��entitys�Ŀɵ�������,entity�����ĸ��������(get)
// 		for (entt::entity entit : view)
// 		{
// 			auto& trasn = m_registry.get<transform>(entit);
// 			auto& trasn = m_registry.get<TagComponent>(entit);

// 			auto& trasn = view.get<transform>(entit);
// 		}
// 
// 		//�������...�е���������
// 		//m_registry.on_construct<transform>().connect<&CallMePls>(); // ����/��Ӧtransform��������¼� connect<&func>() �����ӻص�����	
// 
// 		auto group = m_registry.group<transform>(entt::get<MeshCom>); //group (��ӵ����) ���غ������������ʵ�� ����������Ƭ... �����Ż���..��������������
// 		for (auto entit : group)
// 		{
// 			auto& [as, sb] = group.get<transform,MeshCom>(entit); //����tuple ... �񷵻ؼ���������
// 		}

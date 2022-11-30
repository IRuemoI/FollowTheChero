#include "hzpch.h"
#include "Scene.h"

#include "Entity.h"
#include "Component.h"
#include "Hazel/Renderer/Renderer2D.h"
#include "glm/glm.hpp"

namespace Hazel
{
	//��װ��.......... entt��ĺ�������

	Scene::Scene()
	{


	}


	Scene::~Scene()
	{
		//delete m_mainCamera;
	}


	void Scene::OnUpdateEditor(Timestep ts, EditorCamera& camera)
	{


		Renderer2D::BeginScene(camera);

		auto group = m_registry.group<TransformComponent, SpriteRendererComponent>();

		for (auto entity : group) //����ٴ��ϵ��»���
		{
			auto& [transC, spriteC] = m_registry.get<TransformComponent, SpriteRendererComponent>(entity);
			//Renderer2D::DrawQuad((const glm::mat4&)transC, (const glm::vec4&)spriteC,20);
			//�ƺ�DrawQuad����entityID ��ʱ���ܴ��ݵ�colorAttach1
			Renderer2D::DrawSprite((const glm::mat4&)transC, spriteC, (int)entity);
		}

		Renderer2D::EndScene();

	}

	void Scene::OnUpdateRuntime(Timestep ts)
	{
		//Update Script ... you should bind an specific NativeScriptcomponent before it enter Scene's Update
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

			auto group = m_registry.group<TransformComponent, SpriteRendererComponent>();

			for (auto entity : group)
			{
				auto& [transC, spriteC] = m_registry.get<TransformComponent, SpriteRendererComponent>(entity);
				HZ_CORE_TRACE("Renderer2D::DrawQuad ,entityID: {0}", (int)entity);
				Renderer2D::DrawQuad((const glm::mat4&)transC, (const glm::vec4&)spriteC, (int)entity);

			}

			Renderer2D::EndScene();
		}


	}

	Entity Scene::CreateEntity(const std::string& tag)
	{



		Entity e{ m_registry.create(),this };
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
		static_assert(false); //��̬���� -> �޶�Ӧ�ػ�ģ�� ->�ж�
	}
	//ģ���ػ�
	template <>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
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


	template <>
	void Hazel::Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
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



}


// example:
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

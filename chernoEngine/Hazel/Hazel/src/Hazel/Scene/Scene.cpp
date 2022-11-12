#include "hzpch.h"
#include "Scene.h"
#include "Component.h"
#include "Entity.h"

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
		delete m_mainCamera;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		//render
		Camera* main_Camera = nullptr;
		glm::mat4* main_Camrea_transformMat = nullptr;
		{

			auto view = m_registry.view<CameraComponent,TransformComponent>();
			for (auto entity : view)
			{
				auto&[camera,trans] = view.get<CameraComponent, TransformComponent>(entity);
				if (camera.Primary)
				{

					m_mainCamera = new Entity{entity,this};
					main_Camera = &camera.camera;
					main_Camrea_transformMat = &trans.Transform;
					break;
				}
				
			}
		}

		if (main_Camera)
		{

			Renderer2D::BeginScene(main_Camera->GetProjection(),*main_Camrea_transformMat);

			auto group = m_registry.group<TransformComponent, SpriteRendererComponent>();

			for (auto entity : group)
			{
				auto& [transC, spriteC] = m_registry.get<TransformComponent, SpriteRendererComponent>(entity);
				Renderer2D::DrawQuad((const glm::mat4&)transC, (const glm::vec4&)spriteC);
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

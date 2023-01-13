#pragma once
#include "entt.hpp"

#include "Hazel/Core/Timestep.h"
#include "Hazel/Core/UUID.h"
#include "Hazel/Renderer/EditorCamera.h"

class b2World;

namespace Hazel //100% ��װ �������û��Ӵ�������hazel֮���api
{
	class Entity;// ǰ������ ���ͷ�ļ���(�ڶ���֮ǰ�޷��������Ա)

	class Scene //scene �� rigister�İ�װ��, entity �� conpoment�İ�װ��
	{
	public:
		Scene();
		~Scene();

		static Ref<Scene> Copy(Ref<Scene> other);

		/**
		* @����Ĭ�ϵ�transformComponent��Tag, brief Creates a new entity or recycles a destroyed one.
		* @return Entity.
		*/
		Entity CreateEntity(const std::string& tag = std::string("Entity"));
		Entity CreateEntityWithUUID(UUID uuid, const std::string& tag = std::string("Entity"));
		Entity GetPrimaryCamera();
		
		void OnViewportResize(const uint32_t & width, const uint32_t& height) ;

		void OnUpdateRuntime(Timestep ts);
		void OnUpdateEditor(Timestep ts,EditorCamera& camera);

		void OnRuntimeStart();
		void OnRuntimeStop();

		void DestroyEntity(Entity entity);

		void DuplicateEntity(Entity entity); //����ʵ��

	private:
		template <typename T>
		void OnComponentAdded(Entity entity, T& component);


	private:

		entt::registry m_registry; //ʵ��ע��� ����entity������,���Ƕ�entity����һ�в�����Ҫ������ https://github.com/skypjack/entt
		Entity* m_mainCamera;
		uint32_t m_viewportWidth =0 ;
		uint32_t m_viewportHeight =0 ;

		b2World* m_physicsWorld =nullptr;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel; //that means SceneHierarchyPanel can use scene's private numbers

	};


}


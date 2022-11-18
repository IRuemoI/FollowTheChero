#pragma once
#include "entt.hpp"

#include "Hazel/Core/Timestep.h"


namespace Hazel //100% ��װ �������û��Ӵ�������hazel֮���api
{
	class Entity;// ǰ������ ���ͷ�ļ���(�ڶ���֮ǰ�޷��������Ա)

	class Scene //scene �� rigister�İ�װ��, entity �� conpoment�İ�װ��
	{
	public:
		Scene();
		~Scene();


		/**
		* @����Ĭ�ϵ�transformComponent��Tag, brief Creates a new entity or recycles a destroyed one.
		* @return Entity.
		*/
		Entity CreateEntity(const std::string& tag = std::string("Entity"));
		inline Entity* GetMainCamera(){ return m_mainCamera; };
		
		void OnViewportResize(const uint32_t & width, const uint32_t& height) ;

		void OnUpdate(Timestep ts);

		void DestroyEntity(Entity entity);

	private:
		template <typename T>
		void OnComponentAdded(Entity entity, T& component);


	private:

		entt::registry m_registry; //ʵ��ע��� ����entity������,���Ƕ�entity����һ�в�����Ҫ������ https://github.com/skypjack/entt
		Entity* m_mainCamera;
		uint32_t m_viewportWidth =0 ;
		uint32_t m_viewportHeight =0 ;


		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel; //that means SceneHierarchyPanel can use scene's private numbers

	};


}


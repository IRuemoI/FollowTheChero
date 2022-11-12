#pragma once
#include "Scene.h"
#include "entt.hpp"
#include "Component.h"

namespace Hazel

{


	class Entity //scene's friend class
	{
	public:
		Entity() = default; //cherno ˵��ʵ��Ҳ����Ч��...   �Ҿ����е�Σ��
		Entity(const entt::entity& handle,	 Scene* scene);
		Entity(const Entity & other) = default; //as tishi(0.0)
		Entity(Scene* scene);

		template<typename T ,typename... Args>
		//return: reference of the component
		T& AddComponent(Args&&... args) 
		{

			HZ_CORE_ASSERT(!HasComponent<T>(), "Entity already has component");
			return m_scene->m_registry.emplace <T>(m_entityHandle, std::forward<Args>(args)...);


		}
		template<typename T>
		T& GetComponent()
		{
			HZ_CORE_ASSERT(HasComponent<T>(), "Entity does not have component");
			return m_scene->m_registry.get<T>(m_entityHandle);
		}


		template<typename T>
		bool HasComponent()
		{
			return m_scene->m_registry.all_of<T>(m_entityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			HZ_CORE_ASSERT(HasComponent<T>(), "Entity does not have component");
			m_scene->m_registry.remove<T>(m_entityHandle);
		}

		operator bool() const { return m_entityHandle != entt::null;} //Ϊentity �ṩboolת�� ...�������entity

	private:
		entt::entity m_entityHandle{entt::null};
		//Ref<Scene> m_scene; entity��Ӧ��(ǿ����)shared own scene .ʵ�岻��Ӱ��scene����������,����Ӧ�÷�֮
		Scene* m_scene =nullptr;



	};



}


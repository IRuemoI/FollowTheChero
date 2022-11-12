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


		void OnUpdate(Timestep ts);

	private:



		entt::registry m_registry; //ʵ��ע��� ����entity������,���Ƕ�entity����һ�в�����Ҫ������ https://github.com/skypjack/entt

		Entity* m_mainCamera;
		friend class Entity;


	};
}


#pragma once
#include "Entity.h"

namespace Hazel
{

	class  ScriptableEntity
	{
	public:
		ScriptableEntity() =default;
		virtual ~ScriptableEntity() =default;


		//��Ҫ����! ����ʱ��Ҫ��ȷ����,Ҫô =0,Ҫô������.�����cherno��һ��..���˽ӿ�..ȷ������û������������
		template<typename T>
		T& GetComponent() {

			HZ_CORE_ASSERT(m_entity.HasComponent<T>(), "Entity already has component");
			return m_entity.GetComponent<T>();
		}
		
	protected:
		virtual void OnCreate() {};
		virtual void OnUpdate(Timestep ts) {};
		virtual void OnDestroy() {};



	private:

		Entity m_entity;
		friend class Scene;


	};
}




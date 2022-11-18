#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Hazel/Renderer/OrthographicCamera.h"
#include "Hazel/Core/Timestep.h"
#include "SceneCamera.h"

#include "ScriptableEntity.h"


namespace Hazel
{



	struct Component  //store all information we need to create an specific entity
	{

	};


	//@use: the Transform[3] is its Position
	struct TransformComponent:Component //use degree, like Blender!!
	{

		glm::vec3 Translation = glm::vec3(0.f);
		glm::vec3 Rotation= glm::vec3(0.f);
		glm::vec3 Scale = glm::vec3(1.f);

	

		TransformComponent() = default;
		TransformComponent(const TransformComponent& trans) = default;
		TransformComponent(const glm::vec3& translation)
			:Translation(translation) {};
		glm::mat4 GetTransform() const
		{
			glm::mat4 rotationMat = glm::rotate(glm::mat4(1.f), Rotation.x, { 1.f,0.f,0.f })
				* glm::rotate(glm::mat4(1.f), Rotation.y, { 0.f,1.f,0.f })
				* glm::rotate(glm::mat4(1.f), Rotation.z, { 0.f,0.f,1.f });
			glm::mat4 scaleMat = glm::scale(glm::mat4(1.f), Scale);
			return glm::translate(glm::mat4(1.f), Translation) * rotationMat * scaleMat;

		}

		operator glm::mat4 () { return GetTransform(); }   //����� const &�Ĵ����ƺ��ֲ�����const &���� &������....
		operator const glm::mat4 () const{ return GetTransform(); } //������ת������.֮�����ֱ��ת����...������ʽ��ʽ..������ ������()?? 
	
	};

	struct SpriteRendererComponent:Component
	{
		glm::vec4 Color{1.f,1.f,1.f,1.f};

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent& another) = default;
		SpriteRendererComponent(const glm::vec4& o_color)
			:Color(o_color) {};

		operator glm::vec4& () { return Color; }   
		operator const glm::vec4& () const { return Color; } 
	};

	struct MeshComponent:Component
	{

	};

	struct TagComponent:Component
	{
		std::string Tag ;
		TagComponent() = default;
		TagComponent(const TagComponent& another) = default;
		TagComponent(const std::string& tag)
			:Tag(tag) {};

	};

	struct CameraComponent
	{


		SceneCamera Camera;
		bool Primary = false;//��ǰ������/�������;
		bool FixedAspectRatio = false;//�Ƿ���Ҫ�޸����ݱ�(�����ӿڱ仯���仯)



		CameraComponent() = default;
		CameraComponent(const CameraComponent& another) = default;
		

	};
	struct NativeScripComponent //interface/slot of ScrptableEntity Component
	{
	public:
		
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity* (*InstantiateScript)();//����ָ�� , ��std::function�����?
		void (*DestroyScript)(NativeScripComponent*); //ģ�� ��Ա����?
		template<typename T>
		void Bind() 
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); }; //��ʼ�� Instance
			DestroyScript= [](NativeScripComponent* nsc) {delete nsc->Instance; nsc->Instance = nullptr; };//& ���ò���

			//ת��: 
			//instance û�ó�Ա&Instance , ����ѡ���ٵ���ʱ�ֶ����� .Instance
		}

	};


}



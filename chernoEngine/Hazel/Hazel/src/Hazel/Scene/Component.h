#pragma once

#include "Hazel/Renderer/Texture.h"
#include "Hazel/Core/Timestep.h"
#include "Hazel/Core/UUID.h"

#include "SceneCamera.h"


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/quaternion.hpp" // for qurt and toMat  ��Ҫ����glmʵ�鹦��

namespace Hazel
{


	struct Component  //store all information we need to create an specific entity
	{

	};

	// ʹ��UUID����Ϊentity���
	struct IDComponent:Component
	{
		UUID ID;
		IDComponent() = default;
		IDComponent(UUID id) { ID = id; };
		IDComponent(const IDComponent& other) = default;
	};

	struct TagComponent :Component
	{
		std::string Tag;
		TagComponent() = default;
		TagComponent(const TagComponent& another) = default;
		TagComponent(const std::string& tag)
			:Tag(tag) {};

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
			glm::mat4 rotationMat = glm::toMat4(glm::quat(Rotation));
			glm::mat4 scaleMat = glm::scale(glm::mat4(1.f), Scale);
			return glm::translate(glm::mat4(1.f), Translation) * rotationMat * scaleMat;

		}

		operator glm::mat4 () { return GetTransform(); }   //����� const &�Ĵ����ƺ��ֲ�����const &���� &������....
		operator const glm::mat4 () const{ return GetTransform(); } //������ת������.֮�����ֱ��ת����...������ʽ��ʽ..������ ������()?? 
	
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{1.f,1.f,1.f,1.f};
		Ref<Texture2D> Texture;
		float TilingFactor = 1.f;

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent& another) = default;
		SpriteRendererComponent(const glm::vec4& o_color)
			:Color(o_color) {};

		operator glm::vec4& () { return Color; }   
		operator const glm::vec4& () const { return Color; } 
	};

	struct CircleRendererComponent
	{
		glm::vec4 Color{ 1.f,1.f,1.f,1.f };
		Ref<Texture2D> Texture;
		//Use transform to control a circlr 
		//float Radius = 0.5f; // for a width 1m circle 
		float Thickness =1.0f;
		float Fade = 0.002f;

		CircleRendererComponent() = default;
		CircleRendererComponent(const CircleRendererComponent& another) = default;
		CircleRendererComponent(const glm::vec4& o_color,float thickness,float fade)
			:Color(o_color),Thickness(thickness),Fade(fade)
			{};

		operator glm::vec4& () { return Color; }
		operator const glm::vec4& () const { return Color; }
	};

	struct MeshComponent
	{

	};



	struct CameraComponent
	{


		SceneCamera Camera;
		bool Primary = false;//��ǰ������/�������;
		bool FixedAspectRatio = false;//�Ƿ���Ҫ�޸����ݱ�(�����ӿڱ仯���仯)



		CameraComponent() = default;
		CameraComponent(const CameraComponent& another) = default;
		

	};
	class ScriptableEntity; // ǰ������
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

	//physics component;
	struct Rigidbody2DComponent
	{
		enum class RigidBodyType
		{
			Static=0, Dynamic,Kinematic
			//Kinematic ����ѧ(���϶���ѧ��->�ؽ�/����һ��) 
			//IK, -> b2Body ��û��IK����		
		};

		RigidBodyType BodyType = RigidBodyType::Static;
		bool FixedRotation = false; // no rotation

		//Storage for runtime
		void* RuntimeBody = nullptr; //trace a RigidBody in Runtime and delete after stop

		Rigidbody2DComponent() = default;	
		Rigidbody2DComponent(const Rigidbody2DComponent& other) = default; //copy srtuct
		

	};
	struct BoxCollider2DComponent:Component
	{
		//shape?
		glm::vec2 Offset = { 0.f,0.f };
		glm::vec2 Size= { 0.5f,0.5f };

		//it should belong to physics material
		float Density = 1.f; //�ܶ�
		float Friction = 0.5f;//Ħ��ϵ��
		float Restitution = 0.0f; //�ָ�ϵ��(����)
		float RestitutionThreshold = 0.1f; //�ָ���ֵ(����)



		//Storage for runtime
		void* RuntimeFixture= nullptr; //trace a RigidBody in Runtime and delete after stop

		BoxCollider2DComponent() = default;
		BoxCollider2DComponent(const BoxCollider2DComponent& other) = default; //copy srtuct


	};

}



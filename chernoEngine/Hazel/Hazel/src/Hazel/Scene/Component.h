#pragma once
#include "glm/glm.hpp"
#include "Hazel/Renderer/OrthographicCamera.h"
#include "Hazel/Renderer/Camera.h"

namespace Hazel
{


	struct Component
	{

	};

	struct TransformComponent:Component
	{
		glm::mat4 Transform{ 1.f };
		TransformComponent() = default;
		TransformComponent(const TransformComponent& trans) = default;
		TransformComponent(const glm::mat4& mat)
			:Transform(mat) {};

		operator glm::mat4& () { return Transform; }   //����� const &�Ĵ����ƺ��ֲ�����const &���� &������....
		operator const glm::mat4& () const{ return Transform; } //������ת������.֮�����ֱ��ת����...������ʽ��ʽ..������ ������()?? 
	
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


		Camera camera;
		//TEMP: Ӧ�ý��ɳ�������
		bool Primary = false;//��ǰ������/�������;

		CameraComponent() = default;
		CameraComponent(const CameraComponent& another) = default;
		CameraComponent(const glm::mat4& Projectmat)
			:camera(Projectmat) {};



	};


}



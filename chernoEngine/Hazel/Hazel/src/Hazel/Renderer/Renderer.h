#pragma once

#include "RenderCommand.h"
//extern 
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Hazel
{


		
	class Renderer //it shoud be   Render -> RenderCommand -> RenderAPI -> different platform achivement
	{
	public:


		static void  BeginScene(OrthographicCamera& orCamera );
		static void  EndScene();
		static void  Submit( const Ref<Shader>& shader,const Ref<VertexArray>& vao,const glm::mat4& transformMat = glm::mat4(1.0f));

		static void Init();

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }; 


	private:
		struct SceneData
		{
			
			glm::mat4 ViewProjectionMartix;  //��������� ...����... ,���ñ��봴��ʱ�ͱ���ʼ��

		};

		static SceneData* m_sceneData;
			





	};

}



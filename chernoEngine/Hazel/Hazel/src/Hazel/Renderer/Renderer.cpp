#include "hzpch.h"
#include "Renderer.h"
#include "Platform/openGl/OpenGlShader.h"



namespace Hazel
{
	Renderer::SceneData* Renderer::m_sceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& orC)
	{
		m_sceneData->ViewProjectionMartix = orC.GetViewProjectionMat();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Ref<Shader>& shader,const Ref<VertexArray>& vao, const glm::mat4& transformMat)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGlShader>(shader)->UploadUniformMat4("u_ViewProjection",m_sceneData->ViewProjectionMartix);//������ҪΪ���������shaderָ��ͳһ��uniform��׼
		std::dynamic_pointer_cast<OpenGlShader>(shader)->UploadUniformMat4("u_Transform",transformMat);//������ҪΪ���������shaderָ��ͳһ��uniform��׼

		vao->Bind();
		RenderCommand::DrawIndexed(vao);
	}

	void Renderer::Init()
	{
		RenderCommand::Init();
	}
	

}

#include "hzpch.h"
#include "OpenGlRendererAPI.h"
#include "glad/glad.h"

namespace Hazel
{
	void OpenGlRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r,color.g,color.b,color.a); //������glad�ṩ�ú���
	}

	void OpenGlRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	}

	void OpenGlRendererAPI::DrawIndexed(const Ref<VertexArray>& VA)
	{
		glDrawElements(GL_TRIANGLES, VA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);//�Ѿ�ָ��������������,��nullptr,drawelementʹ�ö����vao/Ĭ�ϵ�vao
	}

	void OpenGlRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//���û�Ϸ�ʽ src_alpha * texture + 1-src_a*theCurrentImage
	}



}

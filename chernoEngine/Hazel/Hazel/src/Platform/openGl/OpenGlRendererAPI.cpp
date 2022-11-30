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

	void OpenGlRendererAPI::DrawIndexed(const Ref<VertexArray>& VA,uint32_t indexCount)
	{
		uint32_t DrawindexCount = indexCount ?indexCount: VA->GetIndexBuffer()->GetCount();

		//CHANGED:glDepthMask
		//glDepthMask(false);
		glDrawElements(GL_TRIANGLES, DrawindexCount, GL_UNSIGNED_INT, nullptr);//�Ѿ�ָ��������������,��nullptr,drawelementʹ�ö����vao/Ĭ�ϵ�vao
		glBindTexture(GL_TEXTURE_2D, 0);//unbind texture
		//glDepthMask(true);
	}

	void OpenGlRendererAPI::Init()
	{
		HZ_PROFILE_FUNCTION();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//���û�Ϸ�ʽ src_alpha * texture + 1-src_a*theCurrentImage


	}

	void OpenGlRendererAPI::SetViewPort(uint32_t x, uint32_t y,uint32_t width, uint32_t height)
	{
		glViewport(x,y,width,height);
		glBindTexture(GL_TEXTURE_2D, 0);//unbind texture
	}
	;


}

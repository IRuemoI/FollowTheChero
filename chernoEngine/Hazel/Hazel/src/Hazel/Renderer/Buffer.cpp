#include "hzpch.h"

#include "Buffer.h"
#include "Platform/openGl/OpenGlBuffer.h"
namespace Hazel
{



	 VertexBuffer* VertexBuffer::Create(float* vertics, uint32_t size) 
	{
		//which api
		switch (Renderer::s_rendererAPI)
		{
		case RendererAPI::OpenGl:
			return new OpenGlVertexBuffer(vertics,size); //���� public �̳з�ʽ����������ת��������...����Ϊ�������Է��ʵ�������?
		case RendererAPI::None:
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		}
		HZ_CORE_ASSERT(false,"Unkonw RendererAPI ,VertexBuffer::Create filed!")
		return nullptr;
	}
	 IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
	
		switch (Renderer::s_rendererAPI)
		{
		case RendererAPI::OpenGl:
			return new OpenGlIndexBuffer(indices, count);
		case RendererAPI::None:
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		}

		
		HZ_CORE_ASSERT(false,"Unkonw RendererAPI,IndexBuffer::Create filed!")
		return nullptr;

	};



	 BufferLayout::~BufferLayout()
	 {

	 }

}
#include "hzpch.h"
#include "UniformBuffer.h"
#include "Platform/openGl/OpenGlUniformBuffer.h"
#include "Renderer.h"


namespace Hazel
{


	Hazel::Ref<Hazel::UniformBuffer> UniformBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGl:
			return CreateRef<OpenGlUniformBuffer>(); //���� public �̳з�ʽ����������ת��������...����Ϊ�������Է��ʵ�������?
		case RendererAPI::API::None:
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		}
		HZ_CORE_ASSERT(false, "Unkonw RendererAPI ,VertexBuffer::Create filed!")
			return nullptr;
	}

}
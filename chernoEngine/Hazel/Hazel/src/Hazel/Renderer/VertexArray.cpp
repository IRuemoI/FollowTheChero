#include "hzpch.h"
#include "VertexArray.h"
#include "Platform/openGl/OpenGlVertexArray.h"
#include "Renderer.h"

namespace Hazel
{
	Ref<VertexArray> VertexArray::Create()
	{


		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGl:
			return std::make_shared<OpenGlVertexArray>(); //���� public �̳з�ʽ����������ת��������...����Ϊ�������Է��ʵ�������?
		case RendererAPI::API::None:
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		}
		HZ_CORE_ASSERT(false, "Unkonw RendererAPI ,VertexBuffer::Create filed!")
			return nullptr;

	}

}

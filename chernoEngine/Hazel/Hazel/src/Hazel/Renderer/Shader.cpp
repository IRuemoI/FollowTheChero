#include "hzpch.h"
#include "Shader.h"


#include "Renderer.h"

#include "Platform/openGl/OpenGlShader.h"

namespace Hazel
{

	Shader* Shader::Create(const std::string& filepath)
	{
		//which api
		switch (Renderer::s_rendererAPI)
		{
		case RendererAPI::OpenGl:
			return new OpenGlShader(filepath); //���� public �̳з�ʽ����������ת��������...����Ϊ�������Է��ʵ�������?
		case RendererAPI::None:
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		}
		HZ_CORE_ASSERT(false, "Unkonw RendererAPI ,Shader::Create filed!")
			return nullptr;

	}


}
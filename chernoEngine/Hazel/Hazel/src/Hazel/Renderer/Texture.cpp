#include "hzpch.h"
#include "Texture.h"

#include "Platform/openGl/OpenGlTexture.h"
#include "Renderer.h"

namespace Hazel
{

	Ref<Texture2D> Texture2D::Create(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
			{//make_shared ����ù��캯��,������Ϊ�������,��Ҫ���ܹ�ʵ����,������ʹ�ó�����    ->�������texture��ʾ�и���ë��ϵ������!
			case RendererAPI::API::OpenGl: return std::make_shared<OpenGlTexture>(filePath); //���� public �̳з�ʽ����������ת��������...����Ϊ�������Է��ʵ�������?
			case RendererAPI::API::None: HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			}
			HZ_CORE_ASSERT(false, "Unkonw RendererAPI,Texture::Create filed!")
				return nullptr;

	}

	

}

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
			case RendererAPI::API::OpenGl: return CreateRef<OpenGlTexture2D>(filePath); //���� public �̳з�ʽ����������ת��������...����Ϊ�������Է��ʵ�������?
			case RendererAPI::API::None: HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			}
			HZ_CORE_ASSERT(false, "Unkonw RendererAPI,Texture::Create filed!")
				return nullptr;

	}

	

	Hazel::Ref<Hazel::Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{//make_shared ����ù��캯��,������Ϊ�������,��Ҫ���ܹ�ʵ����,������ʹ�ó�����    ->�������texture��ʾ�и���ë��ϵ������!
		case RendererAPI::API::OpenGl: return CreateRef<OpenGlTexture2D>(width,height); //���� public �̳з�ʽ����������ת��������...����Ϊ�������Է��ʵ�������?
		case RendererAPI::API::None: HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		}
		HZ_CORE_ASSERT(false, "Unkonw RendererAPI,Texture::Create filed!")
			return nullptr;
	}

}

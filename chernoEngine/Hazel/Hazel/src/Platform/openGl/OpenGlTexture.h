#pragma once
#include "Hazel/Renderer/Texture.h"
#include <glad/glad.h>

namespace Hazel
{

	class OpenGlTexture2D :public Texture2D
	{
	public:
		virtual void Bind(uint32_t slot = 0) const override;
		inline virtual uint32_t GetWidth() const override { return m_width; };
		inline virtual uint32_t GetHeight() const override { return m_heigth; };

		virtual void SetData(void* data, uint32_t size) override;

		virtual bool operator==(const Texture& other)const override { return m_rendererID == ((OpenGlTexture2D&)other).m_rendererID; };
		//��(class)˽�г�Ա���Ա����Ա��������,�����ֳ�Ա���ĸ�ʵ��(instance)�

		virtual inline uint32_t GetRendererID()const override{ return m_rendererID; };


		OpenGlTexture2D(const std::string& path) ;
		OpenGlTexture2D(uint32_t width,uint32_t height) ;
		virtual ~OpenGlTexture2D() ;

	private:
		std::string m_filePath;
		uint32_t m_rendererID;
		int m_width;
		int m_heigth;
		int m_BPP;

		GLenum m_internalFormat, m_dataFormat;


		
	};
}


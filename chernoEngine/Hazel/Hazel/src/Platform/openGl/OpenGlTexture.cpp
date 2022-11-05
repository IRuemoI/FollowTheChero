#include "hzpch.h"
#include "OpenGlTexture.h"

#include <stb_image.h>
namespace Hazel
{

	void OpenGlTexture2D::Bind(uint32_t slot) const
	{
		HZ_PROFILE_FUNCTION();
		//glBindTextureUnit or glBindTexture ,the first will check the texture is a black block
		GLCall( glBindTextureUnit(slot, m_rendererID));//target : ��� ,����һ��Ӧ��һ���۰󶨶������(��������)?


	}




	void OpenGlTexture2D::SetData(void* data, uint32_t size)
	{
		HZ_PROFILE_FUNCTION();
		uint32_t bpp = m_internalFormat == GL_RGBA8 ? 4 : 3;

		//size������ѡ����Ⱦ��ͼ�񲿷�buffer��С....һ�㶼��ȫ��ʾ�˲����õ���
		HZ_CORE_ASSERT(size == m_width * m_heigth * bpp,"SetData error: texture didn't set entire texture");

		glTextureSubImage2D(m_rendererID, 0, 0, 0, m_width, m_heigth, m_dataFormat, GL_UNSIGNED_BYTE, data);

	}

	OpenGlTexture2D::OpenGlTexture2D(const std::string& path)
		: m_filePath(path)
	{
		HZ_PROFILE_FUNCTION();

		stbi_set_flip_vertically_on_load(1);//��ֱ��ת����,Ϊ�����������ش����½ǿ�ʼ������glҪ��
		stbi_uc* image=nullptr;
		{
			HZ_PROFILE_SCOPE("OpenGlTexture::OpenGlTexture(stbi_load image)");

			//ȡ������������ʽ
			 //the final Position: channel= 0 means don't change the oranginal image channel ,
			image = stbi_load(path.c_str(), &m_width, &m_heigth, &m_BPP, 0);//δ�����ǻᵼ�� width,height,bpp��
		}
		HZ_CORE_ASSERT(image, "Texture load error:Faild to load image!");


// 		//����õ�tex2D�����Լ������������͸�gl,�Կ�������Щ��Ϣ�����ռ� 
// 		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_width, m_heigth, 0, GL_RGB, GL_UNSIGNED_BYTE, image));//Parameteri:���� WRAP_T:��ֱ����,CLAMP:Ƕ��
 		GLCall( glCreateTextures(GL_TEXTURE_2D,1, &m_rendererID));

		GLenum internalformat = 0,dataformat =0;
		if (m_BPP ==4) 
		{
			internalformat = GL_RGBA8;
			dataformat= GL_RGBA;
		}
		else if (m_BPP==3)
		{
			internalformat = GL_RGB8;
			dataformat = GL_RGB;

			
		}

		m_dataFormat = dataformat;
		m_internalFormat = internalformat;

		HZ_CORE_ASSERT(internalformat & dataformat,"Load Texture error: not Sported image type");

	
		GLCall(glTextureStorage2D(m_rendererID, 1, internalformat, m_width, m_heigth)); // levels:texture����㼶��(mipmap����,����2D�������Ϊ1) internalformat ͼ�� �洢��ʽ //��APIָ������洢��ʽ
//glTextureParameteri or glTexParameteri , it use id but not enum and don't need bind to set texture
		glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//Parameteri:���� MIN_FILTER:��С������ GL_Linear:����
		glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//Parameteri:���� MAG_FILTER:�Ŵ������ GL_Linear:����
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));//Parameteri:���� WRAP_S:ˮƽ����,CLAMP:Ƕ��
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));//Parameteri:���� WRAP_T:��ֱ����,CLAMP:Ƕ��

		//glTextureSubImage2D or glTexImage2D
		GLCall(glTextureSubImage2D(m_rendererID, 0, 0, 0, m_width, m_heigth,dataformat, GL_UNSIGNED_BYTE, image));
		//submit �ύ����,level:0(ԭʼͼ��,��ʹ�ý�������mipmap)
		//xoffset pixel position value on x label move (+) xoffset
		// similar to xoffset
 
	
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width
		//, m_heigth
		//, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer);
		//����õ�tex2D�����Լ������������͸�gl,�Կ�������Щ��Ϣ�����ռ� 
		//���:0,
		//�ڲ���ʽ(gl_��ȡ����ķ�ʽ):GL_RGBA8(8bit/ͨ��) ,
		//��,
		//��,
		//�߿����ؿ��,
		//��ʽ(�������ݵ�ʵ�ʸ�ʽ),
		//ͨ�����ݵ�����:8bit/ͨ��->unsigned char :gl�Լ����Ը������ϲ�������ռ�
		//�������ݵ�ָ��(data�ᱻcopy���Կ�) ������ʱ�ǿ�


		stbi_image_free(image);


	}

	OpenGlTexture2D::OpenGlTexture2D(uint32_t width, uint32_t height)
		:m_width(width),m_heigth(height),m_BPP(4),m_filePath("")
	{
		HZ_PROFILE_FUNCTION();

		GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID));

		m_internalFormat = GL_RGBA8;
		m_dataFormat = GL_RGBA;
		GLCall(glTextureStorage2D(m_rendererID, 1, m_internalFormat, m_width, m_heigth)); // levels:texture����㼶��(mipmap����,����2D�������Ϊ1) internalformat ͼ�� �洢��ʽ //��APIָ������洢��ʽ
		glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//Parameteri:���� MIN_FILTER:��С������ GL_Linear:����
		glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//Parameteri:���� MAG_FILTER:�Ŵ������ GL_Linear:����
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));//Parameteri:���� WRAP_S:ˮƽ����,CLAMP:Ƕ��
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));//Parameteri:���� WRAP_T:��ֱ����,CLAMP:Ƕ��


	}

	OpenGlTexture2D::~OpenGlTexture2D()
	{
		HZ_PROFILE_FUNCTION();
		glDeleteTextures(1,&m_rendererID);
	}

}
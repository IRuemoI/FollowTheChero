#include "hzpch.h"
#include "OpenGlTexture.h"

#include <glad/glad.h>
#include <stb_image.h>
namespace Hazel
{

	void OpenGlTexture::Bind(uint32_t slot) const
	{
		//glBindTextureUnit or glBindTexture ,the first will check the texture is a black block
		GLCall( glBindTextureUnit(slot, m_rendererID));//target : ��� ,����һ��Ӧ��һ���۰󶨶������(��������)?


	}




	OpenGlTexture::OpenGlTexture(const std::string& path)
		: m_filePath(path)
	{
		stbi_set_flip_vertically_on_load(1);//��ֱ��ת����,Ϊ�����������ش����½ǿ�ʼ������glҪ��
		//ȡ������������ʽ
		stbi_uc* image = stbi_load(path.c_str(), &m_width, &m_heigth, &m_BPP, 0);//the final Position: channel= 0 means don't change the oranginal image channel ,
		HZ_CORE_ASSERT(image, "Texture load error:Faild to load image!");


// 		GLCall(glGenTextures(1, &m_rendererID));
// 		GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));//ָ���洢�������ù��� ���������н�������
// 		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));//Parameteri:���� MIN_FILTER:��С������ GL_Linear:����
// 		//����2d����Ĳ���:��С��ʽ(������)Ϊ ����
// 		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));//Parameteri:���� MAG_FILTER:�Ŵ������ GL_Linear:����
// 		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));//Parameteri:���� WRAP_S:ˮƽ����,CLAMP:Ƕ��
// 		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));//Parameteri:���� WRAP_T:��ֱ����,CLAMP:Ƕ��
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

		HZ_CORE_ASSERT(internalformat & dataformat,"Load Texture error: not Sported image type");

	
		GLCall(glTextureStorage2D(m_rendererID, 1, internalformat, m_width, m_heigth)); // levels:texture����㼶��(mipmap����,����2D�������Ϊ1) internalformat ͼ�� �洢��ʽ //��APIָ������洢��ʽ
//glTextureParameteri or glTexParameteri , it use id but not enum and don't need bind to set texture
		glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//Parameteri:���� MIN_FILTER:��С������ GL_Linear:����
		glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//Parameteri:���� MAG_FILTER:�Ŵ������ GL_Linear:����
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

	OpenGlTexture::~OpenGlTexture()
	{
		glDeleteTextures(1,&m_rendererID);
	}

}
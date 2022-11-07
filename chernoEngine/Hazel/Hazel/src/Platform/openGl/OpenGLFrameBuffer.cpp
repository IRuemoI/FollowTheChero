#include "hzpch.h"
#include "OpenGLFrameBuffer.h"
#include "Glad/glad.h"

namespace Hazel
{

	OpenGlFrameBuffer::OpenGlFrameBuffer(const FrameBufferSpecification& spec)
		:m_specification(spec)
	{
		
		
		//Currently just for debug!
		Invalidate();
	}


	OpenGlFrameBuffer::~OpenGlFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_rendererID);
		glDeleteTextures(1, &m_colorAttachMent);
		glDeleteTextures(1, &m_depthAttachMent);
	}

////////////һ��֧��OpenGL��Ⱦ�Ĵ���(��֡����) ���ܰ������µ���ϣ�
// 
// 			�� ����4����ɫ����
// 
// 			�� һ����Ȼ���
// 
// 			�� һ��ģ�建��
// 
// 			�� һ�����ۻ���
// 
// 			�� һ�����ز�������
//////////////////
	void OpenGlFrameBuffer::Invalidate()
	{

		if (m_rendererID) //��һ�δ���fbʱɾ������fb/��ʾͼ��
		{
			glDeleteFramebuffers(1, &m_rendererID);
			glDeleteTextures(1, &m_colorAttachMent);
			glDeleteTextures(1, &m_depthAttachMent);
		}

		glCreateFramebuffers(1, &m_rendererID);
		glBindFramebuffer(GL_FRAMEBUFFER,m_rendererID);

		glCreateTextures(GL_TEXTURE_2D,1,&m_colorAttachMent);
		glBindTexture(GL_TEXTURE_2D,m_colorAttachMent);//safe!
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_specification.width, m_specification.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorAttachMent,0);
		//������ͼ��֡����...�ṩĳ��buffer��ֵ
		//�����ṩ��ɫ: GL_COLOR_ATTACHMENT0 �ṩ���:GL_DEPTH_ATTACHMENT ��Ϊģ��(�ɰ�):GL_STENCIL_ATTACHMENT��(����λֻ������..? ͬʱ��Ϊ�����ģ�� GL_DEPTH_STENCIL_ATTACHMENT
		

		glCreateTextures(GL_TEXTURE_2D, 1, &m_depthAttachMent);
		glBindTexture(GL_TEXTURE_2D, m_depthAttachMent);//safe!
		//glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_specification.width, m_specification.height);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_specification.width, m_specification.height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);//GL_DEPTH24_STENCIL8 ���ģ���ʽ:�ں���Ⱥ�������������������Ȼ�������ͬʱ����ģ�建������
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthAttachMent,0);

		HZ_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER)== GL_FRAMEBUFFER_COMPLETE,"OpenGL Error:FrameBuffer Invalidate failed!"); //���frameBuffer�Ƿ��������


		glBindBuffer(GL_FRAMEBUFFER, 0);//safe!..����ȷ���Ƿ�ʹ�����֡����

	}

	void OpenGlFrameBuffer::Bind() const
	{	
		glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);
		glViewport(0, 0, m_specification.width, m_specification.height); //�����ӿ�
	}

	void OpenGlFrameBuffer::UnBind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0	);

	}

	void OpenGlFrameBuffer::ReSize(uint32_t width, uint32_t height)
	{
		m_specification.width = width;
		m_specification.height = height;
		Invalidate();
	}

}

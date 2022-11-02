#include "hzpch.h"
#include "OpenGlBuffer.h"

#include "glad/glad.h"

namespace Hazel
{


	/////////////////////////////////////////////
	//////////Vertex buffer /////////////////////
	/////////////////////////////////////////////




	OpenGlVertexBuffer::OpenGlVertexBuffer(float* vertices, uint32_t size) 
	{
		HZ_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_rendererID); //�����Gen,Create����������������ʼ��buffer,����Ϊ��ǰ�buffer,��...������
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);//����buffer����
	}


	OpenGlVertexBuffer::OpenGlVertexBuffer(uint32_t size)
	{
		HZ_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_rendererID); //�����Gen,Create����������������ʼ��buffer,����Ϊ��ǰ�buffer,��...������
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);//����buffer����...,nullptr...��ʱ�ǿյ�, Dynamic ����Ϊ֮��ᶯ̬�޸����buffer
	}

	OpenGlVertexBuffer::~OpenGlVertexBuffer()
	{

		glDeleteBuffers(1, &m_rendererID);

	}

	void OpenGlVertexBuffer::Bind() const
	{
		HZ_PROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER,m_rendererID);
	}

	void OpenGlVertexBuffer::UnBind() const
	{
		HZ_PROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER,	0);
	} 



	void OpenGlVertexBuffer::SetData(const void* data, uint32_t size) 
	{

		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	};


	/////////////////////////////////////////////
	///////////index buffer /////////////////////
	/////////////////////////////////////////////


	OpenGlIndexBuffer::OpenGlIndexBuffer(uint32_t* indies, uint32_t count)
		:m_count(count)
	{
		HZ_PROFILE_FUNCTION();
		glCreateBuffers(1, &m_rendererID); //�����Gen,Create����������������ʼ��buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(uint32_t), indies, GL_STATIC_DRAW);//����buffer����

	}

	OpenGlIndexBuffer::~OpenGlIndexBuffer()
	{
		HZ_PROFILE_FUNCTION();
		glDeleteBuffers(1,&m_rendererID);
	
	}

	void OpenGlIndexBuffer::Bind() const
	{
		HZ_PROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
	}

	void OpenGlIndexBuffer::UnBind() const
	{
		HZ_PROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	

}
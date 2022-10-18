#include "IndexBuffer.h"
#include "renderer.h"

//�ǵ�,�к����ļ�û�б���������Ŀ��,���ᱻ����,Ҫ�ֶ����
IndexBuffer::IndexBuffer(const unsigned int* Data, unsigned int count)
	:m_count(count)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));
	GLCall(glGenBuffers(1, &m_rendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));//��(ѡ��)������(֮��ʹ�����������) , (�û�������ʹ�÷�ʽ(���) , bufferID)
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), Data, GL_STATIC_DRAW));
		
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1,&m_rendererID));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
}

void IndexBuffer::Unbind() const
{

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0));
}

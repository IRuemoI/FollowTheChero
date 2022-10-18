#include "VertexBuffer.h"


#include "renderer.h"
VertexBuffer::VertexBuffer(const void* Data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_rendererID));//����1�� ������ , bufferID�����Ļ�����ID(opengl�Ĵ������������һ���޷�������ID)
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));//��(ѡ��)������(֮��ʹ�����������) , (�û�������ʹ�÷�ʽ , bufferID)
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, Data, GL_STATIC_DRAW));
	//ʵ����Ⱦ��,���㲻ֻλ����һ������,������Ҫָ��һ�����������������,��Щ����,����һ�������������s
	//gl��Ҫ���Ǹ��������㻺�����Ĳ���,���������ڴ��ﲻ����һ�Ѹ�����
	//�Լ����������,��������,����,uv�ȵ�	
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_rendererID));

}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

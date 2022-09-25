#include "VertexArray.h"

#include "renderer.h"
#include "BufferLayout.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_rendererID));
	GLCall(glBindVertexArray(m_rendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_rendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& buffer, const BufferLayout& bl)
{
	Bind();
	buffer.Bind();

	const  auto elements = bl.GetElements();
	unsigned int offset = 0;
	for(unsigned int i =0; i<elements.size();i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.ifNormalized,bl.GetStride(), (const void*) offset));
		//ʵ�����������˵�ǰ�󶨵Ķ��㻺����,��ʵ���ϴ�����/��ֵ��һ����������
		//(ָ���������(�ڶ��������)������ , ->��Ӧ��shader�е� layout
		//�������õ����(����)����(ֻ��1,2,3,4��ѡ),
		//�������������
		//�Ƿ��һ��(bool),
		//ÿ������֮����ֽ�ƫ����(�����С), //ʵ�������� ����,������� ��������
		//������ʼλ�������Ե��ֽ�ƫ����(��һ��ָ��0.0,�����ֱ��(const void*) num(0����))(ƫ���������ú�,�ø�) )		
		offset += element.count * LayoutElement::GetSizeofType(element.type);
	}
	
}

void VertexArray::Bind()const
{
	GLCall(glBindVertexArray(m_rendererID));
}

void VertexArray::Unbind()const
{
	GLCall(glBindVertexArray(0));
}

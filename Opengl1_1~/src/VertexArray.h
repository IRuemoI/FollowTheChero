#pragma once

#include "VertexBuffer.h"
class BufferLayout;
//����va��renderer����,��bufferlayout.h������renderer,����ѭ�������˵��´���,
//Ϊ�˹������bufferlayout.hʹ��������

class VertexArray
{
private: 
	unsigned int m_rendererID;

public:
	VertexArray();
	~VertexArray();
	void AddBuffer(const VertexBuffer& buffer,const BufferLayout& bl);
	void Bind()const;

	void Unbind() const;
};


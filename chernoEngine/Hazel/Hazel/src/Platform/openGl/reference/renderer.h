#pragma once

#include<GLFW\glfw3.h>
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"






class renderer//����д�ɾ�̬��,����chernoΪ�˶��߳�д�ɿ�ʵ����
{
public:
	void Drawer(const VertexArray& va,const IndexBuffer& ib,const Shader& shader)const;
	void clear() const;
};


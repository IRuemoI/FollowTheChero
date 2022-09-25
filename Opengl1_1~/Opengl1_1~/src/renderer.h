#pragma once

#include<GL\glew.h>
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

#define LOG(x) std::cout<<x<<std::endl

//use MSVC lib for ����debugger

#define ASSERT(x) if(!(x)) __debugbreak()
#define GLCall(x) GlClearError();x;ASSERT(GlLogCall(#x,__FILE__,__LINE__)); //#x ,��x��Ϊ�ַ���,�����������б�����֧�ֵ�
//������,����
//�������Ӵ��� , �Ҳ���/�޷������ⲿ����ʱ ���������ú��������ĸ���������ӵ���Ŀ����
//opengl ��ʵ�����Կ��������ṩ ,glfwֻ���ṩ��opengl�Ĺ淶(����,��������,������ʵ�ֵ�),������ʵ����Ҫ�����Կ����� , windowsʹ�õ�ԭ��ͼ����Ⱦ�� direct3d 
//������һЩ�����(�����)����������ʹ��opengl(���µĸ��๦��): GLEW opengl������չ����(ʹ��ǰ��Ҫ��ʼ��glewInit())

//�ִ���opengl�Ƚ����ײ� , Ϊ��ʹ���� �������� GLEW

void GlClearError();

bool GlLogCall(const char* function, const char* file, int line);


class renderer//����д�ɾ�̬��,����chernoΪ�˶��߳�д�ɿ�ʵ����
{
public:
	void Drawer(const VertexArray& va,const IndexBuffer& ib,const Shader& shader)const;
	void clear() const;
};


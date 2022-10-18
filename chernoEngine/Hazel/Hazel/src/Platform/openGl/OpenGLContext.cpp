#include "hzpch.h"
#include "OpenGLContext.h"
#include "hazel/core.h"
#include <glad/glad.h> //glad �Ѿ�֧��opengl ,���õ�glfw�е�opengl(gl��ѡ)�������ͻ (c û�� pragma once??)
#include <GLFW/glfw3.h>	//glad��glfw����gl��׼,����ͨ��(������չ..),gladʵ����֧�ֵ���4.6(�ִ��߰汾��)��gl


namespace Hazel
{




	OpenGlContext::OpenGlContext(GLFWwindow* windowHandle)
		:m_windowHandle(windowHandle)
	{
		HZ_CORE_ASSERT(m_windowHandle,"wimdowHandle is null")
	}

	OpenGlContext::~OpenGlContext()
	{

	}

	void OpenGlContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle); //����init��Ҫ GLFWwindow* ���� 
		int stauts = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); //��ʼ�� Glad ʹ�� glfw�����
		HZ_CORE_ASSERT(stauts, "Failed to initialize Glad!");// false ��������
	
		HZ_CORE_INFO("OpenGl Info: ");//���opengl����ʹ�õ���Ⱦ�豸���ṩ��,��ȾӲ��
		HZ_CORE_INFO("Vendor: {0} ", glGetString(GL_VENDOR));
		HZ_CORE_INFO("Renderer: {0} ", glGetString(GL_RENDERER));
		HZ_CORE_INFO("Version: {0} ", glGetString(GL_VERSION));
	}

	void OpenGlContext::SwapBuffers()
	{
// 		glBegin(GL_TRIANGLES);
// 		glEnd(); //���� cherno ���Ե��� gl.h���һЩ�ɵ�ֱ����Ⱦ�ĺ�������ʧ����


		glfwSwapBuffers(m_windowHandle);

	}

}
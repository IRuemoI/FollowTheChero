
#include "hzpch.h" //����Ԥ����ͷ,��Ŀ���ú�ÿ��cpp��Ҫ�õ�,�G
#include <GLFW/glfw3.h>
#include "Hazel/Core/Application.h"
#include "Platform/Windows/WindowsInput.h"

namespace Hazel
{

	Input* Input::s_Instance = new WindowsInput();



	bool WindowsInput::IsKeyPressedImple(int keycode) //ֻ��������дʵ�ֲ���дoverride��,
	{//��Ҫ��ȡwindow��m_window��ѯ��
		//���Ҫ���õĻ���Ҫ�̳�const
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		
		auto state  = glfwGetKey(window, keycode); //keycode>38
		//glfw������״̬

		return state == GLFW_PRESS || state == GLFW_REPEAT;
		
	
	}

	bool WindowsInput::IsMouseButtonPressedImple(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;

	}

	std::pair<float, float> WindowsInput::GetMousePosImple()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;

		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos,(float)ypos };
	}

	float WindowsInput::GetMouseXImple()
	{
		auto[xpos, ypos] = GetMousePosImple();
		return xpos;

	}

	float WindowsInput::GetMouseYImple()
	{
		
		auto[xpos, ypos] = GetMousePosImple();
		return ypos;

	}

}

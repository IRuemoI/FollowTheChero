
#include "hzpch.h" //����Ԥ����ͷ,��Ŀ���ú�ÿ��cpp��Ҫ�õ�,�G
#include <GLFW/glfw3.h>

#include "Hazel/Core/Application.h"
#include "Hazel/Core/Input.h"

namespace Hazel
{




	bool Input::IsKeyPressed(int keycode) //ֻ��������дʵ�ֲ���дoverride��,
	{//��Ҫ��ȡwindow��m_window��ѯ��
		//���Ҫ���õĻ���Ҫ�̳�const
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		
		auto state  = glfwGetKey(window, keycode); //keycode>38
		//glfw������״̬

		return state == GLFW_PRESS || state == GLFW_REPEAT;
		
	
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;

	}

	std::pair<float, float> Input::GetMousePos()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;

		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos,(float)ypos };
	}

	float Input::GetMouseX()
	{
		auto[xpos, ypos] = GetMousePos();
		return xpos;

	}

	float Input::GetMouseY()
	{
		
		auto[xpos, ypos] = GetMousePos();
		return ypos;

	}

}

#include "Application.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Log.h"

namespace Hazel 
{

	Application::Application()
	{

	}

	Application::~Application()
	{

	}
	void Application::Run()
	{


		WindowsResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryInput))
		{
		HZ_INFO(e); //spdlog��Ҫ���� fmt/ostr.h �������Զ�������(�޸��ַ����������<<)

		}
		if (e.IsInCategory(EventCategoryApplication))
		{
		HZ_INFO(e); //spdlog��Ҫ���� fmt/ostr.h �������Զ�������(�޸��ַ����������<<)

		}
		 //�ȿ����ٳ�������....QAQ
	}
}
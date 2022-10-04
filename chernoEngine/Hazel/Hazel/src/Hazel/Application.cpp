#include "hzpch.h"

#include "Application.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Log.h"

#include "GLFW/glfw3.h"
 
namespace Hazel 
{

#define BIND_EVENT_FN(x)  std::bind(&Application::x,this,std::placeholders::_1)
	Application::Application()
	{
		
		m_window = std::unique_ptr<Window>(Window::Create());//���������windowswindowcppʵ�ֵ�
		//make_unique<>() ��������˵����һ��ʮ�����õĶ���,<_tp> ������ unique_ptr��

		m_window->SetEventCallback(std::bind(&Application::OnEvent,this,std::placeholders::_1));

	}
	

	void Application::OnEvent(Event&e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.DisPatch<WindowsCloseEvent>(BIND_EVENT_FN(OnWindowClose));//bind : the first parameter is waitting
			//dispatcher, if you see WindowCloseEvent ,then use this callfuction with your event e

		HZ_CORE_TRACE("{0}",e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			// vector �ṹӦ���� begin�� 1 2 3 4 5 end��
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;

		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverLayer(Layer* layer)
	{
		m_LayerStack.PushOverLayer(layer);
	}

	Application::~Application()
	{

	}
	void Application::Run()
	{


// 		WindowsResizeEvent e(1280, 720);
// 
// 		if (e.IsInCategory(EventCategoryInput))
// 		{
// 		HZ_INFO(e); //spdlog��Ҫ���� fmt/ostr.h �������Զ�������(�޸��ַ����������<<)
// 
// 		}
// 		if (e.IsInCategory(EventCategoryApplication))
// 		{
// 		HZ_INFO(e); //spdlog��Ҫ���� fmt/ostr.h �������Զ�������(�޸��ַ����������<<)
// 
// 		}
		 //�ȿ����ٳ�������....QAQ

		while (m_running)
		{
			m_window->onUpdate();
			glClearColor(0.01f, 0.2f, 0.7f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

		};
	}

	bool Application::OnWindowClose(WindowsCloseEvent& e)
	{
		m_running = false;
		return true;
	}
}
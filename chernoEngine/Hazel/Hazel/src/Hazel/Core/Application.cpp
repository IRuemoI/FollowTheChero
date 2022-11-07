#include "hzpch.h"

#include "Application.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Core/Log.h"

//���ú��,glfw�Ѿ�������gl��,��Ҫglad����glͷ��Ϊ�亯���ṩʵ��

#include "Hazel/Core/Input.h"
#include "Hazel/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace Hazel 
{

#define BIND_EVENT_FN(x)  std::bind(&Application::x,this,std::placeholders::_1) //��Ҫ��Ϊ����lambdaһ���и�����Ĳ�����λ




	Application* Application::s_instance = nullptr; //application ��Ϊ����ģʽ

	Application::Application(const std::string& windowName )
	{
		HZ_PROFILE_FUNCTION();

		HZ_CORE_ASSERT(!(s_instance) ,"Application has been exists") // ������ , ��֮ͣ��

		s_instance = this;
		
		m_window = std::unique_ptr<Window>(Window::Create(windowName));//���������windowswindowcppʵ�ֵ�... windowName�Զ��������windowprops��
		//make_unique<>() ��������˵����һ��ʮ�����õĶ���(�ƺ��Զ����ù��캯��??),<_tp> ������ unique_ptr��
		m_ImGuiLayer = new ImGuiLayer; //����ѡ��ԭʼָ��,����uniqueptr���±�ɾ��

		m_window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		Renderer::Init(); //��ʼ�� Renderer�ĸ�������

		PushOverLayer(m_ImGuiLayer);

		
		//�μ� gl�Ǹ�״̬��!!!!!!!!!,˳����Ҫ


	}
	

	void Application::OnEvent(Event&e)
	{
		HZ_PROFILE_FUNCTION();


		EventDispatcher dispatcher(e);
		dispatcher.DisPatch<WindowsCloseEvent>(BIND_EVENT_FN(OnWindowClose));//bind : the first parameter is waitting
		dispatcher.DisPatch<WindowsResizeEvent>(BIND_EVENT_FN(OnWindowResize));//bind : the first parameter is waitting
			//dispatcher, if you see WindowCloseEvent ,then use this callfuction with your event e

		//HZ_CORE_TRACE("{0}",e);

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
		HZ_PROFILE_FUNCTION();


		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLayer(Layer* layer)
	{
		HZ_PROFILE_FUNCTION();


		m_LayerStack.PushOverLayer(layer);
		layer->OnAttach();
	}

	void Application::Close()
	{
		m_running = false;
	}

	Application::~Application()
	{

	}
	void Application::Run()
	{
		//�����һ֡

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


		HZ_PROFILE_FUNCTION();
		while (m_running)
		{	
			HZ_PROFILE_SCOPE("RunLoop");
			float time = (float) glfwGetTime(); //glfw ���
			Timestep  timestep =  time -m_LastFrameTime;
			m_LastFrameTime = time;
			
			if (!m_minimized)
			{

				{
					HZ_PROFILE_SCOPE("layerstack_layers Onupdate");

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(timestep);
					//����������ֵ� ��Ⱦ�߳� ��ִ��
				}
				//imgui layer ��viewport�ǲ�ֿ��� , ��������С����Ӱ��ImGui
				
					m_ImGuiLayer->Begin(); //����ImGuiLayer������  �μ�,unique_ptr��ָ��!���� ->
				{

					HZ_PROFILE_SCOPE("laystack_ImGuilayers OnImGuiRender");

					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender();
				}
					m_ImGuiLayer->End();	 

			}
								   
			//��ѯ����
			/*auto [x, y] = Input::GetMousePos(); */
			//�����ѯ����,���ǲ�Ӧ������glfw�ĺ�������keycode,��ᵼ�¼���������	 
			/*HZ_CORE_TRACE("{0},{1}", x, y);*/

			m_window->onUpdate();


		};
	}

	bool Application::OnWindowClose(WindowsCloseEvent& e)
	{
		HZ_PROFILE_FUNCTION();
		m_running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowsResizeEvent& e)
	{
		HZ_PROFILE_FUNCTION();


		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_minimized = true;
		}
		else
		{
			m_minimized = false;
		}

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}
		
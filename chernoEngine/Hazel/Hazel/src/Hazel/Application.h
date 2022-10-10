#pragma once

#include "core.h"

#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"


namespace Hazel {


	class HAZEL_API Application
	{

	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event&); //as the callback func :how we deal with the event?


		void PushLayer(Layer* layer);
		void PushOverLayer(Layer* layer);

		inline Window& GetWindow() { return *m_window; } //unique_ptr ���Ǹ㲻����t _ t
		inline static Application& Get() { return *m_instance; } 

		
	private:
		
		bool OnWindowClose(WindowsCloseEvent& e);
		std::unique_ptr<Window> m_window;
		bool m_running = true;
		LayerStack m_LayerStack;

		static Application* m_instance; //����ǵ�����

	};
	//To be definde in CLIENT һ���ӿ�,�ڿͻ���ʵ��
	Hazel::Application* CreateApplication();
}

#pragma once

#include "core.h"

#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"

#include "Hazel/ImGui/ImGuiLayer.h"

#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

	

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

		//�����ڿͻ��˱�¶ImGui,��Hazel����ImGuiLayer
		 

		bool OnWindowClose(WindowsCloseEvent& e);
		bool m_running = true;


		std::unique_ptr<Window> m_window;
		ImGuiLayer* m_ImGuiLayer;
		
		LayerStack m_LayerStack;

		static Application* m_instance; //����ǵ�����

		std::shared_ptr<VertexArray> m_VertexArray;  // VB,IB������ VA����
		std::shared_ptr<Shader> m_shader; //��shared_ptr��...����ɱģʽ...// shader...,����application��,����Ψһ�� --�ж���
		std::shared_ptr<VertexArray> m_SquraVA; //for test

	};
	//To be definde in CLIENT һ���ӿ�,�ڿͻ���ʵ��
	Hazel::Application* CreateApplication();
}

#include "Hazel.h"
//app ����������ϸ�ڲ�����Ȥ, �������(main)Ӧ�������涨��, appֻ��Ҫͨ��ʵ��������
//û����ȷ�ĳ�����ڵ� �� dllû�и���,lib�ṩ�ĺ���������dll����Ӧ�����
#include "imGui/imgui.h"
// #include "imGui/backends/imgui_impl_opengl3.h"
// #include "imGui/backends/imgui_impl_glfw.h"

class ExampleLayer :public Hazel::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{




	}
	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnUpdate() override
	{
		//HZ_INFO("ExampleLayer::Updata");
		if (Hazel::Input::IsKeyPressed(HZ_KEY_C)) 
		{
			HZ_TRACE(" c is pressed");
		}
	}

	void OnEvent(Hazel::Event& e) override
	{
	

		if (e.GetEventType() == Hazel::EventType::KeyPressed)
		{
			Hazel::KeyPressedEvent& ep = (Hazel::KeyPressedEvent&) e;
			HZ_TRACE("{0}", (char)ep.GetKeyCode());
		}

	}
};


class SandBox:public Hazel::Application
{
public:
	SandBox()
	{
	//	PushOverLayer(new Hazel::ImGuiLayer()); //�ظ�����ImGUILayer!!!����!!!
		PushOverLayer(new ExampleLayer());// ExampleLayer* -->Layer* 
	
	}
	~SandBox()
	{

	}
};

// a box about how the game work would be send/trans to engine's entry point

Hazel::Application* Hazel::CreateApplication()
{
	return new SandBox;	

}
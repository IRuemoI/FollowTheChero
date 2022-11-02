#pragma once



#include "GLFW/glfw3.h" // glad �Ѿ�ͬ������� ��֪��glfwȥ��gl���� ,����,��Ŀ��Ҳ�Ѿ�Ԥ������gl���,����glfw,������glad

#include "Hazel/Core/Window.h"
#include "hazel/Renderer/GraphicsContext.h"

namespace Hazel
{
	class WindowsWindow:public Window
	{	

	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void onUpdate() override; //application���� ,ÿִ֡�� ,GLFWѯ���¼�
		virtual unsigned int  GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallBackFn& Callbackfn)override { m_Data.EventCallback = Callbackfn; };
		void SetVSync(bool enabled) override;
		virtual void SetViewPort(float width, float height) override ;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const override { return m_Window; } ;
		//virtual Ϊ�˺���!!
		//��...��ʵ ����(��������)�麯�������ĺ����ṹ�ϵ����к��������麯��(ʹ�û���/��̬��ָ��ʱ��̬������).... ��ֻ��������
		
		// window��ʹ��ʵ���� ��̬��application��,����ʵĻ�����ͨ��application��������
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;


		struct WindowData
		{
			std::string title;
			unsigned int Width;
			unsigned int Height;

			bool VSync;

			EventCallBackFn EventCallback;
		};
		WindowData m_Data;
	};

}


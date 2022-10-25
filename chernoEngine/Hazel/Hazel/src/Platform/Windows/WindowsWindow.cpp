#include "hzpch.h"
#include "WindowsWindow.h"
#include "Hazel/Window.h"
#include "Platform/openGl/OpenGLContext.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/KeyEvent.h"




namespace Hazel
{
	static bool s_GLFWInitialized = false;


	static void GLFWErrorCallback(int error_code, const char* description)
	{
		HZ_CORE_ERROR("GLFW Error {0}:{1}", error_code, description);

	}

	Window* Window::Create(const WindowProps& props ) { //attention : Ĭ�ϲ�����������,�ڶ����ﲻҪ��д��,������ض���Ĭ�ϲ���

		return new WindowsWindow(props);//applcation ���л���һ��ָ��������洢��
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);

	}
	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}
	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		m_Data.title = props.Title;


		HZ_CORE_INFO("Create Window {0}({1}, {2})", props.Title, props.Width, props.Height);
		
		if (!s_GLFWInitialized)
		{

			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Could not intialize GLFW!");//ASSERT core.h����Ķ���

			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.title.c_str(),nullptr,nullptr);
		
		m_Context = new OpenGlContext(m_Window);//? m_Context ���ܻ��Ǿ�̬��,��Ϊ������ֻ��һ������ ,OpenGlContext�� GraphicContext()������ʵ����֮һ
		m_Context->Init();
		// ���������´���



		glfwSetWindowUserPointer(m_Window, &m_Data); //ʹm_Window���û�ָ��(void*) ָ�� m_data: m_data������Ҫ�Ǵ��ݻص�����
		SetVSync(true);//yi bu

		//SET GLFW CallBack
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)  //  �ص�������ʽ�ѱ�glfwָ��
			{
				WindowData& data =*(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width; //ά��
				data.Height= height;

				WindowsResizeEvent event(width,height);
				data.EventCallback(event);

			
			}); 
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) //m_Window �ᱻopengl��Ϊlambda�Ĳ����ķ���
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowsCloseEvent event;
				data.EventCallback(event);


			});
		//git clone https://github.com/CompVis/stable-diffusion.git repositories/stable-diffusion

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window,int key,int scancode,int action ,int mods) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				switch (action)
				{
				case GLFW_PRESS:
				{
					
					KeyPressedEvent event(key,0); //0: repeat count
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);

					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key,1); //��ʱ��1
					data.EventCallback(event);
					break;
				}
				default:
					break;
				}

			});
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) //chartyped �� KeyCallback������ ???,����a~z�¼�������,glfw������Ȼ�����ı����봦��,charCallBackû��KeycallBack 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event((int)keycode);
				data.EventCallback(event);


				//event spread: window -> application.onevent(by binding to data) -> layer.onevent in layerstack -> dispatch in layer.onevent

			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				switch (action)
				{
				case GLFW_PRESS:
				{
					
					MouseButtonPressedEvent event(button); //0: repeat count
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);

					break;
				}
				
				default:
					break;
				}

			});
		
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				MouseScorllEvent event((float)xoffset, (float)yoffset); //��ƫ����
				data.EventCallback(event);

			});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				MouseMoveEvent event((float)xpos, (float)ypos);
				data.EventCallback(event);

			});
		

			
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}
	void WindowsWindow::onUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers(); //�� ���ǽ��������(Ϊ�˽����Ķ�ƽ̨,�ȴ�opengl����һ��)

	}


	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);//���������Ϊһ֡ �ȴ�֡������Ͻ�����һ֡,�⽫����֡����Ƶ�ʴ���/С����Ļˢ��Ƶ��(60~70)
		else
			glfwSwapInterval(0);
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync()const
	{
		return m_Data.VSync;
	}


}
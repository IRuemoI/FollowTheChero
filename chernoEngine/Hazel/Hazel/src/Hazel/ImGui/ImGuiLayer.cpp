
#include "hzpch.h"
#include "ImGuiLayer.h"




#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"



#include "Hazel/Core/Application.h"


namespace Hazel
{

	ImGuiLayer::ImGuiLayer()
		:Layer("ImGuiLayer") //��ʼ�� ���ø��๹�� m_time ��ʼ����cherno��ͬ p15	
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{

	}


	void ImGuiLayer::OnAttach() //�ҵ�ջ��׼����Ⱦ��
	{
		HZ_PROFILE_FUNCTION();



		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		
		//���imgui�� io��  ��������
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform/Renderer backends
		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		
		//temporary
		//��������! ����! cherno 
// 		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB; //��λӳ��:��ʱ��¼��ô��ļ�λ
// 		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;	
// 		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
// 		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
// 		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
// 		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
// 		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
// 		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
// 		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
// 		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
// 		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
// 		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
// 		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
// 		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
// 		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
// 		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
// 		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
// 		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
// 		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
// 		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
// 		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;


		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410"); 
	}

	void ImGuiLayer::OnDetach()
	{
		HZ_PROFILE_FUNCTION();

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

	}

// 	void ImGuiLayer::OnUpdate()
// 	{
// 		
// 
// 		ImGuiIO& io = ImGui::GetIO();
// 		
// 		Application& app = Application::Get(); //get singal instance
// 		Window& app_window = app.GetWindow();
// 		io.DisplaySize = ImVec2(app_window.GetWidth(), app_window.GetHeight());
// 
// 		float time = (float)glfwGetTime(); //���ʱ��
// 		io.DeltaTime= m_time > 0.0 ? (time - m_time):(1.0f / 60.0f); //���	֡��ʱ��
// 
// 		ImGui_ImplOpenGL3_NewFrame();
// 		ImGui::NewFrame(); //����ߴ�,��֡??
// 
// 		static bool show =true;
// 		ImGui::ShowDemoWindow(&show);
// 
// 		ImGui::Render();
// 		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());	
// 
// 		//������ imguiLayer��onevent();
// 	}

	void ImGuiLayer::Begin() //OnUpdat() �����Ϊ Begin,ImGuiRender,End	 ����Ⱦ��������ǰ ����Begin() ,��Ⱦ���ݺ� ���� end()
	{
		HZ_PROFILE_FUNCTION();


		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

	}
	void ImGuiLayer::End()
	{
		HZ_PROFILE_FUNCTION();

		ImGuiIO& io = ImGui::GetIO();


		Application& app = Application::Get();
		
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(),(float)app.GetWindow().GetHeight());


		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) //����������ӿ�
		{
			GLFWwindow* backup_current_constext = glfwGetCurrentContext();

			ImGui::UpdatePlatformWindows();

			ImGui::RenderPlatformWindowsDefault();

			glfwMakeContextCurrent(backup_current_constext);
		}
	
	} 

	void ImGuiLayer::OnImGuiRender()
	{
		HZ_PROFILE_FUNCTION();

		static bool show = true;



	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		if (m_blockImGuiEvent)
		{

			ImGuiIO& io = ImGui::GetIO();

			event.Handled |= event.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;//����¼���Mouse �� ImGui��Ҫ�����¼� ��ô������,ֹͣ�¼�����
			event.Handled |= event.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;//����¼��Ǽ������ �� ImGui��Ҫ�������� ....

			//WantCaptureMouse  �� ������ ��������ͣ������ImGuiԪ�صľͻ�Ϊ��(��foucus)/��������ע���ｨ������ô��? ϲϲ

		}

		


	}

// 	void ImGuiLayer::OnEvent(Event& e)
// 	{
// 
// 		EventDispatcher diapatcher(e);
// 		switch (e.GetEventType())
// 		{//û��Ҫswitch �����Ҿ�Ҫ
// 		
// 		case EventType::MouseMoved:
// 			
// 			diapatcher.DisPatch<MouseMoveEvent>(BIND_EVENT_CALLFN(ImGuiLayer::OnMouseMoveEvent));
// 			break;
// 		case EventType::MouseButtonPressed :
// 			 
// 			diapatcher.DisPatch<MouseButtonPressedEvent>(BIND_EVENT_CALLFN(ImGuiLayer::OnMouseButtonPressedEvent));
// 			break;
// 		case EventType::MouseButtonReleased:
// 			 
// 			diapatcher.DisPatch<MouseButtonReleasedEvent>(BIND_EVENT_CALLFN(ImGuiLayer::OnMouseButtonReleasedEvent));
// 			break;
// 		case EventType::MouseScrolled:
// 			 
// 			diapatcher.DisPatch<MouseScorllEvent>(BIND_EVENT_CALLFN(ImGuiLayer::OnMouseScorllEvent));
// 			break;
// 		case EventType::KeyPressed:
// 			 
// 			diapatcher.DisPatch<KeyPressedEvent>(BIND_EVENT_CALLFN(ImGuiLayer::OnKeyPressedEvent));
// 			break;
// 		case EventType::KeyReleased:
// 			 
// 			diapatcher.DisPatch<KeyReleasedEvent>(BIND_EVENT_CALLFN(ImGuiLayer::OnKeyReleasedEvent));
// 			break;
// 		case EventType::WindowResize:
// 			 
// 			diapatcher.DisPatch<WindowsResizeEvent>(BIND_EVENT_CALLFN(ImGuiLayer::OnWindowsResizeEvent));
// 			break;
// 		case EventType::KeyTyped:
// 			diapatcher.DisPatch<KeyTypedEvent>(BIND_EVENT_CALLFN(ImGuiLayer::OnKeyTypedEvent));
// 			break;
// 		default:
// 			break;
// 
// 		}
// 
// 
// 	}
// 
// 
// 	bool ImGuiLayer::OnMouseMoveEvent(MouseMoveEvent& e) //ģ��Imguiԭ�����¼��ص�
// 	{
// 
// 		ImGuiIO& io = ImGui::GetIO();
// 		io.MousePos = ImVec2(e.GetX(), e.GetY());
// 
// 		return false;
// 	}
// 
// 	bool ImGuiLayer::OnMouseScorllEvent(MouseScorllEvent& e)
// 	{
// 		ImGuiIO& io = ImGui::GetIO();
// 		io.MouseWheelH+=  e.GetXOffset();
// 		io.MouseWheel += e.GetYOffset();
// 
// 
// 		return true;
// 	}
// 
// 	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
// 	{
// 		ImGuiIO& io = ImGui::GetIO();
// 		io.MouseDown[e.GetMouseButtonCode()] =true;
// 		return false; //ϣ��������͸
// 	}
// 
// 	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
// 	{
// 		ImGuiIO& io = ImGui::GetIO();
// 		io.MouseDown[e.GetMouseButtonCode()] = false;
// 		return false; //ϣ��������͸
// 	}
// 
// 	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
// 	{
// 		ImGuiIO& io = ImGui::GetIO();
// 
// 		//һЩ�ؼ��������Ᵽ����(��Ҫ������Ϊ����)
// 
// 		io.KeysDown[e.GetKeyCode()] = true;
// 		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
// 		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
// 		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
// 		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER]; // windows �� mac ��
// 		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
// 		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
// 		return true;
// 	}
// 
// 	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
// 	{
// 		ImGuiIO& io = ImGui::GetIO();
// 		io.KeysDown[e.GetKeyCode()] = false;
// 		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
// 		return true;
// 	}
// 
// 	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
// 	{
// 		ImGuiIO& io = ImGui::GetIO();
// 		int keycode = e.GetKeyCode();
// 
// 		if (keycode > 0 && keycode < 0x100000)
// 			io.AddInputCharacter((unsigned int)keycode);//�����ı���Ҫ���,0.0
// 
// 		return false;
// 	}
// 
// 
// 	bool ImGuiLayer::OnWindowsResizeEvent(WindowsResizeEvent& e)
// 	{
// 		ImGuiIO& io = ImGui::GetIO();
// 		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());//��update�ظ���
// 		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f); //layer��Ⱦ��С:մ��displaysize
// 		glViewport(0, 0, e.GetWidth(), e.GetHeight()); //��gl��Ⱦ�ӿ�
// 		return true;
// 	}

}
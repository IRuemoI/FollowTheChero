#include "Hazel.h"


//-------------entry point	-------------
#include "Hazel/Core/EntryPoint.h"
//---------------------------------------

//app ����������ϸ�ڲ�����Ȥ, �������(main)Ӧ�������涨��, appֻ��Ҫͨ��ʵ��������
//û����ȷ�ĳ�����ڵ� �� dllû�и���,lib�ṩ�ĺ���������dll����Ӧ�����

#include "imGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SandBox2D.h"


class ExampleLayer :public Hazel::Layer //layerҲ����Ҫ���� delta,����application����delta?, layerͬʱ����GUi�ĸ��²���..˫�氡..
{
public:
	ExampleLayer()
		:Layer("Example"), m_cameraController(1280.f/720.f,true)
	{
		m_VertexArray = (Hazel::VertexArray::Create());// they are the same type , so just equal!
		m_VertexArray->Bind();

		float vertices[7 * 3] =
		{
			-0.5f,0.5f,0.0f,0.7f,0.8f,0.1f,1.0f, //��Ȼ��ǰд�˶���ɫ���ǲ�Ӱ������ֻ��λ��
			0.5f,0.5f,0.0f, 0.7f,0.3f,0.1f,1.0f,
			0.0f,-0.5f,0.0f,0.7f,0.3f,0.1f,1.0f,
		};

		Hazel::Ref<Hazel::VertexBuffer> TrangleVertexBuffer;
		TrangleVertexBuffer = Hazel::VertexBuffer::Create(vertices, sizeof(vertices));


		Hazel::BufferLayout Layout = //initializer_list ������ Ԫ�ص��ù��캯�����б�,����,����
		{
			{Hazel::ShaderDataType::Float3 ,"a_Position"},//������Ҫͬ��...,����ֻ����ǿ�ɶ�
			{Hazel::ShaderDataType::Float4 ,"a_Color"}
		};

		TrangleVertexBuffer->SetLayout(Layout); //���õ�AddVertexBuffer��	// ע��,�����ҽ��󶨲���ָ��ŵ���SetLayout��,��cherno������
		m_VertexArray->AddVertexBuffer(TrangleVertexBuffer);//����,��AddVB��Ӧ�ò���,��ҪVB���в��ֲ�Ȼ����
		TrangleVertexBuffer->Bind();



		uint32_t indices[3] = { 0,1,2 };

		Hazel::Ref<Hazel::IndexBuffer> TrangleIndexBuffer;
		TrangleIndexBuffer = Hazel::IndexBuffer::Create(indices, 3); //3����ΪCherno��ǿ��֢ T_T
		m_VertexArray->SetIndexBuffer(TrangleIndexBuffer);	//�ܶ�ط�����Bind��....���ܻᾭ���ظ�bind
		TrangleIndexBuffer->Bind();


		m_flatVA =(Hazel::VertexArray::Create());
		float SquraVertics[4 * 5] =
		{
			-0.5f,-0.5f,0.0f,0.0f,0.0f,
			0.5f,-0.5f,0.0f,1.0f,0.0f,
			0.5f,0.5f,0.0f,1.0f,1.0f,
			-0.5f,0.5f,0.0f,0.0f,1.0f

		};
		uint32_t SquareIndics[6] = { 0,1,2,2,3,0 };

		Hazel::Ref<Hazel::VertexBuffer> SquraVB = Hazel::Ref<Hazel::VertexBuffer>(Hazel::VertexBuffer::Create(SquraVertics, sizeof(SquraVertics)));
		Hazel::BufferLayout SquareLayout = //initializer_list ������ Ԫ�ص��ù��캯�����б�,����,����
		{
			{Hazel::ShaderDataType::Float3 ,"a_Position"},
			{Hazel::ShaderDataType::Float2 ,"a_UVCoord"}
		};
		SquraVB->SetLayout(SquareLayout);
		m_flatVA->AddVertexBuffer(SquraVB);
		Hazel::Ref<Hazel::IndexBuffer> SquraIB = Hazel::Ref<Hazel::IndexBuffer>(Hazel::IndexBuffer::Create(SquareIndics, sizeof(SquareIndics) / sizeof(uint32_t)));
		m_flatVA->SetIndexBuffer(SquraIB);


		//the shader which just use filename , their name from filename

		m_shader=m_shaderLib.Load("Assets/shader/base.glsl"); //С���� std::string str = R"(�������⻻��,զд���� )"
		m_flatShader= m_shaderLib.Load("Assets/shader/flat.glsl"); //С���� std::string str = R"(�������⻻��,զд���� )"
		m_textureShader=m_shaderLib.Load("Assets/shader/texture.glsl"); //С���� std::string str = R"(�������⻻��,զд���� )"


		m_squareTexture = Hazel::Texture2D::Create("Assets/Texture/quancifang.png");
		m_chernoLogo = Hazel::Texture2D::Create("Assets/Texture/theChernoLogo.png");

		m_shaderLib.Get("texture")->Bind();
		m_shaderLib.Get("texture")->SetInt("u_Texture", 0);//use 0.num slot

		m_flatShader->Bind();
		m_flatShader->SetFloat3("u_color", m_flatColor);


	}
	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Grid Control");
		ImGui::ColorEdit3("Grid Color", glm::value_ptr(m_flatColor));
		ImGui::End();
	}

	void OnUpdate(Hazel::Timestep deltaime) override
	{


		Hazel::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		Hazel::RenderCommand::Clear(); //��	


		m_cameraController.OnUpdate(deltaime);
		Hazel::Renderer::BeginScene(m_cameraController.GetCamera());//��ʼ����,���ó������� //�ύ��������� ,ע�� ��"�ύ" , vp����������
		//2D type
		
		glm::mat4 scale = glm::scale(glm::mat4(1.0f),glm::vec3(0.1f));

		//Hazel::Materialref* material = new Hazel::Material(Shader);
		//Hazel::MaterialInstanceRef* mi = new Hazel::MaterialInstance(Shader);
		//
		//mi->set("uniform",data);
		//squareMesh->Setmaterial(mi);//�Լ���Ⱦ����������Ⱦ
		//�������ݴ洢��


		for (int j = 0; j < 20; j++)
		{
			for (int i = 0; i < 20; i ++)
			{
				glm::vec3 pos = glm::vec3(i * 0.11f,j*0.11f,0.0f);
				glm::mat4 tra = glm::translate(glm::mat4(1.0f), pos)*scale;
		
				Hazel::Renderer::Submit(m_flatShader, m_flatVA,tra);//�ύshader,material,mesh,��Ϊ��Ⱦ����
			}
		}
		m_chernoLogo->Bind();
		Hazel::Renderer::Submit(m_textureShader, m_flatVA, glm::scale( glm::mat4(1.0f), glm::vec3(1.5f)));//�ύshader,material,mesh,��Ϊ��Ⱦ����

		m_squareTexture->Bind();
		Hazel::Renderer::Submit(m_textureShader, m_flatVA, glm::scale( glm::mat4(1.0f), glm::vec3(1.5f)));//�ύshader,material,mesh,��Ϊ��Ⱦ����

		//Hazel::Renderer::Submit(m_flatShader, m_VertexArray);
	
		Hazel::Renderer::EndScene();//һЩ������


	}

	void OnEvent(Hazel::Event& e) override //���ȵĽ���ж���application ��Onevent ,���ù�
	{

		m_cameraController.OnEvent(e);

		if (e.GetEventType() == Hazel::EventType::WindowResize) //  ��������Ӧ
		{
			auto& wre =  (Hazel::WindowsResizeEvent&)e;

			//float zoom = width / 1280.f;
			//m_cameraController.SetZoomLevel(zoom);

		}
	}

private:

	Hazel::Ref<Hazel::VertexArray> m_VertexArray;  // VB,IB������ VA����
	Hazel::Ref<Hazel::VertexArray> m_flatVA; //for test

	Hazel::Ref<Hazel::Shader> m_shader; //��shared_ptr��...����ɱģʽ...
	Hazel::Ref<Hazel::Shader> m_flatShader,m_textureShader;
	Hazel::ShaderLibrary m_shaderLib; //MOVE : Renderer


	Hazel::Ref<Hazel::Texture2D> m_squareTexture,m_chernoLogo;
	
	
	Hazel::OrthographicCameraController m_cameraController; //cherno��position�������?? 


	glm::vec3 m_flatColor = { 0.2,0.3f,0.8f };

};




class SandBox:public Hazel::Application
{
public:
	SandBox()
	{
	//	PushOverLayer(new Hazel::ImGuiLayer()); //�ظ�����ImGUILayer!!!����!!!
		//PushLayer(new ExampleLayer());// ExampleLayer* -->Layer* 
		PushLayer(new SandBox2D());// ExampleLayer* -->Layer* 
	
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
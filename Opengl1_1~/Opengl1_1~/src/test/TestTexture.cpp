#include "TestTexture.h"
#include "ImGui/imgui.h"



#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Texture.h"
namespace test
{




	TestTexture::TestTexture()
		:m_translationA(200, 200, 0), m_translationB(400, 200, 0),
		m_proj(glm::ortho(0.0f, 960.0f, 0.0f, 640.0f, -1.0f, 1.0f)),
		m_view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))

	{
		float Position[] = //position + uv
		{
		-50.0f,-50.0f,0.0f,0.0f,
		50.0f ,-50.0f,1.0f,0.0f,
		50.0f ,50.0f ,1.0f,1.0f,
		-50.0f,50.0f ,0.0f,1.0f
		};
		//�������ݻ�����,���ǻ���Ҫ����������	
		//ʡ�ظ��ڴ� 0,1,2,2,3,0
		unsigned int indices[] =
		{
			0,1,2,
			2,3,0
		};

		//����opengl�ĺ���  , �����ȥ docs.gl ��վ��ѯ��ϸ��Ϣ	
		m_Vao = std::make_unique<VertexArray>();
		m_IBO = std::make_unique<IndexBuffer>(indices, 6);
		m_shader = std::make_unique<Shader>("res/shaders/basic.shader");
		m_VBO = std::make_unique<VertexBuffer>(Position,4*4*sizeof(float));
		//VertexBuffer vb(Position, 4 * 4 * sizeof(float));
		//�����VertexBuffer ��cpu �� Gpu֮������ ӳ���ϵ. cpu��vb��ɾ, Gpu����Ŀռ�ͬ����ɾ,��ʱvb������������������ɾһ��GPU�Ϸ����vb,�⵼���˱���
		//����������Ҫת����cpu�ϳ���ά��vb

		BufferLayout Layout;
		Layout.Push<float>(2);
		Layout.Push<float>(2);
		m_Vao->AddBuffer(*m_VBO, Layout);




		//mģ�� v��ͼ pͶӰ ����
		//ͶӰ(����/͸��) //ģ��(ģ�ͱ任) //��ͼ(ģ�����,λ���뷽��,��ģ�ͽ�����任)
		 //lrbt nf:Ŀ���/��Ļ��Χ
		//���ص� proj*(l,b,n,1)T = (-1~1, -1~1, -1~1 1)T
		//a view : glm �ľ��������������Ų���
// 		for (int i =0; i <proj.length();i++)
// 		{
// 			std::cout<< proj[i].x<<" "<<proj[i].y << " " << proj[i].z << " " << proj[i].w << std::endl;
// 		}
		//glm::mat4 modle = glm::translate(glm::mat4(1.0f),glm::vec3(300,200,0)); //ƽ��
		
		//glm::mat4 mvp = proj * view * modle;


		
		m_shader->Bind();

		//��Ҫ��ͼƬͨ��vs�Ͻ���!!!!!vs��ƭ�˵�!!!!!
		//���� ��Դ������ ���� ^ . ^
		m_Texture= std::make_unique<Texture>("res/tex/theChernoLogo.png");
		m_Texture->Bind();
		m_shader->SetUniform1i("u_Texture", 0);//ʹ��������0
		m_shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);


		//���
		m_Vao->Unbind();
		m_VBO->Unbind();
		m_IBO->Unbind();
		m_shader->Unbind();
	}

	TestTexture::~TestTexture()
	{	
		
	}

	void TestTexture::onUpdate(float deltaTime)
	{

	}

	void TestTexture::onRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT)); //�����ɫ����
		renderer m_render;

		{
			glm::mat4 modle = glm::translate(glm::mat4(1.0f), m_translationA); //ƽ��
			glm::mat4 mvp = m_proj * m_view * modle;
			m_shader->Bind();
			m_shader->SetUniformMat4f("u_MVP", mvp);
			m_render.Drawer(*m_Vao,*m_IBO,*m_shader);
		}
		{
			glm::mat4 modle = glm::translate(glm::mat4(1.0f),m_translationB); //ƽ��
			glm::mat4 mvp = m_proj * m_view * modle;
			m_shader->Bind();
			m_shader->SetUniformMat4f("u_MVP", mvp);
			m_render.Drawer(*m_Vao, *m_IBO,*m_shader); //����Ⱦ(��Ⱦ���)

		}
	}

	void TestTexture::onImGuiRender()
	{
		ImGui::SliderFloat3("Translation A", &m_translationA.x, 0.0f, 960.0f); //һ�����û���,��ֵ��translation // Edit 3 float using a slider from 0.0f to 960.0f    
		ImGui::SliderFloat3("Translation B", &m_translationB.x, 0.0f, 960.0f); //һ�����û���,��ֵ��translation  
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}
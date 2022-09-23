#include "TestTexture.h"
#include "renderer.h"
#include "ImGui/imgui.h"

#include "VertexArray.h"
#include "BufferLayout.h"
#include "glm/gtc/matrix_transform.hpp"
namespace test
{




	TestTexture::TestTexture()
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
		VertexArray va;
		VertexBuffer vb(Position, 4 * 4 * sizeof(float));

		BufferLayout Layout;
		Layout.Push<float>(2);
		Layout.Push<float>(2);
		va.AddBuffer(vb, Layout);

		IndexBuffer ib(indices, 6);


		//mģ�� v��ͼ pͶӰ ����
		//ͶӰ(����/͸��) //ģ��(ģ�ͱ任) //��ͼ(ģ�����,λ���뷽��,��ģ�ͽ�����任)
		glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 640.0f, -1.0f, 1.0f); //lrbt nf:Ŀ���/��Ļ��Χ
		//���ص� proj*(l,b,n,1)T = (-1~1, -1~1, -1~1 1)T
		//a view : glm �ľ��������������Ų���
// 		for (int i =0; i <proj.length();i++)
// 		{
// 			std::cout<< proj[i].x<<" "<<proj[i].y << " " << proj[i].z << " " << proj[i].w << std::endl;
// 		}
		//glm::mat4 modle = glm::translate(glm::mat4(1.0f),glm::vec3(300,200,0)); //ƽ��
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		//glm::mat4 mvp = proj * view * modle;

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
	}

	void TestTexture::onImGuiRender()
	{

	}

}
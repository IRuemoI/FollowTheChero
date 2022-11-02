#include "hzpch.h"
#include "OpenGlVertexArray.h"
#include "Glad/glad.h"

namespace Hazel
{
	static GLenum ShaderDataTypeToGlType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float: return GL_FLOAT;
		case ShaderDataType::Float2: return GL_FLOAT;
		case ShaderDataType::Float3: return GL_FLOAT;
		case ShaderDataType::Float4: return GL_FLOAT;
		case ShaderDataType::Mat3: return GL_FLOAT;
		case ShaderDataType::Mat4: return GL_FLOAT;
		case ShaderDataType::Int: return GL_INT;
		case ShaderDataType::Int2: return GL_INT;
		case ShaderDataType::Int3: return GL_INT;
		case ShaderDataType::Int4: return GL_INT;
		case ShaderDataType::Bool: return GL_BOOL;
		case ShaderDataType::None: return 0;
		}
		HZ_CORE_ASSERT(false, "Not Defined Type in ShaderDatatype ");
		return 0;
	}


	OpenGlVertexArray::OpenGlVertexArray()
	{
		HZ_PROFILE_FUNCTION();
		glGenVertexArrays(1, &m_rendererID); //��Gen�ͻ���ʽ��ʹ��Ĭ�ϵ�vao,��֮û��
	}

	OpenGlVertexArray::~OpenGlVertexArray()
	{
		glDeleteVertexArrays(1, &m_rendererID);
	}

	void OpenGlVertexArray::Bind()  
	{
		HZ_PROFILE_FUNCTION(); //�������һ���ô��ǿ��Կ����󶨴���.
		glBindVertexArray(m_rendererID);
	}

	void OpenGlVertexArray::UnBind()
	{
		HZ_PROFILE_FUNCTION();
		glBindVertexArray(0);

	}

	void OpenGlVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexbuffer)
	{
		HZ_PROFILE_FUNCTION();
		HZ_CORE_ASSERT(vertexbuffer->GetLayout().GetLayoutElement().size(),"VertexBuffer didn't add any Layout yet")

		glBindVertexArray(m_rendererID);
		vertexbuffer->Bind();
		const auto& Layout = vertexbuffer->GetLayout();
		uint32_t index = 0;
		for (const auto& element : Layout) //��Ӧ���Լ���Layout �� ����ӵ����������¼�������....Ϊ��ʡ��Դ?
		{
			//�����ڶ�������:ÿ������֮����ֽ�ƫ����(�����С), //ʵ�������� ����,������� ��������
			//������һ������:ƫ����,����˵pointerָ��Ĵ�0����������ʼλ����λ(�������Ե�ָ�밡....)
			glEnableVertexAttribArray(index);//������Ŷ�������
			glVertexAttribPointer(index, element.GetElementCount(), ShaderDataTypeToGlType(element.type), element.ifNormalized ? GL_TRUE : GL_FALSE, Layout.GetStride(), (const void*)element.offset);
			index++;
		}
		m_vertexBuffers.push_back(vertexbuffer);
	}

	void OpenGlVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexbuffer)
	{
		HZ_PROFILE_FUNCTION();
		indexbuffer->Bind();

		m_indexBuffer=indexbuffer;

	}



}



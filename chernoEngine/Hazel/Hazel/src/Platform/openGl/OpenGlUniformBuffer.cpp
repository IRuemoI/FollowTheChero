#include "hzpch.h"
#include "OpenGlUniformBuffer.h"
#include "glad/glad.h"

namespace Hazel
{
	//OpenglUniform�ڴ���ʱ����gpu��ʼ��������layoutȫ�ֿ�����
	OpenGlUniformBuffer::OpenGlUniformBuffer(uint32_t size, uint32_t binding)
	{
		glCreateBuffers(1, &m_rendererID);

		//��������ʼ�����������������
		glNamedBufferData(m_rendererID, size, nullptr, GL_DYNAMIC_DRAW); // TODO: investigate usage hint

		glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_rendererID);
		//bingding : index in GPU -> ayout(std140, binding = 0) uniform Camera 

	}

	OpenGlUniformBuffer::~OpenGlUniformBuffer()
	{
		glDeleteBuffers(1, &m_rendererID);
	}

	void OpenGlUniformBuffer::SetData(const void* data, uint32_t size, uint32_t offset)
	{
		//���»������������ݴ洢���Ӽ�
		//offset:ָ���������������ݴ洢��ƫ���� �����滻���Ӻδ���ʼ�����ֽ�Ϊ��λ��
		//�������ö���
		glNamedBufferSubData(m_rendererID,offset,size,data);

	}

}
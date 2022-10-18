#pragma once

#include "Hazel/Renderer/Buffer.h"

namespace Hazel

{
	class OpenGlVertexBuffer : public VertexBuffer
	{

	public:
		OpenGlVertexBuffer(float* vertics, uint32_t size);
		virtual ~OpenGlVertexBuffer() ;

		virtual void Bind()const  override ;
		virtual void UnBind()const  override ;

		virtual void SetLayout(const BufferLayout& layout) override
		{
			m_bufferLayout = layout;
			//��� layout ��const& ��ô�������ӿ� beginҲ����Ҫ begin()const����,����const iterator,�������ǲ������(�ṹ�ϲ���),��������û�ж�Ӧconst&�ĵ���������ʵ��,����ֻ���Է�const����ʹ���Լ���Bufferlayout
			//����! stl�ֲ�����һ��,�����ʹ�� const_iterator ����ֵ����� begin() const�汾ʵ��
			//ApplyLayout();
		};
		inline virtual const BufferLayout& GetLayout() const override
		{
			return m_bufferLayout;
		};

	private:
		//void ApplyLayout() const ;//ApplyҲ���� const,��Ҫlayoutʹ��ͬ����Begin() constʵ��
		uint32_t m_rendererID;
		BufferLayout m_bufferLayout;
	};

	class OpenGlIndexBuffer : public IndexBuffer
	{

	public:
		OpenGlIndexBuffer(uint32_t* indie, uint32_t size);
		virtual ~OpenGlIndexBuffer() ;

		virtual void Bind() const override;
		virtual void UnBind()const  override;
		virtual uint32_t GetCount() const override { return m_count; };

	private:

		uint32_t m_rendererID;
		uint32_t m_count;


	};

}
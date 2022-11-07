#pragma once
#include "Hazel/Renderer/FrameBuffer.h"

namespace Hazel
{
	/// <summary>
	///֡����ĸ������,�������������һ����Ⱦ��һ��ͼ,�д�����ô��,ʵ����ʾ�ľ�������ͼ,������ֶ�������ֱ������ʾ����ʾ������ʾ��,����������н���Ⱦ����Ⱦ�Ķ���(Bind,UnBind)
	/// </summary>
	class OpenGlFrameBuffer:public FrameBuffer
	{
	public:
		OpenGlFrameBuffer(const FrameBufferSpecification& spec);
		virtual ~OpenGlFrameBuffer() {};

		void Invalidate(); //��Ч��...��ɿհ�֡
		virtual void Bind() const override;	
		virtual void UnBind() const override;
		virtual const FrameBufferSpecification& GetSpecification() const override { return m_specification; }; //��û���const....��ȫ��һ...
		virtual  uint32_t GetColorAttachMentRendererID() const { return m_colorAttachMent; }; //��û���const....��ȫ��һ...


	private:
		FrameBufferSpecification m_specification;

		uint32_t m_rendererID;
		uint32_t m_colorAttachMent;
		uint32_t m_depthAttachMent;
	};

}


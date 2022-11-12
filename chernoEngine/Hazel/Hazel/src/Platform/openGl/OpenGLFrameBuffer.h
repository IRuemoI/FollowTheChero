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

		virtual ~OpenGlFrameBuffer(); //������Ҫ��������д���....��Ȼ����Ϊ����ʱ������ø������������/����û����������



		void Invalidate(); //��Ч��...��ɿհ�֡
		virtual void Bind() const override;	
		virtual void UnBind() const override;
		virtual const FrameBufferSpecification& GetSpecification() const override { return m_specification; }; //��û���const....��ȫ��һ...
		virtual  uint32_t GetColorAttachMentRendererID() const { return m_colorAttachMent; }; //��û���const....��ȫ��һ...


		virtual void ReSize(uint32_t width, uint32_t height) override;


	private:
		FrameBufferSpecification m_specification;


		uint32_t m_rendererID =0;
		uint32_t m_colorAttachMent= 0;
		uint32_t m_depthAttachMent =0;

	};

}


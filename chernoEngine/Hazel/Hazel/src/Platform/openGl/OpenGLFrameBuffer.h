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
<<<<<<< HEAD
		virtual ~OpenGlFrameBuffer(); //������Ҫ��������д���....��Ȼ����Ϊ����ʱ������ø������������/����û����������
=======
		virtual ~OpenGlFrameBuffer() {};
>>>>>>> 09c9513fa9700bc556c182756b0d40ca526de9c6

		void Invalidate(); //��Ч��...��ɿհ�֡
		virtual void Bind() const override;	
		virtual void UnBind() const override;
		virtual const FrameBufferSpecification& GetSpecification() const override { return m_specification; }; //��û���const....��ȫ��һ...
		virtual  uint32_t GetColorAttachMentRendererID() const { return m_colorAttachMent; }; //��û���const....��ȫ��һ...

<<<<<<< HEAD
		virtual void ReSize(uint32_t width, uint32_t height) override;
=======
>>>>>>> 09c9513fa9700bc556c182756b0d40ca526de9c6

	private:
		FrameBufferSpecification m_specification;

<<<<<<< HEAD
		uint32_t m_rendererID =0;
		uint32_t m_colorAttachMent= 0;
		uint32_t m_depthAttachMent =0;
=======
		uint32_t m_rendererID;
		uint32_t m_colorAttachMent;
		uint32_t m_depthAttachMent;
>>>>>>> 09c9513fa9700bc556c182756b0d40ca526de9c6
	};

}


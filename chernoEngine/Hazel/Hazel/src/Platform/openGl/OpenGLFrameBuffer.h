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


		virtual int8_t ReadPixel(uint32_t attachmentIndex ,int x,int y) override;
		void Invalidate(); //��Ч��...��ɿհ�֡
		virtual void Bind() const override;	
		virtual void UnBind() const override;
		virtual const FrameBufferSpecification& GetSpecification() const override { return m_specification; }; //��û���const....��ȫ��һ...
		virtual  uint32_t GetColorAttachMentRendererID(uint32_t index =0) const { return m_colorAttachmentIDs[index]; }; //��û���const....��ȫ��һ...
		virtual void ClearColorAttachment(uint32_t attachmentIndex, int value) override;


		virtual void ReSize(uint32_t width, uint32_t height) override;


	private:
		FrameBufferSpecification m_specification;


		uint32_t m_rendererID =0;

		//�ֿ�color��depth -> color������ĸ�����Ҫ����??
		
		std::vector<FrameBufferAttachmentSpecifcation> m_colorAttachmentspecifications;
		FrameBufferAttachmentSpecifcation m_depthAttchmentSpecification ;

		std::vector<uint32_t> m_colorAttachmentIDs;
		uint32_t m_depthAttachmentID = 0;
	};

}


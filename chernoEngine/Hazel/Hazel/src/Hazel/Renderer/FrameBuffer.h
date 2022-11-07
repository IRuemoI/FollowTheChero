#pragma once

#include "Hazel/Core/Base.h"

namespace Hazel
{

	struct FrameBufferSpecification //frameBuffer��ϸ�趨�ṹ��
	{

		uint32_t width, height;
		//FrameBufferFormat Format =  //deffault set
		uint32_t samples = 1;

		bool SwapChainTarget = false;
		//equal glBindBuffer(0); ...swapChain ��opengl�о���ǰ��֡����: backbuffer(�󻺳���)��֡����/����֡.. ���ֻ�ǲ�����ʾ��ˢ��һ��buffer����Ҫ"��Ⱦͨ��"�뽻����Ŀ�������ĸ���/����
		//���ﻹ��Ϊ�˿�ƽ̨׼��..vulkan��swapchain�Ǹ���ʽ�ἰ�ĸ���




	}; 

	class  FrameBuffer
	{
	public:

<<<<<<< HEAD
		virtual ~FrameBuffer() = default; //��Ҫ��һ��virtual���� �Ż�鿴�����������ִ��

=======
>>>>>>> 09c9513fa9700bc556c182756b0d40ca526de9c6
		 //virtual FrameBufferSpecification& GetSpecification()const = 0;
		virtual const FrameBufferSpecification& GetSpecification() const = 0; //��û���const....��ȫ��һ...
		virtual  uint32_t GetColorAttachMentRendererID() const = 0;
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

<<<<<<< HEAD
		virtual void ReSize(uint32_t width,uint32_t height) = 0;

=======
>>>>>>> 09c9513fa9700bc556c182756b0d40ca526de9c6

		static Ref<FrameBuffer> Create(const FrameBufferSpecification& spec);
	private:

	};
}



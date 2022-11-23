#pragma once

#include "Hazel/Core/Base.h"
#include <glm/glm.hpp>

namespace Hazel
{

	enum class FrameBufferTextureFormat
	{
		None = 0,

		RGB = 1, RGBA, RGBA16F, 
		
		RED_INTEGER,

		DEPTH24STENCIL8, DEPTH = DEPTH24STENCIL8,
	};


	enum class TextureWrap
	{
		Default =0
	};

	struct FrameBufferAttachmentSpecifcation
	{
		FrameBufferAttachmentSpecifcation() = default;
		FrameBufferAttachmentSpecifcation(FrameBufferTextureFormat format) 
			:Format(format)
		{};
		FrameBufferTextureFormat Format = FrameBufferTextureFormat::None;
		//TODO: use it to specific the texture wraptype
		TextureWrap warp;
	};

	struct FrameBufferSpecification //frameBuffer��ϸ�趨�ṹ�� -
	{

		FrameBufferSpecification() = default;
		FrameBufferSpecification(uint32_t Width,uint32_t Height)
			:width(Width),height(Height) {};
		FrameBufferSpecification(const std::initializer_list<FrameBufferAttachmentSpecifcation>& attachments)
			:Attachments(attachments) {};

		uint32_t width, height;

		//what's this-> > if Frame need its attachment to have miniMap?
		uint32_t Samples = 1;

		//equal glBindBuffer(0); ...swapChain ��opengl�о���ǰ��֡����: backbuffer(�󻺳���)��֡����/����֡.. ���ֻ�ǲ�����ʾ��ˢ��һ��buffer����Ҫ"��Ⱦͨ��"�뽻����Ŀ�������ĸ���/����
		//���ﻹ��Ϊ�˿�ƽ̨׼��..vulkan��swapchain�Ǹ���ʽ�ἰ�ĸ���
		bool SwapChainTarget = false;
		std::vector<FrameBufferAttachmentSpecifcation> Attachments;

		glm::vec4 ClearColor = { 0.1f,0.1f,0.1f,1.f };
		//TODO:NoResize
		bool NoResize = false;

		std::vector<FrameBufferAttachmentSpecifcation>::iterator begin() { return Attachments.begin(); } //�ṩ�������ӿ�,�������
		std::vector<FrameBufferAttachmentSpecifcation>::iterator end() { return Attachments.end(); }
		std::vector<FrameBufferAttachmentSpecifcation>::const_iterator begin() const { return Attachments.begin(); } //�ṩ�������ӿ�,�������
		std::vector<FrameBufferAttachmentSpecifcation>::const_iterator end() const { return Attachments.end(); }//ר��Ϊconst& ��const�����ṩ�� const������

	}; 

	class  FrameBuffer
	{
	public:


		virtual ~FrameBuffer() = default; //��Ҫ��һ��virtual���� �Ż�鿴�����������ִ��

		 //virtual FrameBufferSpecification& GetSpecification()const = 0;
		virtual const FrameBufferSpecification& GetSpecification() const = 0; //��û���const....��ȫ��һ...

		virtual  uint32_t GetColorAttachMentRendererID(uint32_t index = 0) const = 0;
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;


		virtual void ReSize(uint32_t width,uint32_t height) = 0;
		virtual int ReadPixel(uint32_t attachmentIndex,int x,int y) = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSpecification& spec);
	private:

	};
}



#pragma once

#include "hzpch.h"
#include "Hazel/Core/Base.h"
#include "Hazel/Events/Event.h"

namespace Hazel
{
	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title="Hazel Engine", uint32_t width = 1280, uint32_t height=720)
			:Title(title), Width(width), Height(height)
		{

		}


	};

	class  Window //������/�ӿ� ,û��Ա
	{
	public:
		using EventCallBackFn = std::function<void(Event&)>;//����ָ��
		
		virtual ~Window() {};
		virtual void onUpdate() = 0;
		virtual uint32_t  GetWidth() const= 0;
		virtual uint32_t  GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallBackFn& callback) = 0; //����и��ص�������Ա
		virtual void SetViewPort(float width,float height) = 0; //����и��ص�������Ա
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;
		//��¶m_window - for input,void*����Ϊ��һ����glfwwindow

		static Window* Create(const WindowProps& props = WindowProps());//  ��̬,������Ա?,���ⶨ��
		//Create ������Ӧƽ̨�Ķ���汾,���ڻ�����Ҫʵ�� window.h ��Ϊ�ӿ�


	};




}
#pragma once

#include "hzpch.h"
#include "Hazel/core.h"
#include "Hazel/Events/Event.h"

namespace Hazel
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title="Hazel Engine", unsigned int width = 1280, unsigned int height=720)
			:Title(title), Width(width), Height(height)
		{

		}


	};

	class HAZEL_API Window //������/�ӿ� ,û��Ա
	{
	public:
		using EventCallBackFn = std::function<void(Event&)>;//����ָ��
		
		virtual ~Window() {};
		virtual void onUpdate() = 0;
		virtual unsigned int  GetWidth() const= 0;
		virtual unsigned int  GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallBackFn& callback) = 0; //����и��ص�������Ա
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;
		//��¶m_window - for input,void*����Ϊ��һ����glfwwindow

		static Window* Create(const WindowProps& props = WindowProps());//  ��̬,������Ա?,���ⶨ��
		//Create ������Ӧƽ̨�Ķ���汾,���ڻ�����Ҫʵ�� window.h ��Ϊ�ӿ�


	};




}
#pragma once
//some basic macro
#include<memory>

#include "Hazel/Core/PlatformDetection.h"


#ifdef HZ_DEBUG
#if defined(HZ_PLATFORM_WINDOWS)
#define HZ_DEBUGBREAK() __debugbreak()
#elif defined(HZ_PLATFORM_LINUX)
#include <signal.h>
#define HZ_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define HZ_ENABLE_ASSERTS
#else
#define HZ_DEBUGBREAK()
#endif

#define HZ_EXPAND_MACRO(x) x
#define HZ_STRINGIFY_MACRO(x) #x

#define BIT(x) (1<<x) //1λ��xλ

//���Ǻܶ�& �� this ����?: ��������?,ʹ��this,�ǳ�Ա���������ز�����
//�ǵ� ���������ռ�/����
#define  BIND_EVENT_CALLFN(x) std::bind(&x,this,std::placeholders::_1) 







namespace Hazel
{
	template <typename T>
	using Scope = std::unique_ptr<T>;//ָ���������޶�
	template<typename T ,typename... Args> //typename...  �β��б�� ����Ϊ Args
	constexpr Scope<T> CreateScope(Args&& ... args)//Args�����۵��� ����Ϊ args(��Ϊ��ֵ?)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);//ת���β�args(...���)
	}

	template <typename T>
	using Ref = std::shared_ptr<T>; //ָ���ʲ���ref����,����ref���а�װ,����֮��Ķ��߳�ͨ��,����ֻ����Լ����ʲ�ǿ����һ��

	template <typename T,typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)//constexpr func() �������ʽ��������....��֤���س���(ֻ����return��������������),���ڱ���ʱ�����
	{
		return std::make_shared<T>(std::forward<Args>(args)...); 

	}

}


#include "Hazel/Core/Log.h"
#include "Hazel/Core/Assert.h"

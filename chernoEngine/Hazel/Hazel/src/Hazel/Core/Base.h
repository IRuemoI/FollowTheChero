#pragma once
//some basic macro
#include<memory>



#ifdef _WIN32
	#ifdef _WIN64
		#define HZ_PLATFORM_WINDOWS
	#else
		#error "x86 Buidls are not supported"
	#endif
#elif defined(__APPLE__)||defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR ==1
		#error "IOS simulator is not supported"
#elif TARGET_OS_IPHONE ==1
#define HZ_PLATFORM_IOS
#error "IOS is not supported!"
#elif TARGET_OS_MAC ==1
#define "MacOs is not supported!"
#else
#error "UnKonw Apple platform!"
#endif

#elif defined(__ANDROID__)
#define  HZ_PLATFORM_ANDROID
#error "Android is not supported!"
#elif defined(__Linux__)
#define HZ_PLATFORM_LINUX 
#error "Linux is not supported!"
#else
#error "unKown platform!"
#endif // _WIN32





#ifdef HZ_PLATFORM_WINDOWS
#if HZ_DYNAMIC_LINK
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API __declspec(dllexport)
	#else
		#define HAZEL_API __declspec(dllimport)
	#endif
#else
	#define HAZEL_API 
#endif	

#else
	#error Hazel only support windows!
#endif

#ifdef HZ_DEBUG
#define HZ_ENABLE_ASSERTS
#endif // HZ_DEBGUG



#ifdef HZ_ENABLE_ASSERTS
#define HZ_ASSERT(x,...) {if(!(x)) {HZ_ERROR("Assertion Failed:{0}",__VA_ARGS__ );__debugbreak();} }
#define HZ_CORE_ASSERT(x,...) {if(!(x)) {HZ_CORE_ERROR("Assertion Failed:{0}",__VA_ARGS__ );__debugbreak();} }

void GlClearError();
bool GlLogCall(const char* function, const char* file, int line);

#define GLCall(x) GlClearError();x;HZ_CORE_ASSERT(GlLogCall(#x,__FILE__,__LINE__)," OpenGL Error! "); //#x ,��x��Ϊ�ַ���,�����������б�����֧�ֵ�
#else
#define HZ_ASSERT(x,...)
#define HZ_CORE_ASSERT(x,...)
#define GLCall(x) x
#endif // HZ_ENABLE_ASSERTS


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
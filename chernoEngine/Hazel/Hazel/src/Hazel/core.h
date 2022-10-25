#pragma once
//some basic macro
#include<memory>


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
#endif // HZ_ENABLE_ASSERTS


#define BIT(x) (1<<x) //1λ��xλ

#define  BIND_EVENT_CALLFN(x) std::bind(&x,this,std::placeholders::_1) //���Ǻܶ�& �� this ����?: ��������?,ʹ��this,�ǳ�Ա���������ز�����

namespace Hazel
{
	template <typename T>
	using Scope = std::unique_ptr<T>;//ָ���������޶�

	template <typename T>
	using Ref = std::shared_ptr<T>; //ָ���ʲ���ref����,����ֻ����Լ����ʲ�ǿ����һ��


}
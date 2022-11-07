#pragma once
#include "Hazel/Core/Base.h"
//  Entry point ���ı������� SandBoxApp.cpp ��, int main ������ʵ�� �� hazel.h ���,��˿��Բ�����hazel/...h ��ʹ������


#ifdef HZ_PLATFORM_WINDOWS
#include <stdio.h>
extern Hazel::Application* Hazel::CreateApplication();//�ⲿ����



int main(int argc,char** argv)
{



	Hazel::Log::Init(); 

	HZ_PROFILE_BEGIN_SESSION("StartUp","HazelProfile-Startup.json");
	auto app = Hazel::CreateApplication();
	HZ_PROFILE_END_SESSION();


	HZ_PROFILE_BEGIN_SESSION("Run","HazelProfile-Runtime.json");
	app->Run();
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("Run","HazelProfile-ShutDown.json");
	delete app;
	HZ_PROFILE_END_SESSION();
}

#endif // HZ_PLATFORM_WINDOWS  

#pragma once

//  Entry point ���ı������� SandBoxApp.cpp ��, int main ������ʵ�� �� hazel.h ���,��˿��Բ�����hazel/...h ��ʹ������


#ifdef HZ_PLATFORM_WINDOWS
#include <stdio.h>
extern Hazel::Application* Hazel::CreateApplication();//�ⲿ����

bool func(Hazel::MouseButtonPressedEvent mos)
{

	printf("bbbbb");
	return false;
}

int main(int argc,char** argv)
{



	Hazel::Log::Init(); 
	HZ_INFO("initialized ClientLog");
	HZ_INFO("x log test: ver= {0}",5 );
	HZ_CORE_INFO("initialized CoreLog");


	printf("welcome enter hazel\n");
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif // HZ_PLATFORM_WINDOWS  

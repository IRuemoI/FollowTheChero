#include "Hazel.h"
//app ����������ϸ�ڲ�����Ȥ, �������(main)Ӧ�������涨��, appֻ��Ҫͨ��ʵ��������
//û����ȷ�ĳ�����ڵ� �� dllû�и���,lib�ṩ�ĺ���������dll����Ӧ�����


class SandBox:public Hazel::Application
{
public:
	SandBox()
	{

	}
	~SandBox()
	{

	}
};

// a box about how the game work would be send/trans to engine's entry point

Hazel::Application* Hazel::CreateApplication()
{
	return new SandBox;

}
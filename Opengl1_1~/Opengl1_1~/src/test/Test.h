#pragma once
#include <iostream>
#include <vector>
#include <functional> //for function
#include "ImGui/imgui.h"
namespace test
{
	class Test
	{
	public:
		Test() {};
		virtual ~Test() {}; //����
		 
		virtual void onUpdate(float deltaTime) {}
		virtual void onRender() {}
		virtual void onImGuiRender() {}


	};

	class TestMenu :public Test
	{
	public:
		TestMenu(Test*& current);
		//��ջ��,����Ҫ
		void onImGuiRender()override;
		
		template<typename T>
		void RegisterTest(const std::string& lable)
		{
			std::cout << "Register a test:"<<lable<< std::endl;
			m_tests.push_back(std::make_pair(lable, [](){return new T();})); //���ϵ�,�Ͼ�������ʽɾ��
		}
	private:
		Test*& m_currentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_tests;//testmenu �ϵİ�ť���»ᴴ��һ��test ,���Ǹ�����,��Ҫlambda/����ָ��


	};


}


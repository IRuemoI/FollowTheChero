#include "Test.h"

namespace test
{
	TestMenu::TestMenu(Test*& current)//����� Test* �ͻ����½�һ��ջ�ϵ�ָ�봫ֵ����!!!,
		:m_currentTest(current)
	{

	}
	void TestMenu::onImGuiRender()
	{
		for (auto& atest : m_tests)
		{
			if (ImGui::Button(atest.first.c_str()))
			{
				m_currentTest = atest.second();//ִ�Ŵ���test����
			}
			
		}
		
	}
}
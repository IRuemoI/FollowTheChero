//�ӿ�,  ʵ����ƽ̨���
//ʵ����ѯ���� , ask()
//input �� ��̬ȫ�ֵ�

//������ glfw��io?

#pragma once

#include "hzpch.h"
#include "Hazel/Core/Base.h"

namespace Hazel
{
	class HAZEL_API Input
	{
	public:

		static bool IsKeyPressed(int Keycode);//ask key 
		static bool IsMouseButtonPressed(int button);//ask key 
		static float GetMouseX();
		static float GetMouseY();
		static std::pair<float, float> GetMousePos();


	};



}
#include "hzpch.h"
#include "Hazel/Utils/PlantformUtils.h"

#include "Hazel/Core/Application.h"
#include <commdlg.h> //? for a bunch of spersific types about File? ͨ�öԻ����ͷ�ļ��������ļ��Ի�����ɫ�Ի��򣬴�ӡ�Ի��� ->�ϵײ��cͷ , QTһ�������Լ��������ɳ�һ����
//��������������һ���ļ��������򴰿�ѡ���ļ�

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h> //for get glfwGetWin32Monitor


namespace Hazel
{
	
	std::string  PlantformUtils::OpenFile(const char* filter) //filter��ʽ: "�ı��ļ�(*.txt)\0*.txt\0�����ļ�(*.*)\0*.*\0\0"
	{
		OPENFILENAMEA ofn; // �����Ի���ṹ��
		CHAR szFile[260] = { 0 }; // ���������ȡ�ļ����ƵĻ������� 

		ZeroMemory(&ofn, sizeof(OPENFILENAME)); // ��ʼ��ѡ���ļ��Ի���
		ofn.lStructSize = sizeof(OPENFILENAME); //ָ������ṹ�Ĵ�С�����ֽ�Ϊ��λ��
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
		ofn.lpstrFile = szFile; //�򿪵��ļ���ȫ·��
		ofn.nMaxFile = sizeof(szFile);//ָ��lpstrFile����Ĵ�С����TCHARsΪ��λ
		ofn.lpstrFilter = filter; //���ļ����͹�����
		ofn.nFilterIndex = 1; //ָ�����ļ����Ϳؼ��е�ǰѡ��Ĺ�����������

		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR; //λ��ǵ����ã������ʹ������ʼ���Ի���
		if(GetOpenFileNameA(&ofn) == true) // ��ʾ"��ѡ���ļ��Ի���"��  
		{
			return ofn.lpstrFile;

		}
		return std::string();

		//OPENFLIENAME ���� https://blog.csdn.net/kevinfan2011/article/details/84982588

// 		open.lpstrFile[0] = '\0'; //��һ���ַ����ǹ�������������ʾ�ַ���
// 		open.lpstrFileTitle = NULL; // ָ�����ѡ����ļ����ļ�������չ���Ļ��壨����·����Ϣ���������Ա������NULL��
// 		open.nMaxFileTitle = 0;  //ָ��lpstrFileTitle����Ĵ�С����TCHARsΪ��λ
// 		open.lpstrInitialDir = NULL;  //ָ���Կ��ַ��������ַ���������������ַ�����ָ����ʼĿ¼��
// 		open.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;//λ��ǵ����ã������ʹ������ʼ���Ի���
// 		if (GetOpenFileName(&open))  // ��ʾ��ѡ���ļ��Ի���  
// 		{
// 			path = file;
// 			printf(path + "\n");
// 		}
// 		system("pause");


	}
	
	std::string  PlantformUtils::SaveFile(const char* filter)
	{
		OPENFILENAMEA ofn; 
		CHAR szFile[260] = { 0 };

		ZeroMemory(&ofn, sizeof(OPENFILENAME)); // ��ʼ��ѡ���ļ��Ի���
		ofn.lStructSize = sizeof(OPENFILENAME); //ָ������ṹ�Ĵ�С�����ֽ�Ϊ��λ��
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
		ofn.lpstrFile = szFile; 
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = filter; 
		ofn.nFilterIndex = 1; 

		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR; //: ·���������,�ļ��������,���ܲ����ļ�
		if (GetSaveFileNameA(&ofn) == true) // ��ʾ"�����ļ��Ի���"��  
		{
			return ofn.lpstrFile;

		}
		return std::string();
	}



}
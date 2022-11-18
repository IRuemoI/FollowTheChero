#pragma once
#include <string>


namespace Hazel
{

	class PlantformUtils //just used to organize a bunch of relational functions and data
	{
	public:

		//return empty strings if cancelled
		//"�ı��ļ�(*.txt)\0*.txt\0�����ļ�(*.*)\0*.*\0\0"
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);



	};

}



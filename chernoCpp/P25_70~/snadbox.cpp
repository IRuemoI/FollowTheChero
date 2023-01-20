#include "Array.h"
#include "Vector.h"


#include <iostream>
#include <Vector>


int main()
{
	LOG("P70:��дSTD ����ģ��_��ϵ�� (P91~94)");
	//Array
#if 0
	{
		LOG("---------------------------------Array---------------------------------");
		constexpr int z = 10;
		Array<int, z> arr;
		memset(arr.Data(), 0, arr.Size() * sizeof(int)); //�ֶ���ʼ��

		static_assert(arr.Size() <= 10, "Array too large");

		for (size_t i = 0; i < arr.Size(); i++)
		{
			LOG(arr[i]);
		}
}
#endif
	//Vector	
#if 0
	LOG("---------------------------------Vector---------------------------------");
	{

		Vector<Vector3> data;
#if 0
		LOG("PushBack")
		data.pushBack({ 2,2,3 });
		//pushBack , ʵ�����ǹ����˶���� ,�ƶ�/���Ƶ�������
		data.pushBack(Vector3(1.f));
		data.pushBack(Vector3(3.f));
		PrintVector(data);
		data.Clear();
#else

		LOG("emplace");
		data.emplaceBack(2, 2, 3);
		data.emplaceBack(1.f);
		data.emplaceBack(3.f);
		//emplaceBack ��ȡ����Ĳ���,�͵��ڶ����й�������
		//��������?
		PrintVector(data);
#endif



		LOG("popBack")
		data.PopBack();
		data.Clear();
		data.emplaceBack(1.f);
		data.emplaceBack(2.f);
		data.emplaceBack(3.f);
		data.emplaceBack(4.f);
		data.emplaceBack(5.f);
		data.emplaceBack(6.f);

		PrintVector(data);
// 			LOG("Clear")
// 			data.Clear();
	}
#endif
	//iterater
#if 0
	{
		//iterator  ���ڴ�����ϵ�������, ͻ����index�����ı�����ʽ,ͬʱ֧�ָ����ӵĲ���
		LOG("STD::vector auto for loop use iterator");
		{

			std::vector<int> data = { 1,2,3,4,5 };
			for (auto element : data)
			{
				LOG(element);
			}

		}

		LOG("Custom vector for loop use iterator");
		{
			Vector<std::string> data;
			data.emplaceBack("1");
			data.emplaceBack("2");
			data.emplaceBack("3");
			data.emplaceBack("4");
			data.emplaceBack("5");

			for (Vector<std::string>::Iterator it = data.begin(); it != data.end(); it++)
			{
				LOG(it->c_str());
			}

		}

	}
#endif


}
#include<iostream>
#define LOG(x) std::cout<<x<<std::endl
#include <future> //���߳� �� �첽���� �� ��
#include <mutex>
#include <string_view>

uint32_t s_AllocCount = 0;

void* operator new(size_t size) //��new��ʽ�� , ȫ�ֵ�new(���ؿ�����ָ��) ����˵��c++ԭ����new,ֻ�ܽ���size_t -> stlʹ��
{
	s_AllocCount++;
	std::cout << "Allocating : "<<size<< std::endl;
	return malloc(size);
}

void Printname(const std::string& name)
{
	std::cout << name<<std::endl;
}
void Printname(const std::string_view& name)
{
	std::cout << name<<std::endl;
}

int main()
{
//LOG("part59:c++����Ķ��̼߳����Ż�");//û������,����첽���� async(),����ύmeshʱ,Ϊ�˷�ֹ��������vector����lock/������?

	LOG("part60:c++������ַ�����");
	{
#if 0
			std::string name = "ilove OpenGL";
			const char* tag = "MyHero Cherno";
	#if 0
			std::string first = name.substr(0, 5);
			std::string last = name.substr(6, 12);
			//����ֻ����鿴����ڴ��е�һ����,�������ڶ����½�,����string����������Ҳ������.
	#else
			//ʹ��c++17:  string_view  һ��const char*(sub��ͷ) �� һ�� size , ָ�������ַ����Ĳ��� , ����������ڴ� , 
	//Ҳ���ֶ�����
			std::string_view first(name.c_str(), 5);
			std::string_view last(name.c_str() + 6, 6);
	#endif

#else
			const char* tag = "MyHero Cherno";
			// const char*  ����ʽͬʱҲ���׺�c�����ַ���
			std::string_view first(tag, 6);
			std::string_view last(tag+7, 6);

#endif





		//Printname("OpenGl"); //������const & ��Բ�ͬ���ͻ��ǵù���һ��
		//Printname(name);
		Printname(first);
		Printname(last);
		//Printname(name.substr(0, 12));//name.substr ������һ��std::string

		//PS:visual studio��msvc����debugģʽӦ����Ϊ�˲�����Է��Ž�����new���ã��ַ�������Ӧ��Ҳ�Ǵ���ջ����ġ������releaseģʽ�ж��ַ����Ż�SSO
			//���ַ����Ż�SSO:gcc��stringĬ�ϴ�С��32���ֽڣ��ַ���С�ڵ���15ֱ�ӱ�����ջ�ϣ�����֮��Ż�ʹ��new����.gcc��stringĬ����sso�ġ�

		std::cout << s_AllocCount << " Allocated" << std::endl;
	}
}
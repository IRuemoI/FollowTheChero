#include<iostream>
#include<vector>
#include<array>
#include<functional>//for lambda
#include<algorithm> //for find_if
//#define WAIT std::cin.get()
//��Ҫ��ôд,�ɶ��Ի���

#define LOG(x) std::cout<<x<<std::endl
//�����÷�

//2 :���ú���release�汾��ȥ����־ϵͳ
//�� ��Ŀ - ���� - C++ - Ԥ������ - Ԥ������ �о���������Щ��(�����пո�) -> ������Ϊ #define �������
//���û�ж���P15_DEBUG , P15_DEBUG==1��Ȼ���Ա�������Ϊ��false
//���� 0 ͬ����Ԥ�����б���Ϊ��false
#if 0

#define P15_RELEASE=0
#if P15_DEBUG ==1
#define  LOGX(x) std::cout<<x<<std::endl
#else
#define LOGX(x) 
#endif // P15_DEBUG

#endif

//���к� ��Ҫ��ô�� ��\ת������з�
// 
// #define MAIN int main() \
// {\
// 	LOG("MAIN�����ں�");\
// }
// 
// MAIN

std::string getname()
{

	return "rabitank";
}
auto getsmt() {
	return "hh";
}

template<typename T>
void printArray(const T& array)
{
	std::cout << array.size() << std::endl;
}

void Printhello( int a) {
	LOG("hellow world");
	LOG(a);
}

void fuckvalue(int a)
{
	std::cout << a << " had been fucked" << std::endl;
}
void Foreach( std::vector<int > values , void(*whatyouwantdo)(int) )
{
	for (int value : values)
	{
		whatyouwantdo(value);
	}
}
void Foreachlambda(std::vector<int > values, const std::function<void(int)>& whatyouwantdo)
{
	for (int value : values)
	{
		whatyouwantdo(value);
	}
}

namespace sb { namespace function {
		
	static int sbInTheWorld = 2;
} }
//namespace SB = sb;


class rabit
{
	private:
		int a, b;
public:
	static void printType() {
		std::cout << "rabit" << std::endl;
	}
	static std::array<int, 4>& arr;
	//���ǲ��ܰѾ�̬��Ա�ĳ�ʼ����������Ķ����У����ǿ���������ⲿͨ��ʹ�÷�Χ��������� :: ������������̬�����Ӷ��������г�ʼ��
};
int main()
{

	std::cout << "part36:��_����" << std::endl;
	{
		//WAIT;
		//Ԥ������,���ı��滻
		LOG("�Ұ�C++��");
		//LOGX("������C++��!");
	}
	LOG(5);
	LOG("part37:auto");
	{
		//�����������Ƶ�������ʱ,ʹ��auto�Զ��涨����
		auto a = 5;
		auto b = a;
		//���ĺô���,����ı��Խ������ķ���ֵʱ,ʹ��auto���㲻��Ҫ�Ķ���ֵ
		//���Ƕ������ֵ������Ҫ��ʱ,����ò�Ҫʹ��auto,������������׸ı�
		//�㲻֪������ֵ�Ǹ�ɶʱ,Ҳ������auto
		//autoҲ�������� ��������������
		//����һ�������,��������ֳ��ֳ�,ʹ��auto�����ٴ����
		//���� using yourname = typename ��������
		auto name = getname();
		std::vector<std::string> ss;
		ss.reserve(2);
		ss.push_back("sb");
		ss.push_back("cnm");
		for (auto it = ss.begin(); it != ss.end(); it++)
		{
			LOG(*it);
		}
		//auto���Լ���const & * ... auto���ᴦ������,������Ǹ���
		int c = 4;
		const auto& staticptr = c;

		//����,,,cherno��ϲ��auto,would never use auto,��˵���ô����Ѷ�


	}

	LOG("part38:std::array");
	{
		//std::array ��̬����(���������ռ�)
		std::array<int, 4> sa = {1,2,3,4}; 
		sa[2] = 34;
		//��Ҫ�涨�����볤�� ��Ϊstd��ʹ����ģ�� ,����ʵ��һ��������
		//����,��Կ��ܳ��ֵ��������͵�ʵ��,������ô����? ʹ��ģ��д����
		printArray(sa);
		//stdarray ֧�ֵ����� ����� begin end foreach
		//stdarray ��debugģʽ��,array���к����Խ����,�㲻��Խ��
		//std::array ��û��ʵ�ʴ洢size , ���ص�size()ʵ������ģ�����,���ƺ�,һ��Դ�볣��
		//
		//���std::vector vector �Ǵ����ڶ��ϵĵײ�����(����Ϊ׼)
		//ģ���� ������ֱ��д��ͷ�ļ�������Ҫʵ���ļ�,��Ϊ��������
	}

	LOG("part39:c�����ָ��");
	{
		//��������һ��cpuָ�� �����,�з���,�洢���ڴ��ĳ���ط�
		//����Ի�����ָ���ָ��,*��ʾ������,()��ʾ��Ϊ����ִ��,
		auto hello = Printhello; 
		//*Printhello , &Printhello , ���ض���Printhelloһ��,�Ǻ���ָ��(����ʽת��) , () �ŻὫָ����ʽת��Ϊab(*cd)() ����;
		(*hello)(555);
		hello(666);
		//����? ��������(*name)(������������);
		void(*sb)(int a) = Printhello;
		sb(777);

		typedef void(*hellofunction)(int a) ; //������Щ���� ��Ϊ typedef void(*name)()  ; name  inputname -> void(*inputname)() 
		hellofunction functo = Printhello;
		functo(888);

		//����԰Ѻ�����Ϊ�ɱ����,�ڵ���ʱ������һ��������,�������ҵ�����д��;
		//�ڵ���ʱ������ָ����Ϊ����������һ����������Ϊ;����ִ��һ������? ,�е��� �ص�? .callback()?
		
		std::vector<int> vi = { 1,1,4,5,1,4 };
		Foreach(vi, fuckvalue);

		//lambda , ��ͨ��ʱ(���������ָ��ᱻɾ��)�������� [�������:���봫��������ʽ](��ʽ����){��������}
		Foreach(vi, [](int value) {std::cout << "value:" << value << std::endl; });

		//c���Է���Ѿ�û������,̫����
	}
	LOG("part40:lambda");
	{
		//lambda �����ǲ���Ҫ��������Ϳ���ʹ��һ�������ķ���;
		//��ʹ�ú���ָ��ĵط�������lambda

		std::vector<int> vi = { 1,1,4,5,1,4 };

		//lambda , ��ͨ��ʱ(���������ָ��ᱻɾ��)�������� [�������:���봫��������ʽ](��ʽ����){��������}
		//����δ���Ĵ���,����lambda������!
		auto lambda = [](int value) {std::cout << "value:" << value << std::endl; };
		Foreach(vi, lambda);

		//���� ���lambda�ⲿ�ֲ�����,���ݵ�lambda body�й���ʹ��
		//������չ�ɴ�����????!!!! C++nb�
		int i = 3;
		const char* string = "��ɱ�����ų�!!!";
		auto pritnsmtnum = [&,i](int value) {std::cout << "value:" << value<<i<<string << std::endl; };
		Foreachlambda(vi, pritnsmtnum);
		// = ����ֵ(����) , & ���ñ������� , name ����ָ��������ֵ���� , &name �����ض��������� ,
		//��ͳ c���ĺ���ָ�� �� c++ �в����lambda ����������,����Ϊ���Ͳ�ͬ
		//c++ �޲����lambda �������Ա���ʽת��Ϊ����ָ��
		//Ҫʹ���в���lambda��Ϊָ�� ��Ҫ���� functionalͷ�ļ�
		
		//lambda�β� const std::function<void(int)>&   <��������(�����б�)>
		//lambdaһ�㲻�������޸Ĳ�����ⲿ���� ��ʹ�� [=]
		auto changenum = [&, i](int value) mutable {i = 2; vi.clear(); };
		//������Լ��� mutable �����޸�

		//find_if ���� �����Ƿ�����ĳ���������ص�bool,���������������ĵ�һ��Ԫ�ص�λ�õĵ�����
		auto it =std::find_if(vi.begin(), vi.end(), [](int value) {return value > 4; });
		//��find_if �����п��� ����ú��������������Ľ�����(��Ԫ��)��Ϊ��������,����lambda���β����͵ú�Ԫ���������
		LOG(*it);
	}

	LOG("part_std: why not using namespace std");
	{
		//������ھֲ�����������
		using namespace std;
		//����cherno˵:����,���ٲ���using namespace std��eastl

		//1.std::��ȷ���ͻ�����������,cherno����eastl(��Դc++��)����std,������������һ��,��������
		//2.std��һ��Ѷ��������õĲ���.
		//3.ͬ���������Ĳ�ͬ�����ڲ�ͬnamespace���ͷų�������ظ�����,��ʹ�β����Ͳ�ͬ���������,��������ƥ�侫ȷ���͵�����ԭ��,�㻹���жϵ������ĸ�����
		//4.attention! ���Բ�Ҫ��ͷ�ļ���using namespace ,����������Ĵ���
		//5.��һ����С������������ok��
	}

	LOG("part41:namespace");
	{
		//ֻ�Ƿ�ֹ���ֳ�ͻ,��ָ���ĸ���;
		//�����ռ����Ƕ��,����
		//�������������ڶ���
		
		// :: ���������ռ� , ��ȵ�Ҳ��һ�������ռ� , ����Ҫ ::�����ڲ���̬����
		//ʹ����������ռ乹����̬����������,�絥Ԫ������Ҫ��ֵ/��Ҫ����,�㻹��ֱ���������ռ����ͬ������
		rabit::printType(); //rabit.printType() ĵ��
		rabit::arr[0] = 1; 
		std::cout << sb::function::sbInTheWorld << std::endl;
		//��̬��Ա��������ж������ǹ���ġ���������������ĳ�ʼ����䣬�ڴ�����һ������ʱ�����еľ�̬���ݶ��ᱻ��ʼ��Ϊ�㡣
		//���ǲ��ܰѾ�̬��Ա�ĳ�ʼ����������Ķ����У����ǿ���������ⲿͨ��ʹ�÷�Χ��������� :: ������������̬�����Ӷ��������г�ʼ����

		//�㻹����ָ������һ�������ռ��ĳЩ����
		using sb::function::sbInTheWorld;
		std::cout << sbInTheWorld << std::endl;

		//�㻹����Ϊ�����ռ������,�������Сȡ������д��������
		namespace SB = sb;
		std::cout << SB::function::sbInTheWorld << std::endl;
	
		//�����������������ռ�
		using namespace SB;
		using namespace function;
		//��
		using namespace SB::function;

	}
}

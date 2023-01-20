#include<iostream>
#define LOG(x) std::cout<<x<<std::endl

#include <tuple>
#include <string>

#include <optional>
#include <fstream>

#include <variant>

#include <any>

std::tuple<std::string, int> CreatePerson() //�������� pairҲ�� tuple֧�ָ������������
{
	return { "smart tuanzhang",20 }; //���ù�������

}

//optional c++17  ����,ָ������Ϊ��
std::optional<std::string> ReadFileAsString(const std::string& filePath)
{

	std::ifstream streamR(filePath);
	if (streamR)
	{
		std::string str;
/*		outSuccess = true;*/
		//read
		std::getline(streamR, str);
		streamR.close();
		return str;
	}

/*	outSuccess = false;*/
	return {};

}

//varraint c++17

enum class Error
{
	None = 0 ,TypeError,UnknowError
};

std::variant<std::string,int> ReadFileAsStringByVarriant(const std::string& filePath) //varriant �Ӹ�������
{

	std::ifstream streamR(filePath);

	if (streamR)
	{
		std::variant<std::string,int> str;
		/*		outSuccess = true;*/
				//read
		
		streamR.close();
		return str;
	}

	/*	outSuccess = false;*/
	return {};

}

int main()
{
	LOG("Part55:�ṹ����"); //tuple
	{
		auto  me = CreatePerson();
		std::cout << std::get<0>(me) << std::endl; //�ǵ� , ���ʳ�Ա�е㷳��


		int age;
		std::string name;
		std::tie(name, age) = CreatePerson(); //std::tie �ṩ�����÷��ʷ���,��Ȼ�е��鷳

		//c++17 �ṹ���� ,�ѱ�׼����һ��
		auto [m_name, m_age] = CreatePerson();
		std::cout << m_name << ":" << m_age << "\n"; //������ֻ��һ�εĽṹ������!!!

 	}
	LOG("Part56:OPTIONAL���ݴ���- ��Ƶ�ѵ�P76"); //����״̬δ֪״���µĶ�ȡ
	{
		bool ifsuccesss = false;
		std::optional<std::string> content = ReadFileAsString("data.txt");
// 		if (content != "")
// 		{
// 
// 		}
// 		if (ifsuccesss)
// 		{
// 
// 		}

		std::string value = content.value_or("can.t open it! "); //����� ����ֵ ,û��/��ȡʧ�� ��������������

		if (content ) //optional �Դ�bool,��ֵ�˻���true content.has_value()
		{
			std::cout << *content << std::endl;
			content.value(); //����value �����
			LOG("you did it");
		}
		else
		{
			std::string& str = *content;
			std::cout << "you can't do " <<value<< std::endl;
			

		}
	}
	//c++17 �����Ա���
	LOG("Part57:��һ������Ŷ���������	");
	{
		std::variant<std::string, int> data;
		data = "rabitank";
		std::string str = std::get<std::string>(data);
		//int inta = std::get<int>(data); cant
		LOG(str);
		data = 2;
		data.index(); //1 ���ص�ǰdata���ݵ����͵���������  <type1,type2,type3,type4>  0��type1,1��....
		std::string* strptr = std::get_if<std::string>(&data); //���ָ��ָ��������string ��get ����ָ�����ݵ�ָ�� ��֮ nullptr
		if (strptr)
		{
			LOG(*strptr);
		}
		//������ get_if()  , ��ȫ
		//variant ���������� �ڴ��ǳ�Ա֮��
		int a  = std::get<int>(data);
		LOG(a);
		data = "qiumi!";
		//data = false;//����,���Ǹ���δ�������͵�ֵ��Ͳ��ܷ�����


	}
	LOG("Part58:���������������_any");
	{
		std::any data; //no need template

		data = "love";
		data = 2;
		data = std::string("i love sword");
		
		// get 
		std::string str = std::any_cast<std::string>(data);//if it is not the type of data,there will be a error

		//if you ver is more than 32u,any will dynamic distribute memory,it is bad
		// but varriant always static distribute the memory

		//cherno: useless
	}
}
#include <iostream>
//#include <string>
//yes,you need it to print std::string by std::cout
//but now you don't

void PrintString(const std::string& string) {
	//string += "h";//it is const ,you can't
	std::cout << string << std::endl;
}
//c++�Ĳ������ݾ���һ���Ⱥ� 
//���� �β� = ʵ��;�������ָ�������,�����ʱ�����ڿ���ʵ��
//���ռ���ڴ�:(

//const
class Entity
{
private:
	 int m_X, m_Y;
	 mutable int var;
public:
	 int GetX() const 
	 { 
		//const�ڷ�����֮��,!!ֻ�����п�����ô��!!
		//��Ϊ,�����޸��κ�ʵ�ʵ���,(���ᶯ��Ա����),ֻ���������
		
		 //������Ҫ�ı�ĳ��������const��,�����ʹ�� mutable �ؼ���
		 //��Ϊ�ɱ��,�ı�����������const��ͻ
		 var = 4;

		 return m_X;//��const��ʵ������
	 }
// 	 int GetX() { //����const��ʵ������
// 		 return m_X;
// 	 }
	 //������ʱ��һ�ַ������������汾
	 int GetY() //�������ǲ��ܱ�֤GetY�����޸���
	 { 
		
		 return m_Y;

	 }

private:

};

void PrintEntity(const Entity& e,Entity& f) {//���ñ���ʼ���������޸�ָ��,ֻ���޸����Լ�
	//����const֮�� ��const Entity ,�޸�e ���޸�һ��const Entity,��ͬ������
	std::cout << e.GetX() << std::endl;
	//��ͨʵ���ܹ�ʹ��const����,����constʵ������ʹ����ͨ����
	std::cout << f.GetX() << std::endl;
	//std::cout << e.GetY() << std::endl;
	//const Entity�������Լ��ĳ�Ա GetY������
	//GetY��δ��֤�Լ������޸ĳ�Ա,����const Entity��֤�����ͻ
	//��,����޸�Ҳ����
}


int main() {
	std::cout << "<==========Part13:string==========>" << std::endl;
	const char* name = "Rabit";
	//"Rabit"�洢���ڴ��constֻ������,�����ܹ�����constʹ��char*,����Ȼ���Ըı���
	//name[2]='c';��Ҫ��ô��,��û��,���������
	char namearray[] = "Rabit";
	namearray[2] = 'c';//�����ǿ��Ե�

	char name2[5] = { 'R','a','b','i','t' };
	char name3[6] = { 'R','a','b','i','t' };//"Rabit"���һ��\0��ֹ��,ռ6�ֽ�
	//const char* ��c�����ַ���
	//const ��C11��ǰ������Ҫ,����һ�㲻��Ķ��ַ������Ի����
	//c11��, �ַ�����ʽ�̶�Ϊ const char*(�ͱ������й�)
	//�ַ����ڴ�̶�,�޷���չ
	//"Rabit"��δʹ��new ,����ջ��,����ҪҲ������delete[]
	std::cout << name << std::endl;
	std::cout << name2 << std::endl;//���������ڴ�����cc
	//std::cout << name3 << std::endl;
	//nameβ��һ��00 �ֽ�0,��ʾ�ַ�����ֹ
	//û������ַ���ֹ��,��ֻ��һ���ַ�����

	std::string stringname = "Rabit";//�����string,�ұ���const char*
	std::cout << stringname << std::endl;
	stringname.size();

	//std����Ϊstring,��c++����Ӧ��ʹ����,����baiscstringģ���һ��charʵ��
	//������char��������ú���
	//�����const char*��char*,��͵�ʹ��c��������������,��strlen(),strcpy()
	//+��string�б�������,�����
	stringname += " tank!";//�����ν�string��const char*
	//find����->contain
	bool contain = stringname.find("an") != std::string::npos;
	//npos �Ƿ�λ��,����λ��,��ζ������
	
	//�ַ�������
	PrintString("sb");


	std::cout << "<==========Part13:stragestring==========>" << std::endl;
	//�ж�
	const char name4[11] = u8"Rabit\0tank";
	//u8ûʲô��˼,����ͨ�ַ���һ��-utf8
	std::cout << strlen(name4) << std::endl;
	
	//���ַ� L""
	const wchar_t* namewchar = L"Rabit";
	//widechar �еı�����(vs) ������Ϊ ˫�ֽ�

	//char16,32
	const char16_t* name16 = u"Rabit"; //˫�ֽ�?-utf16
	const char32_t* name32 = U"Rabit";//���ֽ�?��utf32

	using namespace std::string_literals;//һЩ����/�﷨��

	std::string namestring = "Rabit"s + "tank";
	//s : ����һ��std::string
	//std::wstring L""  std::u32string U""  std::u16.....
	const char* nameR = R"(Rabit
Tank
is 
pretty
)"; //�����������
	//R"()" ����ת���ַ�,����/\�ͻس�,���ҳϵ��������
	const char* nameRex = "Rabit\n"
		"tank\n"
		"is wonderful\n";
	std::cout << nameR << nameRex << std::endl;

	//�ַ�������
	"SB"; //�����һ���ַ�������,ֻ�洢��ֻ���ڴ���
	const char namesurfacecopy[] = "SB";//����ʵ�Ǹ���"SB"��ջ�ϵ�����


	std::cout << "<==========Part14:const==========>" << std::endl;
	//const ������ʵ��Ӱ��������,��ֻ����Կ�����Ա�ػ���,һ�ֳ�ŵ
	//��ŵ����Ķ�
	const int MAX_AGE = 90;//�ƺ�д����ֻ����
	const int* a = new int;//�㲻���޸�ָ��ָ�������,ֻ�ܶ�ȡ
	//������д�� int const* a
	//ע��,������ָ�벻��,����ָ������ݲ��ܱ�
	//*a = 2;
	a = &MAX_AGE;//����� int* a,ǿ�ƽ�&MAX_AGE��constint*��Ϊint*����ִ�����
	//���֮��ǿ�и�ֵ���ܻ��ó������
	std::cout << *a << std::endl;

	//2
	int* const b = new int;
	//�����޸�ָ������,���ǲ����޸�ָ��
	*b = 2;
	//b = (int*)&MAX_AGE;

	//3
	const int* const c = new int;
	//�����޸����� const* �����޸�ָ�� *const






}

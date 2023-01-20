#include <iostream>

#define LOG(x) std::cout<<x<<std::endl

void PrintName_constRef(const std::string& name)
{};

void PrintName_L_Ref( std::string& name)
{};

void PrintName_R_Ref(std::string&& name)
{};

void PrintName(std::string&& name)
{};

void PrintName(const std::string& name)
{};


class  String
{
public:
	int m_size;
	char* m_data;

	String(const char* str)
	{

		printf("Create\n");
		m_size = strlen(str);
		m_data = new char[m_size];
		memcpy(m_data, str, m_size);
	}

	String(const String& other) 
	{
		printf("Copied\n");
		m_size = other.m_size;
		//m_data = other.m_data; //ֱ�Ӹ���ָ��ᵼ�� double free
		m_data = new char[m_size];
		memcpy(m_data, other.m_data, m_size);
	}

	String(String&& other) noexcept //�ƶ����캯�� , �ƶ�,�����븴��,��������Ϊ�������ݷ����ڴ�,�����ƶ����������ڴ������Ȩ
	//noexcept ���߱������������׳��쳣
	{
		printf("Moved\n");
		m_size = other.m_size;
		m_data = other.m_data; //�µ���ֵ�������Ȩ
		other.m_data = nullptr; // �ɵ�,��ʱ����ֵʧȥ�����ڴ�����Ȩ,֮�����Ͼͱ�����.
		other.m_size = 0;
		//��������Ȼ���ʺϿ�������,�����������Ҳ����ֵ,���Ĵ�����ʹ����˵���� , ��Ӧ�ñ����Ըı�.

	}

	String& operator=(const String& other) //������ֵ
		//���񿽱�����,���ǻ��ǵ�д
	{
		printf("l_equal\n");
		m_size = other.m_size;
		m_data = new char[m_size];
		memcpy(m_data, other.m_data, m_size);
		return *this;
	}

	String& operator=(String&& other)
		//���ƶ����첻ͬ,this�Ѿ���ʼ��������,����move����֮ǰ��Ҫ������������,��Ȼ�������й©
	{
		printf("r_moveEqual\n");

		if (this == &other) //���ƶ���ֵ���
		{
			return *this;
		}
		delete[] m_data; //�����Լ��������ڴ�; 

		m_size = other.m_size;
		m_data = other.m_data; //�������Ȩ

		other.m_data = nullptr; // �ɵ�,��ʱ����ֵʧȥ�����ڴ�����Ȩ,֮�����Ͼͱ�����.
		other.m_size = 0;
		

		
		return *this;
	}

	~String()
	{
		printf("Destoried\n");
		delete[] m_data;
	}

	void Print()
	{
		for (int i = 0; i < m_size; i++)
		{
			printf("%c",m_data[i]);
		}
		printf("\n");
	}



};


struct Entity
{
	String m_string;
	Entity(const String& name)
		:m_string(name)
	{

	}

	Entity(String&& name)
		:m_string(std::move(name) ) //rlReference -> call String move construct function
		//:m_string((String&&) name) //rlReference -> call String move construct function

		//******** �����ֵ���ֵ��������ֵ, �������ֵ��ֵ˵��,c++���۵����� ********
		//��Ҫͨ������ת��������ֵ���� , ���û��(String&&) , ���ǻ�ʹ�ÿ�������.
		//����ͨ�� std::move ����������ֵ����
	{

	}
	
	void PrintName()
	{
		m_string.Print();
	}

}; 

int main()
{
	LOG("P65: ��ֵ��ֵ (P85) ");

#if 0
	{
		int i = 10;
		int& j = 10; //& ��ֵר������
		const int& z = 10; // ʵ����: int temp =10; const int& z =temp;	
		const int& z_l = i; //ͬʱ֧�� rl;

	}
	{
		std::string name_1 = "rabit";
		std::string name_2 = "tank";
		PrintName_L_Ref(name_1 + name_2);
		PrintName_constRef(name_1 + name_2);
		PrintName_R_Ref(name_1 + name_2);


		std::string&& name_3 = "Best"; //��ֵ������������ֵ,��������ֵ,�������е�ַ
		PrintName_L_Ref(name_3);
		PrintName_constRef(name_3);
		PrintName_R_Ref(name_3);

		//const& �� && �ڲ�ͬ����µ����ȼ�
		PrintName(name_1 + name_2);
		PrintName(name_1);


	}
#endif
	LOG("P66: �������� ��̬���� (P86,87) "); 
	//CI
	//���,������Jenkins , ��������(CI)�ܹ��ڴ����ύ�������Զ�����,���в���,һ��ܹ��ڷ������Ϲ����ύ����,���,���ٿ�����Ա�Ĳ��Թ���.
	//��̬����
	//�����д����ʱ�ķ���,������,����ƴд,�����﷨����,���㻭������. ���

	LOG("P67: ��������˳�� (P88) ");
	//��������˳��,c++��׼��δ�Դ˽��ж���,�ڲ����Ͻ��м�����δ������Ϊ,C++17���Ժ�Դ˹涨�ȶԲ�����׺������Ҫ˳�����㴫ֵ,���ܲ���.

	LOG("P68: �ƶ�����(P89) ");
#if 0
	{
		Entity entity("rabit tank");
		entity.PrintName();

		std::cin.get();
	}
#endif
	
	LOG("P69: �ƶ�����_stdmove���ƶ���ֵ(P90) ");
	{
		String&& rrstr = "RabitTank_r";
		String lstr = "RabitTank_l";

		String rrstr_t_lstr_no_move("");
		String lstr_t_lstr_no_move("");
		
		String rrstr_t_lstr_move("");
		String lstr_t_lstr_move("");

		LOG("���ƶ���ֵ");
		rrstr_t_lstr_no_move = rrstr;
		lstr_t_lstr_no_move = lstr;

		
		LOG("�ƶ���ֵ");
		rrstr_t_lstr_move = std::move(rrstr); //��û���ƶ���ֵʱ,l_equalҲ�ǿ��Խ��ܵ�
		lstr_t_lstr_move = std::move(lstr);
		lstr.Print();

		rrstr_t_lstr_move.Print();
		rrstr_t_lstr_move = std::move(rrstr_t_lstr_move);
		rrstr_t_lstr_move.Print();
		//std::move ��������ԭ��������,���Ƕ�������ֵ����;
		
		
		std::cin.get();
	}


}
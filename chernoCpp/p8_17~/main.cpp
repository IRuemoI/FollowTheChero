#include <iostream>


using String = std::string;
class Entity
{
private:
	std::string m_Name;
	int m_score;

public:
	//��Ա��ʼ���б�
	//��������ôд,�����ǰ��������Ա�Ķ���˳������ʼ����
	//���Ա��밴�ն���˳��д��ʼ���б�
	//�����ô����׶����,���ܼ�������(������Щ������ʼ������)
	//һ���ʼ����,�ڶ���ʱ�ͽ���һ�γ�ʼ������,Ȼ���ڳ�ʼ�����������µĸ��ǵ��ɵ�
	//����ʼ���б�ֻ���ʼ��һ��,���ʡ����Դ
	Entity()
		:m_Name("Unknow"),m_score(0){}

	Entity(const std::string& Name)
		:m_Name(Name),m_score(0){};

	Entity(int score)
		:m_Name("unknow"), m_score(score) {};
	 explicit Entity(const String& Name, int score)
		:m_Name(Name), m_score(score) {};
	const String GetName() const
	{
		return m_Name;
	}

};

void PrintEntity(const Entity& entity) {
	std::cout << entity.GetName() << std:: endl;
}


void main() {
	std::cout << "Part17:��Ա��ʼ���б�" << std::endl;
	Entity e;
	std::cout << e.GetName() << std::endl;

	std::cout << "Part18:��Ԫ�����" << std::endl;
	// ? = if;
	{
		int a = 1;
		int b = 2;
		if (a > 5)
			b = 10;
		else
			b = 5;
		//��ͬ��

		b = a > 5 ? 10 : 5;//ֻ��Ϊ��һ����ֵ,һ�м�����,�ٶȻ��
		b = a > 5 ? a > 10 ? 15 : 10 : 5;
		//��ͬ��a > 5 ? (a > 10 ? 15 : 10) : 5;
		b = a > 5 && a < 100 ? a > 10 ? 15 : 10 : 5;
		//b = (a > 5 && a<100) ?( a > 10 ? 15 : 10) : 5;
		//��Ԫ��������鲻ҪǶ��,��Ҫֱ��Ƕ���������Ŷ�û :(

	}
	
	std::cout << "Part19:�������������" << std::endl;
	{
		//�ں���ջ�ṹ�еĴ��� stack
		Entity entity;//��ʼ��
		Entity entity1("rabit");//��ʼ��-ָ������
		Entity entity2 = Entity("tank");//��ʼ��-һ�㷽��
		//����һ��ջ�ṹ�ı�־ { }, }ջ�ṹ����,��һ��������,������ֶ��������{}���޶�һЩ�ֲ�������������
		Entity* ep;
		{
			Entity entity3;
			ep = &entity3;
		}//entity3������

		//ջһ�㶼��С,1,2mb,������Ҫ������ʵ��ʱ���ö� heap

		Entity* entity4 = new Entity("ɵ��");//new ����һ����Ӧ�ѵ�voidָ��
		Entity* eph;
		eph = entity4;
		delete entity4;
		//c++�еĶ�,����Ҫ�ֶ�ɾ����,���Ҷѷ������
	}

	std::cout << "Part20:new" << std::endl;
	{
		//new ��һ�� operater ,�����������
		int* b = (int*)new int[20]; //80bytes in heap ,һ����
		Entity* ep2 = new Entity();
		//new 1. malloc(sizeof(Entity))�����ڴ� 2.����Entity�Ĺ��캯��
		//����ָ��������һ���ڴ�
		Entity* ep3 = new(b) Entity;
		delete ep2;
		delete[] b;
		//deleteҲ�ǲ�����

	}

	std::cout << "Part21:��ʽ���캯��������ת��" << std::endl;
	
	{
		//��ʽת��ֻ����һ��:entity ���� std::stirng , int 
		Entity entity = (std::string)"rabit";//const char ��ʽ-> std::string ->entity;һ��
		Entity entity1 = 20;//int -> entity һ��
		Entity entity11 = { 20 };
		PrintEntity(22);//int -> entity һ��
		PrintEntity((String)"ɱ�����ų�");//const char ��ʽ-> std::string ->entity;һ��

		//explicit �ؼ��� 
		//��ֹ��Ĺ��캯��������ʽת��,����żȻ�ķ�����ת��,����ʶ��ת��
		Entity entity3("sb", 20);
		Entity entity4 = { "����������",20 };//������

	}
}
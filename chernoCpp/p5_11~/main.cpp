#include <iostream>
#include <array>

class Entity {
	int X, Y;//Ĭ��private
	//private:ֻ��Entity�ڵĳ�Ա/��friend��ǿ��Է�����,��ȡ������
public:
	Entity() {
		X = 0;
	}
protected:
	int Z;
	//protected:���������������ڿ��Է�����
public:
	int W;
	//�����˿ɼ�
};

class Player :public Entity
{
public:
	Player() {
		//X = 2;//����,entity��
		Z = 2;//����,protected
	}
};

void Part(int x, const char* name) {
	std::cout << "<=================="
		<< "Part" << x << ":" << name << "==================>" << std::endl;

}

///////////////////////////

void main() {
	Part(11, "�������η�");//Ҳ�пɼ����η�
	Entity e;
	//e.X = 2;����,entity֮��
	//e.Z = 2;����,protected
	//�ɼ��Ժʹ��������޹�,��ֻ��Ϊ�����ǽ�������,�����Լ���������
	//public ������ʹ�õ�,�����,
	//�㲻Ӧ��ֱ�ӵ���private�����͸���private����,���������ص��ڲ��߼�
	//���������ʹ��private,�������ƻ���Ĺ���

	Part(12, "Array");

	int example[5];			//��ջ��,������������ʱ����
	int* another = new int[5];//�ڶ���,�ֶ����ٻ�������
	for (int i = 0; i < 5; i++)
		example[i] = 2;
	for (int i = 0; i < 5; i++)
		another[i] = 2;
	delete[] another;//������뷵���ں������´���������,��Ҫ��new
	//���е�new �ᵼ���ڴ���Ѱַ(�ȷ���this)

	example[0] = 2;
	example[4] = 4;
	
	//example[-1] = 5;
	//example[5] = 10;
	//����release���������,����ı��˲������Լ����ڴ�(��ָ��ǰ4�ֽ���ָ���20~24�ֽ�)
	
	std::cout << example[0] << std::endl;
	std::cout << example << std::endl;//��ӡ�����ַ
	//����Ԫ��/д��Ԫ�� ���ʵ�ַ:ָ��+�±�*�����ֽ��� 
	//��example[2] = example + 2*4;
	
	int* ptr = example;
	*(ptr + 2) = 6;
	//���� example[2]=6;���� *(int*)((char*)ptr+8)=6
	//+2������Ϊ ptr + 2*ptr�����ֽ���

	//std������д��array(std::array),���б߽���,��ȡ��С�ȷ���,��Щ��ԭ��û�е�
	//�ֶ���ԭ�������count��������,����Ҫ�Լ�ά��(�����䳤��)
	int a[5];
	int counta = sizeof(a) / sizeof(int);//5
	int* b = new int[5];
	int countb = sizeof(b) / sizeof(int);//1 ָ��ĳ���Ϊ4�ֽ�
	const int examplesize = 5;//�����л�Ҫ����static������
	int exampleconst[examplesize];
	std::array<int, 5> stdarray;//һ��stdarray,�ж��⿪��
	std::cout << stdarray.size() << std::endl;
}
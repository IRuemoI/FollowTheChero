#include<iostream>
#define LOG(x) std::cout<<x<<std::endl;
#include<algorithm> //for sort
#include<vector>
#include<functional>

struct ver2
{ //д����,���������ɶҲ��д,Ҳ���ٻ���һ���ֽ�
private: int x, y;//������8�ֽ�
public:
	ver2(int ix, int iy)
		:x(ix), y(iy) {}
	int* getPostion()
	{
		return &x;
	}
};
struct vector2 
{
	float x, y;
};
struct vector4
{
	union 
	{
		struct 
		{
			//����struct�����ĸ������һ����Ա,�ٰ����ŵ�union��
			float x, y, z,w; //��������verctor2

			//�����������,��ֻ��һ�����ݽṹ,��ֻҪ .x ���ܷ���x

		};
		struct 
		{
			float r, b, g, a;
		};
		struct
		{
			vector2 A, B; //A ����x,y,B����z,w 
		};

	};
// 
// 	vector2& getA()
// 	{
// 		//�õ�ǰ��λ
// 		return *(vector2*)&x;
// 	}
	
};


class base 
{
public:
	base()
	{
		LOG("base creator!");
	}
	virtual ~base()
	{
		LOG("base destructor!");
	}
	

};
class deriver:public base
{
public: 
//���������� �ڱ�����(ɾ��)ʱ��Ҫ���û���Ĺ��캯��(��ɻ����Ա�ĳ�ʼ��)/��������,
//���Ҫ���乹�캯���������������ܱ���������õ�,��public��protected
	deriver()
	{
		LOG("deriver creator!")
	}
	~deriver()
	{
		LOG("deriver destructor!")
	}
};
class anotherclass:public base
{
private:
	int a;
public:
	anotherclass(double ia)
		:a(ia)
	{
		
	}
	~anotherclass()
	{

	}

};
int main()
{
	LOG("part45:����")
	{
		std::vector<int> vws = { 2,3,4,23,17,932,12 };

		//sort ����: 1,��ʼ������ 2,���������� 3,������/ν��/��ѡ
		//ν�ʽ���
		//< :���� Ĭ��
		//> :����
		//std::greater<int>() һ��std��>�ȽϺ���ģ��

		//������:�������� bool ��� ����Ҫa��bǰ ,��ô����true
		//���������׳���,����ó�ֿ��ǿ��ܵ����,��ÿ��Ԫ�ص�λ�ö��ܱ�ȷ������
		std::sort(vws.begin(), vws.end(), [](int a, int b) {
			if (a == 23)
				return true;
			if (b == 23)
				return false; //ǿ�а�23�ŵ���һ��
			return a<b;
			});
		for (int value : vws)
			LOG(value);
		
	}
	LOG("part46:����˫��")
	{
		//�ƹ�c++��ǿ����ϵͳ?
		//���㴴��ĳ���ͱ���ʱ���Ƿ������ڴ�
		//��ô���ܲ����ƹ��������ư��ڴ�����������������?


		int a = 114513;
		double b = *(double*)&a; //a��ָ��ת��Ϊdouble����ָ��,��double��ʽ���ʵ�ַ�ٸ���b;
		//double& b = *(double*)&a; b =0.0 �����ǲ��е�,�㲻����4�ֽڿռ�д8�ֽ�,������debug�в���
		LOG(b); //��������������ת�����ҵ�
		int c[2] = {1,0};
		double& d = *(double*)&c;
		d = 1; //��������,�������8�ֽڿ�д
		LOG(d);

		ver2  ver = { 2,2 };//�����ֱ�Ӱ�ver���� int[2],����8�ֽ��ڴ���ʽ�ʺ���ô��
		
		int* ver2a =(int*)& ver;
		LOG(ver2a[0]<<ver2a[1]); //ʵ����,[n]������ת��һ��ָ���ַ��n������ƫ���ٽ�����,�������Ĳ�������

		int charz = *(int*)((char*)&ver + 4); //��char��ʽ���ʵ�ַ,���ƶ�4��char�õ���ַ,����int���ʵõ��ĵ�ַ
		LOG(charz);

		//�ٱ���ֱ�ӵõ���ַ,������ƹ��ܶණ��ֱ�����ӵ��ڴ沢�������
		int* postion = ver.getPostion();
		*postion = 4;
		LOG(ver2a[0] << ver2a[1]);
		//����д�ֽ���,��Ҫ��������ʲô����,ֱ�Ӱ������ֽ����
	}
	LOG("part47:union")
	{
		//c++union like to class
		//�������classһ������,������ֻռ���Լ�һ����Ա�ڴ�(���г�Ա����һ����Ա�ڴ�,�������������й�),�������ֲ�ͬ
		//������˫���й�,���Խ�����������,Ҳ���Լ�������ת���͸���
		//�������й��캯���� , ���ǲ������麯��

		//����union ����ӵ�г�Ա����

// 		struct Union  
// 		{
// 			union 
// 			{
// 				int x;
// 				float y;
// 
// 			};	
// 		};
// 		Union u;
// 		u.x = 2;
// 		LOG(u.x << "," << u.y);
		//
		//
		vector4 ver4 = { 1.0,2.0,3.0,4.0 };
		LOG(ver4.A.x << ver4.A.y);
		ver4.y = 500.0;
		LOG(ver4.A.x << ver4.A.y);

	}
	LOG("part48:����������")
	{
		base* ins1 = new base();
		delete ins1;
		LOG("-------------------------------");
		deriver* ins2 = new deriver;
		delete ins2;
		LOG("-------------------------------");
		base* in3 = new deriver;
		delete in3;
		//ֻ��base������������������,����deriverû��,�⵼��deriver���ֳ�Աû�б�ɾ������ڴ�й©
		//c++��֪���������������һ����������,
		//�����Ϊʲô��Ҫ virtual ���Ϊvirtual����ζ���������ܻᱻ��д,c++�ͻ�֪���ڲ�νṹ�µ�����������ܱ���д�ˡ�,��������������Ҫ����
		//

		//������������һ����鷽���Ĳ�ͬ��
		//�鷽�� �ǵȴ�����д,��д��ֻ���ø�д��ķ���
		//��������������������������һ�𱻵��� ,�ȵ��������������������������� 
		LOG("-------------------------------");

		//deriver* in4 = new base;
		

	}
	LOG("part49:c++��������ת��")
	{
		//casting ������ָ������ת�� ,�����һ��
		
		//c����
		double a = 3.2;
		int	b = (int)a + 5.6; //ȥβcast
		LOG(b)
		//c++����
		//���Ǻ�c��������û�������������,ֻ��ϸ����c��ת�����Ͳ���ʽע��,���������ڱ���ʱ���������(�������͵�)ת���ܷ�ɹ�
		//����c++������ת����������������,���ٴ���,��������
			// ����cast static_cast reinterpret_cast dynamic_cast const_cast
			//�����﷨�Ƕ���,c������ static ��̬ת�� reinterpret ˫��(�ı�ָ������,�ؽ����ڴ�,������д�ڴ�����) const (�ƹ�)/������const
		
			//static_cast:��������ʽִ�е��κ�����ת����������static_cast�����,һ��ת��
		int s = static_cast<int>(a) + 5.6;
		LOG(s)
			//double ca = reinterpret_cast<base*>(&a)+3.3; //static_cast<base*>(&a);��Ч,�˴�ӦΪһ��˫��
			//dynamic_cast:������֮��ת��,���Ҷ�̬���?
		base* devi = new deriver;
		anotherclass* ac = dynamic_cast<anotherclass*>(devi);
		//����ac�ǿյ�,deviָ�����deriver,dynamic_cast������ʱ����������ת�����������ϵ,��ac��Ϊ��
		anotherclass* ac2 = static_cast<anotherclass*>(devi);
		//ac2��Ϊ�� static_cast��ֻ��ɵ�����ذ�ָ�븳��ac2
		deriver* dc = dynamic_cast<deriver*>(devi);
		//dc����,dynamic_cast����ת��

		//cherno: ��֪��c++��ת���ܺ�,�������޷�����cת��

		std::cin.get();


	}
}
#include<iostream>
#include<thread> //���� �߳�.... �ƺ�chrono��ʵ�ֱ��ƶ����� thread
//#include<chrono> //���� timer


#define LOG(x) std::cout<<x<<std::endl //std::endl�ƺ��е���??

static bool if_enter=false;

void DoWork()
{
	
	LOG("�߳̿�!");
	while (1)
	{
		using namespace std::literals::chrono_literals; 
		//����Ϊ�� 1s �ܱ�sleep_for���,�����˲�����""s ,""h��
		LOG("�߳�2~:����ûس�!!"); //�����һֱ������ٶȸ���Щ��,����̻߳��cpuռ���ʸ㵽100%
		std::this_thread::sleep_for(0.5s);
		std::this_thread::sleep_for(std::chrono::milliseconds(500)); //0.5��

		//std::this_thread ��ǰ���̵�һЩ����,�������Ƶ�ǰ����
		//get_ID
		std::cout << "now the thread's id is: " << std::this_thread::get_id() << std::endl;
		if (if_enter) break;
	}
	
	LOG("�߳̽�����");
}

struct Timer
{
	std::chrono::steady_clock::time_point start ,end;
	std::chrono::duration<float> duration;  //nano������??
	Timer() {

		start = std::chrono::high_resolution_clock::now();
	}
	~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start; //  /s
		float durms = duration.count()*1000.0f;
		LOG("it live for " << durms << "ms");
	}

};

int main()
{
	auto start = std::chrono::high_resolution_clock::now();
	LOG("part42:�߳�");
	{

	//�ü���� ͬʱִ�ж���ָ�� ,
	//����֮ǰ���ǵĴ��붼��˳��ִ�е�,һ��std::cin.get()���ܶ���,��Ϊ����ͣ�µȴ�

	std::thread work(DoWork); //������һ���߳�,ִ�к��� �߳�name(������/ָ��)
	LOG("����ûس�!!");
	// 	while (1)
	// 	{
	// 		LOG("�߳�1~");
	// 	}
	std::cin.get();
	if_enter = true; //��ѭ�������ͬʱ�ȴ�����Щʲô,��������߳���
	LOG("����!!");
	work.join();//�߳�join , һ���߳̽������ص���ǰ�߳�ʱ���д���Ż����ִ��,��,�ȴ��߳̽���
	LOG("�߳��Ѽ���");
	std::cout << "now the thread's id is: " << std::this_thread::get_id() << std::endl;

	//������Լ����߳�ʵ��һ�� cin.get() ���������̵߳�����

	//�߳̿��Ժܸ���
	}

	LOG("part43:��ʱ");
	{
		//std::chrono Ϊ��׼�㱨ʱ~
		//chrono C++std�ṩ�ľ�ȷ��ʱ�� ,�ڴ�֮ǰ��Ҫ����ϵͳ������þ�ȷ��ʱ
		LOG("��ʱ��ʽ1");
		using namespace std::literals::chrono_literals;
		auto start=std::chrono::high_resolution_clock::now(); //
		std::this_thread::sleep_for(1s);
		auto end = std::chrono::high_resolution_clock::now();
		//���ּ�ʱ��ʽ���б�����,���Ƿǳ�׼ȷ

		std::chrono::duration<float> durat = end - start;
		LOG(durat.count());

		{
			LOG("��ʱ��ʽ2");
			Timer time;
			std::this_thread::sleep_for(1s);
		}


	}

	LOG("part44:��ά����");
	{
		//��ά��ʵ�� �ø�ά������Ԫ�ر�ɵ�ά�������ָ��,����γ�������Ԫ���ǵ�ά�������ָ��
		int* array1 = new int[10]; //һ��int 4�ֽ� ,���� 40�ֽ��ڴ�
		int** array2 = new int*[10]; // һ��* 4�ֽ� , ���� 40�ֽ��ڴ�
		//��Ҫ������ʲô���͵�ָ��
		//��ס,��ֻ�Ƿ������ڴ�

		
		for (int i = 0; i < 10; i++)
			array2[i] = new int[10];

		//ɾ��������������Щ�鷳, delete[] array2 ֻ��ɾ���˶���ָ������,40�ڴ�,������ʧȥ���������ָ���û��ɾ����������ڴ�й©
		//��Ҫɾ��������Ҫ����
		for (int i =0;i<10;i++)
		{
			delete[] array2[i];

		}
		delete[] array2;
		//�����ڴ���Ƭ����,���ڶ������������,��10�����鲻��������,������Ҫ������ȥ���������ά����ʱ
		//�п������cache miss

		//���õķ�ʽ:��װ�Ǹ�ά����
		int* a2d = new int[10 * 10];
		for (int y=0;y<10;y++)
			for (int x = 0; x < 10; x++) {
				a2d[x + y * 10] = 2;
			}
		//Ҳ������Խ�����Ȼ���ع�һ�� []����

// 		int*** array3 = new int** [10];
// 		for (int i = 0; i < 10; i++)
// 		{
// 			array3[i] = new int* [10];
// 			for (int j = 0;j < 10;j++)
// 				array3[i][j] = new int[10];
// 			//�����������
// 		}

	}
}

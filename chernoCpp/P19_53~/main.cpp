#include<iostream>
#include<chrono>
#define LOG(x) std::cout<<x<<std::endl

class entity
{
public:
	virtual void printname(){}	

};
class player :public entity
{


};
class enemy:public entity	 
{

};


class Timer
{
public:
	Timer()
	{
		m_start=std::chrono::high_resolution_clock::now();
	}
	~Timer()
	{
		stop();
	}
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
	void stop()
	{
		auto end = std::chrono::high_resolution_clock::now();
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start).time_since_epoch().count();//microsecond ΢��
		auto stop = std::chrono::time_point_cast<std::chrono::microseconds>(end).time_since_epoch().count();//microsecond ΢��
		auto duration = start - stop;
		auto ms = duration * 0.001;
		LOG(duration << "/us(" << ms << "/ms");

	};
};
int main()
{
	LOG("part53:dynamic_cast��̬����ת��");
	{
		//�ؼ̳в�νṹ���е�ǿ������ת��
		//�����ں��� , ��������ʱ����ת���ж�,����㲻����д����ʱ�õ�����
		//dynamic_cast �Ĳ��������������̬������(ȷ���������������д),�������麯����()

		//����ת���� ����,��ͬʱ���ǻ���
		//����ת����(��ʽת��������ͨ��) �п��ܲ���,���ǲ�֪���������ָ��ָ���ڴ��ǲ�������,����������ָ�����ʵ����һ������(�������,���ʲ����ڵĳ�Ա�ᵼ�±��� )
		//���ڴ�������Ҫdynamic_cast����(ת��)�ж�,�ж�ָ���ڴ��Ƿ���ָ������ ������ؿ�ָ��,��ô����
		
	
		entity* actualplayer = new player;
		enemy* ene = (enemy*)actualplayer; //�㿴,��Σ��,û����

		enemy* ene1 = dynamic_cast<enemy*>(actualplayer);
		if (!ene1)
		{
			LOG("actualplayer cant cast to enemy");
		}
		player* pla = dynamic_cast<player*>(actualplayer);
		if (pla)
		{
			LOG("actualplayer can cast to player");
		}
		if (dynamic_cast<player*>(actualplayer)) //��ò�Ҫ��ô��...�ж�һ��û��Ҫ���˼�����,�����������ȸ���ֵ���ж�
		{
			LOG("actualplayer is player"); //c#����� actualplayer is playerֱ���ж�
		}
		//dynamic_cast����(����)�ж�
		
		//dynamic_cast ֮����֪������Ϊ ��ʹ��������ʱ��������Ϣ rtti 
		//������ rtti�� ��Ŀ���� c++ ���� ��ص� dynamic_cast ���ò�����	
	
	}
	LOG("part54:��׼(����)����"); {
		//cherno��timer
		{
			Timer timer;
			int i = 0;
			for (int j = 0; j < 10000; j++)
				i += 2;
		}
		//Ҫע�����,��releaseģʽ��,�����Ĵ����ڱ����ᱻ�Ż�����Ŀȫ��,�����������ʱ������Ǻ��������,��Ϊ���Ǹ���û����д����
		//����ֻ��release�µĲ��Բ���Ҫ,��Ϊ�㲻����debug�·�����Ŀ
	}
}
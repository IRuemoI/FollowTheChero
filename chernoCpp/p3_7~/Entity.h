#pragma once
#include <iostream>
class Entity
{
private:
	Entity(int vx,int vy,int vz,int vw) 
	//���������԰ѹ��캯���ص�private��,������Ͳ�����ĳ�ַ���ֱ��ʵ����
	{
		x = vx;
		y = vy;
		z = vz;
		w = vw;
		std::cout << "but you can't!" << std::endl;
	}
public:
	float x, y;//float 4 bites
	float z, w;
	~Entity() {//��������
		std::cout << "entity is being deleting num:" <<x<< std::endl;

	}
	Entity()//���캯��������ͬ�� ,Ĭ�ϴ��ڵĹ��캯�������޲ε�
	{
		z = 0.f;
		w = 0.f;
	}
	//���Զ��������캯���Խ�������
	Entity(int vx, int vy) 
	{
		x = vx;
		y = vy;
	}
	Entity(int vx, int vy, int vz) = delete;//ֱ��ɾ���������,��Ȼ�㲻д��Ҳ������


	void print() {
		std::cout << x << "," << y << std::endl;
		std::cout << z << "," << w << std::endl;
		 

	}
	void Init() {
		x = 0; y = 0;
	}

};


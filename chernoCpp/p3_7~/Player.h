#pragma once
#include "Entity.h"//�̳���Ҫ��ǰ�ļ����������


//Playerͬʱ��Player��Entity��������
class Player:public Entity
{
	//Entity�����в���private�ĳ�Ա������playerʵ���б�����
public:
	const char* name; //char point 4bites
	void Printname() {
		std::cout << name << std:: endl;
	}

};


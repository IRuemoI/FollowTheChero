#include <iostream>



class Printobj {
	//��Ϊ��ֻ������һ�����麯��,���ǽ����ӿ�(�������Ѻ��д��麯�������Ϊ������)
	//�������඼��Ҫ�̳����������һ������ʹ��Ȩ,�����ø���ĺ����ĳ���
	//(����������interface,��c++����Ȼֻ�������)
public:
	virtual std::string GetClassName()=0;
	//virtual std::string TotalVir() = 0;//����һ�����麯��
};

class Entity:public Printobj{
public:
	std::string Getname() {
		return "Entity";
	}
	virtual std::string VirGetname() {
		return "Entity";
	}
	std::string GetClassName()override {
		return "Entity";
	}

};

class Player :public Entity//Entity�Ѿ�ʵ���˴��麯��,���playerû��д�Լ����麯���ͻ��Ҽ̳е�
{
private:
	std::string m_Name; // std::string = const char*
public:

	Player(const std::string& name)
		:m_Name(name){}
	std::string Getname() { return m_Name; }
	std::string VirGetname() override { return m_Name; }
	//������override�����д���麯��,����ⲻ��һ���麯����ᱨ����ʾ��
	//override����Ҳ����,��ֻ�Ǳ��
	std::string GetClassName()override {
		return "Player";
	}
};

void PrintName(Entity* entity) {
	std::cout << entity->Getname() << std::endl;
}
void VirPrintName(Entity* entity) {
	std::cout << entity->VirGetname() << std::endl;
}
void Part(int x, const char* name) {
	std::cout << "<=================="
		<< "Part" << x << ":" << name << "==================>" << std::endl;

}
void PrintClass(Printobj* obj) {
	//ֻ����ָ��,��֤�˽����Ĳ�����GetClassName()��һ����
	//���������ƺ���,ĳЩ��������ͨ��Ҫ����ĳ�ֺ��������Ľӿ����ָ��
	//�����ĳ�����к�����ʹ�ñ�֤,����GetClassName
	std::cout << obj->GetClassName() << std::endl;
}


int main() {
	Entity* e = new Entity();
	PrintName(e);
	Player* p = new Player("rabit");
	PrintName(p);
	//��ָ�����;�����������ͬ�������Ĳ��ҷ�ʽ,���Һ�ָ��������ͬ����ķ���,Ȼ��������/����
	//����ָ������,�ڲ��ҷ���ʱ,ʹ������Entity�ķ���,�β�=(��ֵ)ʵ��
	//�����Ǹ���ʵ��ָ�������,ʹ������player�ķ���
	//���������Ҫ����������ָ�����ݶ�̬ѡ��ʹ�ú���(��д),Ҫ���� ��� ,
	//�������е�ԭ��������Ϊ�麯��(ʹ���麯���ж��⿪��)
	Part(9, "�麯��");
	VirPrintName(e);
	VirPrintName(p);

	Part(10, "���麯��");
	//���麯��,û��ʵ��/����,ֻ������,ֻ��������������ʵ��
	//�������麯���Ļ����޷�ʵ����(���Ƴ��???),ûʵ���麯��������Ҳ����
	PrintClass(e);
	PrintClass(p);




}
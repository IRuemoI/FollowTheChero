#include<iostream>
//part7:enum
#include "Player.h"
// const static int A = 0; //ABCδ������,�������������ɸ���
// const static int B = 1;
// const static int C = 2;
// 
// int main() {
// 	int value = B;//value���Ա�������ֵ,���������ж�,����ЩΣ��
// 	if (value==B) {
// 		//do smthing
// 	}
// }

class Log
{
public:
	enum Loglevel//���������ڶ���:�����������ռ��ڵ�ö������
	{
		LogLevelError = 0, LogLevelWarning, LogLevelInfo,
		//error
		//����ö�ٲ��ܺͷ���ͬ��,һ��Ὣö������Ϊ ����+����
	};
private:
	Loglevel m_Loglevel = LogLevelInfo;//m_��ʾ����һ��˽�б���,Ĭ���κ���Ϣ���ᱻ��ӡ
public:
	void setLevel(Loglevel level) {
		m_Loglevel = level;

	}
	void error(const char* mesg) {
		if (m_Loglevel >= LogLevelError)
			std::cout << "[ERROR]:" << mesg << std::endl;
	}
	void warn(const char* mesg) {
		if (m_Loglevel >= LogLevelWarning)
			std::cout << "[WARNING]:" << mesg << std::endl;
	}
	void info(const char* mesg) {
		if (m_Loglevel >= LogLevelInfo)
			std::cout << "[INFO]:" << mesg << std::endl;
	}

};

void function() {
	Entity e(10,1);
	e.print();
}
enum Example:unsigned char //����ָ��ö�ٵ���������(������8λ)
{
	A, B, C ,D=6,E
	//0,1,2,6,7 ʵ��ֵ,���������ж�,���԰����ǵ�������
};
int main() 
{
	Log log;
	log.setLevel(Log::LogLevelInfo);//��Ҫ��������(�����ռ�)
	log.info("<===========part7:enum===========>");
	Example value = B; //��ֵֻ����ABC
	if (value==1) {
		//do smthing
	}
	log.info("<===========part7:���캯��===========>");

	log.info("���캯��,ÿ������һ��ʵ��ʱ�ͻᱻ����");
	log.info("�ǵó�ʼ��!");
	Entity e;
	e.print();
	//��ʵ��û�г�ʼ��������������ֵ(ֻ�����˵�ַ,û��д������)
	//,����print��������,�������ֱ�ӷ���e.x/y���벻��ͨ��
	e.Init();
	e.print();
	Entity E(3, 4);
	E.print();
	//����ʹ�þ�̬����ʱ,���캯��������ִ��,��Ϊ��û�д���ʵ��
	//new Ҳ��ʹ�ù��캯��
	
	//����ֱ�Ӳ���ʵ����,ֻ��������ľ�̬����
	//Entity ea(3, 4, 5, 6); //����

	log.info("<===========part7:��������===========>");
	log.info("��������,ÿ��ɾ��һ��ʵ��ʱ�ͻᱻ����");
	log.info("һ���Ǿ�̬�ı���,����������ͨ�������ں����ӽ��뵽���ص�ʱ��");
	log.info("������������һ��,����Ҫɾ����ʼ����ֵ,����й¶");
	log.info("������ʼ����ʵ����Ա�ڶ���,��ô����Ҫ���������ֶ�ɾ����");
	log.info("������ֶ�������,������ô��,��ֻ�ǵ���ִ��һ�麯��,�ڱ�ɾ��ʱ����ִ��һ��");
	//����Ϊ����ʾʹ��funtion
	function();//ɾ��������ʵ�� 

	log.info("<===========part8:�̳�===========>");
	log.info("�����Ǹ���ĳ���,���������Ҫ����ĵط�ʹ������");
	log.info("�������д�������游�෽��");
	Player player;
	player.x=2;
	player.print();
	std::cout << sizeof(Player) << std::endl;


	

}
//��һ�к�ʼɾ��֮ǰ������entityʵ��
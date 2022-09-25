#include "Player.h"
#include "Log.h"
#include "sta.h"


int si_sta = 10;//��static int si_staͬ����ȫ�ֱ���
extern int exi_sta;//�� sta.cpp�� int exi_staͬ����ȫ�ֱ���,����extern��ȥ����ʼ����,���������ҵ�exi_sta,��ʹ��� exi_sta��Ϊsta.cpp�е�exi_sta������
//�ⱻ��Ϊ external linking,������Ҳ���ͬ���ķ�externȫ�ֱ���,��ᱨ��
//����ʵ��
void function_sta();//����ͨ��

int x = 10;


//ʹ���� ��̬��ʵ��
class Singleton {
public:
	static Singleton& Get() {
		static Singleton instance;//��ʹ��������Get()��,��Ȼ�����ʹ��ָ����ʵ��,����������鷳
		return instance;//�������������ʵ���ĳ�Ա�뷽��
	}
	void hello() {
		std::cout << "Singleton:hello" << std::endl;
	}
};
void main() {
	Log log;
	log.info("<==================part5:class==================>");
	log.setLevel(log.LogLevelWarning); //��д��main�ڴ���,ȷ������,�ɴ˷���log�����ôʵ��
	log.warn("hello"); //��������ʾ,,�ַ�����Ϊʵ������Ϊconst char* ������ַ���������??
	log.error("hello");
	log.info("hello");
	Player player;

	log.setLevel(log.LogLevelInfo);
	log.info("<==================part6:static==================>");
	log.info("si_sta:"); std::cout << si_sta << std::endl;
	log.info("static�������ǽ�һ��������Ϊ��̬(�������ڱ䳤,��ַ�㶨)����������λ���趨������");
	log.info("������,static �õ�Խ��Խ��,��Ϊ������ڴ�����ͬ�������뺯��(ͬ����)��ȫ����,�ǳ��������ͻ,���߲�֪�������ı���ֵ");
	log.info("����Խ�������ͷ�ļ���,����ÿ����������cpp������һ��������private���Լ��ı�������");
	//sta st = { 2,3 }; //������
	sta st;
	st.x = 3;
	st.y = 5;
	st.print();//������
	sta::x = 4;//�������ʹ�����ַ���
	st.print();

	log.info("<==================part6:static-����������������==================>");
	Singleton::Get().hello();
	//part7~��p7

}

//������:�����е�static���� �����ֲ���̬����
void function_sta() {
	static int i = 0; //���޶�����������function_sta��
	//��һ�α�ʹ�ó�ʼ��,�����ᱻɾ��,��������������������
	int j = 1;
	i++;
	std::cout << "j: " << j << "i: " << i << std::endl;
}





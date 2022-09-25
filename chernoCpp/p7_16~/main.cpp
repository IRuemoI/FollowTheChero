#include<iostream>

class Entity
{
private:
	std::string m_Name;
	mutable int m_DebugCount = 0;
public:
	const std::string& GetName() const
	//��const������ԭ��,������������,���õ��ĳ�Ա������һ��const
	{	
		m_DebugCount++;
		//mutable����ʵ�ʸı��������,����const��ͬ,
		//�������ñ����ӹ�const������������const������
		//����˵��������const�����Ĺؼ���
		return m_Name;
	}
protected:

};



void main() {
	//16 mutable �ؼ���
	const Entity e;
	e.GetName();

	//�õ�mutable����һ���ط�,lambda,����һ���Ե�С����,���Ը�������
	int x = 0;
	auto f = [=]() mutable{
		x++;//mutable: int x = 0;x++;
		std::cout << x<<" lambda hello!" << std::endl;
	};
	//[&] ����,�����& �Ծֲ������������ò���õ� &x , &e
	//[=] ����,����� = ,�Ծֲ��������а�ֵ���ݵõ�x,e��ֵ,��һЩ����
	//����=��ֻ���޶�,������lambda����mutable,ʹ�ÿ����޸�
	//(ʵ���Ǵ�����ͬ���ľֲ���������Ӧ��ֵ),������Ӱ������ı���
	f();
	//��ƽʱ������lambda�õ�mutable��
	
	std::cout << x << std::endl;

}
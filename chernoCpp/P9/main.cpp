#include <iostream>

using String = std::string;



struct Vector2
{
	float x, y;
	Vector2(const float& ix, const float& iy)
		:x(ix), y(iy) {}
	//for math  ,reload
	Vector2 operator+ (const Vector2& other) const //���������Ǻ���,
	{
		return Vector2(x + other.x, y + other.y);
	}
	Vector2 operator* (const Vector2& other) const //����Էֿ�����,дһ��multiple�ĺ���Ȼ���������е�����
	{
		return Vector2(x * other.x, y * other.y);
	}
	bool operator== (const Vector2& other) const
	{
		return x == other.x && y == other.y;
	}
	bool operator!= (const Vector2& other) const
	{
		return !(*this == other);
	}
};

std::ostream& operator<<(std::ostream& stream,const Vector2& vec ) //��vector2��ϵ����,�ҹؼ���std��
{
	stream << vec.x << "," << vec.y;
	return stream; //���ó����ý�,ֻ�ǽ�����һ��ʱ��:)

}

//��ʵ���ڵ����ⲿ����,����Ҫʵ����ԱʱҲ��Ҫthis
//������ʵ��һ���õ��ಢ�һ�������ʹ�õĺ���,
//һ,�����Ķ��������class����֮��,��Ȼ����������,
//��,��������������class֮ǰ,��Ȼ�����޷�ʹ��,
//��,���������õ���,��Ҫ������ǰ������

class Entity;//ܳ!������
void PrintEntity(const Entity& e);
class Entity {
public:
	int x, y;
	Entity(int x,int y ) // һ���㶨����һ������,�Ͳ�����Ĭ�Ϲ��캯����
	{
		//Entity* const & e = this; //this �� Entity* const ����ûд����,������ı�thisָ��,������Ҫ���õĻ�Ҳ��const,��֤�����дthisָ��  ��˵һ��,&���ó�ʼ�����ǲ���������������������,�൱���Ѿ��� *const(�μ�ֻ����һ������)
		// Entity* e = this; �����ôд,��Щ,��Ȼ����һ��ָ�� 
		//��ȻҲ���Բ�д,ֱ����this->x
		//e->x = x;//-> �൱�� *p. �����üӷ��ʳ�Ա
		//e->y = y;

		this->x = x;//��Ϊͬ��,û����ʽ���ʳ�Աx���޷���ֵ
		this->y = y;//д��ָ��� . ���Զ����� ->
		PrintEntity(*this);
		//this,�ڶ��� ,��Ҫdelete this, ʵ���ᱬը
	}

	int GetX()const
	{
		const Entity* e = this; //����ͬ����Ҫ����const ,��ֹ�����ܹ��ı����ʵ��,�����this Ҳ��������const�ĳ��� const Entity* const����
		return e->x;

	}


	~Entity() {
		std::cout << "�ߺߺ߰�����������" <<x<<y<< std::endl;
	}

};
void PrintEntity(const Entity& e) {
	std::cout<<e.x<<","<<e.y<<std::endl;
}
int* CreateArray() {
	int Carray[50];
	return Carray; //ָ��ȷʵ������,��ָ��ĵ�ַ���ͷ���
	//���������,1,��heap�ϴ��� 2,���ⲿ����,ʹ�ú����Ա������в���
}

class scopeptr
{
private:
	Entity* m_ptr;
public:
	scopeptr(Entity* ptr)
		:m_ptr(ptr) {}
	~scopeptr()
	{
		delete m_ptr;//ɾ��ָ������
	}
};

int main() {
	std::cout << "Part22:������,����" << std::endl;
	{	
	//����,������,С��ʹ��,ͨ����дһЩ�Ƚϵײ�����ͺͰ�ʱʹ��
	Vector2 position = { 330,345 };
	Vector2 speed = { 2,2 };
	Vector2 position1 = Vector2(3, 4) * speed + position;
	//����һ��vector2 ,���������Ǳ���,����һ������,��˲��ܱ�����
	// << ���Ʋ���������
	std::cout << position1 << std::endl;
	bool test = true;
	std::cout << (position1 == position) << std::endl;//�������Ż��Ϊostream& == Vector2
	} 
	//��ջ֡

	std::cout << "Part23:this" << std::endl;
	{
		//this��һ��ָ��ʵ�������ʵ������ָ���Ա,���ǿ���ʹ����������(������һ����Ч������õĺ���)
		//��class Entity
	}
	std::cout << "Part24:stack" << std::endl;
	//������: {} if{} class{}.... "{}"�ʹ���һ��������,���ڴ�����ջ���һ��ջ֡(�ṹ),����һ�������������pushһ��ջ֡(����),push��Ͷ��������ջ����
	{
		Entity e0(1,2);
		Entity* e1 = new Entity(3, 4);
		scopeptr e3 = new Entity(11, 45);
	}
	//std::cout<<e1<<std::endl //e1,��ջ�ϵ�ָ��,ͬ���ᱻɾ��,����e1ָ��Ķ��ڴ治��
	//��ʵ�ֺ���ʱ�м���һ��
	//������ָ��,������İ�װ���Զ�����������delete���ϵĶ���; scopeptr



}
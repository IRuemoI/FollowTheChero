#include <iostream>
#include <memory> //smart ptr

class Entity
{
public:
	Entity()
	{
		std::cout << "Created Entity" << std::endl;
	};
	~Entity()
	{
		std::cout << "Destroy Entity" << std::endl;
	};
	int a=1;
};

class String
{
private:
	char* m_Buffer;
	unsigned int m_size;
public:
	String(const char* string)
	{
		m_size = strlen(string);//strlen����\0��ֹ��, strcopy��һ����\0
		m_Buffer = new char[m_size+1];
		memcpy(m_Buffer, string, m_size);
		//�����ڴ� ,const void* �� void�����κ��������� 
		//����string��ǰm_sizeλ
		m_Buffer[m_size] = 0;
	}	
	friend std::ostream& operator<<(std::ostream& stream, const String& string);
	//friend �����ⲿ���������ڲ�private��Ա
	~String() {
		delete m_Buffer;
	}
	char& operator[]( const unsigned int& index ) {
		return m_Buffer[index];//û��,[]�ķ��ؾ���char&
	}
	String(const String& other)//����������ǩ����ʽ
		:m_size(other.m_size)
	{
		std::cout << "copy happened" << std::endl;
		//memcp(this,&other,sizeof(String)),Ĭ�Ͽ������캯��,�㻹����д��m_Buffer(),m_size(),
		//ɾ����������,�������� , String(const String& other) = delete;
		m_Buffer = new char[m_size + 1];
		memcpy(m_Buffer, other.m_Buffer, m_size + 1 ); // ������sizeof(other.m_buffer)��ֻд��4�ֽ�,��Ϊ����ָ����,��sizeof(*other.m_Buffer)Ҳ��
	}

};

class smartPtr
{
	Entity* m_obj;
public:
	smartPtr(Entity* obj)
		:m_obj(obj)
	{

	}
	~smartPtr() {
		delete m_obj;
	}
	Entity* operator->() {
		return m_obj;

	}//Ϊ������smartptr ָ�������ָ��һ��ʹ��->,�����ع�

};

struct Vector3
{
	float x, y, z;
};
std::ostream& operator<<(std::ostream& stream, const String& string)
{
	stream << string.m_Buffer;
	return stream;
}

void PrintString(const String& string)
{
	std::cout << string << std::endl;
}

int main() {

	std::cout << "part25:smart Ptr" << std::endl;
	//������smartptr QAQ,�Զ������ڴ�
	//unique ptr �������Զ�����,�㲻�ܸ���uniqueptr,�����ڴ��ǰ󶨵�
	//���Ŀ����ܵ�
	{
		std::unique_ptr<Entity> entity(new Entity()); 
		//������= new Entity() ,����Ҫ��ʽ���ù��캯��,��unique_ptr�Ĺ�����explicit
		std::unique_ptr<Entity> e1 = std::make_unique<Entity>();
		//��һ�ֳ�ʼ������,����ȫ,��õ�
		//std::unique_ptr <Entity> e2 = e1;
		//����,uniqueptrû�п������캯��,��������,���������
	}
	//shared_ptr ����ָ��,weak_ptr ��ָ��
	{
		std::shared_ptr<Entity> e1 = std::make_unique<Entity>();
		//shared_ptrָ����Ҫ����!����������ʱ���ü�����1,����ʱ�����Լ����ü�����1;
		//�����ü�����0ʱ�ͷ��ڴ�
		std::shared_ptr<Entity> e2(new Entity());
		//��Ҫ������ʼ��,�⽫�ѷ���new Entitty �� ���ü����Ŀ��ƿ� ��Ϊ��������,����Ч��

		//ָ�����
		std::shared_ptr<Entity> e3;
		{
			{
				std::shared_ptr<Entity> e4 = std::make_shared<Entity>();
				e3 = e4; //���ڴ�����:2
			}//e4 godie,e3 alive �ڴ�����:1 !=0 ,�ڴ���
			
		}
	//weakptr ��ָ��, ��������sharedptr������,����ָ��,���žͻ���,���˾�����
		//�����ѯ��weak ��ǰ�ڴ��Ƿ���/����
		std::weak_ptr<Entity> e4 = e3;
		//�ڴ�������Ϊ1;

	}

	std::cout << "part26:�����뿽�����캯��" << std::endl;
	//���ⲻ��Ҫ�Ŀ���
	// = ��ֵ������,������*����ֵ*
	{
		String string("They are SB"); 
		String second = string; 
		//�������!! //ǰ���ǰ�д�Ŀ������캯��ע�͵�0.0
		//char* m_Buffer ��������seconde m_Buffer ,���Ǵ���ͬһ���ڴ�
		//delete m_Buffer ��ζ���ͷ�ָ���ڴ�
		//������String������ִ����������ʱ,m_Bufferָ���ͬһ���ڴ�Ҫ���ͷ�����
		//�ڶ����ͷ�ʱ,��������Ϊ���Ѿ������,�����ٴα�����������
		//�������˱���
		//���������˵��,ǳ����,ֻ������ָ��
		second[9] = 'N';
		
		PrintString(string); PrintString(second);
		//����������Ҫ��д-�������캯�� , �����ڸ�ֵʱ���õ�һ�ֹ��캯��,ʹ����ʹ�������ʽ
	}
	std::cout << "part27:��ͷ������->" << std::endl;
	{
		//˵���� 
		Entity e;
		Entity* ptre = &e;
		ptre->a; //���� (*ptre). �����üӷ��ʳ�Ա

		smartPtr entity = new Entity;
		entity->a;//�㿴

		//Ϊ��smartptr �ع� ->������
		//ʹ��->�õ�ƫ���� ,�ż�

		int py = (int)&((Vector3 *) 0)->z; //��ȡ��0��ַ��ʼƫ�Ƶ�x�ĵ�ַ��д��int ,�õ�ƫ����
		std::cout << py << std::endl;

	}
}
//cherno ���� :����ʹ��const���� ȥ���ݶ���
//��������ֻ��������
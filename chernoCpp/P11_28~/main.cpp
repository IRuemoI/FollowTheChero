#include <iostream>
#include <vector>

struct Vertex
{
	float x, y, z;
	Vertex(float ix, float iy, float iz)
		:x(ix), y(iy), z(iz)
	{
	}
	Vertex()
		:x(0), y(0), z(0)
	{
	}

	Vertex(const Vertex& other)
		:x(other.x) , y(other.y) , z(other.z)
	{
		std::cout << "Vector<Vertex> is copying" << std::endl;

	}
	~Vertex()
	{
		std::cout << "delete V" << std::endl;
	}
};

std::ostream& operator<<(std::ostream& stream, const Vertex& vertex)
{
	stream << vertex.x << "," << vertex.y << "," << vertex.z << "," ;
	return stream;
}

int main()
{
	std::cout << "part28:��̬����" << std::endl;
	{
		//������׼��ģ��� vector ,��������Ƕ�̬���� ??? ���ø��������С ʵ������ɾ���ɵ�,��һ���µ�
		//��׼��Ķ������,����������,���ʱ��Ϊ���ٶ���Ҫ�Խ���׼����EASTl
		std::vector<Vertex> vertics; // ���� <Ԫ������> ����ģ�� vertics �洢��һ���ڴ���,����һ��,�����ȽϿ�
		//��ʱ��ָ����ΪԪ������,���������ԭʼ���ݽ��и���,���ʡ�ܶ���Դ
		//cherno���� : ����ʹ�ö��������ָ�� ,ָ����������ѡ��
		vertics.push_back(Vertex(1, 2, 2));  //��ĩβ���Ԫ��
		vertics.push_back({ 1,1,4 });   //vector �� size����

		for (const Vertex& v : vertics) // ����,������, c++��in Ӧ���� const Vertex& v = vertics[i]
		{
			std::cout << v << std::endl;
		}
		//vertics.clear();//���vertics
		vertics.erase(vertics.begin() + 1); // ��Ƥ����erase ɾ���ڶ���Ԫ�� ,���Ĳ����� vector<vertex>��const_iterator һ�����������
		for (int i = 0; i < vertics.size(); i++)
		{
			std::cout << vertics[i] << std::endl;
		}//д����ʱ���⸴��!!!

	}
	std::cout << "part29:��̬����2" << std::endl; //��ĵ�һ���Ż�
	{
		{
		std::vector<Vertex> vertics;//vertics δ���峤�ȵ�vector����Ϊ��,�κ������Ϊ����Ҫɾ�����½�
		vertics.push_back(Vertex(1, 2, 2));  //vertics ����+1��λ , Vertex(122)��ջ�ϱ����� Ȼ�� �����Ƶ��µĿ�λ�� ���ÿ������캯�� ,
		vertics.push_back(Vertex(3, 3, 4));	//vertics ����+1��λ , vertex(122) �����Ƶ���vertics , vertex(334)�����Ƶ�����¿�λ,���ÿ������캯��*2
		}
		//�Ż�1:ֱ����vector�ķ����ڴ��ﴴ��Vertex���⸴��
		//�Ż�2:��ǰ����Vector������,��ĳ����֮ǰ����Ҫ������+1
		std::cout << "part29:��̬����2_�Ż���" << std::endl;
		std::vector<Vertex> vertics;
		vertics.reserve(3);//Ԥ��Ԫ�ؿ�λ���� 3 , �㲻��std::vector<Vertex> vertics(3):�ⲻֻ�Ƿ����ڴ�,�����Թ�����3��vertex
		vertics.emplace_back(1, 2, 2);//���ݹ��캯���Ĳ����б� , �� vector�Լ�������Щ��������Vertex
		vertics.emplace_back(3, 3, 4);
		vertics.emplace_back(4, 4, 5);

	}




}
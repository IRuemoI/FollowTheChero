
#include <iostream>
#include <tuple> //tuple
#include <functional> // make_pair()


// void print(const char* string) {
// 	std::cout << string << std::endl;
// }
// void print(int x) {
// 	std::cout << x << std::endl;
// }
// void print(float x) {
// 	std::cout << x << std::endl;
// }

//ȷʵ�����ں�
template<typename T> //����ѡ��typename ��Ϊģ���������(getxtypename),T��Ϊ���� ����class��typenameͬ�� ,��Ҳ����д��<class T>
void print(T value)
{
	std::cout << value << std::endl;
}

//template��������
template<typename T,int N> //T ��type,����� N ����һ���갡
class array
{
private:
	T m_array[N];
public:
	int getSize() {
		return N;
	}

};


std::string getString() {

	std::string s = "smttz";
	return s;
}
int main()
{
	std::cout << "part33::�෵��ֵ������" << std::endl;
	{
		
		//1:�������ָ��/���õĶ෵��ֵ������,���ⲿ�������и��� the cherno: ��Ŀ���������outǰ׺,������֪���ı�(���)������Щ����
		//2:���෵��ֵ�����ַ��� ���� return new std::string[] {string1,string2 }; //���㲻֪�������
		//3:����std::array ; �����return�ƺ����԰�������return������Ϊջ����ʱ����ֵ,���Ǳ���Ҫnew�������浽���Ƶ�ʱ��
		//	auto s = getString();
		//std::cout << s << std::endl;
		//4:����std::vector ��array��һ��


		//ͨ�ð취:��ʹ�ǲ�ͬ���͵ķ���ֵҲ��һ�𷵻�
		{
			//tuple     pair
			//tuple Ԫ�� ; ��������Ϊ����,����n��������������������
			std::tuple<std::string, std::string, int> tuplessi((std::string)"smttz", (std::string)"wgnpl", 9);
			//������ʹ�ò�����������:����֮һ,��û��������͵Ķ���,ֻ������
			//pair make_pair ����pair , ֻ�ܰ�����������,����������,����Ҫ��tuple����˵��ģ��, ͬģ��ʵ����pair��tuple�����໥ת��
			auto ss = std::make_pair((std::string)"sd", (std::string)"shit");
			std::tuple<std::string, std::string> tupless = ss;
			//tuple��Ȼ��һ�ֺܷ���Ĵ�ֵ����,�����������ģ��ʵ��ʹ�����Ը��Ƹ�ֵ
			//tuple ȡֵ , ʹ��std::get<Ԫ���±�>
			//pairȡֵ , ͬ������std::get<>,������ .first .second
			std::cout << std::get<0>(tupless) << std::endl;
			std::cout << ss.first << std::endl;
		}
		//ʹ���Խ��ṹ��(�����ǽṹ��) ,����,��Ҫ
	}

	std::cout << "part34:ģ��!!" << std::endl;
	{
		//c++�����


		std::cout << "part34:ģ��!!" << std::endl;
		//templates .�����������������Ƹ���: ����
		//���Խ������Ϊ��,Ԫ���,����ĸ��,�ñ�����������Ĺ�����,һ����ʵ�����Ƶĺ�����������������,����(�ֶ�)����
		//������д�˵��ú�����Դ��ʱ,�������Ż����ģ����ʵ�ʲ����������ɶ�Ӧ����������,��Ȼ������
		//��Ϊ��ʽ�õ�ʵ������ , ���� �������� T;
		print("hello,3Q");
		print(911);
		print(11.4514);

		//�������ʽָ����������
		print<std::string>("thankyou very much");

		//���������������,�Զ�������
		array<int, 6> ar;
		std::cout<<ar.getSize()<<std::endl;


		//template ���Ժ�nb��nb�ܸ��Ӻܸ��� , С��ʹ��,�ʶ�ʹ��
	}

	std::cout << "part35:ջ��ѵıȽ�" << std::endl;
	{
		//ջ��ֻ��һ��cpuָ��
		//���ϵ��� malloc ����һ��ָ�� , ���� cache miss 

		//cherno : ��ջ�����ڴ�,���㲻����ջ����ʱ���ö�
		
	}
	


}
#include<iostream>
#include <Random>

class  Random_SingletonTest
{
public:
	Random_SingletonTest(const Random_SingletonTest& other) = delete; //�����õĸ�ֵ�ᵼ�µ������ơ� -> ɾ�����ƹ��캯��

	static Random_SingletonTest& Get()
	{
		static Random_SingletonTest s_Instance; 
		//��̬��Ա��Ҫ���ⲿ��ʼ��.��Ȼ,��Ϊ�����������ⲿ����Ҳ����,����һ��Getʱ��ʵ���� 
		//�κξ�̬������ֻ��ʵ����һ��,����GetҲֻ���ʼ��һ��

		//Java���и���̬��������, ������ֻ����һ�� ,�Ź�������ǵ�һ��ʵ�����Ż�ִ��,֮��Ͳ�ִ��. �൱����չ��static��Χ

		return s_Instance;
	}; //���ʵ����Ľӿ�


	static float Uint64()  //����ģʽͬ��Ҳ���Լ��ݾ�̬ģʽ,������Ҫ��һ�㾲̬�����İ�װ, ʡ��::Get()  -> ���װ,��������Ҫ���ƹ�ȥ-> ��Ϊɾ��һ�㽻��
		//ͬʱʹ�õ����;�̬ģʽ����, ʹ����������, ���ͨ�������ﵽ��̬�Ͱ�Get�ӵ�private��)
	{
		return Get().IRandomUI64();
	}

private:
	 Random_SingletonTest(); //�������������ⲿʵ����

	 float m_RandomGenerator= 0.5f;


	 std::random_device m_devie;
	 std::mt19937_64 m_random;
	
	 float IFloat() {}; //I: internal ���Ϊ˽�з���
	 unsigned long long IRandomUI64()
	 {
		 return m_random();
	 }; //�����ķ���
	 static Random_SingletonTest s_Instance;//��������


};




 Random_SingletonTest:: Random_SingletonTest()
{
	 m_random = std::mt19937_64(m_devie());
}



 struct AllocationMetrics
 {
	 uint32_t TotalAllocated = 0;
	 uint32_t TotalFreeed = 0;
	
	 uint32_t CurrentUsage() { return TotalAllocated - TotalFreeed; }
 
 };

 static AllocationMetrics s_allocationMetrics;


 struct vec3
 {
	 int x, y, z;
 };

	 void* operator new(size_t size)
		 //���ط�����ڴ��ȫ�������� ::operator new , �Ƚ�ԭʼ�ĵײ�new ,�������Ƿ�����ڴ�İ�װ���������޹�.
		 //�����漰�����ڴ����Ĳ������ᾭ�����new
		 //û������ǰ�ƺ�ʹ�õ����ⲿ�����ƺ�����ʵ�ֵ�,ֻ�ܿ�������
	 {
		 std::cout << "Allocating " << size << " bytes\n";
		 s_allocationMetrics.TotalAllocated += size;

		 return malloc(size);
	 }

	 void operator delete(void* memoery,size_t size ) 
		 // ����Ҫsize ,���ǿ���ͨ��������������ȡ��Ϣ , �������氡(��ʵ����������Ҫ��...,��һ��voidָ��,�����Խ�Ϊ���ܵ�ɾ��ָ�����ʹ�С(sizeof(class))���ڴ�,���Ƕ��ڷ���ʱ����void*���ڴ����Ͳ�֪����)
	 {
		 std::cout << "Freeing  " << size << " bytes\n";
		 s_allocationMetrics.TotalFreeed += size;
		 return free(memoery);
	 }
 

	 static void PrintMemoryUsage()
	 {	
		 std::cout << "Memory Usage: " << s_allocationMetrics.CurrentUsage() << std::endl;
	 }
int main()
{
	PrintMemoryUsage();

	std::cout << "P62:����ģʽ(P82)" << std::endl;
	{
		//cherno��Ϊ�������سƺ������ռ������,����һ�־�̬������ȫ�ֱ�������֯��ʽ
		//��Ҫ��,���������û��Լ�ʵ��������,�ϸ���ƶ���ʵ��,ֻ����һ������ʵ��

		//�������ô�.����˵�����ֱ���������ռ���ŵ���,�ܹ����ع���ʵ��,��ѡ��ر�¶����
		//��Ҫ��¶�ķ���������.h�ļ���,cppʵ��Ҳ��һ��;��
		Random_SingletonTest& s_single = Random_SingletonTest::Get();
		auto& s_single_2 = Random_SingletonTest::Get();
		//or
		uint64_t randomNumber = Random_SingletonTest::Uint64();

		std::cout << randomNumber << std::endl;

		#if 0
				//but
				auto single = Singleton::Get();
				Singleton anotherSingle = Singleton::Get(); //�����õĸ�ֵ�ᵼ�µ������ơ� -> ɾ�����ƹ��캯��
		#endif
	}

	std::cout << "P63:С�ַ����Ż�(P82)" << std::endl;
	//����֮ǰ��SSO
	//cherno���㿴Դ�������
	// 
	//���ö�ջ ���� �ⲿ���� ,��Ҫ�����ײ�����Ҽ�չ��

	std::cout << "P64:�����ڴ����(P83)" << std::endl;
	//����new
	{

		std::string string = "Rabitank";
		auto l_vec3 = new vec3{1,2,3};



		std::unique_ptr<vec3> l_vec3p = std::make_unique<vec3>();
		std::cout << l_vec3p->x << std::endl;

		PrintMemoryUsage();

		void* aBitMemory = ::operator new(32); // ֱ�ӵ���,ǧ��Ҫ����
		int* sup = (int*)aBitMemory;
		// ::��ָȫ��������(ǰ��ɶҲ����)

		delete[] sup,32;//woc,��д��ʲôjb , �����������,������һ��delete[],��û�б�����,����ȷʵ���Լ�sizeɾ����
		//����:void __CRTDECL operator delete[](		void* _Block,	size_t _Size) noexcept;
		//��������������Ӳ����ĸ�ʽ����Ҳ��??

		delete l_vec3;
		// 	size_t size = 15;
		// 	int* x  =  new int(size);
		// 	std::cout << "x: "<<*x << std::endl;

	}

}
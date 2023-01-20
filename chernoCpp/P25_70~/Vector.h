#pragma once

#define LOG(x) std::cout<<x<<std::endl;

template<typename Vector> //���Typename...? ��һ�ּ���,��̬������ϳ���Ȼ���ṩ���� , ��Ӱ�������������������
class VectorIterator
{
public:
	using ValueType = typename Vector::ValueType;
	using PointerType = ValueType*;
	using ReferenceType  = ValueType&;
public:
	VectorIterator(PointerType ptr):m_ptr(ptr){};
	VectorIterator& operator++() //ǰ׺
	{
		m_ptr++;
		return *this;
	};
	const VectorIterator operator++(int)//��׺
	{
		VectorIterator iterator = *this;
		++(*this);
		return iterator;
	};

	VectorIterator& operator--() //ǰ׺
	{
		m_ptr--;
		return *this;
	};
	const VectorIterator operator--(int)//��׺
	{
		VectorIterator iterator = *this;
		--(*this);
		return iterator;
	};

	ReferenceType operator[](size_t index)
	{
		return *(m_ptr + index);
	}

	PointerType operator->()
	{
		return m_ptr;
	}
	
	ReferenceType operator*()
	{
		return *m_ptr;
	}

	bool operator== (const VectorIterator& other) const	
	{
		return m_ptr == other.m_ptr;
	}
	
	bool operator!= (const VectorIterator& other) const	
	{
		return !(*this==other);
	}

private:
	PointerType m_ptr;
};



template<typename T>
class Vector
{
public:
	using ValueType = T;
	using Iterator = VectorIterator<Vector<ValueType>>;

public:
	Vector()
	{
		//allocate 2 elements;
		ReAlloc(2);
	}
	~Vector()
	{
		Clear();

		//���ܻ��Clear,Pop�ظ� , delete[] ����������������λ�õ�����, ��ᵼ��ԭ��Pop��λ�õ�Ԫ�ر��ظ�����.
		//vector3 �е�int* m_memoryBlock���ͷ�����
	}
	void pushBack(const T& element) 
	{
		if (m_size >= m_capacity)
		{
			ReAlloc(m_capacity + m_capacity / 2);
		}

		m_data[m_size] = element;
		m_size++;

	};
	void pushBack(T&& element) 
	{
		if (m_size >= m_capacity)
		{
			ReAlloc(m_capacity + m_capacity / 2);
		}

		m_data[m_size] = std::move(element);

		m_size++;



	};

	

	template<typename... Args>
	T&  emplaceBack(Args&&... args) //ԭ�ع���,�ͻ�������Ҫ�õ�����Ķ���
	{

		if (m_size >= m_capacity)
		{
			ReAlloc(m_capacity + m_capacity / 2);
		}

		new(&m_data[m_size]) T(std::forward<Args>(args)...); //ǰ��ת�� , std::move�Ľ��װ�??�Բ�����ʹ��,����move  ... ��move��չ��
		//���new��placement new ,��ָ����ַ�½�����(ֱ�Ӹ���)...��nb���÷� 
		// ������ m_data[m_size] =  T(std::forward<Args>(args)...) �� move (���Ӧ����m_data�Ѿ�����ʼ��Ȼ�� = �ƶ���ֵ,�����ǿ�������)

		m_size++;

		return m_data[m_size];
	}

	void PopBack()
	{
		if (m_size > 0)
		{
			m_size--;
			m_data[m_size].~T();

		}
	}
	void Clear() //ֻ��ɾ��size���ڵĶ���,���Ƕ�ʵ�ʸ�ֵ��,��Ȼ����
	{
		for (size_t i = 0; i < m_size; i++)
		{
			m_data[i].~T();
		}
		m_size = 0;
	}

	Iterator begin()
	{
		return Iterator(m_data);
	}
	
	Iterator end()
	{
		return Iterator(m_data + m_size);//, sizeof(T));
	}


	T& operator[](int index)  //������ֵ , ���޸�ģʽ
	{
		if (!(index <m_size))
		{
			__debugbreak(); //msvc��debugģʽ�ж�
		}
		return m_data[index];
	}

	const T& operator[](int index) const //ֻ�� , const���͵�array����Ҳ����const���
	{
		if (!(index < m_size))
		{
			__debugbreak(); //msvc��debugģʽ�ж�
		}

		return m_data[index];
	}

	T* Data() { return m_data; }
	const T* Data() const { return m_data; }

	size_t Size() const { return m_size; }


private:
	void ReAlloc(size_t newCapacity) 
	{
		//1. �������ڴ��
		//T* newBlock = new T[newCapacity]; ��Ӧ�ý��й���

		T* newBlock = (T*)::operator new(newCapacity * sizeof(T));
		//����std::String ��,�����ķ�����ܻ��ŵ�����,�Ի�����֮����и�ֵ�����ĸ�����,��û�й������,std::move�������ƶ���ֵ������Ҫ�ĳ�Ա������,���û��ʧ��
		//�����޸���

		if (newCapacity < m_size)
			m_size = newCapacity;

		//2. ����/�ƶ����ݵ����ڴ�
		for (size_t i = 0; i < m_size; i++)
		{
			new (&newBlock[i]) T(std::move(m_data[i])); //�ڳߴ�֮�ھ͵��ƶ�����Ԫ��
		}

		//memcpy(newBlock,newBlock , ) ��������Ϊѡ���˿�����ʽ,��Ҫ��Ŀ������캯��
		//3. ɾ��

		for (size_t i = 0; i < m_size; i++)
		{
			m_data[i].~T();
		}

		::operator delete(m_data, m_capacity * sizeof(T));//��������������������� ��pop,Clear��ͻ,�ظ�����

		m_data = newBlock;
		m_capacity = newCapacity;
	};


private:
	T* m_data = nullptr;
	
	size_t m_size = 0;
	size_t m_capacity = 2; // ���� ���䲢������
};


struct Vector3
{
	float x = 0.f, y = 0.f, z = 0.f;
	int* m_memoryBlock = nullptr; //for test

	Vector3()
	{
		m_memoryBlock = new int[5];
	};
	Vector3(float scale)
		: x(scale), y(scale), z(scale)
	{
		m_memoryBlock = new int[5];
	}
	Vector3(float X, float Y, float Z)
		:x(X), y(Y), z(Z)
	{
		m_memoryBlock = new int[5];
	}
	Vector3(const Vector3& other) 
	: x(other.x), y(other.y), z(other.z)
	{

		LOG("Copy Construct");
	}
	Vector3(Vector3&& other)
		:x(other.x), y(other.y), z(other.z)
	{
		m_memoryBlock = other.m_memoryBlock;
		other.m_memoryBlock = nullptr;

		LOG("Move Construct");
	}
	Vector3& operator=(const Vector3& other) 
	{
		x = other.x;
		y = other.y;
		z = other.z;
		LOG("Copy");

		return *this;
	}
	Vector3& operator=(Vector3&& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;

		m_memoryBlock = other.m_memoryBlock;
		other.m_memoryBlock = nullptr;

		LOG("Move");
		return *this;
	}

	~Vector3() { LOG("Destoied"); delete[] m_memoryBlock; };



};

template<typename T>
void PrintVector(const Vector<T>& vector)
{
	for (size_t i = 0; i < vector.Size(); i++)
	{
		LOG(vector[i]);
	}
	std::cout << "----------------------------" << std::endl;
}
template<>
void PrintVector(const Vector<Vector3>& vector)
{
	for (size_t i = 0; i < vector.Size(); i++)
	{
		LOG(vector[i].x << vector[i].y << vector[i].z);
	}
	std::cout << "----------------------------" << std::endl;
}

#pragma once


template<typename T, size_t S>
class Array
{
public:
	constexpr size_t Size() { return S; } //��û�д���S,�����S���滻Ϊһ��ʵ�ʵĳ��� , ������һ���������ʽ,������Ϊ����ʹ��
	//��һ�н�����ģ���ڱ���ʱ�ͱ�ȷ���Ļ�����

	T& operator[](int i)  //������ֵ , ���޸�ģʽ
	{
		if (!(i < S))
		{
			__debugbreak(); //msvc��debugģʽ�ж�
		}
		return m_data[i];
	}

	const T& operator[](int i) const //ֻ�� , const���͵�array����Ҳ����const���
	{
		return m_data[i];
	}

	T* Data() { return m_data; }
	const T* Data() const { return m_data; }

private:
	T m_data[S]; //ģ����ʹ��ʱ,S�����ǳ���
};
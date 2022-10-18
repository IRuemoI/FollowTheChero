#pragma once


#include <vector>
#include "renderer.h"


struct LayoutElement
{
	unsigned int type;//GL���ǵ�
	unsigned int count;
	unsigned char ifNormalized;

	static unsigned int GetSizeofType(unsigned int type) {
		switch (type)
		{
		case GL_FLOAT:return sizeof(GLfloat);
		case GL_UNSIGNED_INT:return sizeof(GLuint);
		case GL_UNSIGNED_BYTE:return sizeof(GLbyte);

		};
		ASSERT(false);
		return 0;

	}

};


class BufferLayout
{

private:
	std::vector<LayoutElement> m_Elements;
	unsigned int m_Stride;
public:
	BufferLayout()
		:m_Stride(0) {}; //vector �ṩ index
	template<typename T> //ģ���ػ�ǰ��д��ͨ���߼�
	void Push(unsigned int count) //ģ���ػ�,�����ǵñ���һ��
	{
		static_assert(false,"���˾�̬�����ַ���,�����ָ��ģ��");

	};
	template<>//ģ���ػ�(ָ��<>���͵ĺ���ģ��),����ָ��<>
	void Push<float>(unsigned int count) //<type1,type2 >(type1 x,type2 y) ģ��ָ�������������Ӧ(��˵��ϰ��ģ�尡ι!
	{
		m_Elements.push_back({ GL_FLOAT,count,GL_FALSE });
		m_Stride += sizeof(float)*count;
	};
	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({GL_UNSIGNED_INT,count,GL_FALSE });
		m_Stride += sizeof(int) * count;
	};
	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE,count,GL_TRUE});
		m_Stride += sizeof(unsigned char) * count;
	};
	inline std::vector<LayoutElement> GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const{ return m_Stride; }


};


#pragma once
#include "hzpch.h"


namespace Hazel
{
	//cherno����һ����һ���ļ�


	enum class ShaderDataType:uint8_t
	{
		None= 0,
		Float,Float2, Float3, Float4,
		Mat3,Mat4,
		Int, Int2, Int3, Int4,
		Bool

	};

	static uint32_t SizeofShaderDataType(ShaderDataType type) //staticҲû��,��ֻ�޶������cpp��Ԫ��
	{
		switch (type)
		{
		case Hazel::ShaderDataType::None: //breakҲ��ᱻ�Ż���?
			return 0;
			break;
		case Hazel::ShaderDataType::Float:
			return sizeof(float) ;
			break;
		case Hazel::ShaderDataType::Float2:
			return sizeof(float)*2;
			break;
		case Hazel::ShaderDataType::Float3:
			return sizeof(float)*3;
			break;
		case Hazel::ShaderDataType::Float4:
			return sizeof(float)*4;
			break;
		case Hazel::ShaderDataType::Mat3:
			return sizeof(float)*9;
			break;
		case Hazel::ShaderDataType::Mat4:
			return sizeof(float)*16;
			break;
		case Hazel::ShaderDataType::Int:
			return sizeof(int);
			break;
		case Hazel::ShaderDataType::Int2:
			return sizeof(int)*2;
			break;
		case Hazel::ShaderDataType::Int3:
			return sizeof(int)*3;
			break;
		case Hazel::ShaderDataType::Int4:
			return sizeof(int)*4;
			break;
		case Hazel::ShaderDataType::Bool:
			return 1;
			break;
		default:
			break;
		}

		HZ_CORE_ASSERT(false, "Not Defined Type in ShaderDatatype ");
		return 0;
	}

	struct LayoutElement
	{

		LayoutElement()=default;
		ShaderDataType type;//GL����
		std::string name;
		unsigned char ifNormalized;
		uint32_t size; //size
		uint32_t offset;//ptr

		LayoutElement(ShaderDataType Type, const std::string& Name, bool IfNor = false)
			:type(Type), name(Name), ifNormalized(IfNor), size(SizeofShaderDataType(Type)), offset(0)//offset������element����(�ⲿ����,����򵥳�ʼ��һ��	
		{
		}

		inline uint32_t GetElementCount() const //��inline��..�򵥺��������������ڵľ���inline��
		{
			switch (type)
			{
			case Hazel::ShaderDataType::None:
				return 0;
			case Hazel::ShaderDataType::Float:
				return 1;
			case Hazel::ShaderDataType::Float2:
				return 2;
			case Hazel::ShaderDataType::Float3:
				return 3;
			case Hazel::ShaderDataType::Float4:
				return 4;
			case Hazel::ShaderDataType::Mat3:
				return 3*3;
			case Hazel::ShaderDataType::Mat4:
				return 4*4;
			case Hazel::ShaderDataType::Int:
				return 1;
			case Hazel::ShaderDataType::Int2:
				return 2;
			case Hazel::ShaderDataType::Int3:
				return 3;
			case Hazel::ShaderDataType::Int4:
				return 4;
			case Hazel::ShaderDataType::Bool:
				return 1;
			default:
				break;
			}

			HZ_CORE_ASSERT(false, "Not Defined Type in ShaderDatatyp ");
			return 0;
		}

	};

	class BufferLayout
	{
	public:
		BufferLayout(const  std::initializer_list<LayoutElement>& elements)
			:m_elements(elements)
		{
			CalculateOffsetAndStride();//const & �����޸��ⲿ����(�����Ĳ���,const v& ����Ҳ���� const),���ﻹ�ǵ��޸��ڲ���Ա 
		}; //���������,��ֻ��һ�����ݽṹ

		BufferLayout() = default;

		~BufferLayout();
		inline const std::vector<LayoutElement>& GetLayoutElement()const { return m_elements; }
		inline const uint32_t GetStride()const { return m_stride; }

		std::vector<LayoutElement>::iterator begin() { return m_elements.begin(); } //�ṩ�������ӿ�,�������
		std::vector<LayoutElement>::iterator end() { return m_elements.end(); }
		std::vector<LayoutElement>::const_iterator begin() const{ return m_elements.begin(); } //�ṩ�������ӿ�,�������
		std::vector<LayoutElement>::const_iterator end() const { return m_elements.end(); }//ר��Ϊconst& ��const�����ṩ�� const������

	private:
		std::vector<LayoutElement> m_elements;
		uint32_t  m_stride; //���㲽��

		void CalculateOffsetAndStride()
		{
			uint32_t currentOffset = 0;

			for (LayoutElement& element : m_elements)
			{

				element.offset = currentOffset;
				currentOffset += element.size;

			}
			m_stride = currentOffset;
		};

	};

	class VertexBuffer
	{
	public:
		//VertexBuffer() {}; �����й��캯��,�����������ʵ��ʵ������,
		virtual ~VertexBuffer() =default; //ͬʱ��Щ�����������protect��public���ܶ����࿪��,�����Լ��Ĺ�����������Ҫ��������
		//virtual ~VertexBuffer() =default; virtual ~VertexBuffer(){};����,ǰ����ʽָ������Ĭ����������(�е�����±���������Ϊ�㹹��Ĭ�Ϻ���),�������д�˸���ʵ�� 
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static  Ref<VertexBuffer> Create(float* vertics, uint32_t size);
		static  Ref<VertexBuffer> Create(uint32_t size);

		virtual void SetLayout(const BufferLayout& layout)=0;
		virtual void SetData(const void* data,uint32_t size)=0;


		virtual const BufferLayout& GetLayout()const  =0;

	};


	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() =default;

		virtual void Bind()const = 0;
		virtual void UnBind()const = 0;
		virtual uint32_t GetCount()const = 0;

		static  Ref<IndexBuffer> Create(uint32_t* indices, size_t size);

	};


}
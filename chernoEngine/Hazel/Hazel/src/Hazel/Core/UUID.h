#pragma once

#include <xhash>

namespace Hazel
{
	class UUID
	{
	public:
		UUID();
		UUID(uint64_t id);
		UUID(const UUID& other ) = default;

		operator uint64_t() const
		{
			return m_UUID;
		}


	private:

		uint64_t m_UUID; //һ����˵UUID��128λ,������������64λ,ƴ���������̫��,����64λUUID������
	};

}

namespace std
{
	template<>
	struct hash<Hazel::UUID> //std::hash ģ��(hash�ƺ�����һ������,���Ǻ�������,��������ʹ��ʱ��Ҫһ��'()' ) UUID��չ(ģ���ػ�)
	{
		std::size_t operator()(const Hazel::UUID& id) const //hash<Hazel::UUID>()(UUID) �ȼ��� return hash<uint64_t>()(id);
		{
			return hash<uint64_t>()((uint64_t)id); //һ����ϣӳ��,���ܼ� ����10λhashֵ

			//c14 �� ��ͬ�ļ�������ͬ��hashֵ
		}

	};

}
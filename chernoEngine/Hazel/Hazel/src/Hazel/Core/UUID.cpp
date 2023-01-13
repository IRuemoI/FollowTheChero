#include "hzpch.h"
#include "UUID.h"

#include <random>

#include <unordered_map>

std::unordered_map<Hazel::UUID, std::string> m_Map;
static void Add2Map()
{
	m_Map[Hazel::UUID()] = "Hazel_UUID";
}


namespace Hazel
{

	static std::random_device s_RandomDevice; //����豸 -> �ṩ��Ƶ������� ��ȷ�����������������ʹ��Ӳ����Ϊ�������Դ��������ô��۽ϸߣ�һ������������������ӡ�
	static std::mt19937_64 s_Engine(s_RandomDevice()); //��������淵��uint ,_64 ����ָ64λ����.��������α����� �䷶Χ 2^19937 - 1
	static std::uniform_int_distribution<uint64_t> s_UniformDistribution; //ͳһ�����ֲ���? �ַ�uint64_t������һ��hash? ->������ֲ�����

	//�������齨���� ���򼯺Ϸ�UUID,�����½�UUIDʱ����Ƿ��ظ���,cherno˵û��Ҫ,���ʺ�С
	UUID::UUID()
		:m_UUID(s_UniformDistribution(s_Engine))
	{
	}

	UUID::UUID(uint64_t id)
		:m_UUID(id)
	{
	}

}
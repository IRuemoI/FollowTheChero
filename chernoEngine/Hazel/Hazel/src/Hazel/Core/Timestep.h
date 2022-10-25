#pragma once


namespace Hazel
{
	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			:m_Time(time)
		{
		}
		inline float GetSeconds() { return m_Time; };
		inline float GetMilliSeconds() { return m_Time * 1000.0f; }; //����

		operator float() const //use as float,�����ʽת������
		{
			return m_Time;
		}
	private:
		float m_Time = 0.0f;

	};

}


#pragma once

#include <string>
#include <iostream>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <thread>


namespace Hazel
{


struct ProfileResult
{
	std::string Name;
	long long Start, End;
	size_t threadID;
};

struct InstrumentationSession
{
	InstrumentationSession(const std::string& name) { m_name = name; }
	std::string m_name;
};


class Instrumentor
{
public:
	Instrumentor()
		:m_CurrentSession(nullptr), m_ProfileCount(0)
	{

	};

	void BeginSession(const std::string& name, const std::string& filePath = "result.json")
	{
		m_OutputStream.open(filePath);
		WriteHeader();
		m_CurrentSession = new InstrumentationSession(name);
	}

	void EndSession()
	{
		WriteFooter();
		m_OutputStream.close();

		delete m_CurrentSession;
		m_CurrentSession = nullptr;
		m_ProfileCount = 0;
	};



	void WriteProfile(const ProfileResult& result) //д�ļ�����
	{
		if (m_ProfileCount++ > 0)
		{
			m_OutputStream << ",";
		};
		std::string name = result.Name;
		std::replace(name.begin(), name.end(), '"', '\'');

		m_OutputStream << "{";
		m_OutputStream << "\"cat\":\"function\",";   //����
		m_OutputStream << "\"dur\":" << (result.End - result.Start) << ","; //tick
		m_OutputStream << "\"name\":\"" << name << "\","; //funcname
		m_OutputStream << "\"ph\":\"X\",";
		m_OutputStream << "\"pid\":0,";
		m_OutputStream << "\"tid\":" << result.threadID << ",";//�߳�id
		m_OutputStream << "\"ts\":" << result.Start; //��ʼtick
		m_OutputStream << "}";

		m_OutputStream.flush(); //ˢ��/������ļ�


	}

	void WriteHeader()//д�ļ�ͷ
	{
		m_OutputStream << "{\"otherData\":{},\"traceEvents\":[";
		m_OutputStream.flush();
	}
	void WriteFooter()//д�ļ�β
	{
		m_OutputStream << "]}";
		m_OutputStream.flush();

	}

	static Instrumentor& Get()
	{
		static Instrumentor* instance = new Instrumentor();
		return *instance;
	}


private:
	InstrumentationSession* m_CurrentSession;
	std::ofstream m_OutputStream;
	int m_ProfileCount;
};



	class InstrumentationTimer //Instrumentation ��׮
	{
	public:
		InstrumentationTimer(const char* name)
			:m_Name(name), m_stopped(false)
		{
			m_startTimepoint = std::chrono::high_resolution_clock::now();
		}

		void stop()
		{
			auto endTimepoint = std::chrono::high_resolution_clock::now();


			long long start = std::chrono::time_point_cast<std::chrono::microseconds> (m_startTimepoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds> (endTimepoint).time_since_epoch().count();

			m_stopped = true;
			size_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
			Instrumentor::Get().WriteProfile({ m_Name,start,end,threadID });

		}
		~InstrumentationTimer()
		{
			if (!m_stopped)
			{
				stop();
			}
		}

	private:
		const char* m_Name;
		bool m_stopped;

		std::chrono::time_point < std::chrono::steady_clock> m_startTimepoint;
	};


}
#ifdef HZ_DEBUG
#define HZ_PROFILING 1
#else
#define HZ_PROFILING 0
#endif

#if HZ_PROFILING
#define HZ_PROFILE_SCOPE(name)  ::Hazel::InstrumentationTimer time##__LINE__( name)
#define HZ_PROFILE_BEGIN_SESSION(name,filePath) ::Hazel::Instrumentor::Get().BeginSession(name,filePath)
#define HZ_PROFILE_END_SESSION() ::Hazel::Instrumentor::Get().EndSession()
#define HZ_PROFILE_FUNCTION() HZ_PROFILE_SCOPE(__FUNCSIG__);  //__FUNCTION__�ܶ���ǰ�ڵ��ļ���(const char*) ,__FUNCSIG__��ȡ����ǩ��(ǩ�����������غ���������)

#else 
#define HZ_PROFILE_SCOPE(name)	
#define HZ_PROFILE_BEGIN_SESSION(name,filePath) 
#define HZ_PROFILE_END_SESSION()
#define HZ_PROFILE_FUNCTION() HZ_PROFILE_SCOPE(__FUNCSIG__);  //__FUNCTION__�ܶ���ǰ�ڵ��ļ���(const char*) ,__FUNCSIG__��ȡ����ǩ��(ǩ�����������غ���������)
#endif 


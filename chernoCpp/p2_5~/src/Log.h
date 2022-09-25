#pragma once
//��ʽ����һ��ʵ���� log
#include <iostream>


class Log
{
public://����԰Ѳ�ͬ���͵�ͬ����ĳ�Ա�뷽���ֿ�д,���з����������,
//�������public��public�ı���
	enum Loglevel
	{
		LogLevelError=0, LogLevelWarning, LogLevelInfo
	};
private:
	Loglevel m_Loglevel=LogLevelInfo;//m_��ʾ����һ��˽�б���,Ĭ���κ���Ϣ���ᱻ��ӡ
public:
	void setLevel(int level) {
		m_Loglevel = level;

	}
	void error(const char* mesg) {
		if(m_Loglevel>=LogLevelError)
			std::cout << "[ERROR]:" << mesg << std::endl;
	}
	void warn(const char* mesg) {
		if(m_Loglevel>=LogLevelWarning)
			std::cout <<"[WARNING]:"<< mesg << std::endl;
	}
	void info(const char* mesg) {
		if(m_Loglevel>=LogLevelInfo)
			std::cout << "[INFO]:" << mesg << std::endl;
	}

};


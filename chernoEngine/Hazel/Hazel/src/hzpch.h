#pragma once

//Ԥ����ͷ ��ӵ�premake��
#include<iostream>
#include<memory>
#include<utility>
#include<algorithm>
#include<functional>

#include<sstream>	 
#include<string>
#include<vector>
#include<tuple>
#include<unordered_map>
#include<unordered_set>

#include "Hazel/core/Log.h"
#include "Hazel/Debug/Instrumentor.h"


#ifdef HZ_PLATFORM_WINDOWS
#include <Windows.h>
#else
#error Hazel only support windows!
#endif


#pragma once
#include <windows.h>
#include <filesystem>
#include <cstdarg>
#include <fstream>
#include <iostream>
using namespace std;

namespace Core
{
	namespace Debug
	{
		#define ASSERT(condition, message) if(!condition) throw std::runtime_error(message);
		#define DEBUG_LOG(VAR,...)(Log::DebugLog(__FILE__,__LINE__,VAR,__VA_ARGS__));

		class Log
		{
		public:
			
		public:
			ofstream logFile;
			static void DebugLog(const char* file, int line, const char* format, ...);
			void OpenFile(std::filesystem::path const& filename);
			void Print(const char* format, ...);
			~Log();
		};
	}
}
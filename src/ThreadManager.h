#pragma once

#include <string>
#include <iostream>
#include <stdarg.h>
#include <thread>
#include <vector>
#include <string>
#include "LuaScript.h"

using namespace std;

class ThreadManager
{
public:
	static ThreadManager* getInstance();
	~ThreadManager(void);

	//methods	
	void registerThread(LuaScript* script);
	void runThreads();
	void test(int val);
	static void threadContent(LuaScript* script);

	//variables
	int testVal;

private:
	//variables
	vector<std::thread> threads;	

	ThreadManager(void);
};

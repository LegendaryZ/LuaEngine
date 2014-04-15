#include "ThreadManager.h"
#include "ScriptManager.h"
ThreadManager* ThreadManager::getInstance()
{
	static ThreadManager* threadManager;
	if(!threadManager)
		threadManager = new ThreadManager();
	return threadManager;
}

ThreadManager::ThreadManager(void)
{

}


ThreadManager::~ThreadManager(void)
{
}


void ThreadManager::registerThread(LuaScript* script)
{	
	threads.push_back(thread(ThreadManager::threadContent, script));
}

void ThreadManager::threadContent(LuaScript* script)
{
	ScriptManager::runScript(script);
}

void ThreadManager::runThreads()
{
	//iterator
	vector<std::thread>::iterator target=threads.begin();

	//counter
	int count=0;

	//thread count
	cout<<"Threads created: "<<ThreadManager::testVal<<endl;

	//start threads (join)
	for(target;target!=threads.end();target++)
	{
	if(target->joinable())
	{
	cout<<"Thread "<<++count<<" started"<<endl;
	}
	else
	{
	cout<<"Thread "<<++count<<" not started"<<endl;
	}
	}


}

void ThreadManager::test(int val)
{
cout<<val<<endl;
//ThreadManager::testVal++;
//cout<<"Test Value: "<<ThreadManager::testVal<<endl;

}
#include "ThreadManager.h"

/**
 * Singleton accessor/constructor
 **/
ThreadManager* ThreadManager::getInstance()
{
	static ThreadManager* threadManager;
	if(!threadManager)
		threadManager = new ThreadManager();
	return threadManager;
}

ThreadManager::ThreadManager(void)
{}

ThreadManager::~ThreadManager(void)
{}

/**
 * Launches a task to be carried out in the background
 *
 * @param f		the lambda function to be carried out
 **/
void ThreadManager::asyncTask(std::function<void (void)> f)
{
	thread task(f);
	task.detach();
}

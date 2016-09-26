#pragma once

typedef void(*function_)();

class CScript {
	static std::queue<CScript*> * scriptQueue;
protected:
	std::string name;
	virtual void Run() = 0;
	CScript(std::string name):name(name) {
		if (!scriptQueue)
			scriptQueue = new std::queue<CScript*>();
		scriptQueue->push(this);
	}
public:
	static void RunAll()
	{
		log_debug << "Scripts in queue: " << scriptQueue->size() << std::endl;
		while (!scriptQueue->empty())
		{
			scriptQueue->front()->Run();
			log_debug << "Running new script" << std::endl;
			scriptQueue->pop();
		}
	}
};
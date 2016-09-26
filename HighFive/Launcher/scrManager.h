#pragma once

class ScriptManagerContext : public NativeContext {
public:

	ScriptManagerContext()
		: NativeContext() {
	}

	void Reset() {

		m_nArgCount = 0;
		m_nDataCount = 0;
	}

	inline void* GetResultPointer() {

		return m_pReturn;
	}
};

#undef Yield

class Script {
public:

	inline Script(void(*function)()) 
	{
		scriptFiber = nullptr;
		callbackFunction = function;
		wakeAt = timeGetTime();
	}

	inline ~Script() 
	{
		if (scriptFiber) {
			DeleteFiber(scriptFiber);
		}
	}

	void Tick();
	void Yield(uint32_t time);

	inline void(*GetCallbackFunction())() 
	{
		return callbackFunction;
	}

private:
	HANDLE			scriptFiber;
	uint32_t		wakeAt;
	void(*callbackFunction)();
	void			Run();
};

typedef std::map<std::string, std::shared_ptr<Script>> scriptMap;

class ScriptManagerThread : public ScriptThread
{
private:
	static scriptMap		m_scripts;
public:
	virtual void			DoRun() override;
	virtual eThreadState	Reset(uint32_t scriptHash, void * pArgs, uint32_t argCount) override;
	void					AddScript(std::string module, void(*fn)());
	void					RemoveScript(std::string module);
};

namespace ScriptManager {
	void					WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}

void nativeInit(UINT64 hash);
void nativePush64(UINT64 val);
PUINT64 nativeCall();
void scriptWait(unsigned long waitTime);
void scriptRegister(std::string threadName, void(*function)());
void scriptUnregister(std::string threadName);
int32_t getGameVersion();

extern ScriptManagerThread	g_ScriptManagerThread;

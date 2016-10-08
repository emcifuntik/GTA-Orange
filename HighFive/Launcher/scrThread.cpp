#include "stdafx.h"

eThreadState ScriptThread::Tick(uint32_t opsToExecute)
{
	typedef eThreadState(__thiscall * ScriptThreadTick_t)(ScriptThread * ScriptThread, uint32_t opsToExecute);
	ScriptThreadTick_t threadTickGta = (ScriptThreadTick_t)CMemory::Find("80 B9 46 01 00 00 00 8B  FA 48 8B D9 74 05").get<void>(-0xF);
	return threadTickGta(this, opsToExecute);
}

void ScriptThread::Kill()
{
	typedef void(__thiscall * ScriptThreadKill_t)(ScriptThread * ScriptThread);
	ScriptThreadKill_t killScriptThread = (ScriptThreadKill_t)CMemory::Find("48 83 EC 20 48 83 B9 10 01 00 00 00 48 8B D9 74 14").get<void>(-0x6);
	return killScriptThread(this);
}

eThreadState ScriptThread::Run(uint32_t opsToExecute)
{
	if (GetScriptHandler() == nullptr) 
	{
		ScriptEngine::GetScriptHandleMgr()->AttachScript(this);
		this->m_bNetworkFlag = true;
	}

	scrThread * activeThread = ScriptEngine::GetActiveThread();
	ScriptEngine::SetActiveThread(this);

	if (m_Context.m_State != ThreadStateKilled)
		DoRun();

	ScriptEngine::SetActiveThread(activeThread);

	return m_Context.m_State;
}

void ScriptThreadInit(ScriptThread * thread)
{
	typedef void(__thiscall * ScriptThreadInit_t)(ScriptThread * ScriptThread);
	auto scriptThreadInitPattern = CMemory::Find("83 89 38 01 00 00 FF 83 A1 50 01 00 00 F0");//problem
	ScriptThreadInit_t ScriptThreadInit_ = (ScriptThreadInit_t)scriptThreadInitPattern();
	return ScriptThreadInit_(thread);
}

eThreadState ScriptThread::Reset(uint32_t scriptHash, void* pArgs, uint32_t argCount)
{
	memset(&m_Context, 0, sizeof(m_Context));

	m_Context.m_State = ThreadStateIdle;
	m_Context.m_iScriptHash = scriptHash;
	m_Context.m_iUnk1 = -1;
	m_Context.m_iUnk2 = -1;
	m_Context.m_iSet1 = 1;

	ScriptThreadInit(this);

	m_pszExitMessage = "Normal exit";
	return m_Context.m_State;
}
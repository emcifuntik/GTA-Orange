#include "stdafx.h"
#include "Injector.h"
#include <TlHelp32.h>
#include <Shellapi.h>


Injector::Injector()
{
}

void Injector::Run()
{
	Injector inj;
	std::string path = inj.GetExecutablePath();
	ShellExecute(NULL, NULL, "steam://run/271590", NULL, NULL, SW_SHOW);
	inj.WaitUntilGameStarts();
	int pid = inj.FindProcess("GTA5.exe");
	inj.WaitForUnpackFinished(pid);
	//Started and unpacked
	inj.InjectDLL(pid, "ScriptHookV.dll");
	inj.InjectDLL(pid, "NativeTrainer.dll");
	MessageBox(NULL, "Injected", "Alert", MB_OK);
}

int Injector::FindProcess(std::string procName)
{
	HANDLE hSnap = INVALID_HANDLE_VALUE, hProcess = INVALID_HANDLE_VALUE;
	PROCESSENTRY32 ProcessStruct;
	ProcessStruct.dwSize = sizeof(PROCESSENTRY32);
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap == INVALID_HANDLE_VALUE)
		return (int)INVALID_HANDLE_VALUE;
	if (Process32First(hSnap, &ProcessStruct) == FALSE)
		return (int)INVALID_HANDLE_VALUE;
	do {
		if (strcmp(ProcessStruct.szExeFile, procName.c_str()) == 0) {
			CloseHandle(hSnap);
			return ProcessStruct.th32ProcessID;
		}
	} while (Process32Next(hSnap, &ProcessStruct));
	CloseHandle(hSnap);
	return (int)INVALID_HANDLE_VALUE;
}

GameVersion Injector::GetGameVersion()
{
	return GameVersion();
}

void Injector::WaitUntilGameStarts()
{
	while (FindProcess("GTA5.exe") == -1)
		Sleep(1);
}

bool Injector::InjectDLL(int processId, std::string dllName)
{
	HANDLE h = OpenProcess(PROCESS_ALL_ACCESS, false, processId);
	if (!h)
		return false;
	LPVOID LoadLibraryA_ = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
	LPVOID LoadComp = VirtualAllocEx(h, NULL, dllName.length(), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	WriteProcessMemory(h, LoadComp, dllName.c_str(), dllName.length(), NULL);
	HANDLE injectThread = CreateRemoteThread(h, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryA_, LoadComp, 0, NULL);
	WaitForSingleObject(injectThread, INFINITE);
	VirtualFreeEx(h, LoadComp, dllName.length(), MEM_RELEASE);
	CloseHandle(injectThread);
	CloseHandle(h);
	return true;
}

std::string Injector::GetExecutablePath()
{
	return std::string();
}

void Injector::WaitForUnpackFinished(int pid)
{
	HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);

	MODULEENTRY32 ModEnt;
	ModEnt.dwSize = sizeof(MODULEENTRY32);

	HMODULE hMod = NULL;
	HANDLE Snapshot1 = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);

	do {
		Module32First(Snapshot1, &ModEnt);
		do {
			if (strcmp("GTA5.exe", ModEnt.szModule) == 0)
			{
				hMod = ModEnt.hModule;
				break;
			}
		} while (Module32Next(Snapshot1, &ModEnt));
	} while (hMod == NULL);

	unsigned char buff[10];
	ReadProcessMemory(process, (LPVOID)((uint64_t)hMod + 0x1000), buff, 10, NULL);
	for (;;)
	{
		Sleep(1);
		unsigned char newBuff[10];
		ReadProcessMemory(process, (LPVOID)((uint64_t)hMod + 0x1000), newBuff, 10, NULL);
		for (int i = 0; i < 10; ++i)
		{
			if (buff[i] != newBuff[i])
			{
				CloseHandle(process);
				return;
			}
		}
	}
}


Injector::~Injector()
{
}

/*
 * This file is part of the CitizenFX project - http://citizen.re/
 *
 * See LICENSE and MENTIONS in the root of the source tree for information
 * regarding licensing.
 */
#ifndef UTILS_H
#define UTILS_H
#pragma once

#include <algorithm>
#include "string.h"
#include <string>


//
// Base initialization function (for running on library init and so on)
//

class STATIC InitFunctionBase
{
protected:
	InitFunctionBase* m_next;

	int m_order;

public:
	InitFunctionBase(int order = 0);

	virtual void Run() = 0;

	void Register();

	static void RunAll();
};

//
// Initialization function that will be called around initialization of the primary component.
//

class STATIC InitFunction : public InitFunctionBase
{
private:
	void(*m_function)();

public:
	InitFunction(void(*function)(), int order = 0)
		: InitFunctionBase(order)
	{
		m_function = function;

		Register();
	}

	virtual void Run()
	{
		m_function();
	}
};

//
// 'compile-time' hashing
//

template <unsigned int N, unsigned int I>
struct FnvHash
{
	FORCEINLINE static unsigned int Hash(const char(&str)[N])
	{
		return (FnvHash<N, I - 1>::Hash(str) ^ str[I - 1]) * 16777619u;
	}
};

template <unsigned int N>
struct FnvHash<N, 1>
{
	FORCEINLINE static unsigned int Hash(const char(&str)[N])
	{
		return (2166136261u ^ str[0]) * 16777619u;
	}
};

class StringHash
{
private:
	unsigned int m_hash;

public:
	template <unsigned int N>
	FORCEINLINE StringHash(const char(&str)[N])
		: m_hash(FnvHash<N, N>::Hash(str))
	{
	}

	FORCEINLINE operator unsigned int() const
	{
		return m_hash;
	}
};

#ifndef _M_AMD64
#define CALL_NO_ARGUMENTS(addr) ((void(*)())addr)()
#define EAXJMP(a) { _asm mov eax, a _asm jmp eax }
#define WRAPPER __declspec(naked)
#else
#define EAXJMP(a)
#define WRAPPER
#endif

//
// export class specifiers
//

#ifdef COMPILING_GAME
#define GAME_EXPORT DLL_EXPORT
#else
#define GAME_EXPORT DLL_IMPORT
#endif

#ifdef COMPILING_HOOKS
#define HOOKS_EXPORT DLL_EXPORT
#else
#define HOOKS_EXPORT DLL_IMPORT
#endif
/*
#ifdef COMPILING_CORE
#define CORE_EXPORT DLL_EXPORT
#else
#define CORE_EXPORT DLL_IMPORT
#endif
*/
#ifdef COMPILING_GAMESPEC
#define GAMESPEC_EXPORT DLL_EXPORT
#define GAMESPEC_EXPORT_VMT DLL_EXPORT
#else
#define GAMESPEC_EXPORT DLL_IMPORT
#define GAMESPEC_EXPORT_VMT
#endif

//
// formatting/logging functions
//

const char* va(const char* string, ...);
const wchar_t* va(const wchar_t* string, ...);
void trace(const char* string, ...);
void GlobalError(const char* string, ...);
void FatalError(const char* string, ...);

uint32_t HashRageString(const char* string);
uint32_t HashString(const char* string);

inline void LowerString(fwString& string)
{
	std::transform(string.begin(), string.end(), string.begin(), ::tolower);
}


fwString url_encode(const fwString &value);
bool UrlDecode(const std::string& in, std::string& out);
void CreateDirectoryAnyDepth(const char *path);

const DWORD MS_VC_EXCEPTION = 0x406D1388;

#pragma pack(push,8)
typedef struct tagTHREADNAME_INFO
{
	DWORD dwType; // Must be 0x1000.
	LPCSTR szName; // Pointer to name (in user addr space).
	DWORD dwThreadID; // Thread ID (-1=caller thread).
	DWORD dwFlags; // Reserved for future use, must be zero.
} THREADNAME_INFO;
#pragma pack(pop)

void SetThreadName(int threadId, char* threadName);

extern "C" bool
#ifdef COMPILING_CORE
	DLL_EXPORT
#endif
	CoreIsDebuggerPresent();

extern "C" void
#ifdef COMPILING_CORE
	DLL_EXPORT
#endif
	CoreSetDebuggerPresent();

std::string ExplodeAndReturn(std::string stringToExplode, int field, std::string delimiter);
std::vector<std::string> explode(const std::string &delimiter, const std::string &str);
void OutputToConsole(const wchar_t* szFormat, ...);
const char* char_replace(char* string_rep, char match, char replace);
Vector3 getCoordsFromCam(float distance);
#endif
/*
	* Copyright (C) GTA:Multiplayer Team (https://wiki.gta-mp.net/index.php/Team)
	*
	* Redistribution and use in source and binary forms, with or without
	* modification, are permitted provided that the following conditions are
	* met:
	*
	*     * Redistributions of source code must retain the above copyright
	*		notice, this list of conditions and the following disclaimer.
	*     * Redistributions in binary form must reproduce the above
	*		copyright notice, this list of conditions and the following disclaimer
	*		in the documentation and/or other materials provided with the
	*		distribution.
	*     * Neither the name of GTA-Network nor the names of its
	*		contributors may be used to endorse or promote products derived from
	*		this software without specific prior written permission.
	*
	* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
	* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
	* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
	* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef GTAMP_Common_h
#define GTAMP_Common_h

// Enables short loading time, F5(refresh) for UI development
#define CLIENT_DEV 1

#if _WIN64 || __x86_64__ || __ppc64__
#define IS64BIT 1
#else
#define IS64BIT 0
#endif

#if defined(_WIN64) || defined(_WIN32)
#ifdef WIN32
#undef WIN32
#endif
#define WIN32 1
#elif __APPLE__
#define MAC 1
#elif __linux
#define LINUX 1
#elif __unix
#define UNIX 1
#elif __posix
#define POSIX 1
#endif

#if WIN32
#if CRT_ALLOC
#define CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
#endif
#endif

#if WIN32
#include <yvals.h> // This is needed for making stuff compatible

#elif LINUX
#if __GNUC__ < 4 || (__GNUC__ < 4 && __GNUC_MINOR__ < 7) || (__GNUC__ < 4 && __GNUC_MINOR__ < 7 && __GNUC_PATCHLEVEL__ < 2)
#error "Use at least GCC 4.7.2"
#endif 

#if __cplusplus <= 199711L
if !defined(__GXX_EXPERIMENTAL_CXX0X__) || __GXX_EXPERIMENTAL_CXX0X__ != 1
#error "C++11 is required. Try --std=c++0x"
#endif
#endif

#ifndef _NOEXCEPT
#define NOEXCEPT noexcept
#else
#ifdef __clang__
#define NOEXCEPT noexcept
#else
#define NOEXCEPT _NOEXCEPT
#endif
#endif

// at this point we can use C++11

#ifdef WIN32
#include <WinSock2.h> // Just to be sure that there will never be a fucking include guard error
#include <Windows.h>

#include <direct.h>
#include <stdlib.h>
#include <stdio.h>

#pragma warning(disable : 4459)
#pragma warning(disable : 4005)
#pragma comment (lib, "d3d11.lib")

#pragma warning(push, 0)
#include <D2D1.h>
#include <Windows.h>
#include <D3D11.h>
#pragma warning(pop)
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
typedef int SOCKET;

#define sprintf_s(a, b, c) snprintf(a, sizeof(a), b, c)
#endif

// These are C++ standard includes so not platform specific

#pragma region STD
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <chrono>
#include <thread>
#include <functional>
#include <tuple>
#include <algorithm>
#include <array>
#include <memory>

using namespace std::chrono_literals;
#pragma endregion

#include <cassert>
#include <cstdint>
#include <cstring>

typedef std::int8_t int8;
typedef std::uint8_t uint8;

typedef std::int16_t int16;
typedef std::uint16_t uint16;

typedef std::int32_t int32;
typedef std::uint32_t uint32;

typedef std::int64_t int64;
typedef std::uint64_t uint64;

#define _INTERFACE class

// Change to GTAMP_STATIC/API etc.
#ifdef VMP_STATIC
#   define VMP_API
#else
#if defined(VMP_EXPORT) // inside DLL
#   define VMP_API   __declspec(dllexport)
#else // outside DLL
#   define VMP_API   __declspec(dllimport)
#endif
#endif

//#include <ILogger.h>
//
//#define DEBUG_LOG GetLogger("Client")->debug
//
//#define MSG_DEBUG_LOG(...) \
//{ \
//	MessageBoxA(NULL, std::string(__VA_ARGS__).c_str(), "GTA:Multiplayer Debug Exception", MB_ICONERROR|MB_OK); \
//	GetLogger("Client")->debug(__VA_ARGS__);  \
//}
//
//#define MSG_WARNING_LOG(message, header) \
//{ \
//	MessageBoxA(NULL, message, header, MB_ICONEXCLAMATION | MB_OK); \
//	GetLogger("Client")->error("Warning at: %s:[%d]", __FILE__, __LINE__); \
//}
//
//#define MSG_ERROR_LOG(message, header) \
//{ \
//	MessageBoxA(NULL, message, header, MB_ICONERROR | MB_OK); \
//	GetLogger("Client")->error("Error at: %s:[%d]", __FILE__, __LINE__); \
//}
//
//#define ERROR_LOG(...) \
//{ \
//	GetLogger("Client")->error("Error at: %s:[%d]", __FILE__, __LINE__); \
//	GetLogger("Client")->error( __VA_ARGS__); \
//}

#endif // GTAMP_Common_h
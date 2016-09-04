#pragma once

class CMemory
{
	void *address;
	static bool memoryCompare(const BYTE *data, const BYTE *pattern, size_t length);
	static bool memoryCompare(const BYTE *data, const BYTE *pattern, const char *mask);
public:
	static ptrdiff_t baseDiff;
	template<typename T, T Value>
	static T Return()
	{
		return Value;
	}

	CMemory(UINT64 address);
	~CMemory();

	void put(const char *value);
	template <typename T> void put(T value);
	template <typename T> void put(void *address, T value);
	template <typename T> void jump(T func);
	template <typename T> void call(T func);
	template <typename T> T* get(int offset);
	template <typename T> static T get_call(T address);
	template <typename TTarget, typename T> static void set_call(TTarget* target, T address);
	template <typename T> static inline uintptr_t get_adjusted(T _address);

	DWORD getOffset(int offset)
	{
		DWORD* ptr = (DWORD*)((uintptr_t)address + offset);
		return (DWORD)(*ptr + (((uintptr_t)address + offset + sizeof(DWORD)) - (uintptr_t)GetModuleHandle(NULL)));
	}

	DWORD getFunc()
	{
		return (DWORD)((uintptr_t)address - (uintptr_t)GetModuleHandle(NULL));
	}
	
	CMemory operator+(int offset)
	{
		CMemory *m = new CMemory(*this);
		m->address = (void*)((intptr_t)m->address + offset);
		return (*m);
	}

	void nop(size_t length);

	static CMemory *Find(const char* pattern);
	static CMemory *Find_t(const char* text);
	static void Init();
};

template<typename T>
inline void CMemory::put(T value)
{
	unsigned long dwProtectOld;
	VirtualProtect((LPVOID)address, 2, PAGE_EXECUTE_READWRITE, &dwProtectOld);
	memcpy(address, &value, sizeof(T));
	VirtualProtect((LPVOID)address, 2, dwProtectOld, NULL);
}

template<typename T>
inline void CMemory::put(void * address, T value)
{
	unsigned long dwProtectOld;
	VirtualProtect((LPVOID)address, 2, PAGE_EXECUTE_READWRITE, &dwProtectOld);
	memcpy(address, &value, sizeof(T));
	VirtualProtect((LPVOID)address, 2, dwProtectOld, NULL);
}

template<typename T>
inline void CMemory::jump(T func)
{
	put(address, (uint8_t)0xE9);
	put((void*)((size_t*)address + 1), (intptr_t)func - (intptr_t)baseDiff - 5);
}

template<typename T>
inline void CMemory::call(T func)
{
	put(address, (uint8_t)0xE8);
	put((void*)((size_t*)address + 1), (intptr_t)func - (intptr_t)baseDiff - 5);
}

template<typename T>
inline uintptr_t CMemory::get_adjusted(T _address)
{
	return (uintptr_t)_address + baseDiff;
}

template<typename T>
inline T* CMemory::get(int offset)
{
	char* ptr = reinterpret_cast<char*>(address);
	return reinterpret_cast<T*>(ptr + offset);
}

template<typename T>
inline T CMemory::get_call(T _address)
{
	intptr_t target = *(uintptr_t*)(get_adjusted(_address) + 1);
	target += (get_adjusted(_address) + 5);
	return (T)target;
}

template<typename TTarget, typename T>
inline void CMemory::set_call(TTarget* target, T _address)
{
	*(T*)target = get_call(_address);
}

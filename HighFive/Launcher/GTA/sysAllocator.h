#pragma once

namespace rage
{
	enum
	{
		HEAP_TASK = 0,
		HEAP_TASK_CLONE,
		HEAP_LAST
	};
	class sysMemAllocator
	{
		sysMemAllocator()
		{
			heaps = new int64_t[HEAP_LAST];
			heaps[HEAP_TASK] = *(int64_t*)CMemory::Find("48 8B 0D ? ? ? ? 41 B8 10 00 00 00 E8 ? ? ? ? 48 8B D8 48 85 C0 75 ?").getOffset();
			heaps[HEAP_TASK_CLONE] = *(int64_t*)CMemory::Find("48 8B 0D ? ? ? ? 45 33 C0 48 8B D3 E8 ? ? ? ? 48 8B 74 24 38").getOffset();
		}
		int64_t *heaps = nullptr;
		static sysMemAllocator* singleInstance;
	public:
		void* (*_allocate)(int64_t allocatorPtr, int64_t size, int64_t align, int64_t suballocator);
		void* allocate(int64_t size, int64_t align, int heapNumber = HEAP_TASK, int64_t suballocator = 0)
		{
			typedef void*(*__func)(int64_t, int64_t, int64_t, int64_t);
			return (__func)CMemory::Find("48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 20 48 8D 99 A0 00 00 00 49 8B F0 48 8B EA")();
		}

		void (*_free)(int64_t allocatorPtr, void* address);
		void free(void* address, int heapNumber = HEAP_TASK)
		{
			typedef void(*__func)(int64_t, void*);
			((__func)CMemory::Find("48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 48 8D 99 A0 00 00 00 48 8B F2 48 8B F9 48 83 3B 00 74 09")())(heaps[heapNumber], address);
		}

		static sysMemAllocator* Get()
		{
			if (!singleInstance)
				singleInstance = new sysMemAllocator();
			return singleInstance;
		}
	};

	class sysUseAllocator
	{
	public:
		void* operator new(size_t size);

		inline void* operator new[](size_t size)
		{
			return sysUseAllocator::operator new(size);
		}

		void operator delete(void* memory);

		inline void operator delete[](void* memory)
		{
			return sysUseAllocator::operator delete(memory);
		}
	};
}
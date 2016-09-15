#pragma once
using namespace MemoryHook;

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

			heaps[HEAP_TASK] = value<int64_t>((*GTA::CAddress::Get())[TASK_POOL], true);
			heaps[HEAP_TASK_CLONE] = value<int64_t>((*GTA::CAddress::Get())[TASK_CLONE_POOL], true);
		}
		int64_t *heaps = nullptr;
		static sysMemAllocator* singleInstance;
	public:
		void* (*_allocate)(int64_t allocatorPtr, int64_t size, int64_t align, int64_t suballocator);
		void* allocate(int64_t size, int64_t align, int heapNumber = HEAP_TASK, int64_t suballocator = 0)
		{
			return call<void*, int64_t, int64_t, int64_t, int64_t>((*GTA::CAddress::Get())[POOL_ADD], heaps[heapNumber], size, align, suballocator);
		}

		void (*_free)(int64_t allocatorPtr, void* address);
		void free(void* address, int heapNumber = HEAP_TASK)
		{
			call<void, int64_t, void*>((*GTA::CAddress::Get())[POOL_REMOVE], heaps[heapNumber], address);
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
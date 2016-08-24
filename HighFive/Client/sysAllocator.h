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

			heaps[HEAP_TASK] = hook::value<int64_t>(0x234EEA0, true);
			heaps[HEAP_TASK_CLONE] = hook::value<int64_t>(0x228FF40, true);
		}
		int64_t *heaps = nullptr;
		static sysMemAllocator* singleInstance;
	public:
		void* (*_allocate)(int64_t allocatorPtr, int64_t size, int64_t align, int64_t suballocator);
		void* allocate(int64_t size, int64_t align, int heapNumber = HEAP_TASK, int64_t suballocator = 0)
		{
			return hook::call<0x11B7D00, void*, int64_t, int64_t, int64_t, int64_t>(heaps[heapNumber], size, align, suballocator);
		}

		void (*_free)(int64_t allocatorPtr, void* address);
		void free(void* address, int heapNumber = HEAP_TASK)
		{
			hook::call<0x11B7D70, void, int64_t, void*>(heaps[heapNumber], address);
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
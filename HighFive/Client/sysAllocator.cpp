#include "stdafx.h"

namespace rage
{
	sysMemAllocator* sysMemAllocator::singleInstance = nullptr;
	void* sysUseAllocator::operator new(size_t size)
	{
		return sysMemAllocator::Get()->allocate(size, 16, 0);
	}

	void sysUseAllocator::operator delete(void* memory)
	{
		sysMemAllocator::Get()->free(memory);
	}
}


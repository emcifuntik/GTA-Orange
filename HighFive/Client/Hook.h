#pragma once

namespace hook
{
	template<intptr_t address, typename returnType = void>
	auto call()
	{
		auto func = (returnType(*)())((intptr_t)GetModuleHandle(NULL) + address);
		return func();
	}

	template<intptr_t address, typename returnType = void, typename argType1>
	auto call(argType1 arg1)
	{
		auto func = (returnType(*)(argType1))((intptr_t)GetModuleHandle(NULL) + address);
		return func(arg1);
	}

	template<intptr_t address, typename returnType = void, typename argType1, typename argType2>
	auto call(argType1 arg1, argType2 arg2)
	{
		auto func = (returnType(*)(argType1, argType2))((intptr_t)GetModuleHandle(NULL) + address);
		return func(arg1, arg2);
	}

	template<intptr_t address, typename returnType = void, typename argType1, typename argType2, typename argType3>
	auto call(argType1 arg1, argType2 arg2, argType3 arg3)
	{
		auto func = (returnType(*)(argType1, argType2, argType3))((intptr_t)GetModuleHandle(NULL) + address);
		return func(arg1, arg2, arg3);
	}

	template<intptr_t address, typename returnType = void, typename argType1, typename argType2, typename argType3, typename argType4>
	auto call(argType1 arg1, argType2 arg2, argType3 arg3, argType4 arg4)
	{
		auto func = (returnType(*)(argType1, argType2, argType3, argType4))((intptr_t)GetModuleHandle(NULL) + address);
		return func(arg1, arg2, arg3, arg4);
	}

	template<intptr_t address, typename returnType = void, typename argType1, typename argType2, typename argType3, typename argType4, typename argType5>
	auto call(argType1 arg1, argType2 arg2, argType3 arg3, argType4 arg4, argType5 arg5)
	{
		auto func = (returnType(*)(argType1, argType2, argType3, argType4, argType5))((intptr_t)GetModuleHandle(NULL) + address);
		return func(arg1, arg2, arg3, arg4, arg5);
	}

	template<typename Type>
	Type value(intptr_t address, bool followPtr = false)
	{
		if(!followPtr)
			return (Type)((intptr_t)GetModuleHandle(NULL) + address);
		else
			return *(Type*)((intptr_t)GetModuleHandle(NULL) + address);
	}
};
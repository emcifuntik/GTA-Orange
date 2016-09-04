#pragma once

namespace MemoryHook
{
	template<typename returnType = void>
	auto call(intptr_t address)
	{
		auto func = (returnType(*)())((intptr_t)GetModuleHandle(NULL) + address);
		return func();
	}

	template<typename returnType = void, typename argType1>
	auto call(intptr_t address, argType1 arg1)
	{
		auto func = (returnType(*)(argType1))((intptr_t)GetModuleHandle(NULL) + address);
		return func(arg1);
	}

	template<typename returnType = void, typename argType1, typename argType2>
	auto call(intptr_t address, argType1 arg1, argType2 arg2)
	{
		auto func = (returnType(*)(argType1, argType2))((intptr_t)GetModuleHandle(NULL) + address);
		return func(arg1, arg2);
	}

	template<typename returnType = void, typename argType1, typename argType2, typename argType3>
	auto call(intptr_t address, argType1 arg1, argType2 arg2, argType3 arg3)
	{
		auto func = (returnType(*)(argType1, argType2, argType3))((intptr_t)GetModuleHandle(NULL) + address);
		return func(arg1, arg2, arg3);
	}

	template<typename returnType = void, typename argType1, typename argType2, typename argType3, typename argType4>
	auto call(intptr_t address, argType1 arg1, argType2 arg2, argType3 arg3, argType4 arg4)
	{
		auto func = (returnType(*)(argType1, argType2, argType3, argType4))((intptr_t)GetModuleHandle(NULL) + address);
		return func(arg1, arg2, arg3, arg4);
	}

	template<typename returnType = void, typename argType1, typename argType2, typename argType3, typename argType4, typename argType5>
	auto call(intptr_t address, argType1 arg1, argType2 arg2, argType3 arg3, argType4 arg4, argType5 arg5)
	{
		auto func = (returnType(*)(argType1, argType2, argType3, argType4, argType5))((intptr_t)GetModuleHandle(NULL) + address);
		return func(arg1, arg2, arg3, arg4, arg5);
	}

	template<typename returnType = void, typename argType1, typename argType2, typename argType3, typename argType4, typename argType5, typename argType6>
	auto call(intptr_t address, argType1 arg1, argType2 arg2, argType3 arg3, argType4 arg4, argType5 arg5, argType6 arg6)
	{
		auto func = (returnType(*)(argType1, argType2, argType3, argType4, argType5, argType6))((intptr_t)GetModuleHandle(NULL) + address);
		return func(arg1, arg2, arg3, arg4, arg5, arg6);
	}

	template<typename returnType = void, typename argType1, typename argType2, typename argType3, typename argType4, typename argType5, typename argType6, typename argType7>
	auto call(intptr_t address, argType1 arg1, argType2 arg2, argType3 arg3, argType4 arg4, argType5 arg5, argType6 arg6, argType7 arg7)
	{
		auto func = (returnType(*)(argType1, argType2, argType3, argType4, argType5, argType6, argType7))((intptr_t)GetModuleHandle(NULL) + address);
		return func(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	}

	template<typename returnType = void, typename argType1, typename argType2, typename argType3, typename argType4, typename argType5, typename argType6, typename argType7, typename argType8>
	auto call(intptr_t address, argType1 arg1, argType2 arg2, argType3 arg3, argType4 arg4, argType5 arg5, argType6 arg6, argType7 arg7, argType8 arg8)
	{
		auto func = (returnType(*)(argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8))((intptr_t)GetModuleHandle(NULL) + address);
		return func(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
	}

	template<typename returnType = void, typename argType1, typename argType2, typename argType3, typename argType4, typename argType5, typename argType6, typename argType7, typename argType8, typename argType9>
	auto call(intptr_t address, argType1 arg1, argType2 arg2, argType3 arg3, argType4 arg4, argType5 arg5, argType6 arg6, argType7 arg7, argType8 arg8, argType9 arg9)
	{
		auto func = (returnType(*)(argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9))((intptr_t)GetModuleHandle(NULL) + address);
		return func(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
	}

	template<typename returnType = void, typename argType1, typename argType2, typename argType3, typename argType4, typename argType5, typename argType6, typename argType7, typename argType8, typename argType9, typename argType10>
	auto call(intptr_t address, argType1 arg1, argType2 arg2, argType3 arg3, argType4 arg4, argType5 arg5, argType6 arg6, argType7 arg7, argType8 arg8, argType9 arg9, argType10 arg10)
	{
		auto func = (returnType(*)(argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10))((intptr_t)GetModuleHandle(NULL) + address);
		return func(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
	}

	template<typename returnType = void, typename argType1, typename argType2, typename argType3, typename argType4, typename argType5, typename argType6, typename argType7, typename argType8, typename argType9, typename argType10, typename argType11>
	auto call(intptr_t address, argType1 arg1, argType2 arg2, argType3 arg3, argType4 arg4, argType5 arg5, argType6 arg6, argType7 arg7, argType8 arg8, argType9 arg9, argType10 arg10, argType11 arg11)
	{
		auto func = (returnType(*)(argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10, argType11))((intptr_t)GetModuleHandle(NULL) + address);
		return func(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11);
	}

	template<typename returnType = void, typename argType1, typename argType2, typename argType3, typename argType4, typename argType5, typename argType6, typename argType7, typename argType8, typename argType9, typename argType10, typename argType11, typename argType12>
	auto call(intptr_t address, argType1 arg1, argType2 arg2, argType3 arg3, argType4 arg4, argType5 arg5, argType6 arg6, argType7 arg7, argType8 arg8, argType9 arg9, argType10 arg10, argType11 arg11, argType12 arg12)
	{
		auto func = (returnType(*)(argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10, argType11, argType12))((intptr_t)GetModuleHandle(NULL) + address);
		return func(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12);
	}

	template<typename returnType = void, typename argType1, typename argType2, typename argType3, typename argType4, typename argType5, typename argType6, typename argType7, typename argType8, typename argType9, typename argType10, typename argType11, typename argType12, typename argType13>
	auto call(intptr_t address, argType1 arg1, argType2 arg2, argType3 arg3, argType4 arg4, argType5 arg5, argType6 arg6, argType7 arg7, argType8 arg8, argType9 arg9, argType10 arg10, argType11 arg11, argType12 arg12, argType13 arg13)
	{
		auto func = (returnType(*)(argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10, argType11, argType12, argType13))((intptr_t)GetModuleHandle(NULL) + address);
		return func(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13);
	}

	template<typename returnType = void, typename argType1, typename argType2, typename argType3, typename argType4, typename argType5, typename argType6, typename argType7, typename argType8, typename argType9, typename argType10, typename argType11, typename argType12, typename argType13, typename argType14>
	auto call(intptr_t address, argType1 arg1, argType2 arg2, argType3 arg3, argType4 arg4, argType5 arg5, argType6 arg6, argType7 arg7, argType8 arg8, argType9 arg9, argType10 arg10, argType11 arg11, argType12 arg12, argType13 arg13, argType14 arg14)
	{
		auto func = (returnType(*)(argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10, argType11, argType12, argType13, argType14))((intptr_t)GetModuleHandle(NULL) + address);
		return func(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14);
	}

	template<typename returnType = void, typename argType1, typename argType2, typename argType3, typename argType4, typename argType5, typename argType6, typename argType7, typename argType8, typename argType9, typename argType10, typename argType11, typename argType12, typename argType13, typename argType14, typename argType15>
	auto call(intptr_t address, argType1 arg1, argType2 arg2, argType3 arg3, argType4 arg4, argType5 arg5, argType6 arg6, argType7 arg7, argType8 arg8, argType9 arg9, argType10 arg10, argType11 arg11, argType12 arg12, argType13 arg13, argType14 arg14, argType15 arg15)
	{
		auto func = (returnType(*)(argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10, argType11, argType12, argType13, argType14, argType15))((intptr_t)GetModuleHandle(NULL) + address);
		return func(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15);
	}

	template<typename Type>
	Type value(intptr_t address, bool followPtr = false)
	{
		if(!followPtr)
			return (Type)((intptr_t)GetModuleHandle(NULL) + address);
		else
			return *(Type*)((intptr_t)GetModuleHandle(NULL) + address);
	}
	
	void nop(intptr_t address, int count = 5);
	void retn(intptr_t address);
};
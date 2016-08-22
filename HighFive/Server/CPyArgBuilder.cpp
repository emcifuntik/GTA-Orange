#include "stdafx.h"

CPyArgBuilder::CPyArgBuilder()
{
}


CPyArgBuilder::~CPyArgBuilder()
{
	if (argList)
		delete argList;
}

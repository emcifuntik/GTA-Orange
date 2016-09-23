#include "stdafx.h"

class CEventGameFrame :
	public CEvent
{
	std::string Type()
	{
		return "onGameFrame";
	}
	bool CEventGameFrame::Action()
	{
		
		return true;
	}
} _ev;


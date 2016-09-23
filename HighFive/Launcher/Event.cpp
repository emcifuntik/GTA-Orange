#include "stdafx.h"

std::vector<CEvent*> CEvent::_events;

CEvent::CEvent()
{
	_events.push_back(this);
}
#pragma once
class CEventBeforeLoaded :
	public CEvent
{
	std::string Type()
	{
		return "onBeforeLoaded";
	}
	bool CEventBeforeLoaded::Action();
};


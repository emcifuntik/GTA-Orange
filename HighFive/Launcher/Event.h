#pragma once
class CEvent
{
	static std::vector<CEvent*> _events;
protected:
	CEvent();
	virtual std::string Type() = 0;
	virtual bool Action() = 0;
public:
	static bool Trigger(std::string name, bool multithreaded = false)
	{
		for (auto event : _events)
		{
			if (name.compare(event->Type()))
				continue;
			if (!multithreaded)
			{
				if (!event->Action())
					return false;
			}
			else
				std::thread(&CEvent::Action, event).detach();
		}
		return true;
	}
};


#pragma once
class CGlobals
{
	CGlobals() {}
	static CGlobals * singleInstance;
public:
	static CGlobals& Get()
	{
		if (!singleInstance)
			singleInstance = new CGlobals();
		return *singleInstance;
	}
	LPVOID baseAddr = nullptr;
	std::string highFivePath;
	bool alreadyRunned = false;
};


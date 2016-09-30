#include "stdafx.h"

#define _MEM_CACHE_FILE "memcache.xml"

std::map<std::string, DWORD> CMemoryCache::memoryHooks;
CMemoryCache * CMemoryCache::singleInstance;

CMemoryCache::CMemoryCache()
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile((CGlobals::Get().highFivePath + "\\" _MEM_CACHE_FILE).c_str());
	if (!doc.Error())
	{
		tinyxml2::XMLElement * root = doc.FirstChildElement("memory");
		tinyxml2::XMLElement * hooks = root->FirstChildElement("hooks");
		for (tinyxml2::XMLElement* child = hooks->FirstChildElement("hook"); child != NULL; child = child->NextSiblingElement())
			memoryHooks.insert(std::pair<std::string, DWORD>(child->GetText(), child->IntAttribute("offset")));
	}
}


bool CMemoryCache::TryGetOffset(std::string pattern, DWORD & offset)
{
	if (memoryHooks.find(pattern) != memoryHooks.end())
	{
		offset = memoryHooks[pattern];
		return true;
	}
	return false;
}

void CMemoryCache::AddOffset(std::string pattern, DWORD offset)
{
	if (memoryHooks.find(pattern) == memoryHooks.end())
	{
		memoryHooks.insert(std::pair<std::string, DWORD>(pattern, offset));
		Save();
	}
}

void CMemoryCache::Save()
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode * pRoot = doc.NewElement("memory");
	doc.InsertFirstChild(pRoot);
	tinyxml2::XMLNode * pHooks = doc.NewElement("hooks");
	pRoot->InsertFirstChild(pHooks);

	for each (auto pattern in memoryHooks)
	{
		tinyxml2::XMLElement * pHook = doc.NewElement("hook");
		pHook->SetText(pattern.first.c_str());
		pHook->SetAttribute("offset", (int64_t)pattern.second);
		pHooks->InsertEndChild(pHook);
	}
	tinyxml2::XMLError eResult = doc.SaveFile((CGlobals::Get().highFivePath + "\\" _MEM_CACHE_FILE).c_str());
	if (eResult != tinyxml2::XMLError::XML_SUCCESS)
		throw std::exception("TinyXML Error");
}

CMemoryCache::~CMemoryCache()
{
}

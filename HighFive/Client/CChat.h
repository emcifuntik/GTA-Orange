#pragma once
#include <string>
#include <vector>
#include <types.h>

typedef struct tagChatLine
{
	std::string sLineText;
	color_t structColor;
} ChatLine;

enum ScrollRoute
{
	SCROLL_UP = 1,
	SCROLL_DOWN
};

class CChat
{
	void AddLine(ChatLine line);
	CChat();

	static CChat *singleInstance;
	std::vector<ChatLine> vChatLines;
	bool bOpened = false;
	bool bEnabled = true;
	int iOffset = 0;
	std::wstring wsCurrentMessage;

	unsigned int uiCarretPos = 0;

	const unsigned cuChatHistorySize = 100;
	const unsigned cuLinesOnScreen = 10;
	int(*_commandProcess)(std::string command) = nullptr;
public:
	static CChat* Get();

	void RegisterCommandProcessor(int(*callback)(std::string));

	void Scroll(ScrollRoute route);
	void Render();
	void Input();
	void AddChatMessage(std::string text, unsigned char red = 255, unsigned char green = 255, unsigned char blue = 255, unsigned char alpha = 255);
	void AddChatMessage(std::string text, UINT64 rgba);
	void AddChatMessage(std::string text, color_t color);
	void Clear();
	void Toggle();
	void Open();
	void Close();

	static void ScriptKeyboardMessage(DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow);

	~CChat();
};
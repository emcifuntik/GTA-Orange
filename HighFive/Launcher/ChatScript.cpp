#include "stdafx.h"
#include "Natives.h"

void ChatAction()
{
	keyboardHandlerRegister(CChat::ScriptKeyboardMessage);
	for (;;)
	{
		//CChat::Get()->Render();
		CChat::Get()->Input();
		scriptWait(0);
	}
}

SCRIPT("chatScript", ChatAction, chatScript);
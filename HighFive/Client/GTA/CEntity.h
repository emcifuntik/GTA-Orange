#pragma once

namespace GTA
{
	class CEntity// Size = 0xCC
	{
		virtual ~CEntity();
		char pad_0x0008[0x28]; //0x0008
		void *pad_1; // phInstGta* phInstGtaPtr; //0x0030 
		char pad_0x0038[0x10]; //0x0038
		void *pad_2; //CPedDrawHandler* CPedDrawHandlerPtr; //0x0048 
		char pad_0x0050[0x40]; //0x0050
		CVector3 Position; //0x0090 
		char pad_0x009C[0x30]; //0x009C
	};
}
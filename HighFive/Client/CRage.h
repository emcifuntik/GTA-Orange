#define STEAM_VERSION 1

class baseClass;
class CWorld;
class CPed;
class grcRenderTargetDX11;
class grcTextureDX11;
class Tasks;
class CPlayerInfo;
class CTaskTreePed;
class CTaskTree;
class CTaskTreeMotion;
class CEntity_;
class CPedInventory;
class CPedWeaponManager;
class CPedModelInfo;
class phInstGta;
class CPedDrawHandler;
class CTaskTreeMovement;
class CBuilding;
class CPedMethods;
class CPedWeaponManager_;
class CPedClothCollision;
class CPedTaskManager;
class CWeapon;
class CWeaponMethods_;
class CPedFactory;
class CVehicleFactory;
class CTaskTreeFunctions;
class CTaskTreeMovement_;

class baseClass
{
public:
	CWorld* CWorldPtr; //0x0000 
	grcRenderTargetDX11* grcRenderTargetDX11Ptr; //0x0008 
	char pad_0x0010[0x8]; //0x0010
	CPedModelInfo* CPedModelInfoPtr; //0x0018 
	char pad_0x0020[0x8]; //0x0020
	grcTextureDX11* grcTextureDX11Ptr; //0x0028 

}; //Size=0x0030

class CWorld
{
public:
	CPedFactory * CPedFactoryPtr;
	CPed * CPedPtr; //0x0008 

	static CWorld *Get()
	{
		if(Utils::IsSteam())
			return *(CWorld **)((intptr_t)GetModuleHandle(NULL) + 0x228FA58);
		else
			return *(CWorld **)((intptr_t)GetModuleHandle(NULL) + 0x228C910);
	}
}; //Size=0x0010

class CPed
{
public:
	CPedMethods* CPedMethods_; //0x0000 
	char pad_0x0008[0x18]; //0x0008
	CPedModelInfo* CPedModelInfoPtr; //0x0020 
	char pad_0x0028[0x8]; //0x0028
	phInstGta* phInstGtaPtr; //0x0030 
	char pad_0x0038[0x10]; //0x0038
	CPedDrawHandler* CPedDrawHandlerPtr; //0x0048 
	char pad_0x0050[0x40]; //0x0050
	CVector3 Position; //0x0090 
	char pad_0x009C[0x74]; //0x009C
	CVector3 Position2; //0x0110 
	char pad_0x011C[0x4]; //0x011C
	CVector3 Position3; //0x0120 
	char pad_0x012C[0x4]; //0x012C
	float Height; //0x0130 
	char pad_0x0134[0x2C]; //0x0134
	CVector3 Position4; //0x0160 
	char pad_0x016C[0x114]; //0x016C
	float Health; //0x0280 
	float MaxHealth; //0x0284 
	char pad_0x0288[0x2F0]; //0x0288
	float MoveSpeed; //0x0578 
	char pad_0x057C[0x624]; //0x057C
	CBuilding* CBuildingPtr; //0x0BA0 
	char pad_0x0BA8[0x4D8]; //0x0BA8
	Tasks* TasksPtr; //0x1080 
	CPlayerInfo* CPlayerInfoPtr; //0x1088 
	CPedInventory* CPedInventoryPtr; //0x1090 
	CPedWeaponManager* CPedWeaponManagerPtr; //0x1098 
	char pad_0x10A0[0x2A0]; //0x10A0
	CPedClothCollision* CPedClothCollisionPtr; //0x1340 
	char pad_0x1348[0x5A0]; //0x1348

}; //Size=0x18E8

class grcRenderTargetDX11
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class grcTextureDX11
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class Tasks
{
public:
	char pad_0x0000[0x358]; //0x0000
	CPedTaskManager* CPedTaskManagerPtr; //0x0358 
	CTaskTreePed* CTaskTreePedPtr; //0x0360 
	CTaskTree* CTaskTreePtr; //0x0368 
	CTaskTreeMovement* CTaskTreeMovementPtr; //0x0370 
	CTaskTreeMotion* CTaskTreeMotionPtr; //0x0378 
	char pad_0x0380[0x100]; //0x0380

}; //Size=0x0480

class CPlayerInfo
{
public:
	char pad_0x0000[0x210]; //0x0000
	float TimeSinceAim; //0x0210 
	__int32 AimState; //0x0214 
	__int32 CurrentWeaponHash; //0x0218 
	char pad_0x021C[0x44]; //0x021C
	CVector3 AimPosition; //0x0260 
	float AimLength; //0x026C 
	char pad_0x0270[0xA0]; //0x0270
	CEntity_* TargetEntity; //0x0310 
	char pad_0x0318[0x2B0]; //0x0318

}; //Size=0x05C8

class CTaskTreePed
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class CTaskTree
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class CTaskTreeMotion
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class CEntity_
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class CPedInventory
{
public:
	char pad_0x0000[0x48]; //0x0000

}; //Size=0x0048

class CPedWeaponManager
{
public:
	CPedWeaponManager_* CPedWeaponManagerMethods; //0x0000 
	char pad_0x0008[0x80]; //0x0008
	CWeapon* CWeaponPtr; //0x0088 
	char pad_0x0090[0x78]; //0x0090

}; //Size=0x0108

class CPedModelInfo
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class phInstGta
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class CPedDrawHandler
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class CTaskTreeMovement
{
public:
	CTaskTreeMovement_* CTaskTreeMovementMethods; //0x0000 
}; //Size=0x0008

class CBuilding
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class CPedMethods
{
public:
	virtual __int64 *func_1(__int64 a1, char a2) = 0; //0x0000 
	virtual bool *func_2(__int64 a1, int a2) = 0; //0x0008 
	char pad_0x0010[0x18]; //0x0010

}; //Size=0x0028

class CPedWeaponManager_
{
public:
	__int64 (*func_1)(__int64 a1, char a2); //0x0000 
	int (*func_2)(__int64 a1, unsigned int a2); //0x0008 
	int (*func_3)(__int64 a1, int a2, __int64 a3); //0x0010 
	int (*func_4)(__int64 a1); //0x0018

}; //Size=0x0020

class CPedClothCollision
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class CPedTaskManager
{
public:
	__int64 * (*func_1)(__int64 *a1, char a2); //0x0000 
}; //Size=0x0010

class CWeapon
{
public:
	CWeaponMethods_* CWeaponMethods; //0x0000 
	char pad_0x0008[0x10]; //0x0008

}; //Size=0x0018

class CWeaponMethods_
{
public:
	__int64(*Equip)(__int64 a1, char a2); //0x0000 
	char(*Shoot)(__int64 a1, CPed *a2, __int64 a3); //0x0008 
}; //Size=0x0010

class CPedFactory
{
public:
	__int64(*func_1)(CPedFactory* pedFactory, bool a2); //0x0000 
	__int64(*Create)(CPedFactory* pedFactory, unsigned char *a2, int *a3, __int64 a4, bool a5, bool networkEntity, bool a7); //0x0008 
	__int64(*func_3)(CPedFactory* *pedFactory, __int64 a2, int *a3, __int64 a4, int a5, bool a6); //0x0010 
	__int64(*func_4)(CPedFactory* pedFactory, __int64 a2, __int64 a3, bool a4, bool a5); //0x0018 
	void(*func_5)(CPedFactory* pedFactory, __int64 a2, __int64 a3, bool a4); //0x0020 
	__int64(*func_6)(CPedFactory* pedFactory, unsigned char *a2, __int64 a3, __int64 a4, __int64 a5); //0x0028 
	int(*func_7)(CPedFactory* pedFactory, __int64 a2); //0x0030 

}; //Size=0x0038

class PedFactoryHook
{
	static PedFactoryHook* singleInstance;
public:
	PedFactoryHook() {}
	static PedFactoryHook* Get()
	{
		if(!singleInstance)
			singleInstance = new PedFactoryHook();
		return singleInstance;
	}
	__int64(*CreateHook)(CPedFactory* pedFactory, unsigned char *a2, int *a3, __int64 a4, bool a5, bool networkEntity, bool a7);
};

inline __int64 hookCreatePed(CPedFactory* pedFactory, unsigned char *a2, int *a3, __int64 a4, bool a5, bool networkEntity, bool a7)
{
	return (__int64)nullptr;
}

class CVehicleFactory
{
public:
	//__int64(*func_1)(CVehicleFactory* vehicleFactory, bool a2); //0x0000 
	__int64(*Create)(__int64 a1, __int64 a2, unsigned int a3, unsigned int a4, float a5, signed int *a6, char a7, char a8);
	__int64(*func_3)(int *a1, __int64 a2, __int64 a3, __int64 a4, float a5, unsigned int a6, unsigned int a7, bool a8); //0x0010 
	int(*func_4)(CVehicleFactory* vehicleFactory, __int64 a2, unsigned int a3, unsigned int a4, unsigned int a5, __int64 *a6); //0x0018 
	char(*func_5)(CVehicleFactory* vehicleFactory, __int64 a2, unsigned int a3, unsigned int a4, unsigned int a5, WORD *a6); //0x0020 
	char pad_0x0028[0x60]; //0x0028
	static CVehicleFactory* Get()
	{
		if (Utils::IsSteam())
			return (CVehicleFactory*)((intptr_t)GetModuleHandle(NULL) + 0x18DFD70);
		else
			return (CVehicleFactory*)((intptr_t)GetModuleHandle(NULL) + 0x18DCD80);
	}
}; //Size=0x0088
class VehicleFactoryHook
{
	static VehicleFactoryHook* singleInstance;
public:
	VehicleFactoryHook() {}
	static VehicleFactoryHook* Get()
	{
		if (!singleInstance)
			singleInstance = new VehicleFactoryHook();
		return singleInstance;
	}
	__int64(*CreateHook)(__int64 a1, __int64 a2, unsigned int a3, unsigned int a4, float a5, signed int *a6, char a7, char a8);
};

inline __int64 hookCreateVehicle(__int64 a1, __int64 a2, unsigned int a3, unsigned int a4, float a5, signed int *a6, char a7, char a8)
{
	return (__int64)nullptr;
}
//
//class CTaskTreeFunctions
//{
//public:
//	int64_t(*func_1)(int64_t a1, int32_t a2); //0x0000 
//	char pad_0x0008[0x8]; //0x0008
//	char(*func_3)(int64_t ptr1, int64_t ptr2, int a3); //0x0010 
//	int(*func_4)(int64_t ptr1, signed char a2, uint32_t a3); //0x0018 
//	int64_t(*func_5)(int64_t ptr1, int64_t ptr2, float a3); //0x0020 
//	char pad_0x0028[0x18]; //0x0028
//	char(*func_9)(int64_t a1, int64_t a2, unsigned int a3, char a4); //0x0040 
//	char pad_0x0048[0x8]; //0x0048
//	static CTaskTreeFunctions* Get()
//	{
//		return (CTaskTreeFunctions*)((intptr_t)GetModuleHandle(NULL) + 0x1838038);
//	}
//}; //Size=0x0050
//
//class CTaskTreeMovement_
//{
//public:
//	int64_t* (*func_1)(int64_t* a1, int32_t a2); //0x0000 
//	void(*func_2)(int64_t a1); //0x0008 
//	void(*func_3)(int64_t* a1, int64_t a2, int32_t a3); //0x0010 
//	void* (*func_4)(int64_t a1, signed char a2, uint32_t a3); //0x0018 
//	int64_t(*func_5)(int64_t a1, int64_t a2, float a3); //0x0020 
//	char pad_0x0028[0x18]; //0x0028
//	char(*func_9)(int64_t a1, int64_t a2, unsigned int a3, char a4); //0x0040 
//
//}; //Size=0x0048

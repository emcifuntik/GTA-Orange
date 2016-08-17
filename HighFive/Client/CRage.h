#pragma once

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
class CModelInfo;
class CPedModelInfo;
class CVehicleModelInfo;
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
class VTasks;

namespace GTA
{
	class CVehicle;
	class CTask;
};

namespace rageGlobals
{
	void AllowChangeLanguage(bool toggle);
};

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
	CPedModelInfo* PedModelInfo; //0x0020 
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
	char pad_0x1348[0x78]; //0x1348
	int64_t Flags; //0x13C0 
	char pad_0x13C8[0xD0]; //0x13C8
	GTA::CVehicle* pedVehicle; //0x1498 
	char pad_0x14A0[0x450]; //0x14A0

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
	CTaskTree* PrimaryTasks; //0x0360 
	CTaskTree* SecondaryTasks; //0x0368 
	CTaskTree* MovementTasks; //0x0370 
	CTaskTree* MotionTasks; //0x0378 
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
	virtual ~CTaskTree();
	virtual int Clear();
	virtual void AssignTask(GTA::CTask *task, int taskPriority);
	virtual int Play(bool reset, int taskPriority, float speed);
	virtual int AddTask(GTA::CTask *task, float some = 0.f);
	CPed *TaskOwner;
	int32_t ActiveTask;
	int32_t field_4;
	int32_t field_5;
	int32_t field_6;
	GTA::CTask *TasksArray[5];

	GTA::CTask* GetTask()
	{
		if (ActiveTask < 0)
			return nullptr;
		else
			return TasksArray[ActiveTask];
	}
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

class CModelInfo
{
public:
	void* vtable;
	char pad_0x0008[0x10];
	int64_t ModelHash;
};

class CPedModelInfo : public CModelInfo
{
public:
	char pad_0x0020[0xA8]; //0x0020

}; //Size=0x0008

class CVehicleModelInfo : public CModelInfo
{
public:
	char pad_0x0020[0xA8]; //0x0020

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

namespace GTA
{
	class CVehicle
	{
	public:
		char pad_0x0000[0x20]; //0x008
		CVehicleModelInfo *VehicleModelInfo;
		char pad_0x0018[0x70]; //0x0018
		CVector3 Position; //0x0090 
		char pad_0x009C[0x1624]; //0x009C
	}; //Size=0x16C0

	class CObject
	{
	public:
		char pad_0x0000[0x20];
		CModelInfo *ModelInfo;
		char pad_0x0028[0x68]; //0x0028
		CVector3 Position; //0x0090 
	};

	class CTask
	{
	public:
		virtual ~CTask();
		virtual int64_t GetID();
		virtual CTask* Clone();
		virtual void unknown_3();
		virtual bool IsSimple();
		virtual void unknown_5();
		virtual void unknown_6();
		virtual void unknown_7();
		virtual void unknown_8();
		virtual void unknown_9();
		virtual void unknown_10();
		virtual void unknown_11();
		virtual void unknown_12();
		virtual void unknown_13();
		virtual void unknown_14();
		virtual void unknown_15();
		virtual void unknown_16();
		virtual void unknown_17();
		virtual void unknown_18();
		virtual void unknown_19();
		virtual void unknown_20();
		virtual void unknown_21();
		virtual void unknown_22();
		virtual void unknown_23();
		virtual void unknown_24();
		virtual void unknown_25();
		virtual void unknown_26();
		virtual void unknown_27();
		virtual void unknown_28();
		virtual void unknown_29();
		virtual void unknown_30();
		virtual void unknown_31();
		virtual void unknown_32();
		virtual void unknown_33();
		virtual void unknown_34();
		virtual void unknown_35();
		virtual void unknown_36();
		virtual void unknown_37();
		virtual void unknown_38();
		virtual void unknown_39();
		virtual void unknown_40();
		virtual void unknown_41();
		virtual void unknown_42();
		virtual void unknown_43();
		virtual void unknown_44();
		virtual bool IsSerializable();
		virtual void* Serialize();

		void *somePtr;
		CPed *targetPed;
		CTask *Parent;
		CTask *Child;

		std::string GetTree(CTask *task = nullptr, int n = 0);
	};
};

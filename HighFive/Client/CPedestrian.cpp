#include "stdafx.h"

CPedestrian::CPedestrian(Hash Model, CVector3 Position, float Heading) :CEntity(-1)
{
	STREAMING::REQUEST_MODEL(Model);
	while (!STREAMING::HAS_MODEL_LOADED(Model))
		WAIT(1);
	Handle = (Entity)PED::CREATE_PED(1, Model, Position.fX, Position.fY, Position.fZ, Heading, true, false);
}

CPedestrian::CPedestrian(Ped handle) :CEntity(handle)
{
}

CPedestrian::~CPedestrian()
{
	PED::DELETE_PED(&Handle);
}

void CPedestrian::SetDesiredHeading(float heading)
{
	PED::SET_PED_DESIRED_HEADING(Handle, heading);
}

void CPedestrian::GetMoveSpeed(CVector3& vecMoveSpeed)
{
	Vector3 vec = ENTITY::GET_ENTITY_SPEED_VECTOR(Handle, false);
	vecMoveSpeed = CVector3(vec.x, vec.y, vec.z);
}

void CPedestrian::TaskMove(CVector3 vecPos, float fMoveSpeed)
{
	AI::TASK_GO_STRAIGHT_TO_COORD(Handle, vecPos.fX, vecPos.fY, vecPos.fZ, fMoveSpeed, -1, 0.0f, 0.0f);
}

void CPedestrian::ClearTasks()
{
	AI::CLEAR_PED_TASKS(Handle);
}

void CPedestrian::SetModel(Hash model)
{
	//ENTITY::SET_MODEL 
}

bool CPedestrian::IsDucking()
{
	return (PED::IS_PED_DUCKING(Handle)) ? true : false;
}

void CPedestrian::SetDucking(bool ducking)
{
	PED::SET_PED_DUCKING(Handle, ducking);
}

bool CPedestrian::IsJumping()
{
	return (PED::IS_PED_JUMPING(Handle)) ? true : false;
}

void CPedestrian::TaskJump()
{
	AI::TASK_JUMP(Handle, false);
}

void CPedestrian::SetCoordsKeepVehicle(float x, float y, float z)
{
	PED::SET_PED_COORDS_KEEP_VEHICLE(Handle, x, y, z);
}

void CPedestrian::SetArmour(unsigned short armour)
{
	PED::SET_PED_ARMOUR(Handle, armour);
}

unsigned short CPedestrian::GetArmour()
{
	return PED::GET_PED_ARMOUR(Handle);
}

Hash CPedestrian::GetCurrentWeapon()
{
	Hash weapon;
	WEAPON::GET_CURRENT_PED_WEAPON(Handle, &weapon, TRUE);
	return weapon;
}

void CPedestrian::SetCurrentWeapon(Hash weapon, bool equipNow /*= TRUE*/)
{
	WEAPON::SET_CURRENT_PED_WEAPON(Handle, weapon, equipNow);
}

unsigned int CPedestrian::GetCurrentWeaponAmmo()
{
	return WEAPON::GET_AMMO_IN_PED_WEAPON(Handle, GetCurrentWeapon());
}

unsigned int CPedestrian::GetAmmo(Hash weapon)
{
	return WEAPON::GET_AMMO_IN_PED_WEAPON(Handle, weapon);
}

void CPedestrian::SetAmmo(Hash weapon, unsigned int ammo)
{
	WEAPON::SET_PED_AMMO(Handle, weapon, ammo);
}

float CPedestrian::GetBlendRation()
{
	return AI::GET_PED_DESIRED_MOVE_BLEND_RATIO(Handle);
}

void CPedestrian::SetComponentVariation(int component, int drawable, int texture, int palette)
{
	PED::SET_PED_COMPONENT_VARIATION(Handle, component, drawable, texture, palette);
}

void CPedestrian::SetMoney(int money)
{
	PED::SET_PED_MONEY(Handle, money);
}

void CPedestrian::GiveMoney(int money)
{
	PED::SET_PED_MONEY(Handle, GetMoney() + money);
}

int CPedestrian::GetMoney()
{
	return PED::GET_PED_MONEY(Handle);
}

void CPedestrian::GiveWeapon(Hash weapon, int ammo)
{
	WEAPON::GIVE_WEAPON_TO_PED(Handle, weapon, ammo, false, false);
}

void CPedestrian::RemoveWeapon(Hash weapon)
{
	WEAPON::REMOVE_WEAPON_FROM_PED(Handle, weapon);
}

void CPedestrian::RemoveAllWeapons()
{
	WEAPON::REMOVE_ALL_PED_WEAPONS(Handle, true);
}

void CPedestrian::SetAmmo(Hash weapon, int ammo)
{
	WEAPON::SET_PED_AMMO(Handle, weapon, ammo);
}

void CPedestrian::AddAmmo(Hash weapon, int ammo)
{
	WEAPON::ADD_AMMO_TO_PED(Handle, weapon, ammo);
}

void CPedestrian::RemoveAmmo(Hash weapon, int ammo)
{
	WEAPON::SET_PED_AMMO(Handle, weapon, WEAPON::GET_AMMO_IN_PED_WEAPON(Handle, weapon) - ammo);
}

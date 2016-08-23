#include "stdafx.h"

namespace Player
{
	PyObject *setPos(PyObject * self, PyObject* args)
	{
		unsigned int playerID;
		float x, y, z;
		if (!PyArg_ParseTuple(args, "Ifff", &playerID, &x, &y, &z))
		{
			return NULL;
		}
		auto player = CNetworkPlayer::GetByID(playerID);
		if (!player)
			return PyBool_FromLong(0L);
		player->SetPosition(CVector3(x, y, z));
		return PyBool_FromLong(1L);
	}
	PyObject * getPos(PyObject * self, PyObject * args)
	{
		unsigned int playerID;
		if (!PyArg_ParseTuple(args, "I", &playerID))
		{
			return NULL;
		}
		auto player = CNetworkPlayer::GetByID(playerID);
		if (!player)
			return Py_BuildValue("{s:f,s:f,s:f}", "x", 0.0, "y", 0.0, "z", 0.0);
		CVector3 vecPos;
		player->GetPosition(vecPos);
		return Py_BuildValue("{s:f,s:f,s:f}", "x", vecPos.fX, "y", vecPos.fY, "z", vecPos.fZ);
	}
	PyObject * isInRange(PyObject * self, PyObject * args)
	{
		unsigned int playerID;
		float x, y, z, range;
		if (!PyArg_ParseTuple(args, "Iffff", &playerID, &x, &y, &z, &range))
		{
			return NULL;
		}
		auto player = CNetworkPlayer::GetByID(playerID);
		if (!player)
			return PyBool_FromLong(0L);
		CVector3 vecPos, vecNextPos(x, y, z);
		player->GetPosition(vecPos);
		if((vecNextPos - vecPos).Length() <= range)
			return PyBool_FromLong(1L);
		return PyBool_FromLong(0L);
	}
	PyObject * setHeading(PyObject * self, PyObject * args)
	{
		unsigned int playerID;
		float a;
		if (!PyArg_ParseTuple(args, "If", &playerID, &a))
		{
			return NULL;
		}
		auto player = CNetworkPlayer::GetByID(playerID);
		if (!player)
			return PyBool_FromLong(0L);
		player->SetHeading(a);
		return PyBool_FromLong(1L);
	}
	PyObject * giveWeapon(PyObject * self, PyObject * args)
	{
		unsigned int playerID, weapon, ammo;
		
		if (!PyArg_ParseTuple(args, "III", &playerID, &weapon, &ammo))
		{
			return NULL;
		}
		auto player = CNetworkPlayer::GetByID(playerID);
		if (!player)
			return PyBool_FromLong(0L);
		player->GiveWeapon(weapon, ammo);
		return PyBool_FromLong(1L);
	}
	PyObject * giveAmmo(PyObject * self, PyObject * args)
	{
		unsigned int playerID, weapon, ammo;

		if (!PyArg_ParseTuple(args, "III", &playerID, &weapon, &ammo))
		{
			return NULL;
		}
		auto player = CNetworkPlayer::GetByID(playerID);
		if (!player)
			return PyBool_FromLong(0L);
		player->GiveAmmo(weapon, ammo);
		return PyBool_FromLong(1L);
	}
	PyObject * giveMoney(PyObject * self, PyObject * args)
	{
		unsigned int playerID, money;

		if (!PyArg_ParseTuple(args, "Ii", &playerID, &money))
		{
			return NULL;
		}
		auto player = CNetworkPlayer::GetByID(playerID);
		if (!player)
			return PyBool_FromLong(0L);
		player->GiveMoney(money);
		return PyBool_FromLong(1L);
	}
	PyObject * setMoney(PyObject * self, PyObject * args)
	{
		unsigned int playerID, money;

		if (!PyArg_ParseTuple(args, "Ii", &playerID, &money))
		{
			return NULL;
		}
		auto player = CNetworkPlayer::GetByID(playerID);
		if (!player)
			return PyBool_FromLong(0L);
		player->SetMoney(money);
		return PyBool_FromLong(1L);
	}
	PyObject * resetMoney(PyObject * self, PyObject * args)
	{
		unsigned int playerID;

		if (!PyArg_ParseTuple(args, "I", &playerID))
		{
			return NULL;
		}
		auto player = CNetworkPlayer::GetByID(playerID);
		if (!player)
			return PyBool_FromLong(0L);
		player->SetMoney(0);
		return PyBool_FromLong(1L);
	}
	PyObject * getMoney(PyObject * self, PyObject * args)
	{
		unsigned int playerID;

		if (!PyArg_ParseTuple(args, "I", &playerID))
		{
			return NULL;
		}
		auto player = CNetworkPlayer::GetByID(playerID);
		if (!player)
			return PyInt_FromLong(0L);
		int money = player->GetMoney();
		return PyInt_FromLong(money);
	}
	PyObject * setModel(PyObject * self, PyObject * args)
	{
		unsigned int playerID, model;

		if (!PyArg_ParseTuple(args, "II", &playerID, &model))
		{
			return NULL;
		}
		auto player = CNetworkPlayer::GetByID(playerID);
		if (!player)
			return PyBool_FromLong(0L);
		player->SetModel(model);
		return PyBool_FromLong(1L);
	}
	PyObject * getModel(PyObject * self, PyObject * args)
	{
		unsigned int playerID;

		if (!PyArg_ParseTuple(args, "I", &playerID))
		{
			return NULL;
		}
		auto player = CNetworkPlayer::GetByID(playerID);
		if (!player)
			return PyBool_FromLong(0L);
		return PyBool_FromLong(player->GetModel());
	}
	PyObject * setName(PyObject * self, PyObject * args)
	{
		unsigned int playerID;
		char name[32];

		if (!PyArg_ParseTuple(args, "Is", &playerID, name))
		{
			return NULL;
		}
		auto player = CNetworkPlayer::GetByID(playerID);
		if (!player)
			return PyBool_FromLong(0L);
		player->SetName(name);
		return PyBool_FromLong(1L);
	}
	PyObject * getName(PyObject * self, PyObject * args)
	{
		unsigned int playerID;

		if (!PyArg_ParseTuple(args, "I", &playerID))
		{
			return NULL;
		}
		auto player = CNetworkPlayer::GetByID(playerID);
		if (!player)
			return PyBool_FromLong(0L);
		return PyString_FromString(player->GetName().c_str());
	}
	PyObject * setHealth(PyObject * self, PyObject * args)
	{
		unsigned int playerID;
		float health;

		if (!PyArg_ParseTuple(args, "If", &playerID, &health))
		{
			return NULL;
		}
		auto player = CNetworkPlayer::GetByID(playerID);
		if (!player)
			return PyBool_FromLong(0L);
		player->SetHealth(health);
		return PyBool_FromLong(1L);
	}
	PyObject * getHealth(PyObject * self, PyObject * args)
	{
		unsigned int playerID;

		if (!PyArg_ParseTuple(args, "I", &playerID))
		{
			return NULL;
		}
		auto player = CNetworkPlayer::GetByID(playerID);
		if (!player)
			return PyFloat_FromDouble(0.0);
		return PyFloat_FromDouble(player->GetHealth());
	}
	PyObject * setArmour(PyObject * self, PyObject * args)
	{
		unsigned int playerID;
		float armour;

		if (!PyArg_ParseTuple(args, "If", &playerID, &armour))
		{
			return NULL;
		}
		auto player = CNetworkPlayer::GetByID(playerID);
		if (!player)
			return PyBool_FromLong(0L);
		player->SetArmour(armour);
		return PyBool_FromLong(1L);
	}
	PyObject * getArmour(PyObject * self, PyObject * args)
	{
		unsigned int playerID;

		if (!PyArg_ParseTuple(args, "I", &playerID))
		{
			return NULL;
		}
		auto player = CNetworkPlayer::GetByID(playerID);
		if (!player)
			return PyFloat_FromDouble(0.0);
		return PyFloat_FromDouble(player->GetArmour());
	}
	PyObject * setColor(PyObject * self, PyObject * args)
	{
		unsigned int playerID, color;

		if (!PyArg_ParseTuple(args, "II", &playerID, &color))
		{
			return NULL;
		}
		auto player = CNetworkPlayer::GetByID(playerID);
		if (!player)
			return PyBool_FromLong(0L);
		player->SetColor(color);
		return PyBool_FromLong(1L);
	}
	PyObject * getColor(PyObject * self, PyObject * args)
	{
		unsigned int playerID;

		if (!PyArg_ParseTuple(args, "I", &playerID))
		{
			return NULL;
		}
		auto player = CNetworkPlayer::GetByID(playerID);
		if (!player)
			return PyLong_FromLong(0L);
		color_t playerColor = player->GetColor();
		return PyLong_FromLong(((playerColor.red & 0xff) << 24) + ((playerColor.green & 0xff) << 16) + ((playerColor.blue & 0xff) << 8) + (playerColor.alpha & 0xff));
	}
	PyObject * getIP(PyObject * self, PyObject * args)
	{
		unsigned int playerID;

		if (!PyArg_ParseTuple(args, "I", &playerID))
		{
			return NULL;
		}
		auto player = CNetworkPlayer::GetByID(playerID);
		if (!player)
			return PyString_FromString("0.0.0.0");
		//color_t playerColor = player->GetIP();
		return PyString_FromString("0.0.0.0");
	}
};
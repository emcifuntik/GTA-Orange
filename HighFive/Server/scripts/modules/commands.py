# -*- coding: cp1251 -*-
import World
import Player

def isInt(a):
    try:
        int(a)
        return True
    except:
        return False

def isFloat(a):
    try:
        float(a)
        return True
    except:
        return False
	
def cmd_makeadmin( playerid, args ):
	Player.sendMessage( playerid, " * �� ��������� ��������������� %d ������" % 10, 0xFF0000FF)
	return 1
	
def cmd_tp( playerid, args ):
    if len(args) == 1:
        if isInt(args[0]):
            pos = Player.getPos(int(args[0]))
            Player.setPos(playerid, pos['x'], pos['y'], pos['z'])
            Player.sendMessage(playerid, "�� ����������������� � %s" % Player.getName(int(args[0])), 0x00FF00FF)
            return 1
    elif len(args) == 2:
        if isInt(args[0]) and isInt(args[1]):
            pos = Player.getPos(int(args[0]))
            Player.setPos(int(args[1]), pos['x'], pos['y'], pos['z'])
            Player.sendMessage(playerid, "�� ��������������� %s � %s" %(Player.getName(int(args[0])), Player.getName(int(args[1]))), 0x00FF00FF)
            return 1
    elif len(args) == 3:
        if isFloat(args[0]) and isFloat(args[1]) and isFloat(args[2]):
            Player.setPos(playerid, float(args[0]), float(args[1]), float(args[2]))
            Player.sendMessage(playerid, "�� ����������������� �� x: %s y: %s z: %s" %(args[0], args[1], args[2]), 0x00FF00FF)
            return 1
    Player.sendMessage(playerid, "������. �������������: /tp x y z ��� /tp ID ��� /tp ID1 ID2", 0x00FF00FF)
    return 1

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
	Player.sendMessage( playerid, " * Вы назначены администратором %d уровня" % 10, 0xFF0000FF)
	return 1
	
def cmd_tp( playerid, args ):
    if len(args) == 1:
        if isInt(args[0]):
            pos = Player.getPos(int(args[0]))
            Player.setPos(playerid, pos['x'], pos['y'], pos['z'])
            Player.sendMessage(playerid, "Вы телепортировались к %s" % Player.getName(int(args[0])), 0x00FF00FF)
            return 1
    elif len(args) == 2:
        if isInt(args[0]) and isInt(args[1]):
            pos = Player.getPos(int(args[0]))
            Player.setPos(int(args[1]), pos['x'], pos['y'], pos['z'])
            Player.sendMessage(playerid, "Вы телепортировали %s к %s" %(Player.getName(int(args[0])), Player.getName(int(args[1]))), 0x00FF00FF)
            return 1
    elif len(args) == 3:
        if isFloat(args[0]) and isFloat(args[1]) and isFloat(args[2]):
            Player.setPos(playerid, float(args[0]), float(args[1]), float(args[2]))
            Player.sendMessage(playerid, "Вы телепортировались на x: %s y: %s z: %s" %(args[0], args[1], args[2]), 0x00FF00FF)
            return 1
    Player.sendMessage(playerid, "Ошибка. Использование: /tp x y z или /tp ID или /tp ID1 ID2", 0x00FF00FF)
    return 1

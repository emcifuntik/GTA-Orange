# -*- coding: utf-8 -*-
import World
import Player

def onScriptInit():
	World.printMessage("Gamemode loaded")
	print World.hash("adder")
	
def onServerCommand( command ):
	World.printMessage("Server command")
	
def onPlayerConnect( playerid ):
	World.printMessage("Player [ID:%d] connected" % playerid)
	Player.setPos(playerid, -634.78, -719.33, 31.55)
	Player.broadcastMessage( " ~g~* Player ~r~%s [ %d ]~g~ connected to server" % (Player.getName( playerid ), playerid), 0x00FF00FF )
	return 0
	
def onPlayerDisconnect( playerid, reason ):
	World.printMessage("Player [ID:%d] disconnected" % playerid)
	
def onPlayerText( playerid, text ):
	World.printMessage("Player [ID:%d] text: %s" % (playerid, text))
	return 0
	
def onPlayerUpdate( playerid ):
	return 0
	
def _cmd_makeadmin( playerid, args ):
	Player.sendMessage( playerid, " * Вы назначены администратором %d уровня" % 10)
	return 1
	
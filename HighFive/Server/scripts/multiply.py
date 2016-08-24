import World
import Player

def onScriptInit():
	World.printMessage("Gamemode loaded")
	print World.hash("adder")
	
def onServerCommand( command ):
	World.printMessage("Server command")
	
def onPlayerConnect( playerid ):
	print "Player [ ID:", playerid, "] connected"
	Player.setPos(playerid, 0.0, 0.0, 75.0);
	Player.giveWeapon(playerid, World.hash("WEAPON_ADVANCEDRIFLE"), 30);
	
def onPlayerDisconnect( playerid, reason ):
	print "Player [ ID:", playerid, "] disconnected"
	
def onPlayerText( playerid, text ):
	print "Player [ ID:", playerid, "] text:", text
	return 0
	
def onPlayerUpdate( playerid ):
	return 0
	
def _cmd_makeadmin( playerid, args ):
	World.printMessage("makeadmin");
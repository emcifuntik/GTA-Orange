import World
import Player

def OnScriptInit():
	World.printMessage("Gamemode loaded")
	print World.hash("adder")
	
def OnServerCommand( command ):
	World.printMessage("Server command")
	
def OnPlayerConnect( playerid ):
	print "Player [ ID:", playerid, "] connected"
	Player.setPos(playerid, 0.0, 0.0, 0.0);
	
def OnPlayerDisconnect( playerid, reason ):
	print "Player [ ID:", playerid, "] disconnected"
	
def OnPlayerText( playerid, text ):
	print "Player [ ID:", playerid, "] text:", text

def OnPlayerCommand( playerid, command ):
	print "Player [ ID:", playerid, "] command:", command
	
def OnPlayerUpdate( playerid ):
	print "Player [ ID:", playerid, "] updated"
	
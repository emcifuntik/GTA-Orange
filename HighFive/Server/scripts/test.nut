function onPlayerConnect(playerid)
{
	print("Player ID: " + playerid + ", name: " + getPlayerName(playerid) + " connected.\n");
	
	//setPlayerPos(playerid, 100.0, 100.0, 80.0);
	return 1;
}

function onPlayerDisconnect(playerid, reason)
{
	print("Player " + getPlayerName(playerid) + " disconnected(Reason - " + reason + ".\n");
	return 1;
}

function onPlayerUpdate(playerid)
{
	//print("Player " + getPlayerName(playerid) + " update.\n");
	return true;
}


function onScriptLoaded()
{

}

function onScriptUnloaded()
{

}

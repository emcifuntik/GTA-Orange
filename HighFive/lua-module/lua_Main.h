#pragma once

//Main
int lua_print(lua_State *L);

//Player
int lua_PlayerExists(lua_State *L);
int lua_GetPlayerName(lua_State *L);
int lua_GetPlayerCoords(lua_State *L);
int lua_SetPlayerInfoMsg(lua_State *L);

//Blips
int lua_CreateBlipForAll(lua_State *L);
/*************************************************
* LuaGL - an OpenGL binding for Lua
* 2003-2007(c) Fabio Guerra, Cleyde Marlyse
* luagl.sourceforge.net
*-------------------------------------------------
* See Copyright Notice in LuaGL.h
*************************************************/

#ifndef __LUAGLUT_H__
#define __LUAGLUT_H__

#ifdef __cplusplus
extern "C" {
#endif

#define LUAGLUT_VERSION "1.02-beta"

#ifdef _WIN32
  #ifdef BUILDING_LUAGLUT_DLL
    #define LUAGLUT_API __declspec(dllexport)
  #else
    #define LUAGLUT_API __declspec(dllimport)
  #endif
  #include <windows.h>
#else
  #ifdef BUILDING_LUAGLUT_DLL
    #define LUAGLUT_API
  #else
    #define LUAGLUT_API extern
  #endif
#endif

#include <lualib.h>

LUAGLUT_API int luaopen_LuaGlut (lua_State *L);

#ifdef __cplusplus
}
#endif

#endif


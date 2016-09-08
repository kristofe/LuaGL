/*************************************************
*  LuaGL - an OpenGL binding for Lua
*  2003-2007(c) Fabio Guerra, Cleyde Marlyse
*  luagl.sourceforge.net
*-------------------------------------------------
*  Description: This file implements the GLUT
*               binding for Lua 5.0.
*-------------------------------------------------
*  Last Update: 30/12/2007
*  Version: v1.02-beta
*-------------------------------------------------
*  See Copyright Notice in LuaGL.h
*************************************************/

#include <stdlib.h>
#include <string.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

/*#include "glut.h"*/

#ifndef GLUT_API_VERSION
  #if defined(macintosh) || defined(__APPLE__) || defined(OSX)
    #include <GLUT/glut.h>
  #elif defined (__linux__) || defined (UNIX) || defined(WIN32) || defined(_WIN32)
    #include "GL/glut.h"
  #endif
#endif

#define BUILDING_LUAGLUT_DLL

#include "LuaGlut.h"

typedef struct callbackFunc_typ {
  const char *name;
  lua_State *luastate;
} callbackFunc;


static callbackFunc displayFunc;
static callbackFunc keyboardFunc;
static callbackFunc mouseFunc;
static callbackFunc motionFunc;
static callbackFunc passiveMotionFunc;
static callbackFunc specialFunc;
static callbackFunc reshapeFunc;
static callbackFunc idleFunc;

static void display_func(void)
{
   lua_getglobal(displayFunc.luastate, displayFunc.name);

   if(!lua_isfunction(displayFunc.luastate, -1))
      printf("Script error: cannot find %s function.\n\n", displayFunc.name);

   else if(lua_pcall(displayFunc.luastate, 0, 0, 0))
   {
      printf("Error running lua script:\n\n  %s \n\n", lua_tostring(displayFunc.luastate, -1));
      lua_pop(displayFunc.luastate, 1);
   }
}

static void keyboard_func(unsigned char key, int x, int y)
{
   lua_getglobal(keyboardFunc.luastate, keyboardFunc.name);

   if(!lua_isfunction(keyboardFunc.luastate, -1))
      printf("Script error: cannot find %s function.\n\n", keyboardFunc.name);
   else
   {
      lua_pushnumber(keyboardFunc.luastate, key);
      lua_pushnumber(keyboardFunc.luastate, x);
      lua_pushnumber(keyboardFunc.luastate, y);

      if(lua_pcall(keyboardFunc.luastate, 3, 0, 0))
      {
         printf("Error running lua script:\n\n  %s \n\n", lua_tostring(keyboardFunc.luastate, -1));
         lua_pop(keyboardFunc.luastate, 1);
      }
   }
}

static void mouse_func(int button, int state, int x, int y)
{
   lua_getglobal(mouseFunc.luastate, mouseFunc.name);

   if(!lua_isfunction(mouseFunc.luastate, -1))
      printf("Script error: cannot find %s function.\n\n", mouseFunc.name);
   else
   {
      lua_pushnumber(mouseFunc.luastate, button);
      lua_pushnumber(mouseFunc.luastate, state);
      lua_pushnumber(mouseFunc.luastate, x);
      lua_pushnumber(mouseFunc.luastate, y);

      if(lua_pcall(mouseFunc.luastate, 4, 0, 0))
      {
         printf("Error running lua script:\n\n  %s \n\n", lua_tostring(mouseFunc.luastate, -1));
         lua_pop(mouseFunc.luastate, 1);
      }
   }
}

static void motion_func(int x, int y)
{
   lua_getglobal(motionFunc.luastate, motionFunc.name);

   if(!lua_isfunction(motionFunc.luastate, -1))
      printf("Script error: cannot find %s function.\n\n", motionFunc.name);
   else
   {
      lua_pushnumber(motionFunc.luastate, x);
      lua_pushnumber(motionFunc.luastate, y);

      if(lua_pcall(motionFunc.luastate, 2, 0, 0))
      {
         printf("Error running lua script:\n\n  %s \n\n", lua_tostring(motionFunc.luastate, -1));
         lua_pop(motionFunc.luastate, 1);
      }
   }
}

static void passive_motion_func(int x, int y)
{
   lua_getglobal(passiveMotionFunc.luastate, passiveMotionFunc.name);

   if(!lua_isfunction(passiveMotionFunc.luastate, -1))
      printf("Script error: cannot find %s function.\n\n", passiveMotionFunc.name);
   else
   {
      lua_pushnumber(passiveMotionFunc.luastate, x);
      lua_pushnumber(passiveMotionFunc.luastate, y);

      if(lua_pcall(passiveMotionFunc.luastate, 2, 0, 0))
      {
         printf("Error running lua script:\n\n  %s \n\n", lua_tostring(passiveMotionFunc.luastate, -1));
         lua_pop(passiveMotionFunc.luastate, 1);
      }
   }
}

static void special_func(int key, int x, int y)
{
   lua_getglobal(specialFunc.luastate, specialFunc.name);

   if(!lua_isfunction(specialFunc.luastate, -1))
      printf("Script error: cannot find %s function.\n\n", specialFunc.name);
   else
   {
      lua_pushnumber(specialFunc.luastate, key);
      lua_pushnumber(specialFunc.luastate, x);
      lua_pushnumber(specialFunc.luastate, y);

      if(lua_pcall(specialFunc.luastate, 3, 0, 0))
      {
         printf("Error running lua script:\n\n  %s \n\n", lua_tostring(specialFunc.luastate, -1));
         lua_pop(specialFunc.luastate, 1);
      }
   }
}

static void reshape_func(int width, int height)
{
   lua_getglobal(reshapeFunc.luastate, reshapeFunc.name);

   if(!lua_isfunction(reshapeFunc.luastate, -1))
      printf("Script error: cannot find %s function.\n\n", reshapeFunc.name);

   else
   {
      lua_pushnumber(reshapeFunc.luastate, width);
      lua_pushnumber(reshapeFunc.luastate, height);

      if(lua_pcall(reshapeFunc.luastate, 2, 0, 0))
      {
         printf("Error running lua script:\n\n  %s \n\n", lua_tostring(reshapeFunc.luastate, -1));
         lua_pop(reshapeFunc.luastate, 1);
      }
   }
}

static void idle_func(void)
{
   lua_getglobal(idleFunc.luastate, idleFunc.name);

   if(!lua_isfunction(idleFunc.luastate, -1))
      printf("Script error: cannot find %s function.\n\n", idleFunc.name);

   else if(lua_pcall(idleFunc.luastate, 0, 0, 0))
   {
      printf("Error running lua script:\n\n  %s \n\n", lua_tostring(idleFunc.luastate, -1));
      lua_pop(idleFunc.luastate, 1);
   }
}

/*Init () -> none*/
static int glut_init(lua_State *L)
{
   int argc = 1;
   char *argv = (char *)malloc(sizeof(char));
   *argv = 0;

   glutInit(&argc, &argv);

   free(argv);
   return 0;
}

/*InitDisplayMode () -> none*/
static int glut_init_display_mode(lua_State *L)
{
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
   return 0;
}

/*CreateWindow (title) -> windowId*/
static int glut_create_window(lua_State *L)
{
   int windowId = glutCreateWindow((const char *)luaL_checkstring(L, 1));
   lua_pushinteger(L, windowId);
   return 1;
}

/*DestroyWindow (windowId) -> none*/
static int glut_destroy_window(lua_State *L)
{
   glutDestroyWindow(luaL_checkint(L, 1));
   return 0;
}

/*InitWindowPosition (x, y) -> none*/
static int glut_init_window_position(lua_State *L)
{
   glutInitWindowPosition(luaL_checkint(L, 1), luaL_checkint(L, 2));
   return 0;
}

/*ReshapeWindow(width, height) -> none*/
static int glut_reshape_window(lua_State *L)
{
   glutReshapeWindow(luaL_checkint(L, 1), luaL_checkint(L, 2));
   return 0;
}

/*PositionWindow(width, height) -> none*/
static int glut_position_window(lua_State *L)
{
   glutPositionWindow(luaL_checkint(L, 1), luaL_checkint(L, 2));
   return 0;
}

/*InitWindowSize (width, height) -> none*/
static int glut_init_window_size(lua_State *L)
{
   glutInitWindowSize(luaL_checkint(L, 1), luaL_checkint(L, 2));
   return 0;
}

static int glut_display_func(lua_State *L)
{
   displayFunc.name = luaL_checkstring(L, 1);
   displayFunc.luastate = L;

   glutDisplayFunc(display_func);
   return 0;
}

static int glut_idle_func(lua_State *L)
{
   idleFunc.name = luaL_checkstring(L, 1);
   idleFunc.luastate = L;

   glutIdleFunc(idle_func);
   return 0;
}

static int glut_keyboard_func(lua_State *L)
{
   keyboardFunc.name = luaL_checkstring(L, 1);
   keyboardFunc.luastate = L;

   glutKeyboardFunc(keyboard_func);
   return 0;
}

static int glut_motion_func(lua_State *L)
{
   motionFunc.name = luaL_checkstring(L, 1);
   motionFunc.luastate = L;

   glutMotionFunc(motion_func);
   return 0;
}

static int glut_passive_motion_func(lua_State *L)
{
   passiveMotionFunc.name = luaL_checkstring(L, 1);
   passiveMotionFunc.luastate = L;

   glutPassiveMotionFunc(passive_motion_func);
   return 0;
}

static int glut_mouse_func(lua_State *L)
{
   mouseFunc.name = luaL_checkstring(L, 1);
   mouseFunc.luastate = L;

   glutMouseFunc(mouse_func);
   return 0;
}

static int glut_special_func(lua_State *L)
{
   specialFunc.name = luaL_checkstring(L, 1);
   specialFunc.luastate = L;

   glutSpecialFunc(special_func);
   return 0;
}

static int glut_reshape_func(lua_State *L)
{
   reshapeFunc.name = luaL_checkstring(L, 1);
   reshapeFunc.luastate = L;

   glutReshapeFunc(reshape_func);
   return 0;
}

static int glut_main_loop(lua_State *L)
{
   glutMainLoop();
   return 0;
}

static int glut_full_screen(lua_State *L)
{
   glutFullScreen();
   return 0;
}

static int glut_post_redisplay(lua_State *L)
{
   glutPostRedisplay();
   return 0;
}

static int glut_swap_buffers(lua_State *L)
{
   glutSwapBuffers();
   return 0;
}
/* for drawing strings */
static int glut_bitmap_character(lua_State *L)
{
   const char* s = (const char*)luaL_checkstring(L, 1);
   size_t len = (size_t)strlen(s);
   int i;
   for ( i = 0; i < len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
   }
   return 0;
}

static const luaL_reg glutlib[] = {
  {"CreateWindow", glut_create_window},
  {"DestroyWindow", glut_destroy_window},
  {"FullScreen", glut_full_screen},
  {"DisplayFunc", glut_display_func},
  {"IdleFunc", glut_idle_func},
  {"Init", glut_init},
  {"InitDisplayMode", glut_init_display_mode},
  {"InitWindowPosition", glut_init_window_position},
  {"InitWindowSize", glut_init_window_size},
  {"PositionWindow", glut_position_window},
  {"ReshapeWindow", glut_reshape_window},
  {"KeyboardFunc", glut_keyboard_func},
  {"MotionFunc", glut_motion_func},
  {"PassiveMotionFunc", glut_passive_motion_func},
  {"MouseFunc", glut_mouse_func},
  {"SpecialFunc", glut_special_func},
  {"MainLoop", glut_main_loop},
  {"PostRedisplay", glut_post_redisplay},
  {"ReshapeFunc", glut_reshape_func},
  {"SwapBuffers", glut_swap_buffers},
  {"BitmapCharacter", glut_bitmap_character},
  {NULL, NULL}
};

LUAGLUT_API int luaopen_libLuaGlut (lua_State *L){
  luaL_openlib(L, "glut", glutlib, 0);
  return 1;
}


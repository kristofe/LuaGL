/*************************************************
*  LuaGL - an OpenGL binding for Lua
*  2007(c) Fabio Guerra
*  luagl.sourceforge.net
*-------------------------------------------------
*  Description: This file implements the GLU
*               binding for Lua 5.0.
*-------------------------------------------------
*  Last Update: 16/09/2007
*  Version: v1.02-beta
*-------------------------------------------------
*  See Copyright Notice in LuaGL.h
*************************************************/

#include <string.h>

#if defined (__APPLE__) || defined (OSX)
	#include <stdlib.h>
#else
	#include <malloc.h>
#endif


#include <lauxlib.h>

#define BUILDING_LUAGL_DLL

#include "LuaGL.h"
#include "LuaGlu.h"
#include "LuaGLAux.h"

#define ShowError(msg) { luaL_error(L, msg); }

static GLenum get_enum(const char *str, int n)
{
   int i = 0;

   while(glu_str[i].str != 0)
   {
      if(strncmp(str, glu_str[i].str, n) == 0 && glu_str[i].str[n] == 0)
         return glu_str[i].value;
      i++;
   }
   return ENUM_ERROR;
}

static GLenum get_enum2(const char *str, int n)
{
   int i = 0;

   while(gl_str[i].str != 0)
   {
      if(strncmp(str, gl_str[i].str, n) == 0 && gl_str[i].str[n] == 0)
         return gl_str[i].value;
      i++;
   }
   return ENUM_ERROR;
}

static GLenum get_glu_enum(lua_State *L, int index)
{
   if(lua_type(L, index) == LUA_TSTRING)
   {
      unsigned int i;
      const char *str = lua_tostring(L, index);
      GLenum temp = 0, ret = 0;

      for(i = 0; i < strlen(str); i++)
      {
         if(str[i] == ',')
         {
            temp = get_enum(str, i);
            if(temp != ENUM_ERROR)
               ret |= temp;

            str += i+1;
            i = 0;
         }
      }
      temp = get_enum(str, (int)strlen(str));

      if(temp == ENUM_ERROR)
      {
         if(ret == 0)
            return ENUM_ERROR;
         return ret;
      }

      return ret | temp;
	}
	else {
		return (GLenum)lua_tonumber(L, index);
	}
}

/*static const char *get_str_glu_enum(GLenum num)
{
   unsigned int i = 0;

   while(glu_str[i].str != 0)
   {
      if(num == glu_str[i].value)
         return glu_str[i].str;

      i++;
   }
   return NULL;
}*/

/*GetString (name) -> string*/
static int glu_get_string(lua_State *L)
{
   GLenum e;
   const GLubyte *str;

   /* test argument type */
   if(!lua_isstring(L, 1))
      luaL_error(L, "incorrect argument to function 'glu.GetString'");

   /* get string parameter */
   e = get_glu_enum(L, 1);

   /* test argument */
   if(e == ENUM_ERROR)
      luaL_error(L, "incorrect string argument to function 'glu.GetString'");

   /* call opengl function */
   str = glGetString(e);

   lua_pushstring(L, (const char*)str);

   return 1;
}

static GLenum get_gl_enum(lua_State *L, int index)
{
   unsigned int i;
   const char *str = lua_tostring(L, index);
   GLenum temp = 0, ret = 0;

   for(i = 0; i < strlen(str); i++)
   {
      if(str[i] == ',')
      {
         temp = get_enum(str, i);
         if(temp != ENUM_ERROR)
            ret |= temp;

         str += i+1;
         i = 0;
      }
   }
   temp = get_enum2(str, (int)strlen(str));

   if(temp == ENUM_ERROR)
   {
      if(ret == 0)
         return ENUM_ERROR;
      return ret;
   }

   return ret | temp;
}
/*
static const char *get_str_gl_enum(GLenum num)
{
   unsigned int i = 0;

   while(gl_str[i].str != 0)
   {
      if(num == gl_str[i].value)
         return gl_str[i].str;

      i++;
   }
   return NULL;
}*/

/* Ortho(left, right, bottom, top) -> none */
static int glu_ortho_2D(lua_State *L)
{
  if (!( lua_isnumber(L, 1) && lua_isnumber(L, 2) && lua_isnumber(L, 3) && lua_isnumber(L, 4)))
  {
    luaL_error(L, "incorrect argument to function 'glu.Ortho2D'");
    return 0;
  }
  
  gluOrtho2D( (GLdouble)lua_tonumber(L, 1), (GLdouble)lua_tonumber(L, 2), 
        (GLdouble)lua_tonumber(L, 3), (GLdouble)lua_tonumber(L, 4));
  
  return 0;
}

/* Perspective(fovy, aspect, near, far) -> none */
static int glu_perspective(lua_State *L)
{
  if (!( lua_isnumber(L, 1) && lua_isnumber(L, 2) && lua_isnumber(L, 3) && lua_isnumber(L, 4)))
  {
    luaL_error(L, "incorrect string argument to function 'glu.Perspective'");
    return 0;
  }
  gluPerspective((GLdouble)lua_tonumber(L, 1), (GLdouble)lua_tonumber(L, 2), (GLdouble)lua_tonumber(L, 3), (GLdouble)lua_tonumber(L, 4));
  return 0;
}

/* LookAt(Ex, Ey, Ez, Lx, Ly, Lz, Ux, Uy, Uz) -> none */
static int glu_look_at(lua_State *L)
{
  if (!( lua_isnumber(L, 1) && lua_isnumber(L, 2) && lua_isnumber(L, 3)
      && lua_isnumber(L, 4) && lua_isnumber(L, 5) && lua_isnumber(L, 6)
      && lua_isnumber(L, 7) && lua_isnumber(L, 8) && lua_isnumber(L, 9)))
  {
    luaL_error(L, "incorrect argument to function 'glu.LookAt'");
    return 0;
  }
  gluLookAt(
      (GLdouble)lua_tonumber(L, 1), (GLdouble)lua_tonumber(L, 2), (GLdouble)lua_tonumber(L, 3),
      (GLdouble)lua_tonumber(L, 4), (GLdouble)lua_tonumber(L, 5), (GLdouble)lua_tonumber(L, 6),
      (GLdouble)lua_tonumber(L, 7), (GLdouble)lua_tonumber(L, 8), (GLdouble)lua_tonumber(L, 9));

  return 0;
}

/* PickMatrix( x, y, deltax, deltay, const GLint viewport[4] ); */
static int glu_pick_matrix(lua_State *L)
{
   GLint *vp;
   int num_args;

  if (!( lua_isnumber(L, 1) && lua_isnumber(L, 2) && lua_isnumber(L, 3)
    && lua_isnumber(L, 4)))
  {
    luaL_error(L, "incorrect argument to function 'glu.PickMatrix'");
    return 0;
  }

  if(!lua_istable(L, 5) || (num_args = get_arrayi(L, 5, &vp)) < 4)
  {
    luaL_error(L, "incorrect argument to function 'glu.PickMatrix'");
    return 0;
  }
   
  gluPickMatrix(
      (GLdouble)lua_tonumber(L, 1), (GLdouble)lua_tonumber(L, 2), (GLdouble)lua_tonumber(L, 3),
      (GLdouble)lua_tonumber(L, 4), vp);

   DELETE_ARRAY(vp);
      
  return 0;
}

/*ErrorString( errorCode );*/
static int glu_error_string(lua_State *L)
{
  if (!lua_isnumber(L, 1))
  {
    luaL_error(L, "incorrect argument to function 'glu.ErrorString'");
    return 0;
  }

  lua_pushstring(L, (char *)gluErrorString((GLenum)lua_tonumber(L, 1)));

  return 1;
}

/*********************************** GLU Mipmapping ***********************************/

/*int gluScaleImage( GLenum format, GLsizei widthin,
GLsizei heightin, GLenum typein, const void *datain,
GLsizei widthout, GLsizei heightout, GLenum typeout,
void *dataout );*/

/*int gluBuild1DMipmaps( GLenum target,
GLint internalFormat, GLsizei width, GLenum format,
GLenum type, const void *data );*/

/*int gluBuild2DMipmaps( GLenum target,
GLint internalFormat, GLsizei width, GLsizei height,
GLenum format, GLenum type, const void *data );*/

/*Build2DMipmaps(textureData) -> 0 on success, error message otherwise*/
static int glu_build_2d_mipmaps(lua_State *L)
{
  GLenum target, format, type;
  GLubyte *pixels;
  GLint internalFormat;
  GLsizei width, height, w, h;
  int result;

  if(!lua_istable(L, 1))
    ShowError("incorrect argument to function 'glu.Build2DMipmaps'");

  lua_pushstring(L, "target");  lua_gettable(L, 1);  target = get_gl_enum(L, -1);  lua_pop(L, 1);
  lua_pushstring(L, "format");  lua_gettable(L, 1);  format = get_gl_enum(L, -1);  lua_pop(L, 1);
  lua_pushstring(L, "type");    lua_gettable(L, 1);  type   = get_gl_enum(L, -1);  lua_pop(L, 1);
  lua_pushstring(L, "width");   lua_gettable(L, 1);  width  = (GLsizei)lua_tonumber(L, -1);  lua_pop(L, 1);
  lua_pushstring(L, "height");  lua_gettable(L, 1);  height = (GLsizei)lua_tonumber(L, -1);  lua_pop(L, 1);
  lua_pushstring(L, "components");  lua_gettable(L, 1);  internalFormat = (GLint)lua_tonumber(L, -1);  lua_pop(L, 1);

  h = get_array2ubyte(L, 1, &pixels, &w);

  w /= internalFormat;

  if (width > w)
    width = w;

  if (height > h)
    height = h;

  result = gluBuild2DMipmaps(target, internalFormat, width,
                             height, format, type, pixels);

  DELETE_ARRAY(pixels);

   if (result == 0)
     lua_pushnumber(L, 0);
   else
     lua_pushstring(L, (char*)gluErrorString(result));

   return 1;
}

/*int gluBuild3DMipmaps( GLenum target,
GLint internalFormat, GLsizei width, GLsizei height,
GLsizei depth, GLenum format, GLenum type,
const void *data );*/

static const luaL_reg glulib[] = {
  {"GetString", glu_get_string},
  {"Ortho2D", glu_ortho_2D},
  {"Perspective", glu_perspective},
  {"LookAt", glu_look_at},
  {"PickMatrix", glu_pick_matrix},
  {"Build2DMipmaps", glu_build_2d_mipmaps},
  {"ErrorString", glu_error_string},
  {NULL, NULL}
};

LUAGLU_API int luaopen_libLuaGlu(lua_State *L)
{
  int i = 0;

  luaL_register(L, "glu", glulib); /* register table and put on stack */
  lua_pushstring(L, "enums");      /* put key on stack */
  
  /* make enum table */
  lua_newtable(L);                 /* put value on stack */

  /* fill new table */
  while(glu_str[i].str)
  {
    lua_pushstring(L, glu_str[i].str);    /* strings as enum keys */
    lua_pushinteger(L, glu_str[i].value); /* enum value as values */
    lua_settable(L, -3);                  /* set table with (key, value) pair */
    i++;
  }

  lua_settable(L, -3); /* set table with (key, value) pair */
  
  /* glu table is on top of stack here */
  {
    int i=0;
    while(glu_str[i].str)
    {
      lua_pushstring(L, glu_str[i].str);
      lua_pushinteger(L, glu_str[i].value);
      lua_settable(L, -3);
      i++;
    }
  }

  return 1;
}

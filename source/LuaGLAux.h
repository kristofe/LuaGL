/*************************************************
* LuaGL - an OpenGL binding for Lua
* 2003-2007(c) Fabio Guerra, Cleyde Marlyse
* luagl.sourceforge.net
*-------------------------------------------------
* See Copyright Notice in LuaGL.h
*************************************************/
#ifndef __LUAGL_AUX_H__
#define __LUAGL_AUX_H__

#include <string.h>

#if defined (__APPLE__) || defined (OSX)
	#include <stdlib.h>
#else
	#include <malloc.h>
#endif

#ifdef _WIN32
  #ifdef BUILDING_LUAGL_DLL
    #define LUAGL_API __declspec(dllexport)
  #else
    #define LUAGL_API __declspec(dllimport)
  #endif
  #include <windows.h>
#else
  #ifdef BUILDING_LUAGL_DLL
    #define LUAGL_API
  #else
    #define LUAGL_API extern
  #endif
#endif

#include <lualib.h>
#if defined (__APPLE__) || defined (OSX)
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <OpenGL/glext.h>
#else
	#include <GL/gl.h>
#endif

#define STATIC_MEMORY_SIZE 1024

/*#define __luagl_debug_memleak 1*/
int __memleak_malloc_counter;
int __memleak_counter;

void *luaGLMalloc(size_t s);
void luaGLFree(void *v);

/* returns an array with given type and size */
#define NEW_ARRAY(type, size) ( (type *)luaGLMalloc((size) * sizeof(type)) )

/* returns a bi-dimensional array with given type and size */
#define NEW_ARRAY2(type, size1, size2) ( (type *)luaGLMalloc((size1) * (size2) * sizeof(type)) )

/* frees the space for the given array, must be called together with NEW_ARRAY */
#define DELETE_ARRAY(array) { if(array) {luaGLFree(array);} }

/* frees the space for the given bi-dimensional array, must be called together with NEW_ARRAY2 */
#define DELETE_ARRAY2(array) { if(array) {luaGLFree(array);} }

/* returns an array with given type and size, this will always call malloc function */
#define NEW_ARRAY_POINTER(type, size) ( (type *)malloc((size) * sizeof(type)) )

/* returns a bi-dimensional array with given type and size */
#define NEW_ARRAY2_POINTER(type, size1, size2) ( (type *)malloc((size1) * (size2) * sizeof(type)) )

#define INIT_ARRAY(array, type, size, conversionFunc)           \
{                                                               \
  int i;                                                        \
  for(i = 0; i < (size); i++) {                                 \
    lua_rawgeti(L, index, i+1);                                 \
    (array)[i] = (type)(conversionFunc)(L, -1);                 \
    lua_remove(L, -1);                                          \
  }                                                             \
}

#define INIT_ARRAY2(array, type, size1, size2, conversionFunc)  \
{                                                               \
  int i, j;                                                     \
  for(i = 0; i < size1; i++)  {                                 \
    lua_rawgeti(L, index, i+1);                                 \
    if(!lua_istable(L, -1)) return -1;                          \
    for(j = 0; j < *size2; j++) {                               \
      lua_rawgeti(L, -1, j + 1);                                \
      (array)[i*(*size2) + j] = (type)(conversionFunc)(L, -1);  \
      lua_remove(L, -1);                                        \
    }                                                           \
    lua_remove(L, -1);                                          \
  }                                                             \
}

/* set field of a lua table with a number */
void set_field(lua_State *L, unsigned int index, lua_Number value);

/* Gets an array from a lua table, store it in 'array' and returns the no. of elems of the array
   index refers to where the table is in stack. */
int get_arrayb(lua_State *L, int index, GLboolean **array);
int get_arrayd(lua_State *L, int index, GLdouble **array);
int get_arrayf(lua_State *L, int index, GLfloat **array);
int get_arrayi(lua_State *L, int index, GLint **array);
int get_arrayui(lua_State *L, int index, GLuint **array);
int get_arrayubyte(lua_State *L, int index, GLubyte **array);
int get_arrayshort(lua_State *L, int index, GLshort **array);
int get_arrayushort(lua_State *L, int index, GLushort **array);

int get_array2ubyte(lua_State *L, int index, GLubyte **array, int *size);
int get_array2d(lua_State *L, int index, GLdouble **array, int *size);
int get_array2f(lua_State *L, int index, GLfloat **array, int *size);
int get_array2i(lua_State *L, int index, GLint **array, int *size);
int get_array2ui(lua_State *L, int index, GLuint **array, int *size);
int get_array2short(lua_State *L, int index, GLshort **array, int *size);
int get_array2ushort(lua_State *L, int index, GLushort **array, int *size);


int get_arrayb_pointer(lua_State *L, int index, GLboolean **array);
int get_arrayd_pointer(lua_State *L, int index, GLdouble **array);
int get_array2d_pointer(lua_State *L, int index, GLdouble **array, int *size);

int str2mask(const char *str);
const char *mask2str(int mask);

#endif


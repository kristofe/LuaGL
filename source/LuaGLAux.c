/*************************************************
* LuaGL - an OpenGL binding for Lua
* 2003-2007(c) Fabio Guerra, Cleyde Marlyse
* luagl.sourceforge.net
*-------------------------------------------------
* See Copyright Notice in LuaGL.h
*************************************************/

#include "LuaGL.h"
#include "LuaGLAux.h"

#include <lauxlib.h>

static char __luagl_using_static_mem = 0;
static char *static_mem[STATIC_MEMORY_SIZE];

void *luaGLMalloc(size_t s)
{
  if (__luagl_using_static_mem == 0 && s < STATIC_MEMORY_SIZE)
  {
    __luagl_using_static_mem = 0xff;
    return static_mem;
  }
  return malloc(s);
}

void luaGLFree(void *v)
{
  if (v != static_mem)
  {
    free(v);
    return;
  }
  __luagl_using_static_mem = 0;
}

#ifdef __luagl_debug_memleak

int __memleak_malloc_counter = 0;
int __memleak_counter = 0;
static int __malloc_counter = 0;
static void *myMalloc(size_t s) { __memleak_malloc_counter++; __memleak_counter++; return malloc(s); }
static void myFree(void *v) { __memleak_counter--; free(v); }

#define malloc myMalloc
#define free myFree

#endif

/* set field of a lua table with a number */
void set_field(lua_State *L, unsigned int index, lua_Number value)
{
   lua_pushnumber(L, index);
   lua_pushnumber(L, value);
   lua_settable(L, -3);
}

/* Gets an array from a lua table, store it in 'array' and returns the no. of elems of the array
   index refers to where the table is in stack. */
#define DEFINE_GET_ARRAY_FUNC(name, type, conversionFunc) \
int name(lua_State *L, int index, type **array)           \
{                                                         \
   int n = luaL_getn(L, index);                           \
   *array = NEW_ARRAY(type, n);                           \
   INIT_ARRAY(*array, type, n, conversionFunc);           \
   return n;                                              \
}

/* Same as above, but use use NEW_ARRAY_POINTER instead of NEW_ARRAY */
#define DEFINE_GET_ARRAY_POINTER_FUNC(name, type, conversionFunc) \
int name(lua_State *L, int index, type **array)           \
{                                                         \
   int n = luaL_getn(L, index);                           \
   *array = NEW_ARRAY_POINTER(type, n);                   \
   INIT_ARRAY(*array, type, n, conversionFunc);           \
   return n;                                              \
}

#define DEFINE_GET_ARRAY2_FUNC(name, type, conversionFunc)   \
int name(lua_State *L, int index, type **array, int *size)   \
{                                                            \
   int n = luaL_getn(L, index);                              \
   lua_rawgeti(L, index, 1);                                 \
   if(!lua_istable(L, -1)) { lua_remove(L, -1); return -1; } \
   *size = luaL_getn(L, -1);                                 \
   *array = NEW_ARRAY2(type, n, *size);                      \
   INIT_ARRAY2(*array, type, n, size, conversionFunc);       \
   lua_remove(L, -1);                                        \
   return n;                                                 \
}

/* Same as above, but use use NEW_ARRAY2_POINTER instead of NEW_ARRAY2 */
#define DEFINE_GET_ARRAY2_POINTER_FUNC(name, type, conversionFunc)   \
int name(lua_State *L, int index, type **array, int *size)   \
{                                                            \
   int n = luaL_getn(L, index);                              \
   lua_rawgeti(L, index, 1);                                 \
   if(!lua_istable(L, -1)) { lua_remove(L, -1); return -1; } \
   *size = luaL_getn(L, -1);                                 \
   *array = (type *)malloc(*size * n * sizeof(type));        \
   INIT_ARRAY2(*array, type, n, size, conversionFunc);       \
   lua_remove(L, -1);                                        \
   return n;                                                 \
}

DEFINE_GET_ARRAY_FUNC(get_arrayb, GLboolean, lua_toboolean)
DEFINE_GET_ARRAY_FUNC(get_arrayd, GLdouble, lua_tonumber)
DEFINE_GET_ARRAY_FUNC(get_arrayf, GLfloat, lua_tonumber)
DEFINE_GET_ARRAY_FUNC(get_arrayi, GLint, lua_tonumber)
DEFINE_GET_ARRAY_FUNC(get_arrayui, GLuint, lua_tonumber)
DEFINE_GET_ARRAY_FUNC(get_arrayubyte, GLubyte, lua_tonumber)
DEFINE_GET_ARRAY_FUNC(get_arrayshort, GLshort, lua_tonumber)
DEFINE_GET_ARRAY_FUNC(get_arrayushort, GLushort, lua_tonumber)

DEFINE_GET_ARRAY_POINTER_FUNC(get_arrayb_pointer, GLboolean, lua_toboolean)
DEFINE_GET_ARRAY_POINTER_FUNC(get_arrayd_pointer, GLdouble, lua_tonumber)

DEFINE_GET_ARRAY2_FUNC(get_array2ubyte, GLubyte, lua_tonumber)
DEFINE_GET_ARRAY2_FUNC(get_array2d, GLdouble, lua_tonumber)
DEFINE_GET_ARRAY2_FUNC(get_array2f, GLfloat, lua_tonumber)
DEFINE_GET_ARRAY2_FUNC(get_array2i, GLint, lua_tonumber)
DEFINE_GET_ARRAY2_FUNC(get_array2ui, GLuint, lua_tonumber)
DEFINE_GET_ARRAY2_FUNC(get_array2short, GLshort, lua_tonumber)
DEFINE_GET_ARRAY2_FUNC(get_array2ushort, GLushort, lua_tonumber)

DEFINE_GET_ARRAY2_POINTER_FUNC(get_array2d_pointer, GLdouble, lua_tonumber)

#undef DEFINE_GET_ARRAY_FUNC
#undef DEFINE_GET_ARRAY_POINTER_FUNC
#undef DEFINE_GET_ARRAY2_FUNC
#undef DEFINE_GET_ARRAY2_POINTER_FUNC

int str2mask(const char *str)
{
   int i, j;
   int mask = 0;
   int size = (int)strlen(str);
   for(i = 0, j = 0; j < size; i++)
   {
      if(str[i] == '1')
      {
         mask |= (1 << (size-1-j));
         j++;
      }
      else if(str[i] == '0')
         j++;
         
   }
   return mask;
}

const char *mask2str(int mask)
{
   unsigned int i;
   static char str[17];
   for(i = 0; i < 16; i++)
   {
      if(mask & (1 << (15 - i)))
         str[i] = '1';
      else
         str[i] = '0';
   }
   str[i] = 0;
   return str;
}

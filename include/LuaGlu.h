/*************************************************
* LuaGL - an OpenGL binding for Lua
* 2003-2007(c) Fabio Guerra, Cleyde Marlyse
* luagl.sourceforge.net
*-------------------------------------------------
* See Copyright Notice in LuaGL.h
*************************************************/

#ifndef __LUAGLU_H__
#define __LUAGLU_H__

#ifdef __cplusplus
extern "C" {
#endif

#define LUAGLU_VERSION "1.02-beta"

#ifdef _WIN32
  #ifdef BUILDING_LUAGL_DLL
    #define LUAGLU_API __declspec(dllexport)
  #else
    #define LUAGLU_API __declspec(dllimport)
  #endif
  #include <windows.h>
#else
  #ifdef BUILDING_LUAGL_DLL
    #define LUAGLU_API
  #else
    #define LUAGLU_API extern
  #endif
#endif

#include <lualib.h>

#if defined (__APPLE__) || defined (OSX)
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <OpenGL/glext.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif


#include "LuaGL.h"

#define ENUM_ERROR (GLenum)-2

static const gl_str_value glu_str[] = {
   { "VERSION_1_1"                       , GLU_VERSION_1_1 },
   { "VERSION_1_2"                       , GLU_VERSION_1_2 },
   { "INVALID_ENUM"                      , GLU_INVALID_ENUM },
   { "INVALID_VALUE"                     , GLU_INVALID_VALUE },
   { "OUT_OF_MEMORY"                     , GLU_OUT_OF_MEMORY },
   { "INCOMPATIBLE_GL_VERSION"           , GLU_INCOMPATIBLE_GL_VERSION },
   { "VERSION"                           , GLU_VERSION },
   { "EXTENSIONS"                        , GLU_EXTENSIONS },
   { "TRUE"                              , GLU_TRUE },
   { "FALSE"                             , GLU_FALSE },
   { "SMOOTH"                            , GLU_SMOOTH },
   { "FLAT"                              , GLU_FLAT },
   { "NONE"                              , GLU_NONE },
   { "POINT"                             , GLU_POINT },
   { "LINE"                              , GLU_LINE },
   { "FILL"                              , GLU_FILL },
   { "SILHOUETTE"                        , GLU_SILHOUETTE },
   { "OUTSIDE"                           , GLU_OUTSIDE },
   { "INSIDE"                            , GLU_INSIDE },
   /*{ "TESS_MAX_COORD"                    , GLU_TESS_MAX_COORD },*/
   { "TESS_WINDING_RULE"                 , GLU_TESS_WINDING_RULE },
   { "TESS_BOUNDARY_ONLY"                , GLU_TESS_BOUNDARY_ONLY },
   { "TESS_TOLERANCE"                    , GLU_TESS_TOLERANCE },
   { "TESS_WINDING_ODD"                  , GLU_TESS_WINDING_ODD },
   { "TESS_WINDING_NONZERO"              , GLU_TESS_WINDING_NONZERO },
   { "TESS_WINDING_POSITIVE"             , GLU_TESS_WINDING_POSITIVE },
   { "TESS_WINDING_NEGATIVE"             , GLU_TESS_WINDING_NEGATIVE },
   { "TESS_WINDING_ABS_GEQ_TWO"          , GLU_TESS_WINDING_ABS_GEQ_TWO },
   { "TESS_BEGIN"                        , GLU_TESS_BEGIN },
   { "TESS_VERTEX"                       , GLU_TESS_VERTEX },
   { "TESS_END"                          , GLU_TESS_END },
   { "TESS_ERROR"                        , GLU_TESS_ERROR },
   { "TESS_EDGE_FLAG"                    , GLU_TESS_EDGE_FLAG },
   { "TESS_COMBINE"                      , GLU_TESS_COMBINE },
   { "TESS_BEGIN_DATA"                   , GLU_TESS_BEGIN_DATA },
   { "TESS_VERTEX_DATA"                  , GLU_TESS_VERTEX_DATA },
   { "TESS_END_DATA"                     , GLU_TESS_END_DATA },
   { "TESS_ERROR_DATA"                   , GLU_TESS_ERROR_DATA },
   { "TESS_EDGE_FLAG_DATA"               , GLU_TESS_EDGE_FLAG_DATA },
   { "TESS_COMBINE_DATA"                 , GLU_TESS_COMBINE_DATA },
   { "TESS_ERROR1"                       , GLU_TESS_ERROR1 },
   { "TESS_ERROR2"                       , GLU_TESS_ERROR2 },
   { "TESS_ERROR3"                       , GLU_TESS_ERROR3 },
   { "TESS_ERROR4"                       , GLU_TESS_ERROR4 },
   { "TESS_ERROR5"                       , GLU_TESS_ERROR5 },
   { "TESS_ERROR6"                       , GLU_TESS_ERROR6 },
   { "TESS_ERROR7"                       , GLU_TESS_ERROR7 },
   { "TESS_ERROR8"                       , GLU_TESS_ERROR8 },
   { "TESS_MISSING_BEGIN_POLYGON"        , GLU_TESS_MISSING_BEGIN_POLYGON },
   { "TESS_MISSING_BEGIN_CONTOUR"        , GLU_TESS_MISSING_BEGIN_CONTOUR },
   { "TESS_MISSING_END_POLYGON"          , GLU_TESS_MISSING_END_POLYGON },
   { "TESS_MISSING_END_CONTOUR"          , GLU_TESS_MISSING_END_CONTOUR },
   { "TESS_COORD_TOO_LARGE"              , GLU_TESS_COORD_TOO_LARGE },
   { "TESS_NEED_COMBINE_CALLBACK"        , GLU_TESS_NEED_COMBINE_CALLBACK },
   { "AUTO_LOAD_MATRIX"                  , GLU_AUTO_LOAD_MATRIX },
   { "CULLING"                           , GLU_CULLING },
   { "SAMPLING_TOLERANCE"                , GLU_SAMPLING_TOLERANCE },
   { "DISPLAY_MODE"                      , GLU_DISPLAY_MODE },
   { "PARAMETRIC_TOLERANCE"              , GLU_PARAMETRIC_TOLERANCE },
   { "SAMPLING_METHOD"                   , GLU_SAMPLING_METHOD },
   { "U_STEP"                            , GLU_U_STEP },
   { "V_STEP"                            , GLU_V_STEP },
   { "PATH_LENGTH"                       , GLU_PATH_LENGTH },
   { "PARAMETRIC_ERROR"                  , GLU_PARAMETRIC_ERROR },
   { "DOMAIN_DISTANCE"                   , GLU_DOMAIN_DISTANCE },
   { "MAP1_TRIM_2"                       , GLU_MAP1_TRIM_2 },
   { "MAP1_TRIM_3"                       , GLU_MAP1_TRIM_3 },
   { "OUTLINE_POLYGON"                   , GLU_OUTLINE_POLYGON },
   { "OUTLINE_PATCH"                     , GLU_OUTLINE_PATCH },
   { "NURBS_ERROR1"                      , GLU_NURBS_ERROR1 },
   { "NURBS_ERROR2"                      , GLU_NURBS_ERROR2 },
   { "NURBS_ERROR3"                      , GLU_NURBS_ERROR3 },
   { "NURBS_ERROR4"                      , GLU_NURBS_ERROR4 },
   { "NURBS_ERROR5"                      , GLU_NURBS_ERROR5 },
   { "NURBS_ERROR6"                      , GLU_NURBS_ERROR6 },
   { "NURBS_ERROR7"                      , GLU_NURBS_ERROR7 },
   { "NURBS_ERROR8"                      , GLU_NURBS_ERROR8 },
   { "NURBS_ERROR9"                      , GLU_NURBS_ERROR9 },
   { "NURBS_ERROR10"                     , GLU_NURBS_ERROR10 },
   { "NURBS_ERROR11"                     , GLU_NURBS_ERROR11 },
   { "NURBS_ERROR12"                     , GLU_NURBS_ERROR12 },
   { "NURBS_ERROR13"                     , GLU_NURBS_ERROR13 },
   { "NURBS_ERROR14"                     , GLU_NURBS_ERROR14 },
   { "NURBS_ERROR15"                     , GLU_NURBS_ERROR15 },
   { "NURBS_ERROR16"                     , GLU_NURBS_ERROR16 },
   { "NURBS_ERROR17"                     , GLU_NURBS_ERROR17 },
   { "NURBS_ERROR18"                     , GLU_NURBS_ERROR18 },
   { "NURBS_ERROR19"                     , GLU_NURBS_ERROR19 },
   { "NURBS_ERROR20"                     , GLU_NURBS_ERROR20 },
   { "NURBS_ERROR21"                     , GLU_NURBS_ERROR21 },
   { "NURBS_ERROR22"                     , GLU_NURBS_ERROR22 },
   { "NURBS_ERROR23"                     , GLU_NURBS_ERROR23 },
   { "NURBS_ERROR24"                     , GLU_NURBS_ERROR24 },
   { "NURBS_ERROR25"                     , GLU_NURBS_ERROR25 },
   { "NURBS_ERROR26"                     , GLU_NURBS_ERROR26 },
   { "NURBS_ERROR27"                     , GLU_NURBS_ERROR27 },
   { "NURBS_ERROR28"                     , GLU_NURBS_ERROR28 },
   { "NURBS_ERROR29"                     , GLU_NURBS_ERROR29 },
   { "NURBS_ERROR30"                     , GLU_NURBS_ERROR30 },
   { "NURBS_ERROR31"                     , GLU_NURBS_ERROR31 },
   { "NURBS_ERROR32"                     , GLU_NURBS_ERROR32 },
   { "NURBS_ERROR33"                     , GLU_NURBS_ERROR33 },
   { "NURBS_ERROR34"                     , GLU_NURBS_ERROR34 },
   { "NURBS_ERROR35"                     , GLU_NURBS_ERROR35 },
   { "NURBS_ERROR36"                     , GLU_NURBS_ERROR36 },
   { "NURBS_ERROR37"                     , GLU_NURBS_ERROR37 },
   { "CW"                                , GLU_CW },
   { "CCW"                               , GLU_CCW },
   { "INTERIOR"                          , GLU_INTERIOR },
   { "EXTERIOR"                          , GLU_EXTERIOR },
   { "UNKNOWN"                           , GLU_UNKNOWN },
   { "BEGIN"                             , GLU_BEGIN },
   { "VERTEX"                            , GLU_VERTEX },
   { "END"                               , GLU_END },
   { "ERROR"                             , GLU_ERROR },
   { "EDGE_FLAG"                         , GLU_EDGE_FLAG },
   {0, 0}
};

LUAGLU_API int luaopen_LuaGLU(lua_State* L);

#ifdef __cplusplus
}
#endif

#endif

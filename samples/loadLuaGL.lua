if loadlib then                         -- for Lua 5.0
  error('This version of Lua is not supported by the torch interface!!!!')
  loadlib('LuaGlut', 'luaopen_LuaGlut')()
  loadlib('LuaGL', 'luaopen_LuaGL')()
  loadlib('LuaGlu', 'luaopen_LuaGLU')()
else                                    -- for Lua 5.1
  require('libLuaGlut')
  require('libLuaGL')
  require('libLuaGlu')
end

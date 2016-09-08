A wrapper to luagl.

This is a modified version of the LuaGL source code to make it compatible with torch7.

See http://luagl.sourceforge.net/ for more information.

Their license is the MIT License.

-------------------

#Installing into torch
`luarocks make luagl-1-02.rockspec`

------------------
use the libraries by:
```
require('libLuaGlut')
require('libLuaGL')
require('libLuaGlu')
```

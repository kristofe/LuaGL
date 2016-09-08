dofile('loadLuaGL.lua')
dofile('loadTGA.lua')

light = false             -- Lighting ON / OFF
lp = false                -- L Pressed?
fp = false                -- F Pressed?

xrot = 0                  -- X Rotation
yrot = 0                  -- Y Rotation
xspeed = 0                -- X Rotation Speed
yspeed = 0                -- Y Rotation Speed
z = -5                    -- Depth Into The Screen

LightAmbient = {0.5, 0.5, 0.5, 1}    -- Ambient Light Values ( NEW )
LightDiffuse = {1, 1, 1, 1}          -- Diffuse Light Values ( NEW )
LightPosition = {0, 0, 2, 1}         -- Light Position ( NEW )

filter = 1                           -- Which Filter To Use
texture = 0                          -- Storage for the textures

function checkError()
  local err = gl.GetError()
  while err ~= "NO_ERROR" do
    print(err)
    err = gl.GetError()
  end
end

function Reshape(width, height)
  gl.Viewport(0, 0, width, height)

  gl.MatrixMode('PROJECTION')   -- Select The Projection Matrix
  gl.LoadIdentity()             -- Reset The Projection Matrix
  
  if height == 0 then           -- Calculate The Aspect Ratio Of The Window
    height = 1
  end

  glu.Perspective(80, width / height, 0.01, 100)

  gl.MatrixMode('MODELVIEW')    -- Select The Model View Matrix
  gl.LoadIdentity()             -- Reset The Model View Matrix
end

mouse1Down = false
function Mouse(button, state, x, y)
  print(button .." " ..  state .. " " .. x .. " " ..y)
  if(button == 0) then
    if(state == 1) then mouse1Down = false else mouse1Down = true end
  end
end

function MouseMove(x, y)
  if(mouse1Down) then
    print(x .. " " ..y)
  end
end

function DrawGLScene()
  gl.Clear('COLOR_BUFFER_BIT,DEPTH_BUFFER_BIT') -- Clear Screen And Depth Buffer
  checkError()
  gl.LoadIdentity()             -- Reset The Current Modelview Matrix
	gl.Translate(0,0,z)           -- Translate Into/Out Of The Screen By z

	gl.Rotate(xrot,1,0,0)
	gl.Rotate(yrot,0,1,0)

  gl.BindTexture('TEXTURE_2D', texture[filter])

  gl.Begin('QUADS')

    -- Front Face
    gl.Normal( 0, 0, 1)                      -- Normal Pointing Towards Viewer
    gl.TexCoord(0, 0) gl.Vertex(-1, -1,  1)  -- Point 1 (Front)
    gl.TexCoord(1, 0) gl.Vertex( 1, -1,  1)  -- Point 2 (Front)
    gl.TexCoord(1, 1) gl.Vertex( 1,  1,  1)  -- Point 3 (Front)
    gl.TexCoord(0, 1) gl.Vertex(-1,  1,  1)  -- Point 4 (Front)
    
    -- Back Face
    gl.Normal( 0, 0,-1)                      -- Normal Pointing Away From Viewer
    gl.TexCoord(1, 0) gl.Vertex(-1, -1, -1)  -- Point 1 (Back)
    gl.TexCoord(1, 1) gl.Vertex(-1,  1, -1)  -- Point 2 (Back)
    gl.TexCoord(0, 1) gl.Vertex( 1,  1, -1)  -- Point 3 (Back)
    gl.TexCoord(0, 0) gl.Vertex( 1, -1, -1)  -- Point 4 (Back)
    
    -- Top Face
    gl.Normal( 0, 1, 0)                      -- Normal Pointing Up
    gl.TexCoord(0, 1) gl.Vertex(-1,  1, -1)  -- Point 1 (Top)
    gl.TexCoord(0, 0) gl.Vertex(-1,  1,  1)  -- Point 2 (Top)
    gl.TexCoord(1, 0) gl.Vertex( 1,  1,  1)  -- Point 3 (Top)
    gl.TexCoord(1, 1) gl.Vertex( 1,  1, -1)  -- Point 4 (Top)
    
    -- Bottom Face
    gl.Normal( 0,-1, 0)                      -- Normal Pointing Down
    gl.TexCoord(1, 1) gl.Vertex(-1, -1, -1)  -- Point 1 (Bottom)
    gl.TexCoord(0, 1) gl.Vertex( 1, -1, -1)  -- Point 2 (Bottom)
    gl.TexCoord(0, 0) gl.Vertex( 1, -1,  1)  -- Point 3 (Bottom)
    gl.TexCoord(1, 0) gl.Vertex(-1, -1,  1)  -- Point 4 (Bottom)

    -- Right face
    gl.Normal( 1, 0, 0)                      -- Normal Pointing Right
    gl.TexCoord(1, 0) gl.Vertex( 1, -1, -1)  -- Point 1 (Right)
    gl.TexCoord(1, 1) gl.Vertex( 1,  1, -1)  -- Point 2 (Right)
    gl.TexCoord(0, 1) gl.Vertex( 1,  1,  1)  -- Point 3 (Right)
    gl.TexCoord(0, 0) gl.Vertex( 1, -1,  1)  -- Point 4 (Right)

    -- Left Face
    gl.Normal(-1, 0, 0)                      -- Normal Pointing Left
    gl.TexCoord(0, 0) gl.Vertex(-1, -1, -1)  -- Point 1 (Left)
    gl.TexCoord(1, 0) gl.Vertex(-1, -1,  1)  -- Point 2 (Left)
    gl.TexCoord(1, 1) gl.Vertex(-1,  1,  1)  -- Point 3 (Left)
    gl.TexCoord(0, 1) gl.Vertex(-1,  1, -1)  -- Point 4 (Left)

  gl.End()

	xrot = xrot + xspeed
	yrot = yrot + yspeed

  glut.SwapBuffers()
end              

function Keyboard(keyValue)

  key = string.upper(string.format("%c", keyValue))

  if key == 'L' then   -- 'L' Key Being Pressed ?
    if (light) then
      gl.Disable('LIGHTING')
      light = false
    else
      gl.Enable('LIGHTING')
      light = true
    end
  end

  if key == 'F' then   -- 'F' Key Being Pressed ?
    filter = filter + 1
    if filter > 3 then
      filter = 1
    end    
  end

  if keyValue == 27 then  -- 'ESC' Key Being Pressed ?
    os.exit()
  end

end

function SpecialKeys(key, x, y)
  if key == 104 then  z = z - 2 end   -- Is Page Up Being Pressed? If So, Move Into The Screen.
  if key == 105 then  z = z + 2 end   -- Is Page Down Being Pressed? If So, Move Towards The Viewer.

  if key == 101 then  xspeed = xspeed - 0.01 end -- Is Up Arrow Being Pressed? If So, Decrease xspeed.
  if key == 103 then  xspeed = xspeed + 0.01 end -- Is Down Arrow Being Pressed? If So, Increase xspeed.

  if key == 100 then  yspeed = yspeed - 0.01 end -- Is Left Arrow Being Pressed? If So, Decrease yspeed.
  if key == 102 then  xspeed = xspeed + 0.01 end -- Is Right Arrow Being Pressed? If So, Increase yspeed.

  if key == 1 then    -- Pressed F1 ?
    if fullscreen then
      fullscreen = false
      glut.ReshapeWindow(500, 500)
      glut.PositionWindow(50, 50)
    else
      fullscreen = true
      glut.FullScreen()
    end
  end

end              

function LoadGLTextures()
  texture = gl.GenTextures(3)   -- Create The Textures
  
  -- Create Nearest Filtered Texture
  gl.BindTexture('TEXTURE_2D', texture[1])
  gl.TexParameter('TEXTURE_2D','TEXTURE_MIN_FILTER','NEAREST')
  gl.TexParameter('TEXTURE_2D','TEXTURE_MAG_FILTER','NEAREST')

  crate = assert(LoadTGA('data/crate.tga'))

  --gl.TexImage(0, crate)
  gl.TexImage(0, crate.components, crate.format, crate)

  -- Create Linear Filtered Texture
  gl.BindTexture('TEXTURE_2D', texture[2])
  gl.TexParameter('TEXTURE_2D','TEXTURE_MIN_FILTER','LINEAR')
  gl.TexParameter('TEXTURE_2D','TEXTURE_MAG_FILTER','LINEAR')

  gl.TexImage(0, crate)

  -- Create MipMapped Texture
  gl.BindTexture('TEXTURE_2D', texture[3])
  gl.TexParameter('TEXTURE_2D','TEXTURE_MIN_FILTER','LINEAR_MIPMAP_NEAREST')
  gl.TexParameter('TEXTURE_2D','TEXTURE_MAG_FILTER','LINEAR')

  glu.Build2DMipmaps(crate)

end

function Init()  
  gl.Enable('TEXTURE_2D')            -- Enable Texture Mapping ( NEW )
  checkError()

  if LoadGLTextures() == false then      -- Jump To Texture Loading Routine ( NEW )
    return false 
  end            

  checkError()
  gl.ShadeModel('SMOOTH')            -- Enable Smooth Shading
  checkError()
  gl.ClearColor(0, 0, 0, 0.5)        -- Black Background
  checkError()
  gl.ClearDepth(1.0)                 -- Depth Buffer Setup
  checkError()
  gl.Enable('DEPTH_TEST')            -- Enables Depth Testing
  checkError()
  gl.DepthFunc('LEQUAL')             -- The Type Of Depth Testing To Do
  checkError()
  gl.DepthMask(true)
  checkError()
  gl.Hint('PERSPECTIVE_CORRECTION_HINT','NICEST')

  gl.Light('LIGHT1', 'AMBIENT', LightAmbient)        -- Setup The Ambient Light
  gl.Light('LIGHT1', 'DIFFUSE', LightDiffuse)        -- Setup The Diffuse Light
  gl.Light('LIGHT1', 'POSITION', LightPosition)      -- Position The Light

  gl.Enable('LIGHT1')

end              

glut.Init()      
glut.InitDisplayMode("RGB,DOUBLE,DEPTH")
glut.InitWindowSize(640, 480)
glut.CreateWindow('LuaGL Test Application 07')
glut.IdleFunc('DrawGLScene')
glut.DisplayFunc('DrawGLScene')
glut.ReshapeFunc('Reshape')
glut.KeyboardFunc('Keyboard')
glut.MouseFunc('Mouse')
glut.MotionFunc('MouseMove')
glut.PassiveMotionFunc('MouseMove')
glut.SpecialFunc('SpecialKeys')

Init()           

glut.MainLoop()  

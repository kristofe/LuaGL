dofile('loadLuaGL.lua')
dofile('loadTGA.lua')

xrot = 0
yrot = 0
zrot = 0
texture = 0

function Reshape(width, height)
  gl.Viewport(0, 0, width, height)

  gl.MatrixMode('PROJECTION')   -- Select The Projection Matrix
  gl.LoadIdentity()             -- Reset The Projection Matrix

  if height == 0 then           -- Calculate The Aspect Ratio Of The Window
    height = 1
  end

  glu.Perspective(80, width / height, 1, 5000)

  gl.MatrixMode('MODELVIEW')    -- Select The Model View Matrix
  gl.LoadIdentity()             -- Reset The Model View Matrix
end

function DrawGLScene()

  gl.Clear('COLOR_BUFFER_BIT,DEPTH_BUFFER_BIT') -- Clear Screen And Depth Buffer

  gl.LoadIdentity()             -- Reset The Current Modelview Matrix
	gl.Translate(0,0,-5)

	gl.Rotate(xrot,1,0,0)
	gl.Rotate(yrot,0,1,0)
	gl.Rotate(zrot,0,0,1)

  gl.BindTexture('TEXTURE_2D', texture[1])

  gl.Begin('QUADS')
    -- Front Face
    gl.TexCoord(0, 0) gl.Vertex(-1, -1,  1)
    gl.TexCoord(1, 0) gl.Vertex( 1, -1,  1)
    gl.TexCoord(1, 1) gl.Vertex( 1,  1,  1)
    gl.TexCoord(0, 1) gl.Vertex(-1,  1,  1)
    -- Back Face
    gl.TexCoord(1, 0) gl.Vertex(-1, -1, -1)
    gl.TexCoord(1, 1) gl.Vertex(-1,  1, -1)
    gl.TexCoord(0, 1) gl.Vertex( 1,  1, -1)
    gl.TexCoord(0, 0) gl.Vertex( 1, -1, -1)
    -- Top Face
    gl.TexCoord(0, 1) gl.Vertex(-1,  1, -1)
    gl.TexCoord(0, 0) gl.Vertex(-1,  1,  1)
    gl.TexCoord(1, 0) gl.Vertex( 1,  1,  1)
    gl.TexCoord(1, 1) gl.Vertex( 1,  1, -1)
    -- Bottom Face
    gl.TexCoord(1, 1) gl.Vertex(-1, -1, -1)
    gl.TexCoord(0, 1) gl.Vertex( 1, -1, -1)
    gl.TexCoord(0, 0) gl.Vertex( 1, -1,  1)
    gl.TexCoord(1, 0) gl.Vertex(-1, -1,  1)
    -- Right face
    gl.TexCoord(1, 0) gl.Vertex( 1, -1, -1)
    gl.TexCoord(1, 1) gl.Vertex( 1,  1, -1)
    gl.TexCoord(0, 1) gl.Vertex( 1,  1,  1)
    gl.TexCoord(0, 0) gl.Vertex( 1, -1,  1)
    -- Left Face
    gl.TexCoord(0, 0) gl.Vertex(-1, -1, -1)
    gl.TexCoord(1, 0) gl.Vertex(-1, -1,  1)
    gl.TexCoord(1, 1) gl.Vertex(-1,  1,  1)
    gl.TexCoord(0, 1) gl.Vertex(-1,  1, -1)
  gl.End()

	xrot = xrot + 0.3
	yrot = yrot + 0.2
	zrot = zrot + 0.4

  glut.SwapBuffers()

end

function Keyboard(key)
  if key == 27 then
    os.exit()
  end
end

function SpecialKeys(key, x, y)
  if key == 1 then               -- Pressed F1 ?
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
  texture = gl.GenTextures(1)  -- Create The Texture

  -- Typical Texture Generation Using Data From The Bitmap
  gl.BindTexture('TEXTURE_2D', texture[1])
  gl.TexParameter('TEXTURE_2D','TEXTURE_MIN_FILTER','LINEAR')
  gl.TexParameter('TEXTURE_2D','TEXTURE_MAG_FILTER','LINEAR')

  img = LoadTGA('data/nehe.tga')

  gl.TexImage(0, img)
end

function Init()
  gl.Enable('TEXTURE_2D')            -- Enable Texture Mapping ( NEW )

  if LoadGLTextures() == false then      -- Jump To Texture Loading Routine ( NEW )
    return false
  end

  gl.ShadeModel('SMOOTH')            -- Enable Smooth Shading
  gl.ClearColor(0, 0, 0, 0.5)        -- Black Background
  gl.ClearDepth(1.0)                 -- Depth Buffer Setup
  gl.Enable('DEPTH_TEST')            -- Enables Depth Testing
  gl.DepthFunc('LEQUAL')             -- The Type Of Depth Testing To Do
  gl.Enable('COLOR_MATERIAL')
  gl.Hint('PERSPECTIVE_CORRECTION_HINT','NICEST')
end

glut.Init()
glut.InitDisplayMode()
glut.InitWindowSize(640, 480)
glut.CreateWindow('LuaGL Test Application 06')
glut.IdleFunc('DrawGLScene')
glut.DisplayFunc('DrawGLScene')
glut.ReshapeFunc('Reshape')
glut.KeyboardFunc('Keyboard')
glut.SpecialFunc('SpecialKeys')

Init()

glut.MainLoop()

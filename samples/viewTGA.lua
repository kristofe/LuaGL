dofile('loadLuaGL.lua')
dofile('loadTGA.lua')

texture = 0

function Reshape(width, height)
  gl.Viewport(0, 0, width, height)

  gl.MatrixMode('PROJECTION')   -- Select The Projection Matrix
  gl.LoadIdentity()             -- Reset The Projection Matrix
  
  if height == 0 then           -- Calculate The Aspect Ratio Of The Window
    height = 1
  end

  glu.Perspective(45, width / height, 0.1, 5)

  gl.MatrixMode('MODELVIEW')    -- Select The Model View Matrix
  gl.LoadIdentity()             -- Reset The Model View Matrix
end

function DrawGLScene()
  gl.Clear('COLOR_BUFFER_BIT,DEPTH_BUFFER_BIT') -- Clear Screen And Depth Buffer
  
  gl.LoadIdentity()             -- Reset The Current Modelview Matrix
	gl.Translate(0,0,-2.5)

  gl.BindTexture('TEXTURE_2D', texture[1])

  gl.Begin('QUADS')
    gl.TexCoord(0, 0) gl.Vertex(-1, -1)
    gl.TexCoord(1, 0) gl.Vertex( 1, -1)
    gl.TexCoord(1, 1) gl.Vertex( 1,  1)
    gl.TexCoord(0, 1) gl.Vertex(-1,  1)
  gl.End()

  glut.SwapBuffers()
end              

function Keyboard(key)
  if key == 27 then
    os.exit()    
  end            
end              

function Init()  
  gl.Enable('TEXTURE_2D')            -- Enable Texture Mapping ( NEW )

  texture = gl.GenTextures(1)  -- Create The Texture

  -- Typical Texture Generation Using Data From The Bitmap
  gl.BindTexture('TEXTURE_2D', texture[1])
  gl.TexParameter('TEXTURE_2D','TEXTURE_MIN_FILTER','LINEAR')
  gl.TexParameter('TEXTURE_2D','TEXTURE_MAG_FILTER','LINEAR')

  img = LoadTGA(fileName)

  if img == nil then
    print ("Unnable to open the TGA file: " .. fileName)
    os.exit()
  end
 
  glu.Build2DMipmaps(img)
end              

if arg[1] ~= nil then
  fileName = arg[1]
else
  fileName = 'data/luagl.tga'
end

glut.Init()      
glut.InitDisplayMode()
glut.InitWindowSize(640, 480)
glut.CreateWindow('TGA Loader')
glut.IdleFunc('DrawGLScene')
glut.DisplayFunc('DrawGLScene')
glut.ReshapeFunc('Reshape')
glut.KeyboardFunc('Keyboard')

Init()           

glut.MainLoop()  


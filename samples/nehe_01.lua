dofile('loadLuaGL.lua')

function Reshape(width, height)
  gl.Viewport(0, 0, width, height)

  gl.MatrixMode('PROJECTION')   -- Select The Projection Matrix
  gl.LoadIdentity()             -- Reset The Projection Matrix
  
  if height == 0 then height = 1 end       -- Avoid division by zero
  glu.Perspective(80, width / height, 1, 5000) -- Calculate The Aspect Ratio And Set The Clipping Volume

  gl.MatrixMode('MODELVIEW')    -- Select The Model View Matrix
  gl.LoadIdentity()             -- Reset The Model View Matrix
end

function DrawGLScene()
  gl.Clear('COLOR_BUFFER_BIT,DEPTH_BUFFER_BIT') -- Clear Screen And Depth Buffer
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

function Init()
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
glut.CreateWindow('LuaGL Test Application 01')
glut.DisplayFunc('DrawGLScene')
glut.ReshapeFunc('Reshape')
glut.KeyboardFunc('Keyboard')
glut.SpecialFunc('SpecialKeys')

Init()

glut.MainLoop()

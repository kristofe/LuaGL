dofile('loadLuaGL.lua')

rtri = 0
rquad = 0

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
  gl.Translate(-1.5, 0, -6)     -- Move Left 1.5 Units And Into The Screen 6.0
  gl.Rotate(rtri, 0, 1, 0)      -- Rotate The Triangle On The Y axis ( NEW )
  
  gl.Begin('TRIANGLES')         -- Drawing Using Triangles
    gl.Color ( 1, 0, 0)         -- Set The Color To Red
		gl.Vertex( 0, 1, 0)         -- Move Up One Unit From Center (Top Point)
    gl.Color ( 0, 1, 0)         -- Set The Color To Green
    gl.Vertex(-1,-1, 0)         -- Left And Down One Unit (Bottom Left)
    gl.Color ( 0, 0, 1)         -- Set The Color To Blue
    gl.Vertex( 1,-1, 0)         -- Right And Down One Unit (Bottom Right)
  gl.End()                      -- Done Drawing A Triangle

  gl.LoadIdentity()             -- Reset The Current Modelview Matrix
  gl.Translate(1.5, 0, -7)      -- Move Right And Into The Screen
  gl.Rotate(rquad, 1, 0, 0)     -- Rotate The Quad On The X axis ( NEW )
  
  gl.Color (0.5, 0.5, 1)        -- Set The Color To Blue One Time Only
  gl.Begin('QUADS')             -- Draw A Quad
    gl.Vertex(-1, 1, 0)         -- Top Left
    gl.Vertex( 1, 1, 0)         -- Top Right
    gl.Vertex( 1,-1, 0)         -- Bottom Right
    gl.Vertex(-1,-1, 0)         -- Bottom Left
  gl.End()
  
  rtri = rtri + 0.2             -- Increase The Rotation Variable For The Triangle ( NEW )
  rquad = rquad - 0.15          -- Decrease The Rotation Variable For The Quad     ( NEW )

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
glut.CreateWindow('LuaGL Test Application 04')
glut.IdleFunc('DrawGLScene')
glut.DisplayFunc('DrawGLScene')
glut.ReshapeFunc('Reshape')
glut.KeyboardFunc('Keyboard')
glut.SpecialFunc('SpecialKeys')

Init()

glut.MainLoop()

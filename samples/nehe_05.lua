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

  gl.Begin('TRIANGLES')         -- Drawing The Pyramid

    gl.Color ( 1, 0, 0)         -- Red
    gl.Vertex( 0, 1, 0)         -- Top Of Triangle (Front)
    gl.Color ( 0, 1, 0)         -- Green
    gl.Vertex(-1,-1, 1)         -- Left Of Triangle (Front)
    gl.Color ( 0, 0, 1)         -- Blue
    gl.Vertex( 1,-1, 1)         -- Right Of Triangle (Front)

    gl.Color ( 1, 0, 0)         -- Red
    gl.Vertex( 0, 1, 0)         -- Top Of Triangle (Right)
    gl.Color ( 0, 0, 1)         -- Blue
    gl.Vertex( 1,-1, 1)         -- Left Of Triangle (Right)
    gl.Color ( 0, 1, 0)         -- Green
    gl.Vertex( 1,-1,-1)         -- Right Of Triangle (Right)
    
    gl.Color ( 1, 0, 0)         -- Red
    gl.Vertex( 0, 1, 0)         -- Top Of Triangle (Back)
    gl.Color ( 0, 1, 0)         -- Green
    gl.Vertex( 1,-1,-1)         -- Left Of Triangle (Back)
    gl.Color ( 0, 0, 1)         -- Blue
    gl.Vertex(-1,-1,-1)         -- Right Of Triangle (Back)

    gl.Color ( 1, 0, 0)         -- Red
    gl.Vertex( 0, 1, 0)         -- Top Of Triangle (Left)
    gl.Color ( 0, 0, 1)         -- Blue
    gl.Vertex(-1,-1,-1)         -- Left Of Triangle (Left)
    gl.Color ( 0, 1, 0)         -- Green
    gl.Vertex(-1,-1, 1)         -- Right Of Triangle (Left)

  gl.End()                      -- Done Drawing The Pyramid
  
  gl.LoadIdentity()             -- Reset The Current Modelview Matrix
  gl.Translate(1.5, 0, -7)      -- Move Right And Into The Screen
  gl.Rotate(rquad, 1, 1, 1)     -- Rotate The Quad On The X, Y & Z
  
  gl.Begin('QUADS')             -- Draw A Cube

    gl.Color(0, 1, 0)        -- Set The Color To Green
    gl.Vertex( 1, 1,-1)      -- Top Right Of The Quad (Top)
    gl.Vertex(-1, 1,-1)      -- Top Left Of The Quad (Top)
    gl.Vertex(-1, 1, 1)      -- Bottom Left Of The Quad (Top)
    gl.Vertex( 1, 1, 1)      -- Bottom Right Of The Quad (Top)
    
    gl.Color(1, 0.5, 0)      -- Set The Color To Orange
    gl.Vertex( 1,-1, 1)      -- Top Right Of The Quad (Bottom)
    gl.Vertex(-1,-1, 1)      -- Top Left Of The Quad (Bottom)
    gl.Vertex(-1,-1,-1)      -- Bottom Left Of The Quad (Bottom)
    gl.Vertex( 1,-1,-1)      -- Bottom Right Of The Quad (Bottom)
    
    gl.Color(1, 0, 0)        -- Set The Color To Red
    gl.Vertex( 1, 1, 1)      -- Top Right Of The Quad (Front)
    gl.Vertex(-1, 1, 1)      -- Top Left Of The Quad (Front)
    gl.Vertex(-1,-1, 1)      -- Bottom Left Of The Quad (Front)
    gl.Vertex( 1,-1, 1)      -- Bottom Right Of The Quad (Front)
    
    gl.Color(1, 1, 0)        -- Set The Color To Yellow
    gl.Vertex( 1,-1,-1)      -- Bottom Left Of The Quad (Back)
    gl.Vertex(-1,-1,-1)      -- Bottom Right Of The Quad (Back)
    gl.Vertex(-1, 1,-1)      -- Top Right Of The Quad (Back)
    gl.Vertex( 1, 1,-1)      -- Top Left Of The Quad (Back)
    
    gl.Color(0, 0, 1)        -- Set The Color To Blue
    gl.Vertex(-1, 1, 1)      -- Top Right Of The Quad (Left)
    gl.Vertex(-1, 1,-1)      -- Top Left Of The Quad (Left)
    gl.Vertex(-1,-1,-1)      -- Bottom Left Of The Quad (Left)
    gl.Vertex(-1,-1, 1)      -- Bottom Right Of The Quad (Left)
    
    gl.Color(1, 0, 1)        -- Set The Color To Violet
    gl.Vertex( 1, 1,-1)      -- Top Right Of The Quad (Right)
    gl.Vertex( 1, 1, 1)      -- Top Left Of The Quad (Right)
    gl.Vertex( 1,-1, 1)      -- Bottom Left Of The Quad (Right)
    gl.Vertex( 1,-1,-1)      -- Bottom Right Of The Quad (Right)

  gl.End()            -- Done Drawing The Cube
  
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
glut.CreateWindow('LuaGL Test Application 05')
glut.IdleFunc('DrawGLScene')
glut.DisplayFunc('DrawGLScene')
glut.ReshapeFunc('Reshape')
glut.KeyboardFunc('Keyboard')
glut.SpecialFunc('SpecialKeys')

Init()

glut.MainLoop()

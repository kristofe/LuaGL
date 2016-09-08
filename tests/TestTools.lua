function ArrayToString(v)
  s = "";
  if(v == nil) then
     s = s .. ' - nil array - '
  return end
  s = s .. '{ '
  for i, a in pairs(v) do
    s = s .. a .. ','
  end
  return s .. '}\n'
end

function SearchOpenGLError()
  local glerror = gl.GetError()
  if (glerror ~= 'NO_ERROR') then
    print('\n\ngl.GetError() -> ' .. glerror)
    error('\n\ngl.GetError() -> ' .. glerror)
  end
end

function CompareError(n2,n1)
  local function wrapValue( v )
    if type(v) == 'string' then return "'"..v.."'" end
    return tostring(v)
  end
  local errorMsg = 'expected: '..wrapValue(n1)..', actual: '..wrapValue(n2)
  print(errorMsg..'\n')
  error(errorMsg)
end

function CompareArrayError(v2,v1)
  local errorMsg = 'expected: '..ArrayToString(v1)..', actual: '..ArrayToString(v2)
  print(errorMsg..'\n')
  error(errorMsg)
end

function Comp(n1, n2, epsilon)
  if(epsilon == nil) then
    return n1 == n2
  end
  return math.abs(n1 - n2) < epsilon
end

function CompareBool(b1, b2)
  if(b1 ~= b2) then
     CompareError(b2, b1)
  end
end

function Compare(n1, n2, epsilon)
  SearchOpenGLError()
  if( (n1 == nil and n2 ~= nil) or
      (n2 == nil and n1 ~= nil) or
      (Comp(n1, n2, epsilon) == false) ) then
     CompareError(n2, n1)
  end
end

function CompArray(v1, v2, epsilon)
  for i, v in pairs(v1) do
    if( v2[i] == nil or Comp(v, v2[i], epsilon) == false) then
       CompareArrayError(v2,v1)
       return
    end
  end
end

function CompareArray(v1, v2, epsilon)
  SearchOpenGLError()
  if( (v1 == nil and v2 ~= nil) or
      (v2 == nil and v1 ~= nil) or
      (v1 ~= nil and v2 ~= nil and CompArray(v1, v2, epsilon) == false)) then
     CompareError(v2,v1)
  end
end

-- compare floats numbers
function CompareF(n1, n2)
  return Compare(n2, n1, 0.0001)
end

-- compare char numbers
function CompareC(n1, n2)
  return Compare(n2, n1, 0.05)
end

-- compare floats arrays
function CompareArrayF(v1, v2)
  return CompareArray(v2, v1, 0.0001)
end

-- compare char arrays
function CompareArrayC(v1, v2)
  return CompareArray(v2, v1, 0.05)
end


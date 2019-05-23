
__code_begin__

function _draw()
  cls()
end

local i = 0
local d = 1

function _update()
  line(0, 0, 256, i, 2)
  line(256, 0, 256 - i, 256, 3)
  line(256, 256, 0, 256 - i, 4)
  line(0, 256, i, 0, 5)
  i = i + d

  if i == 512 or i == 0 then
    d = -d
  end
end

__code_end__
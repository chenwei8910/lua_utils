package.path = package.path .. ";lua/?.lua"

local t = {1, 2, 3, nil, 4, nil, nil, nil}
print("size of t: " .. #t)
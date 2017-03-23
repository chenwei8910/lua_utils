-- print(package.cpath)

-- package.cpath = package.cpath .. "F:\lua_utils\lua53\Debug\?.dll"

require ("studentdll.person")
require ("studentdll.student")

--print("new laowang")
local p = person.new("laowang", 40, 1);
p:print();

local s = student.new("xiaowang", 10, 0, 3);
s:print();

s:setName("xiaoming");
s:setGrade(4);
s:print();

collectgarbage ()
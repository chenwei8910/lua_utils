-- print(package.cpath)

-- package.cpath = package.cpath .. "F:\lua_utils\lua53\Debug\?.dll"

require ("studentdll.person")
require ("studentdll.student")

local m_per = package.loaded["person"]
print("person table: " .. tostring(m_per) .. " " .. tostring(package.loaded["studentdll.person"]))

local m_stu = package.loaded["studentdll.student"]
print("student table: " .. tostring(m_stu))

--print("new laowang")
local p = person.new("laowang", 40, 1);
p:print();

local s = student.new("xiaowang", 10, 0, 3);
s:print();

s:setName("xiaoming");
s:setGrade(4);
s:print();

collectgarbage ()
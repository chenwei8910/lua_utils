require("classUtil")

base = class()
base.s_static = 100				-- 定义base的一个静态变量

function base:ctor(x)
	print("base ctor")
	self.x = x
end

function base:print_x()
	print("base x = " .. self.x)
end

baseA = class(base)				-- 定义一个基类 baseA
baseA.s_static = 101			-- 定义baseA的一个静态变量
 
function baseA:ctor()			-- 定义 baseA 的构造函数
	print("baseA ctor")
	self.x = 2
end

function baseA:print_x()
	print("baseA x = " .. self.x)
end
 
function baseA:hello()  		-- 定义另一个成员函数 baseA:hello
	print("hello baseA: " .. baseA.s_static)
end

function baseA:showA()			-- 定义baseA自己的函数
	print("showA")
end

baseB = class(base)				-- 定义另一个基类 baseA
baseB.s_static = 102			-- 定义baseB的一个静态变量

function baseB:ctor()
	print("baseB ctor")
	self.x = 3
end

function baseB:print_x()
	print("baseB x = " .. self.x)
end
 
function baseB:hello()  		-- 定义另一个成员函数 baseB:hello
	print("hello baseB: " .. baseB.s_static)
end

function baseB:showB()			-- 定义baseB自己的函数
	print("showB")
end

test = class(baseA, baseB)		-- 定义一个类 test 继承于 baseA 和 baseB
test.s_static = 103				-- 定义test的一个静态变量

function test:ctor()			-- 定义 test 的构造函数
	print("test ctor")
end
 
function test:hello()			-- 重载 baseA:hello 为 test:hello
	print("hello test：" .. test.s_static)
end

function main()
	
	a = test.new(1)
	a:print_x()	-- 输出3，因为baseB的构造函数最后被调用，但是print_x函数实例是BaseA的
	a:hello()	-- 输出hello test，这个函数被重载了。

	a:showA()
	a:showB()

	-- 测试类的静态变量，实例对象无法访问，只能通过类访问
	print("a`s static: " .. (a.s_static or "nil") .. " base`s static: " .. (base.s_static or "nil"))

end

main()

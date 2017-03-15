-- 存储所有类的成员函数的列表
local _class = {}

-- @... 父类列表
function class(...)
	local class_type = {}
	class_type.ctor = false			-- 构造函数
	class_type.supers = {...}		-- 父类列表
	class_type.new = function(...)  -- 实例化对象函数
		local obj = {}
		do
			local create

			-- 记录已构造的父类列表
			local supers_marked = {}

			-- create主要调用构造函数（构造函数也只有在此时被调用，实例本身无法调用构造函数）
			create = function(c, ...)	
				local supers = c.supers
				if supers then
					for i = 1, #supers do 
						local super = supers[i]
						if not supers_marked[super] then
							-- 对没有构造过的父类才调用构造函数，解决多继承时有一个共同父类的问题
							create(super, ...)

							supers_marked[super] = true;
						end
					end
				end
				if c.ctor then
					c.ctor(obj, ...)
				end
			end
			create(class_type, ...)
		end
		-- 类的成员函数实际是存储于_class字典中的代理表（云风借用了C++的概念称之为虚表vtbl）中
		-- 所以实例对象直接去代理表中查找函数
		setmetatable(obj, {__index = _class[class_type]})
		return obj
	end

	-- 真正记录了类成员函数的虚表
	local vtbl = {}
	_class[class_type] = vtbl

	setmetatable(class_type, 
	{
		-- 此处是我的一个尝试，用于模拟实现实例无法直接访问的静态变量
		__newindex = function(t, k, v)
			local v_type = type(v)
			if v_type == "function" then
				-- 类的成员函数存储在_class列表中
				vtbl[k] = v
			else
				-- 类的静态变量存储在类自身中
				rawset(t, k, v)
			end
		end
	})

	-- 虚表中用元表实现多重继承
	local supers = class_type.supers
	if supers and #supers > 0 then
		setmetatable(vtbl, 
		{
			__index = function(t, k)
				for i = 1, #supers do 
					local super = supers[i]
					local ret = _class[super][k]
					if ret then
						vtbl[k] = ret
						return ret
					end
				end
			end	
		})
	end
	return class_type
end
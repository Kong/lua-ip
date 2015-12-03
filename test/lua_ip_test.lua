package.path = package.path..";./?.lua"

local ip = require "lua_ip"

local ip_address = ip.get_ip()

assert(ip_address)
assert(type(ip_address) == "string")

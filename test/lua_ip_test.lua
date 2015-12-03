package.path = package.path..";./?.lua"

local ip = require "lua_ip"

local ip_address = ip.get_ipv4()

assert(ip_address)
assert(type(ip_address) == "string")

ip_address = ip.get_ipv4("hello_world")
assert(ip_address == nil)
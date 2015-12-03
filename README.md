# lua_ip

Lua utility library for IPs.

## Usage

To retrieve the first, non-loopback, IPv4 IP address on the system:

```lua
local ip_utils = require "lua_ip"
local ip_str = ip_utils.get_ip()

print("IP address: "..ip_str)
```

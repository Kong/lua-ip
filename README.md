# lua_ip

Lua utility library for IPs.

## Usage

To retrieve the first, non-loopback, IPv4 IP address on the system. Optionally you can specify the interface to lookup.

```lua
local ip_utils = require "lua_ip"

-- Retrieve first available IP address
print("IP address is: "..ip_utils.get_ipv4())

-- Retrieve specific interface
print("IP address for eth0 is: "..ip_utils.get_ipv4("eth0"))
```


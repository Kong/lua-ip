/***
Generic IP utilities.

@license MIT
@module lua_ip
*/
#include <lua.h>
#include <lauxlib.h>
#include <stdio.h>      
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#include <net/if.h>

#if LUA_VERSION_NUM < 502
# define luaL_newlib(L,l) (lua_newtable(L), luaL_register(L,NULL,l))
# define lua_rawlen lua_objlen
#endif

/// Retrieve the first active non loopback IPv4 address
// @return ip_str
// @function get_ip()
static int get_ipv4(lua_State *L) {
  struct ifaddrs * ifAddrStruct=NULL;
  struct ifaddrs * ifa=NULL;
  void * tmpAddrPtr=NULL;

  getifaddrs(&ifAddrStruct);

  const char * interface = lua_tostring(L, 1);

  int found = 0;

  for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
    if (!ifa->ifa_addr) {
      continue;
    }

    if (!interface || strcmp(interface, ifa->ifa_name) == 0) {
      if ((ifa->ifa_flags & IFF_UP) == 0) continue; // Should be running
      if ((ifa->ifa_flags & IFF_LOOPBACK) != 0) continue; // Should not be loopback

      if (ifa->ifa_addr->sa_family == AF_INET) { // Should be IPv4
        tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
        char addressBuffer[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
        
        lua_pushstring(L, addressBuffer);
        found = 1;
        break;
      }
    }
  }

  if (!found) {
    lua_pushstring(L, NULL);
  }

  if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
  return 1;
}

static const luaL_Reg lua_ip[] = {
  {"get_ipv4", get_ipv4},
  {NULL, NULL}
};

int luaopen_lua_ip(lua_State *L){
  luaL_newlib(L, lua_ip);
  return 1;
}

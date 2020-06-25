#include <stdio.h>
#include "database/database.hpp"
#include <string.h>

int main()
{
    database::kv kv = database::kv("database-1");
    
    // database initialization -------------------------------------------------
    int res;
    if((res = kv.load()))
    {
        if((res = kv.create("0.0.1", "0.0.1")))
            return res;
    }
    
    bool is_exist;
    if((res = kv.is_exist("wifi/enable", is_exist)))
        return res;
    
    if(!is_exist)
    {
        if((res = kv.add("wifi/enable", sizeof(bool))))
            return res;
    }
    
    if((res = kv.is_exist("wifi/ssid", is_exist)))
        return res;
    
    constexpr auto ssid_max_length = 32;
    if(!is_exist)
    {
        if((res = kv.add("wifi/ssid", ssid_max_length)))
            return res;
    }
    
    // database common workflow ------------------------------------------------
    if((res = kv.set("wifi/enable", true)))
        return res;
    
    char ssid[ssid_max_length] = {};
    strcpy(ssid, "test12345");
    if((res = kv.set("wifi/ssid", ssid)))
        return res;
    
    bool enable;
    if((res = kv.get("wifi/enable", enable)))
        return res;
    
    memset(ssid, 0, sizeof(ssid));
    if((res = kv.get("wifi/ssid", ssid)))
        return res;
    
    return 0;
}
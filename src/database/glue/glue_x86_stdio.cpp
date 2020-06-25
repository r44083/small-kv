#include <string>
#include <stdio.h>
#include "glue.hpp"

constexpr const char* database_file = "database.bin";

int database::glue::read(size_t addr, void *buff, size_t size)
{
    FILE *f = fopen(database_file, "rb");
    if(!f)
        return -1;
    
    if(fseek(f, addr, SEEK_SET))
    {
        fclose(f);
        return -1;
    }
    
    int res = 0;
    if(::fread(buff, sizeof(char), size, f) != size)
        res = -1;
    
    int res_close = fclose(f);
    return res ? res : res_close;
}

int database::glue::write(size_t addr, void *buff, size_t size)
{
    FILE *f = fopen(database_file, "rb+");
    if(!f)
    {
        f = fopen(database_file, "wb");
        if(!f)
            return -1;
    }
    
    if(fseek(f, addr, SEEK_SET))
    {
        fclose(f);
        return -1;
    }
    
    int res = 0;
    if(::fwrite(buff, sizeof(char), size, f) != size)
        res = -1;
    
    int res_close = fclose(f);
    return res ? res : res_close;
}
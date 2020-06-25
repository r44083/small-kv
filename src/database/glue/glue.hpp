#pragma once

#include <string>

namespace database
{
class glue
{
    public:
        static int read(size_t addr, void *buff, size_t size);
        static int write(size_t addr, void *buff, size_t size);
        
    private:
        glue() {};
};
}
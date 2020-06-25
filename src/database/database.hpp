#pragma once

#include <string>
#include "glue/config.hpp"
#include "internal_types.hpp"

namespace database
{
class kv
{
    public:
        kv(std::string name);
        ~kv();
        
        int load();
        int create(std::string database_version, std::string datamodel_version);
        
        int is_exist(std::string path, bool &is_exist);
        int add(std::string path, size_t size);
        int del(std::string path);
        
        template <typename T>
        int set(std::string path, const T &value, size_t size = sizeof(T))
        {
            return set(path, (void *)&value, size);
        };
        
        template <typename T>
        int get(std::string path, T &value, size_t size = sizeof(T))
        {
            return get(path, &value, size);
        };
        
    private:
        int set(std::string &path, void *value, size_t size);
        int get(std::string &path, void *value, size_t size);
        int find_index_elem(std::string &path, index_elem_t &index_elem);
        int create_index_elem(index_elem_t &index_elem);
        
        std::string _name;
        header_t _header;
};
}
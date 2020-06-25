#include "database.hpp"
#include "glue/config.hpp"
#include "glue/glue.hpp"
#include "internal_types.hpp"
#include <string.h>
#include <assert.h>

using namespace database;

kv::kv(std::string name) :
    _header{0}
{
    assert(name.length() < database_name_length);
    
    _name = name;
}

kv::~kv()
{
    
}

int kv::load(void)
{
    int res;
    if((res = glue::read(0, &_header, sizeof(_header))))
        return res;
    
    if(_name != _header.name)
    {
        _header = {};
        return -1; // Database not found
    }
    
    // Check CRC
    
    return 0;
}

int kv::create(std::string database_version, std::string datamodel_version)
{
    assert(database_version.length() < database_version_length);
    assert(datamodel_version.length() < datamodel_version_length);
    
    _header = {};
    strncpy(_header.name, _name.c_str(), sizeof(_header.name) - 1);
    strncpy(_header.database_version, database_version.c_str(),
        sizeof(_header.database_version) - 1);
    strncpy(_header.datamodel_version, datamodel_version.c_str(),
        sizeof(_header.datamodel_version) - 1);
    
    // Calculate CRC
    
    int res = glue::write(0, &_header, sizeof(_header));
    
    return res;
}

int kv::is_exist(std::string path, bool &is_exist)
{
    index_elem_t index_elem;
    
    int res = find_index_elem(path, index_elem);
    
    is_exist = true;
    if(res == -2)
    {
        // Index element not found
        is_exist = false;
        res = 0;
    }
    
    return res;
}

int kv::add(std::string path, size_t size)
{
    assert(path.length() < path_max_length);
    
    index_elem_t index_elem;
    
    // Append index element to the end of index segment
    strncpy(index_elem.path, path.c_str(), sizeof(index_elem.path) - 1);
    index_elem.data_offset = sizeof(_header) + _header.index_size +
        sizeof(index_elem) + size;
    index_elem.data_size = size;
    
    int res;
    if((res = create_index_elem(index_elem)))
        return res;
    
    // Update database header after adding new element
    _header.index_size += sizeof(index_elem);
    _header.data_size += index_elem.data_size;
    res = glue::write(0, &_header, sizeof(_header));
    // If res != OK, delete created element
    
    return res;
}

int kv::del(std::string path)
{
    /*
    TODO:
    1. Find index element
    2. Move part of index segment back to sizeof(index_elem_t)
    3. Move part of data segment back to index_elem.data_size
    */
    
    return -1;
}

int kv::set(std::string &path, void *value, size_t size)
{
    assert(size);
    
    index_elem_t index_elem;
    
    int res;
    if((res = find_index_elem(path, index_elem)))
        return res;
    
    /*
    Do 'size' really need to match 'data_size'?
    What about string data type? String may be shorter than 'data_size'. In that
    case, need to make sure that 'size' less than 'data_size'.
    */
    if(size != index_elem.data_size)
        return -2; // Data size doesn't match
    
    res = glue::write(index_elem.data_offset, value, size);
    
    return res;
}

int kv::get(std::string &path, void *value, size_t size)
{
    assert(size);
    
    index_elem_t index_elem;
    
    int res;
    if((res = find_index_elem(path, index_elem)))
        return res;
    
    /*
    Do 'size' really need to match 'data_size'?
    What about string data type? String may be shorter than 'data_size'. In that
    case, need to make sure that 'size' less than 'data_size'.
    */
    if(size != index_elem.data_size)
        return -2; // Data size doesn't match
    
    res = glue::read(index_elem.data_offset, value, size);
    
    return res;
}

int kv::find_index_elem(std::string &path, index_elem_t &index_elem)
{
    int res = 0;
    size_t addr = sizeof(_header);
    
    while(addr < _header.index_size)
    {
        if((res = glue::read(addr, &index_elem, sizeof(index_elem))))
            break;
        
        if(path == index_elem.path)
            break;
        
        addr += sizeof(index_elem);
    }
    
    if(addr >= _header.index_size)
        res = -2; // Index element not found
    
    return res;
}

int kv::create_index_elem(index_elem_t &index_elem)
{
    int res = 0;
    
    if(_header.data_size)
    {
        // Move data segment further to get free space for index element
    }
    
    res = glue::write(sizeof(_header) + _header.index_size, &index_elem,
        sizeof(index_elem));
    
    return res;
}
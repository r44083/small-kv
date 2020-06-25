#pragma once

#include "glue/config.hpp"
#include <stdint.h>

namespace database
{
#pragma pack(push, 1)

struct header_t
{
    uint16_t crc:16;
    char name[database_name_length];
    char database_version[database_version_length];
    char datamodel_version[datamodel_version_length];
    size_t index_size:32;
    size_t data_size:32;
};

struct index_elem_t
{
    char path[path_max_length];
    size_t data_offset:32;
    size_t data_size:32;
};

#pragma pack(pop)
};
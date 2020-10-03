cmake_minimum_required(VERSION 3.5)

project(small-kv)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)

add_compile_options("-std=c++17" "-g" "-O0")

include_directories(src)

add_subdirectory(src/third_party/protobuf/cmake)
add_subdirectory(src/proto_types)
add_subdirectory(src/third_party/rax)
add_subdirectory(src/small-kv)

target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
        proto_types
        rax
        small_kv
        rax
        libprotobuf-lite
)
include_directories(../third_party/protobuf/src)

set(PROTOBUF_INCLUDE_DIR ../third_party/protobuf/src/google/protobuf)
set(PROTOBUF_PROTOC_EXECUTABLE protoc)
include(FindProtobuf)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS types.proto)

add_library(proto_types
    types.pb.cc
)
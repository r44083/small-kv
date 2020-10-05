include_directories(../third_party/protobuf/src)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS types.proto)

add_library(proto_types
    types.pb.cc
)
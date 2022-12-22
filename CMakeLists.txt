cmake_minimum_required(VERSION 3.21)
project(RTree)

set(CMAKE_CXX_STANDARD 11)

add_executable(RTree main.cpp Message.pb.cc)

TARGET_LINK_LIBRARIES(RTree libmysqlclient.so pthread protobuf )

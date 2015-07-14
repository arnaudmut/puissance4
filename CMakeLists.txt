cmake_minimum_required(VERSION 3.2)
project(puissance4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(puissance4 ${SOURCE_FILES} Puissance4.cpp Puissance4.h TCPStream.cpp TCPStream.h TCPConnector.cpp TCPConnector.h TCPAcceptor.cpp TCPAcceptor.h networking.cpp networking.h)
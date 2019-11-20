cmake_minimum_required(VERSION 3.15)
project(Http_Server)

set(CMAKE_CXX_STANDARD 14)

add_executable(Http_Server my_Server.cpp my_Server.h ServerManager.cpp ServerManager.h Parser.cpp Parser.h Reciever.cpp Reciever.h)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Http_Server Threads::Threads)

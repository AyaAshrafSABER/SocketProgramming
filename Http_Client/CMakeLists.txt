cmake_minimum_required(VERSION 3.15)
project(Http_Client)

set(CMAKE_CXX_STANDARD 14)

add_executable(Http_Client my_client.cpp my_client.h ClientManager.cpp ClientManager.h Receiver.cpp Receiver.h Sender.cpp Sender.h Parser.cpp Parser.h)
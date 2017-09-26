cmake_minimum_required(VERSION 2.6)
project(oaksouls)

add_executable(oaksouls main.cpp)

install(TARGETS oaksouls RUNTIME DESTINATION bin)

cmake_minimum_required(VERSION 2.6)
project(oaksouls)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set (CMAKE_CXX_STANDARD 11)

file(GLOB OAK_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp" "${CMAKE_SOURCE_DIR}/src/*.hpp")

file(GLOB OAKGEN_LIB_SOURCES "${CMAKE_SOURCE_DIR}/src/level_gen_tools/*.cpp" "${CMAKE_SOURCE_DIR}/src/level_gen_tools/*.h")


add_library(oakgen STATIC "${OAKGEN_LIB_SOURCES}")
add_executable(oaksouls "${OAK_SOURCES}")

find_package(Curses REQUIRED)
message("Curses Libraries are ${CURSES_LIBRARIES}.")
target_link_libraries(oaksouls "${CURSES_LIBRARIES}" "oakgen")

install(TARGETS oaksouls RUNTIME DESTINATION bin)



#add_executable(cursestest "${CMAKE_SOURCE_DIR}/tests/cursestest.cpp")
#target_link_libraries(cursestest "${CURSES_LIBRARIES}")

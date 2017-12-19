cmake_minimum_required(VERSION 2.6)
project(oaksouls)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

file(GLOB OAK_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp"
"${CMAKE_SOURCE_DIR}/src/*.hpp")

add_executable(oaksouls "${OAK_SOURCES}")

find_package(Curses REQUIRED)
message("Curses Libraries are ${CURSES_LIBRARIES}.")
target_link_libraries(oaksouls "${CURSES_LIBRARIES}")

install(TARGETS oaksouls RUNTIME DESTINATION bin)

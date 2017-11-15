cmake_minimum_required(VERSION 2.6)
project(oaksouls)

file(GLOB OAK_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp"
"${CMAKE_SOURCE_DIR}/src/*.hpp")

add_executable(oaksouls "${OAK_SOURCES}")
target_link_libraries(oaksouls ncurses tinfo)



install(TARGETS oaksouls RUNTIME DESTINATION bin)

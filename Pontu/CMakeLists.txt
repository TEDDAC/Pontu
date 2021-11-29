cmake_minimum_required(VERSION 3.13)

SET(ProjetName Pontu)

project(${ProjetName})

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
add_executable(${ProjetName} ${MY_SOURCES})


SET(WarningGCC -Wall -Wextra -pedantic -Wconversion -std=c17 -D_REENTRANT)

target_compile_options(${ProjetName} PRIVATE ${WarningGCC} -Og -fdiagnostics-color=always)
target_link_libraries(${ProjetName} SDL2)
target_include_directories(${ProjetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include /usr/include/SDL2)

cmake_minimum_required(VERSION 3.13)

SET(PROJECT_NAME Pontu)

project(${PROJECT_NAME})

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
add_executable(${PROJECT_NAME} ${MY_SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/entryPoints/main.c)
add_executable(Test ${MY_SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/entryPoints/test.c)



list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
#find_package(SDL2_ttf REQUIRED)
#find_package(SDL2_net REQUIRED)
#find_package(SDL2_image REQUIRED)


target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${SDL2_INCLUDE_DIR})
target_include_directories(Test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/test ${SDL2_INCLUDE_DIR})

SET(OptionGCC -Wall -Wextra -pedantic -Wconversion -std=c17)

if (MINGW)
	target_link_options(${PROJECT_NAME} PRIVATE -lmingw32 -lSDL2main -lSDL2 -mwindows)
	target_compile_options(${PROJECT_NAME} PRIVATE ${OptionGCC} -Dmain=SDL_main -fdiagnostics-color=always)
	target_link_options(Test PRIVATE -lmingw32 -lSDL2main -lSDL2 -mwindows)
	target_compile_options(Test PRIVATE ${OptionGCC} -Dmain=SDL_main -fdiagnostics-color=always)
elseif(UNIX)
    target_compile_options(${PROJECT_NAME} PRIVATE ${OptionGCC} -D_REENTRANT)
    target_compile_options(Test PRIVATE ${OptionGCC} -D_REENTRANT)
endif()

target_link_libraries(${PROJECT_NAME} SDL2::Main)
target_link_libraries(Test SDL2::Main)

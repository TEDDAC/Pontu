cmake_minimum_required(VERSION 3.13)

SET(PROJECT_NAME Pontu)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/entryPoints/main.c)
add_executable(Test ${CMAKE_CURRENT_SOURCE_DIR}/entryPoints/test.c)



list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
#find_package(SDL2_net REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${SDL2_INCLUDE_DIR})
target_include_directories(Test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${SDL2_INCLUDE_DIR})

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)

target_link_libraries(${PROJECT_NAME} SDL2::Main)
target_link_libraries(Test SDL2::Main)
target_link_libraries(${PROJECT_NAME} SDL2::Image)
target_link_libraries(Test SDL2::Image)
target_link_libraries(${PROJECT_NAME} SDL2::Mixer)
target_link_libraries(Test SDL2::Mixer)
target_link_libraries(${PROJECT_NAME} SDL2::TTF)
target_link_libraries(Test SDL2::TTF)

add_subdirectory(src/debug)
add_subdirectory(src/engine)
add_subdirectory(src/model)
add_subdirectory(src/view)

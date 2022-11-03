cmake_minimum_required(VERSION 3.0.0)
project(new_project VERSION 0.1.0)

find_package(SDL2 REQUIRED)

include_directories("/Library/Frameworks/SDL2.framework")
include_directories(${SDL2_INCLUDE_DIRS})
include_directories("./include/")

file(GLOB TARGET_SRC "./src/*.cpp" )

add_executable(main ${TARGET_SRC})
target_link_libraries(main ${SDL2_LIBRARIES})


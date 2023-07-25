
cmake_minimum_required(VERSION 3.14)
project(SandSimulation)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
#

file(GLOB sourceFile 
        "src/*.cpp"
        "include/*.h"
)

set(SOURCE_FILES ${sourceFile}) 
include_directories(/usr/local/include)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)


# 
add_executable(SandSimulation ${SOURCE_FILES})
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(SandSimulation sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

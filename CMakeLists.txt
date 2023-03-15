cmake_minimum_required(VERSION 3.24)

project(Core LANGUAGES CXX ASM)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

file(GLOB CORE
        *.cpp *.h # root
        Charset/*.cpp Charset/*.h
        Collections/*.cpp Collections/*h
        extern/*.cpp extern/*.h
        Function/*.cpp Function/*.h
        IO/*.cpp IO/*.h
        )

add_library(Core SHARED ${CORE} Collections/Set.cpp Collections/Set.h)

add_executable(Main Test/Main.cpp)

include(ctest)

add_test(NAME CoreT COMMAND "Main.exe" "博納九日")

target_link_libraries(Main Core)

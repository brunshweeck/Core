cmake_minimum_required(VERSION 3.24)

project(Core LANGUAGES CXX ASM)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_RPATH "build/Debug")

file(GLOB CORE
        *.cpp *.h # root
        Charset/*.cpp Charset/*.h
        Collections/*.cpp Collections/*h
        extern/*.cpp extern/*.h
        Function/*.cpp Function/*.h
        IO/*.cpp IO/*.h
        )

add_library(Core SHARED ${CORE} Collections/HashMap.cpp Collections/HashMap.h)

add_executable(Main Test/Main.cpp)

include(ctest)

add_test(NAME CoreT COMMAND "Main.exe" "博納九日")

target_link_libraries(Main Core)

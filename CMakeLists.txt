cmake_minimum_required(VERSION 3.24)

project(Core LANGUAGES CXX ASM)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-3")
#set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -gdwarf-3")

file(GLOB CORE
        *.cpp *.h # root
        Charset/*.cpp Charset/*.h
        Collections/*.cpp Collections/*h
        extern/*.cpp extern/*.h
        Function/*.cpp Function/*.h
        IO/*.cpp IO/*.h
        )

add_library(Core SHARED ${CORE} ValueError.cpp ValueError.h CastError.cpp CastError.h MemoryError.cpp MemoryError.h CodingError.cpp CodingError.h IOError.cpp IOError.h StateError.cpp StateError.h Break.cpp Break.h Collections/LinkedList.cpp Collections/LinkedList.h IndexError.cpp IndexError.h)

add_executable(Main Test/Main.cpp)

include(ctest)

add_test(NAME CoreT COMMAND "Main.exe" "博納九日")

target_link_libraries(Main Core)

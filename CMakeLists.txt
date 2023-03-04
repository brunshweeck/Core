cmake_minimum_required(VERSION 3.24)

project(Core LANGUAGES CXX ASM)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_library(Core SHARED
        Object.h
        Class.h
        extern/Macro.h
        extern/Class.h
        Core.cpp
        Long.cpp
        Long.h
        Number.cpp
        Number.h
        Integer.cpp
        Integer.h
        Byte.cpp
        Byte.h
        Short.cpp
        Short.h
        Float.cpp
        Float.h
        Double.cpp
        Double.h
        Boolean.cpp
        Boolean.h
        Comparable.h
        Enum.h
        Character.cpp
        Character.h
        String.cpp
        String.h
        Errors/Error.cpp
        Errors/Error.h
        Errors/MemoryAllocationError.cpp
        Errors/MemoryAllocationError.h
        Charset/Charset.cpp
        Charset/Charset.h
        Charset/Unicode.cpp
        Charset/Unicode.h
        Charset/UTF8.h
        Collections/Buffer.cpp
        Collections/Buffer.h
        Errors/ValueError.cpp
        Errors/ValueError.h
        Collections/ByteBuffer.cpp
        Collections/ByteBuffer.h
        Errors/OverflowError.cpp
        Errors/OverflowError.h
        Errors/IndexError.cpp
        Errors/IndexError.h
        Collections/CharBuffer.cpp
        Collections/CharBuffer.h
        Charset/UTF8.cpp
        Charset/UTF16.cpp
        Charset/UTF16.h
        Charset/UTF32.cpp
        Charset/UTF32.h
        Charset/MS1250.cpp
        Charset/MS1250.h
        Charset/MS1251.cpp
        Charset/MS1251.h
        Charset/MS1252.cpp
        Charset/MS1252.h
        Charset/MS1253.cpp
        Charset/MS1253.h
        Charset/MS1254.cpp
        Charset/MS1254.h
        Charset/MS1255.cpp
        Charset/MS1255.h
        Charset/MS1256.cpp
        Charset/MS1256.h
        Charset/MS1257.cpp
        Charset/MS1257.h
        Charset/MS1258.cpp
        Charset/MS1258.h
        Charset/MS874.cpp
        Charset/MS874.h
        Charset/MS936.h
        Charset/MS949.cpp
        Charset/MS949.h
        Charset/MS950.cpp
        Charset/MS950.h
        Hashable.cpp Hashable.h
        Errors/CastError.cpp
        Errors/CastError.h
        UCD00.cpp
        UCD01.cpp
        UCD02.cpp
        UCD03.cpp
        UCD04.cpp
        UCD05.cpp
        )

add_executable(Main Main.cpp)

target_link_libraries(Main Core)

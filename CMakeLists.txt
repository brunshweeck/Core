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
        Hashable.cpp Hashable.h
        Errors/CastError.cpp
        Errors/CastError.h
        UCD00.cpp
        UCD01.cpp
        UCD02.cpp
        UCD03.cpp
        UCD04.cpp
        UCD05.cpp
        Charset/US_ASCII.cpp
        Charset/US_ASCII.h
        Charset/UTF16BE.cpp
        Charset/UTF16BE.h Charset/UTF16LE.cpp
        Charset/UTF16LE.h Charset/UTF16LE_BOM.cpp Charset/UTF16LE_BOM.h
        Charset/UTF32BE.cpp Charset/UTF32BE.h Charset/UTF32LE.cpp Charset/UTF32LE.h
        Charset/UTF32LE_BOM.cpp Charset/UTF32LE_BOM.h Charset/UTF32BE_BOM.cpp
        Charset/UTF32BE_BOM.h Charset/UTF16BE_BOM.cpp Charset/UTF16BE_BOM.h
        Errors/IOError.cpp Errors/IOError.h Errors/CodingError.cpp Errors/CodingError.h
        Errors/UnderflowError.cpp Errors/UnderflowError.h Charset/ISO8859_1.cpp
        Charset/ISO8859_1.h Charset/ISO8859_2.cpp Charset/ISO8859_2.h Charset/ISO8859_4.cpp
        Charset/ISO8859_4.h Charset/ISO8859_5.cpp Charset/ISO8859_5.h Charset/ISO8859_7.cpp
        Charset/ISO8859_7.h Charset/ISO8859_9.cpp Charset/ISO8859_9.h Charset/ISO8859_13.cpp
        Charset/ISO8859_13.h Charset/ISO8859_15.cpp Charset/ISO8859_15.h Charset/ISO8859_16.cpp
        Charset/ISO8859_16.h extern/SingleByte.cpp extern/SingleByte.h extern/DoublyByte.cpp
        extern/DoublyByte.h Charset/IBM437.cpp Charset/IBM437.h Charset/IBM737.cpp Charset/IBM737.h
        Charset/IBM775.cpp Charset/IBM775.h Charset/IBM850.cpp Charset/IBM850.h Charset/IBM852.cpp
        Charset/IBM852.h Charset/IBM857.cpp Charset/IBM857.h Charset/IBM858.cpp Charset/IBM858.h
        Charset/IBM862.cpp Charset/IBM862.h Charset/IBM866.cpp Charset/IBM866.h Charset/IBM874.cpp
        Charset/IBM874.h Charset/IBM855.cpp Charset/IBM855.h Charset/GB18030.cpp Charset/GB18030.h
        Charset/GB18030_00.cpp Charset/GB18030_01.cpp Charset/GB18030_02.cpp Charset/GB18030_03.cpp
        Collections/Collection.cpp Collections/Collection.h Function/Consumer.cpp Function/Consumer.h
        Function/Functional.h Void.h Void.cpp Errors/Break.cpp Errors/Break.h Function/Predicate.cpp Function/Predicate.h Collections/CharArray.cpp Collections/CharArray.h Errors/StateError.cpp Errors/StateError.h)

add_executable(Main Test/Main.cpp)

include(ctest)

add_test(NAME CoreT COMMAND "Main.exe" "博納九日")

target_link_libraries(Main Core)

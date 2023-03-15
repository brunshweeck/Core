//
// Created by brunshweeck on 16/02/2023.
//

#ifndef CORE_EXTERN_CLASS_H
#define CORE_EXTERN_CLASS_H

#include "Macro.h"
#include <typeinfo>

class Void;

class Boolean;

class Byte;

class Short;

class Integer;

class Long;

class Float;

class Double;

class String;

class Character;

template<class E>
class Enum;

namespace core {
#pragma visibility push
#pragma visibility "hidden"
    namespace Class {
        /**
         *  Indicate that test is ok
         */
        struct AlwaysTrue {
            CORE_FAST static gbool V = true;
        };

        /**
         *  Indicate that test fail
         */
        struct AlwaysFalse {
            CORE_FAST static gbool V = false;
        };

        template<class T>
        struct Always {
            using Type = T;
        };

        template<class T, class U = T &&>
        CORE_FAST U _decl(i32);

        template<class T>
        CORE_FAST T _decl(i64);

        template<class T>
        CORE_FAST decltype(_decl<T>(0)) decl();

        template<class T, class U>
        struct Similar  : AlwaysFalse {
        };

        template<class T>
        struct Similar<T, T>  : AlwaysTrue {
        };

        template<class T>
        struct NoReference final : Always<T> {
        };

        template<class T>
        struct NoReference<T &> final : Always<T> {
        };

        template<class T>
        struct NoReference<T &&> final : Always<T> {
        };

        template<class T, gbool>
        struct If final : AlwaysFalse {
        };

        template<class T>
        struct If<T, true> : Always<T> {
        };

        template<class T, gbool, class U>
        struct IfElse final : Always<U> {
        };

        template<class T, class U>
        struct IfElse<T, true, U> final : Always<T> {
        };

        template<class T, class ...U>
        Always<decltype(decl<T>()(decl<U>()...))> ReturnTest1(i32);

        template<class T, class O, class ...U>
        Always<decltype((decl<O>().*decl<T>())(decl<U>()...))> ReturnTest2(i32);

        template<class T, class O, class ...U>
        Always<decltype(((*decl<O>()).*decl<T>())(decl<U>()...))> ReturnTest3(i32);

        template<class ...>
        AlwaysFalse ReturnTest1(i64);

        template<class ...>
        AlwaysFalse ReturnTest2(i64);

        template<class ...>
        AlwaysFalse ReturnTest3(i64);

        template<class Fn, class ...Args>
        struct Return final {
            using Type = decltype(ReturnTest1<Fn, Args...>(0));
            CORE_FAST static gbool V = !Similar<Type, AlwaysFalse>::V;
        };

        template<class R, class Fn, class Obj, class ...Args>
        struct Return<R Fn::*, Obj, Args...> final {
            using O = typename NoReference<Obj>::Type;
            using Type1 = decltype(ReturnTest2<R Fn::*, O, Args...>(0));
            using Type2 = decltype(ReturnTest3<R Fn::*, O, Args...>(0));
            CORE_FAST static gbool V1 = !Similar<Type1, AlwaysFalse>::V;
            CORE_FAST static gbool V2 = !Similar<Type2, AlwaysFalse>::V;
            CORE_FAST static gbool V = V1 || V2;
            using Type = typename IfElse<Type1, V1, Type2>::Type;
        };

        template<class T>
        struct Constant final : AlwaysFalse, Always<T const> {
            using Type2 = T;
        };

        template<class T>
        struct Constant<T const> final : AlwaysTrue, Always<T const> {
            using Type2 = T;
        };

        template<class T>
        struct Reference final : AlwaysFalse, Always<T &> {
            using Type2 = T;
            using Type3 = T &&;
        };

        template<class T>
        struct Reference<T &> final : AlwaysTrue, Always<T &> {
            using Type2 = T;
            using Type3 = T &&;
        };

        template<class T>
        struct Reference<T &&> final : AlwaysTrue, Always<T> {
            using Type2 = T;
            using Type3 = T &&;
        };

        template<>
        struct Reference<void> final : AlwaysFalse, Always<void> {
            using Type2 = void;
            using Type3 = void;
        };

        template<class T>
        struct Volatile final : AlwaysFalse, Always<T volatile> {
            using Type2 = T;
        };

        template<class T>
        struct Volatile<T volatile> final : AlwaysTrue, Always<T volatile> {
            using Type2 = T;
        };

        template<class T>
        struct Pointer final : AlwaysFalse, Always<T *> {
            using Type2 = T;
        };

        template<class T>
        struct Pointer<T *> final : AlwaysTrue, Always<T **> {
            using Type2 = T;
        };

        template<class T>
        struct Pointer<T &> final : AlwaysTrue, Always<T *> {
            using Type2 = T;
        };

        template<class T>
        struct Pointer<T &&> final : AlwaysTrue, Always<T *> {
            using Type2 = T;
        };

        template<class T>
        struct Template final : AlwaysFalse {
            using Type2 = T;
        };

        template<template<class ...> class T, class ...U>
        struct Template<T<U...>> final : AlwaysTrue {
        };

        template<class T>
        struct Function : Similar<T, T const> {
        };

        template<class T>
        struct Member final : AlwaysFalse {
            using Type2 = T;
        };

        template<class T, class U>
        struct Member<T U::*> final : AlwaysTrue {
        };

        template<class T>
        struct Member2 final : AlwaysFalse {
            using Type2 = T;
        };

        template<class T, class U>
        struct Member2<T U::*> final : Function<T> {
        };

        template<class T, CORE_SIZE = sizeof(T)>
        CORE_FAST gbool AbstractTest(i32) { return __is_abstract(T); }

        template<class ...>
        CORE_FAST gbool AbstractTest(i64) { return false; }

        template<class T, class U, CORE_SIZE = sizeof(T), CORE_SIZE = sizeof(U)>
        CORE_FAST gbool SuperTest(i32) { return __is_base_of(T, U); }

        template<class ...>
        CORE_FAST gbool SuperTest(i64) { return false; }

        template<class T>
        struct Array : AlwaysFalse, Always<T> {
        };

        template<class T, CORE_SIZE S>
        struct Array<T[S]> : AlwaysTrue, Always<T> {
        };

        template<class T>
        struct Array<T[]> : AlwaysTrue, Always<T> {
        };

        template<class T>
        void call(T);

        template<class T, class U, class = decltype(call<U>(decl<T>()))>
        AlwaysTrue ConvertTest(i32);

        template<class T, class U>
        AlwaysFalse ConvertTest(i64);

        template<class T, class U>
        struct Convert final : decltype(ConvertTest<T, U>(0)) {
        };

        template<class T>
        struct CR final : AlwaysFalse, Always<T const &> {
            using Type2 = T;
        };

        template<class T>
        struct CR<T &> final : AlwaysFalse, Always<T const &> {
            using Type2 = T;
        };

        template<class T>
        struct CR<T &&> final : AlwaysFalse, Always<T const &> {
        };

        template<class T>
        struct CR<T const> final : AlwaysFalse, Always<T const &> {
            using Type2 = T;
        };

        template<class T>
        struct CR<T const &> final : AlwaysFalse, Always<T const &> {
            using Type2 = T;
        };

        template<class T>
        struct CR<T const &&> final : AlwaysFalse, Always<T const &> {
            using Type2 = T;
        };

        template<>
        struct CR<void> final : AlwaysFalse, Always<void> {
            using Type2 = void;
        };

        template<class T>
        struct CV final : AlwaysFalse, Always<T const volatile> {
            using Type2 = T;
        };

        template<class T>
        struct CV<T const> final : AlwaysFalse, Always<T const volatile> {
            using Type2 = T;
        };

        template<class T>
        struct CV<T volatile> final : AlwaysFalse, Always<T const volatile> {
            using Type2 = T;
        };

        template<class T>
        struct CV<T const volatile> final : AlwaysFalse, Always<T const volatile> {
            using Type2 = T;
        };

        template<>
        struct CV<void> final : AlwaysFalse, Always<void> {
            using Type2 = void;
        };

        template<class T>
        struct CVR final : AlwaysFalse, Always<T const volatile &> {
            using Type2 = T;
        };

        template<class T>
        struct CVR<T &> final : AlwaysFalse, Always<T const volatile &> {
            using Type2 = T;
        };

        template<class T>
        struct CVR<T &&> final : AlwaysFalse, Always<T const volatile &> {
            using Type2 = T;
        };

        template<class T>
        struct CVR<T const> final : AlwaysFalse, Always<T const volatile &> {
            using Type2 = T;
        };

        template<class T>
        struct CVR<T const &> final : AlwaysFalse, Always<T const volatile &> {
            using Type2 = T;
        };

        template<class T>
        struct CVR<T const &&> final : AlwaysFalse, Always<T const volatile &> {
            using Type2 = T;
        };

        template<class T>
        struct CVR<T volatile> final : AlwaysFalse, Always<T const volatile &> {
            using Type2 = T;
        };

        template<class T>
        struct CVR<T volatile &> final : AlwaysFalse, Always<T const volatile &> {
            using Type2 = T;
        };

        template<class T>
        struct CVR<T volatile &&> final : AlwaysFalse, Always<T const volatile &> {
            using Type2 = T;
        };

        template<class T>
        struct CVR<T const volatile> final : AlwaysFalse, Always<T const volatile &> {
            using Type2 = T;
        };

        template<class T>
        struct CVR<T const volatile &> final : AlwaysFalse, Always<T const volatile &> {
            using Type2 = T;
        };

        template<class T>
        struct CVR<T const volatile &&> final : AlwaysFalse, Always<T const volatile &> {
            using Type2 = T;
        };

        template<class T, class U>
        struct CVR<T U::*> final : AlwaysFalse, Always<T const volatile> {
            using Type2 = T;
        };

        template<>
        struct CVR<void> final : AlwaysFalse, Always<void> {
            using Type2 = void;
        };

        template<class T, CORE_SIZE = sizeof(T)>
        AlwaysTrue CompleteTest(i32);

        template<class ...>
        AlwaysFalse CompleteTest(i64);

        template<class T>
        struct Complete : decltype(CompleteTest<T>(0)) {
        };

        template<class T>
        struct Array2 final : Always<void> {
        };

        template<class T, CORE_SIZE S>
        struct Array2<T[S]> final : Always<T> {
        };

        template<class T, CORE_SIZE S>
        struct Array3 final : Always<T[S]> {
        };

        template<CORE_SIZE S>
        struct Array3<void, S> final : Always<void> {
        };

        template<class T>
        struct Primitive : Always<void> {
        };

        template<>
        struct Primitive<Boolean> : Always<gbool> {
        };
        template<>
        struct Primitive<Byte> : Always<i8> {
        };
        template<>
        struct Primitive<Short> : Always<i16> {
        };
        template<>
        struct Primitive<Integer> : Always<i32> {
        };
        template<>
        struct Primitive<Long> : Always<i64> {
        };
        template<>
        struct Primitive<Float> : Always<f32> {
        };
        template<>
        struct Primitive<Double> : Always<f64> {
        };
        template<>
        struct Primitive<Character> : Always<u16> {
        };
        template<>
        struct Primitive<String> : Always<char *> {
        };

        template<class T>
        struct Class : Always<void> {
        };

        template<>
        struct Class<void> : Always<Void> {
        };
        template<>
        struct Class<gbool> : Always<Boolean> {
        };
        template<>
        struct Class<gchar> : Always<Character> {
        };
        template<>
        struct Class<wchar_t> : Always<Character> {
        };
        template<>
        struct Class<i8> : Always<Byte> {
        };
        template<>
        struct Class<i16> : Always<Short> {
        };
        template<>
        struct Class<i32> : Always<Integer> {
        };
        template<>
        struct Class<i64> : Always<Long> {
        };
        template<>
        struct Class<f32> : Always<Float> {
        };
        template<>
        struct Class<f64> : Always<Double> {
        };
        template<>
        struct Class<char> : Always<Character> {
        };
        template<>
        struct Class<char32_t> : Always<Integer> {
        };
        template<>
        struct Class<char *> : Always<String> {
        };
        template<>
        struct Class<char const *> : Always<String> {
        };
        template<>
        struct Class<char volatile *> : Always<String> {
        };
        template<>
        struct Class<char const volatile *> : Always<String> {
        };
        template<>
        struct Class<char16_t *> : Always<String> {
        };
        template<>
        struct Class<char16_t const *> : Always<String> {
        };
        template<>
        struct Class<char16_t volatile *> : Always<String> {
        };
        template<>
        struct Class<char16_t const volatile *> : Always<String> {
        };
        template<>
        struct Class<char32_t *> : Always<String> {
        };
        template<>
        struct Class<char32_t const *> : Always<String> {
        };
        template<>
        struct Class<char32_t volatile *> : Always<String> {
        };
        template<>
        struct Class<char32_t const volatile *> : Always<String> {
        };
        template<>
        struct Class<wchar_t *> : Always<String> {
        };
        template<>
        struct Class<wchar_t const *> : Always<String> {
        };
        template<>
        struct Class<wchar_t volatile *> : Always<String> {
        };
        template<>
        struct Class<wchar_t const volatile *> : Always<String> {
        };
        template<CORE_SIZE S>
        struct Class<char[S]> : Always<String> {
        };
        template<CORE_SIZE S>
        struct Class<char const[S]> : Always<String> {
        };
        template<CORE_SIZE S>
        struct Class<char volatile[S]> : Always<String> {
        };
        template<CORE_SIZE S>
        struct Class<char const volatile[S]> : Always<String> {
        };
        template<CORE_SIZE S>
        struct Class<char16_t[S]> : Always<String> {
        };
        template<CORE_SIZE S>
        struct Class<char16_t const[S]> : Always<String> {
        };
        template<CORE_SIZE S>
        struct Class<char16_t volatile[S]> : Always<String> {
        };
        template<CORE_SIZE S>
        struct Class<char16_t const volatile[S]> : Always<String> {
        };
        template<CORE_SIZE S>
        struct Class<char32_t[S]> : Always<String> {
        };
        template<CORE_SIZE S>
        struct Class<char32_t const[S]> : Always<String> {
        };
        template<CORE_SIZE S>
        struct Class<char32_t volatile[S]> : Always<String> {
        };
        template<CORE_SIZE S>
        struct Class<char32_t const volatile[S]> : Always<String> {
        };
        template<CORE_SIZE S>
        struct Class<wchar_t[S]> : Always<String> {
        };
        template<CORE_SIZE S>
        struct Class<wchar_t const[S]> : Always<String> {
        };
        template<CORE_SIZE S>
        struct Class<wchar_t volatile[S]> : Always<String> {
        };
        template<CORE_SIZE S>
        struct Class<wchar_t const volatile[S]> : Always<String> {
        };

        String const& className(void const* const address);

    }
#pragma visibility pop
}

#endif //CORE_EXTERN_CLASS_H

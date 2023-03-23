//
// Created by brunshweeck on 16/02/2023.
//

#ifndef CORE_MACRO_H
#define CORE_MACRO_H

#define CORE_FAST constexpr
#define CORE_EXPLICIT explicit
#define CORE_IMPLICIT explicit(false)
#define CORE_WARNINGS(WARN) [[WARN]]
#define CORE_DEPRECATED [[deprecated]]
#define CORE_NODISCARD [[nodiscard]]
#define CORE_NOTHROW noexcept

using CORE_BOOL = bool;
using CORE_CHAR8 = char;
using CORE_CHAR16 = char16_t;
using CORE_CHAR32 = char32_t;
using CORE_BYTE = signed char;
using CORE_SHORT = signed short int;
using CORE_INT = signed int;
using CORE_LONG = signed long long int;
using CORE_FLOAT = float;
using CORE_DOUBLE = double;
using CORE_SIZE = decltype(sizeof(0));

using u16 = CORE_CHAR16;
using i8 = CORE_BYTE;
using i16 = CORE_SHORT;
using i32 = CORE_INT;
using i64 = CORE_LONG;
using f32 = CORE_FLOAT;
using f64 = CORE_DOUBLE;

using gbool = CORE_BOOL;
using gchar = u16;
using gbyte = i8;
using gshort = i16;
using gint = i32;
using glong = i64;
using gfloat = f32;
using gdouble = f64;
#ifndef CORE_REQUIRE
#define CORE_REQUIRE(simpleCondition, errorMessage) static_assert((gbool)(simpleCondition), errorMessage "")
#endif //CORE_REQUIRE

#ifndef CORE_TEMPLATE_REQUIREMENT
#define CORE_TEMPLATE_REQUIRE_MUTABLE(E) CORE_REQUIRE(!Class<E>::isImmutable(), u"Immutable type not permitted")
#define CORE_TEMPLATE_REQUIRE_UNREFERENCED(E) CORE_REQUIRE(!Class<E>::isReference(), u"Reference type not permitted")
#define CORE_TEMPLATE_REQUIRE_NON_VOLATILE(E) CORE_REQUIRE(!Class<E>::isVolatile(), u"Volatile type not permitted")
#define CORE_TEMPLATE_REQUIRE_OBJECT(E) CORE_REQUIRE(Class<Object>::template isSuper<E>(), u"Only type deriving from Object are supported")

#define CORE_TEMPLATE_REQUIREMENT(E) \
    CORE_TEMPLATE_REQUIRE_MUTABLE(E);     \
    CORE_TEMPLATE_REQUIRE_UNREFERENCED(E);\
    CORE_TEMPLATE_REQUIRE_NON_VOLATILE(E);\
    CORE_TEMPLATE_REQUIRE_OBJECT(E);

#endif //CORE_TEMPLATE_REQUIREMENT

CORE_REQUIRE(sizeof(gbyte) << 3 == 8, u"This Compiler is not supported");
CORE_REQUIRE(sizeof(gshort) << 3 == 16, u"This Compiler is not supported");
CORE_REQUIRE(sizeof(gint) << 3 == 32, u"This Compiler is not supported");
CORE_REQUIRE(sizeof(glong) << 3 == 64, u"This Compiler is not supported");
CORE_REQUIRE(sizeof(gfloat) << 3 == 32, u"This Compiler is not supported");
CORE_REQUIRE(sizeof(gdouble) << 3 == 64, u"This Compiler is not supported");
CORE_REQUIRE(sizeof(gchar) << 3 == 16, u"This Compiler is not supported");
CORE_REQUIRE(sizeof(gbool) << 3 == 8, u"This Compiler is not supported");

#pragma region "PLATFORM MACRO LIST"

#ifndef CORE_SYSTEM
#if defined(__APPLE__) && defined(__GNUC__) || defined(__xlC__) || defined(__xlc__)
#define CORE_SYSTEM_APPLE

#elif defined(__WEBOS__)
#define CORE_SYSTEM_WEBOS

#elif defined(__ANDROID__) || defined(ANDROID)
#define CORE_SYSTEM_ANDROID
#define CORE_SYSTEM_LINUX

#elif defined(__CYGWIN__)
#define CORE_SYSTEM_CYGWIN

#elif !defined(SAG_COM) && (!defined(WINAPI_FAMILY) || WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP) && (defined(WIN64) || defined(_WIN64) || defined(__WIN64__))
#define CORE_SYSTEM_WIN64
#define CORE_SYSTEM_WIN32

#elif !defined(SAG_COM) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
#define CORE_SYSTEM_WIN32

#elif defined(__sun) || defined(sun)
#define CORE_SYSTEM_SOLARIS

#elif defined(hpux) || defined(__hpux)
#define CORE_SYSTEM_HUPX

#elif defined(__native_client__)
#define CORE_SYSTEM_NACL

#elif defined(__EMSCRIPTEN__)
#define CORE_SYSTEM_WASM

#elif defined(__linux__) || defined(__linux)
#define CORE_SYSTEM_LINUX

#elif defined(__FreeBSD__) || defined(__DragonFly__) || defined(__FreeBSD_kernel__)
#define CORE_SYSTEM_FREEBSD
#define CORE_SYSTEM_BSD4

#elif defined(__NetBSD__)
#define CORE_SYSTEM_NETBSD
#define CORE_SYSTEM_BSD4

#elif defined(__OpenBSD__)
#define CORE_SYSTEM_OPENBSD
#define CORE_SYSTEM_BSD4

#elif defined(__INTERIX)
#define CORE_SYSTEM_INTERIX
#define CORE_SYSTEM_BSD4

#elif defined(_AIX)
#define CORE_SYSTEM_AIX

#elif defined(__Lynx__)
#define CORE_SYSTEM_LYNX

#elif defined(__GNU__)
#define CORE_SYSTEM_HURD

#elif defined(__QNXNTO__)
#define CORE_SYSTEM_QNX

#elif defined(__INTEGRITY)
#define CORE_SYSTEM_INTEGITY

#elif defined(__rtems__)
#define CORE_SYSTEM_RTERMS

#elif defined(VXWORKS)
#define CORE_SYSTEM_VXWORKS

#elif defined(__HAIKU__)
#define CORE_SYSTEM_HAIKU

#elif defined(__MAKEDEPEND__)
#define CORE_SYSTEM_MAKEDEPEND
#else
#define CORE_SYSTEM 0
#endif //CORE_SYSTEM

#ifndef CORE_SYSTEM
#define CORE_SYSTEM 1
#endif //CORE_SYSTEM

#if defined(CORE_SYSTEM_WIN32) || defined(CORE_SYSTEM_WIN64)
// pour les system windows
#define CORE_SYSTEM_WINDOWS
#endif// CORE_SYSTEM_WIN

#if defined(CORE_SYSTEM_WINDOWS)

#ifdef CORE_SYSTEM_UNIX
#undef CORE_SYSTEM_UNIX
#endif// CORE_SYSTEM_UNIX

#elif !defined(CORE_SYSTEM_UNIX)
#define CORE_SYSTEM_UNIX
#endif //

#endif
#pragma endregion //PLATFORM MACRO LIST

#define CORE_CLASS_DECLARATIONS \
    template <class E> class ArrayList;\
    template <class T, class U> class BiConsumer;\
    template <class T, class U, class R> class BiFunction;\
    template <class T, class U> class BiPredicate;\
    class Boolean;\
    class Break;\
    class Byte;\
    class CastError;\
    class Charater;\
    class CharArray;\
    class CharBuffer;\
    class Charset;\
    template <class T> class Class;\
    class CodingError;\
    template <class E> class Collection;\
    template <class T> class Comparable;\
    template <class T> class Consumer;\
    class Double;\
    template <class E> class Enum;\
    class Error;\
    class Float;\
    template <class T, class R> class Function;\
    class Hashable;\
    template <class K, class V> class HashMap;\
    template <class E> class HashSet;\
    class IndexError;\
    class Integer;\
    class IOError;\
    template <class E> class LinkedList;\
    template <class E> class List;\
    class Long;\
    template <class K, class V> class Map;\
    class MemoryError;\
    class Number;\
    class Object;\
    template <class T> class Predicate;\
    template <class E> class Set;\
    class Short;\
    class StateError;\
    class String;\
    template <class K, class V> class TreeMap;\
    template <class E> class TreeSet;\
    class ValueError;\
    class Void;

#define CORE_TEMPLATE_REQUIRE_PRIMITIVE(_Obj, _Prim, _Holder, _Mask) \
    Class<gbool>::Require<!Class<_Prim>::isClass() && Class<_Prim>::isLiteral()> = true,                        \
    class _Holder = typename Class<_Prim>::Object,                      \
    Class<gbool>::Require<Class<_Obj>::template isSuper<_Holder>()> = true


#endif //CORE_MACRO_H

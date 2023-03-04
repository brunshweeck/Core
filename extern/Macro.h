//
// Created by brunshweeck on 16/02/2023.
//

#ifndef CORE_MACRO_H
#define CORE_MACRO_H

#define CORE_FAST constexpr
#define CORE_EXPLICIT explicit
#define CORE_IMPLICIT
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

static_assert(sizeof(gbool) == 1, "This Compiler Is Not Supported");
static_assert(sizeof(gchar) == 2, "This Compiler Is Not Supported");
static_assert(sizeof(i8) << 3 == 8, "This Compiler Is Not Supported");
static_assert(sizeof(i16) << 3 == 16, "This Compiler Is Not Supported");
static_assert(sizeof(i32) << 3 == 32, "This Compiler Is Not Supported");
static_assert(sizeof(i64) << 3 == 64, "This Compiler Is Not Supported");
static_assert(sizeof(f32) << 3 == 32, "This Compiler Is Not Supported");
static_assert(sizeof(f64) << 3 == 64, "This Compiler Is Not Supported");

#endif //CORE_MACRO_H

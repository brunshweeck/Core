//
// Created by brunshweeck on 17/02/2023.
//

#include "Object.h"
#include "String.h"
#include "Long.h"
#include "extern/Class.h"
#include "MemoryError.h"

static String classname = {};

#include <cxxabi.h>
#include <cstdlib>

static char *mangle_name = (char *) malloc(256);
size_t mangle_size = 256;
gint mangle_status = 0;

String const &core::Class::className(const void *const v) {
    if (v == nullptr)
        throw MemoryError("Access to memory address failed");
    const char *c = ((std::type_info const *const) v)->name();
    __cxxabiv1::__cxa_demangle(c, mangle_name, &mangle_size, &mangle_status);
    classname = mangle_name;
    return classname;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"







#pragma GCC diagnostic pop
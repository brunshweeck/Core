//
// Created by brunshweeck on 09/03/2023.
//

#include "CharArray.h"
#include "../Errors/ValueError.h"
#include "../Errors/MemoryAllocationError.h"
#include "../Errors/IndexError.h"

CharArray::CharArray(gint length, gchar fill) : len(0), value() {
    if (length < 0)
        throw ValueError("Illegal array length");
    try {
        value = new gchar[length + 1];
        gint i;
        for (i = 0; i < length; ++i)
            value[i] = fill;
        value[i] = '\u0000';
        len = length;
    } catch (...) { throw MemoryAllocationError(); }
}

CharArray::CharArray(const CharArray &array) : len() {
    try {
        value = new gchar[array.len + 1];
        gint i;
        for (i = 0; i < array.len; ++i)
            value[i] = array.value[i];
        value[i] = '\u0000';
        len = array.len;
    } catch (...) { throw MemoryAllocationError(); }
}

CharArray::CharArray(CharArray &&array) CORE_NOTHROW {
    gchar *old = value;
    value = array.value;
    array.value = old;
    gint old2 = len;
    len = array.len;
    array.len = old2;
}

CharArray &CharArray::operator=(const CharArray &array) {
    if (this != &array) {
        delete value;
        len = 0;
        try {
            value = new gchar[array.len + 1];
            gint i;
            for (i = 0; i < array.len; ++i)
                value[i] = array.value[i];
            value[i] = '\u0000';
            len = array.len;
        } catch (...) { throw MemoryAllocationError(); }
    }
    return *this;
}

CharArray &CharArray::operator=(CharArray &&array) CORE_NOTHROW {
    if (this != &array) {
        gchar *old = value;
        value = array.value;
        array.value = old;
        gint old2 = len;
        len = array.len;
        array.len = old2;
    }
    return *this;
}

gint CharArray::length() const {
    return len < 0 || !value ? 0 : len;
}

gchar CharArray::get(gint index) const {
    if (index < 0 || index >= len)
        throw IndexError(index);
    return value[index];
}

gchar CharArray::set(gint index, gchar c) {
    if (index < 0 || index >= len)
        throw IndexError(index);
    gchar old = value[index];
    value[index] = c;
    return old;
}

gchar const CharArray::operator[](gint index) const {
    return get(index);
}

gchar &CharArray::operator[](gint index) {
    if (index < 0 || index >= len)
        throw IndexError(index);
    return value[index];
}

gint CharArray::compareTo(const CharArray &obj) const {
    gint i;
    for (i = 0; i < len && i < obj.len; ++i) {
        if (value[i] != obj.value[i])
            return value[i] - obj.value[i];
    }
    return len == obj.len ? 0 : i == len ? obj.value[i] : value[i];
}

gbool CharArray::equals(const Object &obj) const {
    if(this == &obj)
        return true;
    if(!dynamic_cast<CharArray const*>(&obj))
        return false;
    CharArray const& array = (CharArray const&) obj;
    if(len != array.len)
        return false;
    return compareTo(array) == 0;
}

Object &CharArray::clone() const {
    try { return *new CharArray(*this); }catch (...) { throw MemoryAllocationError(); }
}

String CharArray::toString() const {
    if(len == 0)
        return "[]";
    gint newLen = len + len*2 + (len-1)*2 + 2;
    //            char   '+'     ,+space    error
    gint j = 0;
    gchar out[newLen];
    out[j++] = '[';
    out[newLen] = 0;
    for (gint i = 0; i < len; ++i) {
        out[j++] = '\'';
        out[j++] = value[i];
        out[j++] = '\'';
        if(i < len-1) {
            out[j++] = ',';
            out[j++] = ' ';
        }
    }
    out[j++] = ']';
    return String(out+0, 0, j);
}

void CharArray::set(const Object &obj) {
    if (this != &obj)
        if (dynamic_cast<CharArray const *>(&obj)) {
            CharArray const &array = (CharArray const &) obj;
            *this = array;
        }
}

CharArray CharArray::of(gchar _0) {
    gchar c[] = {_0};
    return CharArray(c);
}

CharArray CharArray::of(gchar _0, gchar _1) {
    gchar c[] = {_0, _1};
    return CharArray(c);
}

CharArray CharArray::of(gchar _0, gchar _1, gchar _2) {
    gchar c[] = {_0, _1, _2};
    return CharArray(c);
}

CharArray CharArray::of(gchar _0, gchar _1, gchar _2, gchar _3) {
    gchar c[] = {_0, _1, _2, _3};
    return CharArray(c);
}

CharArray CharArray::of(gchar _0, gchar _1, gchar _2, gchar _3, gchar _4) {
    gchar c[] = {_0, _1, _2, _3, _4};
    return CharArray(c);
}

CharArray CharArray::of(gchar _0, gchar _1, gchar _2, gchar _3, gchar _4, gchar _5) {
    gchar c[] = {_0, _1, _2, _3, _4, _5};
    return CharArray(c);
}

CharArray CharArray::of(gchar _0, gchar _1, gchar _2, gchar _3, gchar _4, gchar _5, gchar _6) {
    gchar c[] = {_0, _1, _2, _3, _4, _5, _6};
    return CharArray(c);
}

CharArray CharArray::of(gchar _0, gchar _1, gchar _2, gchar _3, gchar _4, gchar _5, gchar _6, gchar _7) {
    gchar c[] = {_0, _1, _2, _3, _4, _5, _6, _7};
    return CharArray(c);
}

CharArray CharArray::of(gchar _0, gchar _1, gchar _2, gchar _3, gchar _4, gchar _5, gchar _6, gchar _7, gchar _8) {
    gchar c[] = {_0, _1, _2, _3, _4, _5, _6, _7, _8};
    return CharArray(c);
}

CharArray
CharArray::of(gchar _0, gchar _1, gchar _2, gchar _3, gchar _4, gchar _5, gchar _6, gchar _7, gchar _8, gchar _9) {
    gchar c[] = {_0, _1, _2, _3, _4, _5, _6, _7, _8, _9};
    return CharArray(c);
}

CharArray::CharArray(const CharBuffer &buffer): CharArray(buffer.remaining()) {
    gint mark = buffer.position();
    gint i = 0;
    while (buffer.hasRemaining())
        value[i++] = buffer.get();
}

CharArray::operator CharBuffer() {
    CharBuffer buffer = CharBuffer(-1, 0, len, len, value, 0);
    return buffer;
}

//
// Created by brunshweeck on 24/02/2023.
//

#include "String.h"
#include "MemoryError.h"
#include "Character.h"
#include "ValueError.h"
#include "IndexError.h"
#include "Collections/CharArray.h"
#include "Charset/Charset.h"
#include "Integer.h"

template<class T, class K>
static void fill(T v[], K i, glong len) {
    for (gint j = 0; j < len; ++j)
        v[j] = i;
}

template<class T, class K>
static void swap(T &v, K &i) {
    K k = i;
    i = v;
    v = k;
}

template<class T, class K>
static void swap(T &&v, K &i) {
    K k = i;
    i = (T &&) v;
    v = k;
}

template<class T = gbyte>
static T *allocate(glong len) {
    if (len < 0)
        return nullptr;
    T *buffer;
    try {
        buffer = new T[(len << 1) + 1];
    } catch (...) {
        if (len == 0)
            return nullptr;
        throw MemoryError();
    }
    fill(buffer, 0x00, len + 1);
    return buffer;
}

template<class T, class K>
void arraycopy(T src[], glong srcBegin, K dst[], glong dstBegin, glong length) {
    srcBegin = srcBegin << 1;
    dstBegin = dstBegin << 1;
    length = length << 1;
    for (gint i = 0; i < length; ++i)
        dst[i + dstBegin] = (T) src[i + srcBegin];
}


static gint nextIndex = -1;

static gchar getChar(gbyte const v[], gint index) {
    nextIndex = index + 1;
    index = index << 1;
    return Character(v[index], v[index + 1]).charValue();
}

static gchar getChar2(gbyte const v[], gint index) {
    nextIndex = index - 1;
    index = index << 1;
    return Character(v[index - 1], v[index]).charValue();
}


static gint getCP(gbyte const v[], gint index) {
    gchar c = getChar(v, index);
    if (Character::isHighSurrogate(c)) {
        gchar d = getChar(v, nextIndex);
        if (Character::isLowSurrogate(d)) {
            nextIndex = index + 2;
            return Character::joinSurrogates(c, d);
        }
    }
    nextIndex = index + 1;
    return (gint) c;
}

static gint getCP2(gbyte const v[], gint index) {
    gchar c = getChar2(v, index);
    if (Character::isLowSurrogate(c)) {
        gchar d = getChar2(v, nextIndex);
        if (Character::isHighSurrogate(d)) {
            nextIndex = index - 2;
            return Character::joinSurrogates(d, c);
        }
    }
    nextIndex = index - 1;
    return (gint) c;
}

static void put(gbyte v[], gint index, gchar c) {
    v[index << 1] = Character::highByte(c);
    v[(index << 1) + 1] = Character::lowByte(c);
    nextIndex = index + 1;
}

static void put(gbyte v[], gint index, gint cp) {
    if (!Character::isValidCodePoint(cp))
        throw ValueError("Illegal unicode code point: U+" + Integer::toHexString(cp));
    if (!Character::isSupplementary(cp))
        put(v, index, (gchar) cp);
    else {
        put(v, index, Character::highSurrogate(cp));
        put(v, nextIndex, Character::lowSurrogate(cp));
    }
}

//String::String() : value(allocate(0)), len(0) {}

String::String(String &&original) CORE_NOTHROW: String() {
    swap(original.value, value);
    swap(original.len, len);
}

String::String(const String &original) {
    value = allocate(original.len);
    len = original.len;
    arraycopy(original.value, 0, value, 0, len << 1);
}

String String::concat(const String &str) const {
    String out;
    delete[] out.value;
    out.value = allocate(len + str.len);
    out.len = len + str.len;
    arraycopy(value, 0, out.value, 0, len);
    arraycopy(str.value, 0, out.value, len, str.len);
    return out;
}

String::String(const gbyte *bytes, gint length, const Charset &charset) {
    Charset &cs = (Charset &) charset;
    ByteBuffer byteBuffer = ByteBuffer(-1, 0, length, length, (gbyte *) bytes, 0);
    CharBuffer charBuffer = cs.decode(byteBuffer);
    value = allocate(charBuffer.remaining());
    len = 0;
    for (gint j = 0; charBuffer.hasRemaining(); j = len = nextIndex)
        put(value, j, charBuffer.get());
    delete[] (gchar *) charBuffer.base();
}

String &String::operator=(const String &str) {
    if (this != &str) {
        if (len != str.len) {
            delete[] value;
            len = 0;
            value = allocate(str.len);
            len = str.len;
        }
        arraycopy(str.value, 0, value, 0, len);
    }
    return *this;
}

String &String::operator=(String &&str) CORE_NOTHROW {
    swap(str.value, value);
    swap(str.len, len);
    return *this;
}

String String::replace(gchar oldChar, gchar newChar) const {
    String out;
    delete[] out.value;
    out.value = allocate(len);
    out.len = len;
    for (gint i = 0; i < len; i = nextIndex) {
        gchar c = getChar(value, i);
        put(out.value, i, c == oldChar ? newChar : c);
    }
    return out;
}

String String::strip() const {
    gint i;
    for (i = 0; i < len; i = nextIndex)
        if (!Character::isSpace(getCP(value, i)))
            break;
    if (i >= len)
        return "";
    gint j;
    for (j = len - 1; j > i; j = nextIndex)
        if (!Character::isSpace(getCP2(value, j)))
            break;
    String out;
    delete[] out.value;
    out.value = allocate(j - i + 1);
    out.len = j - i + 1;
    arraycopy(value, i, out.value, 0, out.len);
    return out;
}

String String::stripLeading() const {
    gint i;
    for (i = 0; i < len; i = nextIndex)
        if (!Character::isSpace(getCP(value, i)))
            break;
    if (i >= len)
        return "";
    String out;
    delete[] out.value;
    out.value = allocate(len - i);
    out.len = len - i;
    arraycopy(value, i, out.value, 0, out.len);
    return out;
}

String String::stripTrailing() const {
    gint j;
    for (j = len - 1; j >= 0; j = nextIndex)
        if (!Character::isSpace(getCP2(value, j)))
            break;
    if (j < 0)
        return "";
    String out;
    delete[] out.value;
    out.value = allocate(j + 1);
    out.len = j + 1;
    arraycopy(value, 0, out.value, 0, out.len);
    return out;
}

String String::replace(const String &regex, const String &replacement) const {
    gint cnt = count(regex);
    gint newSize = len + (replacement.len - regex.len);
    String out;
    delete[] out.value;
    out.value = allocate(newSize);
    out.len = newSize;
    for (gint i = 0, k = 0; i < len;) {
        gint j;
        for (j = 0; j < regex.len; j = nextIndex) {
            if (getCP(value, i + j) != getCP(regex.value, j))
                break;
        }
        if (j < regex.len) {
            put(out.value, k, getCP(value, i));
            k = nextIndex;
            i = i + 1;
        } else {
            arraycopy(replacement.value, 0, out.value, k, replacement.len);
            k = k + replacement.len;
            i = i + regex.len;
        }
    }
    return out;
}

String String::repeat(gint count) const {
    if (count < 0)
        throw ValueError("Repeat times is negative");
    String out;
    delete[] out.value;
    out.value = allocate(len * count);
    out.len = len * count;
    for (gint i = 0; i < len; ++i)
        for (gint j = 0; j < count; ++j)
            put(out.value, i * j, getChar(value, i));
    return out;
}

String String::toUpperCase() const {
    String out;
    delete[] out.value;
    out.value = allocate(len);
    out.len = len;
    gint i;
    gint j = 0;
    for (i = 0; i < len;) {
        gint c = getCP(value, i);
        i = nextIndex;
        gint cp = Character::toUpperCase(c);
        put(out.value, j, cp);
        j = nextIndex;
    }
    return out;
}

String String::toLowerCase() const {
    String out;
    delete[] out.value;
    out.value = allocate(len);
    out.len = len;
    for (gint i = 0; i < len; i = nextIndex)
        put(out.value, i, Character::toLowerCase(getCP(value, i)));
    return out;
}

String String::toTitleCase() const {
    String out;
    delete[] out.value;
    out.value = allocate(len);
    out.len = len;
    for (gint i = 0; i < len; i = nextIndex)
        put(out.value, i, Character::toTitleCase(getCP(value, i)));
    return out;
}

String String::toString() const {
    return *this;
}

gbool String::isAscii() const {
    for (gint i = 0; i < len; ++i)
        if (!Character::isAscii(getChar(value, i)))
            return false;
    return true;
}

String String::subString(gint begin) const {
    if (begin < 0 || begin > len)
        throw IndexError(begin);
    String out;
    delete[] out.value;
    out.value = allocate(len - begin);
    out.len = len - begin;
    arraycopy(value, begin, out.value, 0, out.len);
    return out;
}

String String::subString(gint begin, gint end) const {
    if (begin < 0 || begin > len)
        throw IndexError(begin);
    if (end < 0)
        throw IndexError(end);
    if (end >= len)
        end = len - 1;
    String out;
    delete[] out.value;
    out.value = allocate(end - begin + 1);
    out.len = end - begin + 1;
    arraycopy(value, begin, out.value, 0, out.len);
    return out;
}

gchar String::charAt(gint index) const {
    if (index < 0 || index >= len)
        throw IndexError(index);
    return getChar(value, index);
}

gint String::codepointAt(gint index) const {
    if (index < 0 || index >= len)
        throw IndexError(index);
    return getCP(value, index);
}

gbool String::isEmpty() const {
    return len == 0 || !value;
}

gint String::length() const {
    return isEmpty() ? 0 : len;
}

gint String::bytes(gbyte *dst, gint length, gint begin, gint end) const {
    if (begin < 0)
        throw IndexError(begin);
    if (end < 0)
        throw IndexError(end);
    gint size = end - begin + 1;
    size = size > length ? length : size;
    size = size > len ? len : size;
    size = size < 0 ? 0 : size;
    arraycopy(value, begin, dst, 0, size);
    return size << 1;
}

gbool String::equals(const Object &obj) const {
    if (this == &obj)
        return true;
    if (!dynamic_cast<String const *>(&obj))
        return false;
    String const &str = (String const &) obj;
    if (str.len != len)
        return false;
    for (gint i = 0; i < len; i = nextIndex)
        if (getChar(value, i) != getChar(str.value, i))
            return false;
    return true;
}

gbool String::equalsIgnoreCase(const String &str) const {
    if (len != str.len)
        return false;
    for (gint i = 0; i < len; i = nextIndex)
        if (Character::toLowerCase(getChar(value, i)) != Character::toLowerCase(getChar(str.value, i)))
            return false;
    return true;
}

gint String::compareTo(const String &str) const {
    gint i;
    for (i = 0; i < len && i < str.len; i = nextIndex) {
        gchar c1 = getChar(value, i);
        gchar c2 = getChar(str.value, i);
        if (c1 != c2)
            return c1 - c2;
    }
    gchar c;
    return len == str.len ? 0 :
           i == len ? (c = getChar(str.value, i)) == 0 ? -1 : -c :
           (c = getChar(value, i)) == 0 ? 1 : c;
}

gint String::compareToIgnoreCase(const String &str) const {
    gint i;
    for (i = 0; i < len && i < str.len; i = nextIndex) {
        gchar c1 = getChar(value, i);
        gchar c2 = getChar(str.value, i);
        if (c1 != c2)
            if (Character::toLowerCase(c1) != Character::toLowerCase(c2))
                return c1 - c2;
    }
    gchar c;
    return len == str.len ? 0 :
           i == len ? (c = getChar(str.value, i)) == 0 ? -1 : -c :
           (c = getChar(value, i)) == 0 ? 1 : c;
}

gbool String::startsWith(const String &prefix, gint begin) const {
    if (len - begin >= prefix.len && prefix.len > 0) {
        for (gint i = 0; i < prefix.len; i = nextIndex)
            if (getChar(value, i + begin) != getChar(prefix.value, i))
                return false;
        return true;
    }
    return false;
}

gbool String::startsWith(const String &prefix) const {
    return startsWith(prefix, 0);
}

gbool String::endsWith(const String &suffix) const {
    if (len >= suffix.len && suffix.len > 0) {
        gint i = suffix.len - 1, j;
        for (j = len - 1; i >= 0;) {
            gchar c1 = getChar2(value, j);
            j = nextIndex;
            gchar c2 = getChar2(suffix.value, i);
            i = nextIndex;
            if (c1 != c2)
                return false;
        }
        return true;
    }
    return false;
}

glong String::hash() const {
    glong _hash = 0;
    for (gint i = 0; i < len; i = nextIndex)
        _hash = _hash + 31 * getChar(value, i);
    return _hash;
}

gint String::indexOf(gint ch) const {
    return indexOf(ch, 0);
}

gint String::indexOf(gint ch, gint begin) const {
    if (Character::isValidCodePoint(ch))
        for (gint i = begin; i < len; i = nextIndex)
            if (getCP(value, i) == ch)
                return i;
    return -1;
}

gint String::lastIndexOf(gint ch) const {
    return lastIndexOf(ch, len);
}

gint String::lastIndexOf(gint ch, gint begin) const {
    if (begin >= len)
        begin = len - 1;
    if (Character::isValidCodePoint(ch))
        for (gint i = begin; i >= 0; i = nextIndex)
            if (getCP2(value, i) == ch)
                return i;
    return -1;
}

gint String::indexOf(const String &str) const {
    return indexOf(str, 0);
}

gint String::indexOf(const String &str, gint begin) const {
    for (gint i = begin; i < len && len - i >= str.len;) {
        gint j;
        for (j = 0; j < str.len; j = nextIndex)
            if (getChar(value, i + j) != getChar(str.value, j))
                break;
        if (j >= str.len)
            return i;
        i = i + 1;
    }
    return -1;
}

gint String::lastIndexOf(const String &str) const {
    return lastIndexOf(str, len);
}

gint String::lastIndexOf(const String &str, gint begin) const {
    if (begin >= len)
        begin = len - 1;
    for (gint i = begin; i >= 0 && i + 1 >= str.len;) {
        gint j;
        for (j = 0; j < str.len; j = nextIndex)
            if (getCP(value, i + j - str.len + 1) != getCP(str.value, j))
                break;
        if (j >= str.len)
            return i - str.len + 1;
        i = i - 1;
    }
    return -1;
}

gint String::count(const String &str) const {
    gint _count = 0;
    if (str.len > 0)
        for (gint i = 0; i < len && len - i >= str.len;) {
            gint j;
            for (j = 0; j < str.len; j = nextIndex)
                if (getCP(value, i + j) != getCP(str.value, j))
                    break;
            if (j >= str.len) {
                _count += 1;
                i += str.len;
            } else
                i = i + 1;
        }
    return _count;
}

gbool String::isBlank() const {
    for (gint i = 0; i < len; i = nextIndex)
        if (!Character::isSpace(getChar(value, i)))
            return false;
    return true;
}

gbool String::isUpperCase() const {
    gchar c;
    for (gint i = 0; i < len; i = nextIndex)
        if ((c = getCP(value, i)) != Character::toUpperCase(c))
            return false;
    return true;
}

gbool String::isLowerCase() const {
    gchar c;
    for (gint i = 0; i < len; i = nextIndex)
        if ((c = getCP(value, i)) != Character::toLowerCase(c))
            return false;
    return true;
}

gbool String::isTitleCase() const {
    gchar c;
    for (gint i = 0; i < len; i = nextIndex)
        if ((c = getCP(value, i)) != Character::toTitleCase(c))
            return false;
    return true;
}

Object &String::clone() const {
    try { return *new String(*this); } catch (...) { throw MemoryError(); }
}

gint countChars(gbyte const b[], gint length) {
    gint i;
    gint j = 0;
    for (i = 0; i < length;) {
        if (b[i] >= 0) {
            i += 1;
            j += 1;
        } else if (b[i] >> 5 == -2) {
            i += 2;
            j += 1;
        } else if (b[i] >> 4 == -2) {
            i += 3;
            j += 1;
        } else if (b[i] >> 3 == -2) {
            i += 4;
            j += 2;
        } else {
            // error: replacement action size
            i += 1;
            j += 1;
        }
    }
    return j;
}

gint decode_literal_string(gbyte const src[], gint srcLen, gbyte dst[], gint dstLen) {
    gint i;
    gint j = 0;
    for (i = 0; i < srcLen; j = nextIndex) {
        gbyte b1 = src[i];
        if (b1 >= 0) {
            put(dst, j, b1);
            i += 1;
        } else if (b1 >> 5 == -2) {
            if ((b1 & 0x1e) == 0) {
                put(dst, j, '?');
            } else {
                gbyte b2 = src[i + 1];
                if ((b2 & 0xc0) != 0x80)
                    put(dst, j, '?');
                else {
                    put(dst, j, (gchar) (((b1 << 6) ^ b2) ^ (((gbyte) 0xC0 << 6) ^ ((gbyte) 0x80 << 0))));
                }
            }
            i += 2;
        } else if (b1 >> 4 == -2) {
            gbyte b2 = src[i + 1];
            gbyte b3 = src[i + 2];
            if ((b1 == (gbyte) 0xe0 && (b2 & 0xe0) == 0x80) || (b2 & 0xc0) != 0x80 || (b3 & 0xc0) != 0x80) {
                put(dst, j, '?');
            } else {
                gchar c = (gchar) ((b1 << 12) ^ (b2 << 6) ^
                                   (b3 ^ (((gbyte) 0xE0 << 12) ^ ((gbyte) 0x80 << 6) ^ ((gbyte) 0x80 << 0))));
                if (!Character::isSurrogate(c)) {
                    put(dst, j, c);
                } else {
                    put(dst, j, '?');
                }
            }
            i += 3;
        } else if (b1 >> 3 == -2) {
            gbyte b2 = src[i + 1];
            gbyte b3 = src[i + 2];
            gbyte b4 = src[i + 3];
            gint cp = ((b1 << 18) ^ (b2 << 12) ^ (b3 << 6) ^ (b4 ^ (((gbyte) 0xF0 << 18) ^ ((gbyte) 0x80 << 12) ^
                                                                    ((gbyte) 0x80 << 6) ^ ((gbyte) 0x80 << 0))));
            if ((b2 & 0xc0) != 0x80 || (b3 & 0xc0) != 0x80 || (b4 & 0xc0) != 0x80 || !Character::isSupplementary(cp)) {
                put(dst, j, '?');
            } else {
                put(dst, j, cp);
            }
            i += 4;
        } else {
            put(dst, j, '?');
            i += 1;
        }
    }
    return j;
}

String::String(const gbyte b[], gint memorySize, gint memoryCharSize, gint codec) : value(), len() {
    if (!b)
        throw ValueError("Null pointer");
    len = memorySize / memoryCharSize;
    if (memoryCharSize == 2 || codec == 2) {
//         utf-16LE to utf-16BE
        value = allocate(len);
        gint i;
        gint j = 0;
        gchar const *chars = (gchar *) b;
        for (i = 0; i < len; ++i, j = nextIndex)
            put(value, j, chars[i]);
    } else if (memoryCharSize == 4 || codec == 4) {
//        utf-32LE to utf-16BE
        value = allocate(len * 2);
        gint i;
        gint j = 0;
        gint const *codepoints = (gint *) b;
        for (i = 0; i < len; ++i, j = nextIndex)
            put(value, j, codepoints[i]);
        len = i;
    } else if (memoryCharSize == 1 || codec == 1) {
//        utf-8 to utf-16BE
        len = countChars(b, memorySize);
        value = allocate(len);
        len = decode_literal_string(b, memorySize, value, len);
    }
}

String::~String() {
    len = 0;
    delete[] value;
    value = nullptr;
}

CharArray String::chars() const {
    CharArray array(len);
    for (gint i = 0; i < len; ++i)
        array.set(i, charAt(i));
    return array;
}

String::String(const CharArray &chars) : String(chars, 0) {}

String::String(const CharArray &chars, gint offset) : String() {
    if (offset < 0)
        throw ValueError("Negative array offset");
    if (offset > chars.length())
        offset = chars.length();
    len = chars.length() - offset;
    value = allocate(len);
    gint i = 0;
    gint j = 0;
    for (i = 0; i < len; ++i, j = nextIndex)
        put(value, j, chars[i]);
}

CharArray String::chars(gint begin, gint end) const {
    if (begin < 0)
        throw IndexError(begin);
    if (end < 0)
        throw IndexError(end);
    if (end < begin || begin >= len)
        return CharArray(0);
    if (end >= len)
        end = len - 1;
    end = end + 1;
    gint n = end - begin;
    CharArray array(n);
    for (gint i = 0; i < n; ++i)
        array.set(i, charAt(i + begin));
    return array;
}

String &String::operator+=(const String &str) {
    return *this = concat(str);
}

String operator+(const String &lhs, const String &rhs) {
    return lhs.concat(rhs);
}

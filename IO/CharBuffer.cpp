//
// Created by brunshweeck on 26/02/2023.
//

#include "CharBuffer.h"
#include "../MemoryError.h"
#include "../IndexError.h"
#include "../CodingError.h"

CharBuffer::CharBuffer(gint mark, gint position, gint limit, gint capacity, gchar buffer[], gint offset) :
        Buffer(mark, position, limit, capacity), _buffer(buffer), _offset(offset) {}

CharBuffer::CharBuffer(gint mark, gint position, gint limit, gint capacity) :
        Buffer(mark, position, limit, capacity), _offset(0) {
    try {
        _buffer = new gchar[capacity + 1];
        _buffer[capacity] = 0;
        for (gint i = 0; i < capacity; ++i)
            _buffer[i] = 0;
    } catch (...) {
        throw MemoryError();
    }
}

gchar CharBuffer::get() const {
    return _buffer[nextPosition() + _offset];
}

gchar CharBuffer::get(gint index) const {
    if (index >= limit() || index < 0)
        throw IndexError(index);
    return _buffer[index + _offset];
}

CharBuffer &CharBuffer::put(gchar b) {
    if (!isReadOnly())
        _buffer[nextPosition()] = b;
    else
        nextPosition();
    return *this;
}

gbool CharBuffer::isReadOnly() const {
    return _isReadOnly;
}

Buffer::BufferData CharBuffer::base() const {
    return _buffer;
}

gint CharBuffer::compareTo(const CharBuffer &obj) const {
    gint r1 = remaining();
    gint r2 = obj.remaining();
    gint r = r1 < r2 ? r1 : r2;
    for (int i = 0; i < r; ++i) {
        gint i1 = _buffer[i + position()] & 0xFFFF;
        gint i2 = obj._buffer[i + obj.position()] & 0xFFFF;
        if (i1 != i2)
            return i1 - i2;
    }
    return r1 == r2 ? 0 : r == r2 ? -1 : 1;
}

gbool CharBuffer::equals(const Object &obj) const {
    return 0;
}

Object &CharBuffer::clone() const {
    return *new CharBuffer(markValue(), position(), limit(), capacity(), _buffer, _offset);
}

CharBuffer::CharBuffer(gint capacity) : Buffer(capacity), _offset(0) {
    try {
        _buffer = new gchar[capacity + 1];
        _buffer[capacity] = 0;
        for (gint i = 0; i < capacity; ++i)
            _buffer[i] = 0;
    } catch (...) {
        throw MemoryError();
    }
}

CharBuffer &CharBuffer::put(CharBuffer &src) {
    if(isReadOnly())
        return *this;
    gint srcPos = src.position();
    gint srcLim = src.limit();
    gint srcRem = srcPos <= srcLim ? srcLim - srcPos : 0;
    gint dstPos = position();
    gint dstLim = limit();
    gint dstRem = dstPos < dstLim ? dstLim - dstPos : 0;
    if (srcRem > dstRem)
        throw CodingError::overflow();
    for (int i = srcPos, j = dstPos; i < srcRem; ++i, j++)
        _buffer[j] = src._buffer[i];
    position(dstPos + srcRem);
    src.position(srcPos + srcRem);
    return *this;
}

gint CharBuffer::offset() const {
    return _offset;
}

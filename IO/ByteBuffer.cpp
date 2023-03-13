//
// Created by brunshweeck on 26/02/2023.
//

#include "ByteBuffer.h"
#include "../MemoryError.h"
#include "../ValueError.h"
#include "../CodingError.h"
#include "../IndexError.h"
#include "../Byte.h"

ByteBuffer::ByteBuffer(gint mark, gint position, gint limit, gint capacity, gbyte buffer[], gint offset) :
        Buffer(mark, position, limit, capacity), _buffer(buffer), _offset(offset) {
    if (!_buffer)
        throw ValueError("base buffer is  null");
}

ByteBuffer::ByteBuffer(gint mark, gint position, gint limit, gint capacity) :
        Buffer(mark, position, limit, capacity), _buffer(), _offset(0) {
    try {
        _buffer = new gbyte[capacity + 1];
        _buffer[capacity] = 0;
        for (int i = 0; i < capacity; ++i)
            _buffer[i] = 0;
    } catch (...) {
        throw MemoryError();
    }
}

gbyte ByteBuffer::get() const {
    return _buffer[nextPosition() + _offset];
}

gbyte ByteBuffer::get(gint index) const {
    if (index >= limit() || index < 0)
        throw IndexError(index);
    return _buffer[index + _offset];
}

ByteBuffer &ByteBuffer::put(gbyte b) {
    if (!isReadOnly())
        _buffer[nextPosition()] = b;
    else
        nextPosition();
    return *this;
}

gbool ByteBuffer::isReadOnly() const {
    return _isReadOnly;
}

Buffer::BufferData ByteBuffer::base() const {
    return _buffer;
}

gint ByteBuffer::compareTo(const ByteBuffer &obj) const {
    gint r1 = remaining();
    gint r2 = obj.remaining();
    gint r = r1 < r2 ? r1 : r2;
    for (int i = 0; i < r; ++i) {
        gint i1 = _buffer[i + position()] & 0xFF;
        gint i2 = obj._buffer[i + obj.position()] & 0xFF;
        if (i1 != i2)
            return i1 - i2;
    }
    return r1 == r2 ? 0 : r == r2 ? -1 : 1;
}

gbool ByteBuffer::equals(const Object &obj) const {
    return 0;
}

Object &ByteBuffer::clone() const {
    return *new ByteBuffer(markValue(), position(), limit(), capacity(), _buffer, _offset);
}

void ByteBuffer::set(const Object &obj) {
    if (!dynamic_cast<ByteBuffer const *>(&obj)) {}
    ByteBuffer const &b = (const ByteBuffer &) obj;
    _buffer = b._buffer;
    _offset = b._offset;
}

ByteBuffer::ByteBuffer(gint capacity) : Buffer(capacity), _offset(0) {
    try {
        _buffer = new gbyte[capacity + 1];
        _buffer[capacity] = 0;
        for (gint i = 0; i < capacity; ++i)
            _buffer[i] = 0;
    } catch (...) {
        throw MemoryError();
    }
}

ByteBuffer &ByteBuffer::put(ByteBuffer &src) {
    if (isReadOnly())
        return *this;
    gint srcPos = src.position();
    gint dstPos = position();
    gint srcLim = src.limit();
    gint dstLim = limit();
    gint srcRem = srcPos < srcLim ? srcLim - srcPos : 0;
    gint dstRem = dstPos < dstLim ? dstLim - dstPos : 0;
    if (srcRem > dstRem)
        throw CodingError::overflow();
    for (gint i = srcPos, j = dstPos; i < srcLim; ++i, ++j)
        _buffer[j] = src._buffer[i];
    position(dstPos + srcRem);
    src.position(srcPos + srcRem);
    return *this;
}

gint ByteBuffer::offset() const {
    return _offset;
}

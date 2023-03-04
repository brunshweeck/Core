//
// Created by brunshweeck on 26/02/2023.
//

#include "Buffer.h"
#include "../Errors/ValueError.h"
#include "../Errors/OverflowError.h"

Buffer::Buffer(gint mark, gint position, gint limit, gint capacity) :
        _mark(mark),
        _position(position),
        _limit(limit),
        _capacity(capacity) {
    if (capacity < 0)
        throw ValueError("capacity < 0");
}

Buffer::Buffer(gint capacity) : Buffer(-1, 0, capacity, capacity) {}

gint Buffer::capacity() const {
    return _capacity;
}

gint Buffer::position() const {
    return _position;
}

Buffer &Buffer::position(gint newPos) {
    if (newPos < 0)
        throw ValueError("position is negative");
    if (newPos > _limit)
        throw ValueError("position overflow");
    if (_mark > newPos)
        _mark = -1;
    _position = newPos;
    return *this;
}

gint Buffer::limit() const {
    return _limit;
}

Buffer &Buffer::limit(gint newLimit) {
    if (newLimit < 0)
        throw ValueError("limit is negative");
    if (newLimit > _capacity)
        throw ValueError("limit overflow");
    if (_mark > newLimit)
        _mark = -1;
    _limit = newLimit;
    return *this;
}

Buffer &Buffer::mark() {
    _mark = _position;
    return *this;
}

Buffer &Buffer::reset() {
    if (_mark > 0)
        _position = _mark;
    return *this;
}

Buffer &Buffer::clear() {
    _position = 0;
    _limit = _capacity;
    _mark = -1;
    return *this;
}

Buffer &Buffer::flip() {
    _limit = _position;
    _position = 0;
    _mark = -1;
    return *this;
}

Buffer &Buffer::rewind() {
    _position = 0;
    _mark = -1;
    return *this;
}

gint Buffer::remaining() const {
    gint i = _limit - _position;
    return i < 0 ? 0 : i;
}

gbool Buffer::hasRemaining() const {
    return _position < _limit;
}

gint Buffer::nextPosition() const {
    gint &p = (gint &) _position;
    if (p >= _limit)
        throw OverflowError();
    (gint &) _position = p + 1;
    return p++;
}

gint Buffer::nextPosition(gint n) const {
    gint p = (gint &) _position;
    if (p >= _limit)
        throw OverflowError();
    (gint &) _position = p + n;
    return p;
}

gint Buffer::markValue() const {
    return _mark;
}

void Buffer::discardMark() {
    _mark = -1;
}


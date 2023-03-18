//
// Created by brunshweeck on 26/02/2023.
//

#ifndef CORE_BYTE_BUFFER_H
#define CORE_BYTE_BUFFER_H


#include "Buffer.h"
#include "../Comparable.h"

class ByteBuffer : public Buffer, public Comparable<ByteBuffer> {
public:
    /**
     * Creates a new buffer with the given mark, position, limit, capacity, backing array, and array offset
     */
    CORE_EXPLICIT ByteBuffer(gint mark, gint position, gint limit, gint capacity, gbyte buffer[], gint offset);

    /**
     * Creates a new buffer with the given mark, position, limit, and capacity
     */
    CORE_EXPLICIT ByteBuffer(gint mark, gint position, gint limit, gint capacity);

    CORE_EXPLICIT ByteBuffer(gint capacity);

    /**
     * Reads the byte at this buffer's
     * current position, and then increments the position.
     */
    virtual gbyte get() const;

    /**
     * Absolute get method.  Reads the byte at the given
     * index.
     * \param index The index from which the byte will be read
     */
    virtual gbyte get(gint index) const;

    /**
     * Writes the given byte into this buffer at the current
     * position, and then increments the position.
     */
    virtual ByteBuffer& put(gbyte b);

    /**
     *  This method transfers the bytes remaining in the given source
     * buffer into this buffer.  If there are more bytes remaining in the
     * source buffer than in this buffer, that is, if src.remaining() < this.remaining(),
     * then no bytes are transferred and a OverflowError is thrown.
     * This method has not effect if this buffer is read-only
     * \param src The source buffer from which chars are to be read; must not be this buffer
     */
    virtual ByteBuffer& put(ByteBuffer& src);

    gbool isReadOnly() const override;

    BufferData base() const override;

    gint compareTo(const ByteBuffer &obj) const override;

    gbool equals(const Object &obj) const override;

    Object &clone() const override;

    gint offset() const override;

private:
    Class<gbyte>::Pointer _buffer;
    gint _offset;
    gbool _isReadOnly = false;
};


#endif //CORE_BYTE_BUFFER_H

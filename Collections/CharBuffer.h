//
// Created by brunshweeck on 26/02/2023.
//

#ifndef CORE_CHAR_BUFFER_H
#define CORE_CHAR_BUFFER_H


#include "Buffer.h"
#include "../Comparable.h"

class CharBuffer : public Buffer, public Comparable<CharBuffer> {
public:
    /**
     * Creates a new buffer with the given mark, position, limit, capacity, backing array, and array offset
     */
    CORE_EXPLICIT CharBuffer(gint mark, gint position, gint limit, gint capacity, gchar buffer[], gint offset);

    /**
     * Creates a new buffer with the given mark, position, limit, and capacity
     */
    CORE_EXPLICIT CharBuffer(gint mark, gint position, gint limit, gint capacity);

    CORE_EXPLICIT CharBuffer(gint capacity);

    /**
     * Reads the char at this buffer's
     * current position, and then increments the position.
     */
    virtual gchar get() const;

    /**
     * Absolute get method.  Reads the byte at the given
     * index.
     * \param index The index from which the byte will be read
     */
    virtual gchar get(gint index) const;

    /**
     * Writes the given char into this buffer at the current
     * position, and then increments the position.
     */
    virtual CharBuffer &put(gchar c);

    /**
     * This method transfers the chars remaining in the given source
     * buffer into this buffer.  If there are more chars remaining in the
     * source buffer than in this buffer, that is, if src.remaining() > this.remaining()
     * then no chars are transferred and a OverflowError is thrown.
     *  This method has not effect if this buffer is read-only
     * \param src The source buffer from which chars are to be read; must not be this buffer
     */
    virtual CharBuffer &put(CharBuffer const &src);

    gbool isReadOnly() const override;

    BufferData base() const override;

    gint compareTo(const CharBuffer &obj) const override;

    gbool equals(const Object &obj) const override;

    Object &clone() const override;

    gint offset() const override;

protected:
    void set(const Object &obj) override;

private:
    Class<gchar>::Pointer _buffer;
    gint _offset;
    gbool _isReadOnly = false;
};


#endif //CORE_CHAR_BUFFER_H

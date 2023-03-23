//
// Created by brunshweeck on 26/02/2023.
//

#ifndef CORE_BUFFER_H
#define CORE_BUFFER_H


#include "../String.h"

class Buffer : public Object {
protected:
    using BufferData = Class<void>::Pointer;

public:
    /**
     * Creates a new buffer with given capacity.
     */
    CORE_EXPLICIT Buffer(gint capacity);

    /**
     * Construct new Buffer with the given mark, position, limit, and capacity,
     */
    CORE_EXPLICIT Buffer(gint mark, gint position, gint limit, gint capacity);

    /**
     * Returns this buffer's capacity.
     */
    virtual gint capacity() const;

    /**
     * Returns this buffer's position.
     */
    virtual gint position() const;

    /**
     * Sets this buffer's position.  If the mark is defined and larger than the
     * new position then it is discarded.
     * \param newPos The new position value; must be non-negative and no larger than the current limit
     */
    virtual Buffer &position(gint newPosition);

    /**
     * Returns this buffer's limit.
     */
    virtual gint limit() const;

    /**
     * Sets this buffer's limit.  If the position is larger than the new limit
     * then it is set to the new limit.  If the mark is defined and larger than
     * the new limit then it is discarded.
     * \param newLimit The new limit value; must be non-negative and no larger than this buffer's capacity
     */
    virtual Buffer &limit(gint newLimit);

    /**
     * Sets this buffer's mark at its position.
     */
    virtual Buffer &mark();

    /**
     * Resets this buffer's position to the previously-marked position.
     * Is done if mark is set (mark >= 0)
     */
    virtual Buffer &reset();

    /**
     * Clears this buffer.  The position is set to zero, the limit is set to
     * the capacity, and the mark is discarded.
     */
    virtual Buffer &clear();

    /**
     * Flips this buffer.  The limit is set to the current position and then
     * the position is set to zero.  If the mark is defined then it is
     * discarded.
     */
    virtual Buffer &flip();

    /**
     * Rewinds this buffer.  The position is set to zero and the mark is
     * discarded.
     */
    virtual Buffer &rewind();

    /**
     * Returns the number of elements between the current position and the
     * limit.
     */
    virtual gint remaining() const;

    /**
     * Tells whether there are any elements between the current position and
     * the limit.
     */
    virtual gbool hasRemaining() const;

    /**
     * Tells whether or not this buffer is read-only.
     */
    virtual gbool isReadOnly() const = 0;

    /**
     * Return data of buffer
     */
    virtual BufferData base() const = 0;

    virtual gint offset() const = 0;

protected:
    /**
     * Checks the current position against the limit, throwing a OverflowError
     * if it is not smaller than the limit, and then increments the position.
     */
    virtual gint nextPosition() const;

    /**
     * Checks the current position against the limit, throwing a OverflowError
     * if it is not smaller than the limit, and then increments the position
     * of specified offset 'n'.
     */
    virtual gint nextPosition(gint n) const;

    virtual gint markValue() const;

    virtual void discardMark();

private:
    /**
     * Condition: mark <= position <= limit <= capacity
     */
    gint _mark = -1;
    gint _position = 0;
    gint _limit;
    gint _capacity;
};


#endif //CORE_BUFFER_H

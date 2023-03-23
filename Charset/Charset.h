//
// Created by brunshweeck on 25/02/2023.
//

#ifndef CORE_CHARSET_H
#define CORE_CHARSET_H

#include "../Object.h"
#include "../Comparable.h"
#include "../IO/ByteBuffer.h"
#include "../IO/CharBuffer.h"
#include "../CodingError.h"

class Charset : public Object, public Comparable<Charset> {
protected:
    /**
     * Replacement used by decode method. must End With byte 0x00
     * By default is '?'
     */
    gbyte REPLACEMENT_BYTES[8];

    /**
     * Replacement used by encode method. End With null character ('\u0000')
     * By default is "\ufffd"
     */
    gchar REPLACEMENT_CHARS[4];

    static gint CODING_ERROR_LENGTH;

public:
    /**
     * Initializes a new charset
     */
    Charset() {
        // default replacement used by encoder '?'
        REPLACEMENT_BYTES[0] = 0x3f;
        REPLACEMENT_BYTES[1] =
        REPLACEMENT_BYTES[2] =
        REPLACEMENT_BYTES[3] =
        REPLACEMENT_BYTES[5] =
        REPLACEMENT_BYTES[6] =
        REPLACEMENT_BYTES[7] = 0x00;

        // default replacement used by decoder '\ufffd'
        REPLACEMENT_CHARS[0] = 0xfffd;
        REPLACEMENT_CHARS[1] =
        REPLACEMENT_CHARS[2] =
        REPLACEMENT_CHARS[3] = 0x0000;
    }

    /**
     * Returns this charset's canonical name.
     */
    virtual String name() const = 0;

    /**
     * A description of the result state of a coder.
     */
    enum class CoderResult : gbyte {
        /**
         * Result object indicating underflow, meaning that either the input buffer
         * has been completely consumed or, if the input buffer is not yet empty,
         * that additional input is required.
         */
        UNDERFLOW,

        /**
         * Result object indicating overflow, meaning that there is insufficient
         * room in the output buffer.
         */
        OVERFLOW,
        MALFORMED,
        UNMAPPABLE,
    };

    enum class ErrorAction {
        IGNORE,
        REPORT,
        REPLACE
    };

    /**
     *  Return action  that must be does after malformed coder error
     */
    virtual ErrorAction malformedAction() const;

    /**
     * Return action  that must be does after unmappable coder error
     */
    virtual ErrorAction unmappableAction() const;

    /**
     * Decodes one or more bytes into one or more characters.
     * \param in The input byte buffer
     * \param out The output character buffer
     */
    virtual CoderResult decodeLoop(ByteBuffer &src, CharBuffer &dst) = 0;

    /**
     * Encodes one or more characters into one or more bytes.
     * \param in The input character buffer
     * \param out The output byte buffer
     */
    virtual CoderResult encodeLoop(CharBuffer &src, ByteBuffer &dst) = 0;

    /**
     * Number character per byte
     */
    virtual gfloat averageCharsPerByte() const = 0;

    /**
     * Number of character per byte
     */
    virtual gfloat averageBytesPerChar() const = 0;

    /**
     * Convenience method that decodes the remaining content of a single input
     * byte buffer into a newly-allocated character buffer.
     * \param in The input byte buffer
     */
    CharBuffer decode(ByteBuffer &in);

    /**
     * Convenience method that encodes the remaining content of a single input
     * character buffer into a newly-allocated byte buffer.
     * \param in The input character buffer
     */
    ByteBuffer encode(CharBuffer &in);

    /**
     * Return string representation of this object
     */
    String toString() const override;

    /**
     * Compares this charset to another.
     * \param obj The charset to which this charset is to be compared
     */
    gint compareTo(const Charset &obj) const override;

    /**
     * Tells whether or not this object is equal to another.
     * Two charsets are equal if, and only if, they have the same canonical
     * names.  A charset is never equal to any other type of object.
     * \param obj
     */
    gbool equals(const Object &obj) const override;

    /**
     * Tells whether or not this charset contains the given charset.
     * A charset C is said to contain a charset D if,
     * and only if, every character representable in D is also
     * representable in C.  If this relationship holds then it is
     * guaranteed that every string that can be encoded in D can also be
     * encoded in C without performing any replacements.
     *
     * That C contains D does not imply that each character
     * representable in C by a particular byte sequence is represented
     * in D by the same byte sequence, although sometimes this is the
     * case.
     *
     * <p> Every charset contains itself.
     * \param cs The given charset
     */
    virtual gbool contains(Charset const &cs) const = 0;

    virtual gbool canEncode(gchar c) const;

    virtual Charset &onMalformed(ErrorAction action);

    virtual Charset &onUnmapped(ErrorAction action);

private:
    CoderResult encode(CharBuffer &in, ByteBuffer &out, bool endOfInput);

    CoderResult decode(ByteBuffer &in, CharBuffer &out, gbool endOfInput);
//ERROR LENGTH
};


#endif //CORE_CHARSET_H

//
// Created by brunshweeck on 27/02/2023.
//

#ifndef CORE_UTF16_H
#define CORE_UTF16_H


#include "Unicode.h"

class UTF16 final : public Unicode {
public:
    CORE_FAST static gchar UTF16BE_BOM = (gchar) 0xfeff;
    CORE_FAST static gchar UTF16LE_BOM = (gchar) 0xfffe;
    /**
     * Construct new instance of utf16 charset
     */
    CORE_EXPLICIT UTF16(Endian byteOrder = NONE);

    /**
     *  Construct new instance of utf16 charset
     */
    CORE_EXPLICIT UTF16(Endian byteOrder, gbool withBOM);

    /**
     * Return endianness
     */
    virtual Endian byteOrder() const;

    /**
     *  Return current endianness
     */
    virtual Endian currentByteOrder() const;

    /**
     * Tell if this charset need mark
     */
    virtual gbool needsMark() const;

    /**
     * Return canonical name
     */
    String name() const override;

    /**
     *  Return number of characters per byte
     */
    gfloat averageCharsPerByte() const override;

    /**
     *  Return number of bytes per character
     */
    gfloat averageBytesPerChar() const override;

    CoderResult decodeLoop(ByteBuffer &in, CharBuffer &out) override;

    CoderResult encodeLoop(CharBuffer &in, ByteBuffer &dst) override;

    CharBuffer decode(ByteBuffer &in) override;

    ByteBuffer encode(CharBuffer &in) override;

    void reset();

    /**
     * Return copy of this instance
     */
    Object &clone() const override;

private:
    gchar decode(int b1, int b2) const;
    void put(gchar c, ByteBuffer dst);

    Endian _byteOrder;
    Endian _current;
    gbool _withBOM;

public:
    static UTF16 INSTANCE;
    static UTF16 BIG_INSTANCE;
    static UTF16 BIG_BOM_INSTANCE;
    static UTF16 LITTLE_INSTANCE;
    static UTF16 LITTLE_BOM_INSTANCE;
};


#endif //CORE_UTF16_H

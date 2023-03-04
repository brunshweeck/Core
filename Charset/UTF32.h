//
// Created by brunshweeck on 28/02/2023.
//

#ifndef CORE_UTF32_H
#define CORE_UTF32_H


#include "Unicode.h"

class UTF32 final : public Unicode {
public:
    CORE_FAST static gint UTF32BE_BOM = (gint) 0x0000feff;
    CORE_FAST static gint UTF32LE_BOM = (gint) 0xfffe0000;
    /**
     * Construct new instance of utf16 charset
     */
    CORE_EXPLICIT UTF32(Endian byteOrder = NONE);

    /**
     *  Construct new instance of utf16 charset
     */
    CORE_EXPLICIT UTF32(Endian byteOrder, gbool withBOM);

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

    CoderResult decodeLoop(ByteBuffer &src, CharBuffer &dst) override;

    CoderResult encodeLoop(CharBuffer &src, ByteBuffer &dst) override;

    void reset();

    CharBuffer decode(ByteBuffer &in) override;

    ByteBuffer encode(CharBuffer &in) override;

    /**
     * Return copy of this instance
     */
    Object &clone() const override;

private:
    gint get(ByteBuffer &src);

    void put(gint cp, ByteBuffer &dst);

    Endian _byteOrder;
    Endian _current;
    gbool _withBOM;

public:
    static UTF32 INSTANCE;
    static UTF32 BIG_INSTANCE;
    static UTF32 BIG_BOM_INSTANCE;
    static UTF32 LITTLE_INSTANCE;
    static UTF32 LITTLE_BOM_INSTANCE;
};


#endif //CORE_UTF32_H

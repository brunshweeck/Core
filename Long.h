//
// Created by brunshweeck on 2023/02/19.
//

#ifndef CORE_LONG_H
#define CORE_LONG_H


#include "Number.h"
#include "Comparable.h"
#include "Hashable.h"

/**
 * Long class represent all integer number representing with 64 bits
 */
class Long final : public Number, public Comparable<Long>, public Hashable {
public:
    /**
     * Construct new Long instance
     */
    CORE_IMPLICIT Long();

    /**
     * Construct new Long instance and initialize with glong value
     * \param v 64-bits signed integer
     */
    CORE_IMPLICIT Long(glong v);

    /**
     * Return value of this instance as int after narrowing conversion
     */
    gint intValue() const override;

    /**
     * Return value of this instance as long
     */
    glong longValue() const override;

    /**
     * Return value of this instance as float after widening conversion
     */
    gfloat floatValue() const override;

    /**
     * Return value of this instance as double after widening conversion
     */
    gdouble doubleValue() const override;

    /**
     * Compares this instance with specified object
     * \param obj object to be comparing
     */
    gbool equals(const Object &obj) const override;

    /**
     * Compares this instance with literal number
     * \param v literal number
     */
    template<class T,
            Class<gbool>::Require<!Class<T>::isNumber()> = true,
            class S = typename Class<T>::NIVR,
            class U = typename Class<S>::Object>
    gbool equals(T &&v) const {
        return equals(U((T &&) v));
    }

    /**
     * Compares this long instance with another numerically
     * \param i value to be comparing
     */
    gint compareTo(Long const &i) const;

    /**
     * Return value of this instance as long
     */
    operator glong() const;

    /**
     * Return value of this instance as long
     */
    operator glong &();

    /**
     * Return copy of this instance
     */
    Object &clone() const override;

    String toString() const override;

    static String toString(glong i);

    static String toString(glong i, gint base);

    static String toUnsignedString(glong i);

    static String toUnsignedString(glong i, gint base);

    static String toHexString(glong i);

    static String toOctalString(glong i);

    static String toBinaryString(glong i);

    static glong parseLong(String const& str);

    static glong parseLong(String const& str, gint base);

    static glong parseUnsignedLong(String const& str);

    static glong parseUnsignedLong(String const& str, gint base);

    static Long valueOf(String const& str);

    static Long valueOf(String const& str, gint base);

    /**
     * Decodes a String into a Long.
     * Accepts decimal, hexadecimal, octal and binary numbers given by the following grammar.
     * \details
     * [Sign]    DecimalDigits.
     * [Sign] 0x HexDigits.
     * [Sign] 0X HexDigits.
     * [Sign] 0b BinaryDigits.
     * [Sign] 0B BinaryDigits.
     * [Sign] 0  OctalDigits.
     * \example
     *      "0x7f" -> 127.
     *      "0177" -> 127.
     *      "0b1111111" -> 127.
     *      "0b01111111" -> 127.
     *      "127" -> 127.
     * \throw ValueError if specified string not respect grammar or value represented out of range [MIN;MAX]
     */
    static Long decode(String const& str);

protected:
    /**
     * Set long value
     * \param obj long instance
     * \throw CastError if specified object is not Long instance
     */
    void set(const Object &obj) override {
        Long const *l = dynamic_cast<Long const *>(&obj);
        if (!l) {}
        value = l->value;
    }

public:

    /**
     * Compares two literal 64 bits signed integers numerically
     * \param x the first operand
     * \param y the second operand
     */
    static gint compare(glong x, glong y);

    /**
     * Return new instance representing by specified literal value
     */
    static Long valueOf(glong i);

    /**
     * A constant holding the maximum value a long can have, 2^63-1.
     */
    CORE_FAST static glong MAX = 0b0111111111111111111111111111111111111111111111111111111111111111;

    /**
     * A constant holding the minimum value a long can have, -2^63.
     */
    CORE_FAST static glong MIN = 0b1000000000000000000000000000000000000000000000000000000000000000;

    /**
     * Returns the number of one-bits in the two's complement binary
     * representation of the specified long value.
     */
    static gint bitCount(glong i);

    /**
     * Compares two long values numerically treating the values as unsigned.
     */
    static gint compareUnsigned(glong x, glong y);

    /**
     * Returns the value obtained by compressing the bits of the specified
     * long value, i, in accordance with the specified bit mask.
     */
    static glong compressBits(glong i, glong mask);

    /**
     * Returns the value obtained by expanding the bits of the specified
     * long value, i, in accordance with the specified bit mask.
     */
    static glong expandBits(glong i, glong mask);

    /**
     * Returns the value obtained by reversing the order of the bits in the
     * two's complement binary representation of the specified long value.
     */
    static glong reverseBits(glong i);

    /**
     * Returns the value obtained by reversing the order of the bytes in the
     * two's complement representation of the specified long value.
     */
    static glong reverseBytes(glong i);

    /**
     * Returns the value obtained by rotating the two's complement binary
     * representation of the specified long value left by the specified number of bits.
     */
    static glong rotateLeft(glong i, gint distance);

    /**
     * Returns the value obtained by rotating the two's complement binary
     * representation of the specified long value right by the specified number of bits.
     */
    static glong rotateRight(glong i, gint distance);

    /**
     * Returns the value obtained by shift the two's complement binary
     * representation of the specified long value left by the specified number of bits.
     */
    static glong shiftLeft(glong i, gint distance);

    /**
     * Returns the value obtained by shift the two's complement binary
     * representation of the specified long value right by the specified number of bits.
     */
    static glong shiftRight(glong i, gint distance);

    /**
     * Returns the signum function of the specified long value.
     */
    static gint signum(glong i);

    /**
     * Returns the number of zero bits preceding the highest-order ("leftmost")
     * one-bit in the two's complement binary representation of the specified long value.
     */
    static gint leadingZeros(glong i);

    /**
     * Returns the number of zero bits following the lowest-order ("rightmost")
     * one-bit in the two's complement binary representation of the specified long value.
     */
    static gint trailingZeros(glong i);


    glong hash() const override;

    static glong hash(glong i);

private:
    glong value;
};


#endif //CORE_LONG_H

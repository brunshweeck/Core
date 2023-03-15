//
// Created by brunshweeck on 2023/02/19.
//

#ifndef CORE_INTEGER_H
#define CORE_INTEGER_H


#include "Number.h"
#include "Comparable.h"
#include "Hashable.h"

/**
 * The Integer class wraps a value of the primitive type int in an object.
 * An object of type Integer contains a single field whose type is int.
 * In addition, this class provides several methods for converting an int
 * to a String and a String to an int, as well as other constants and methods
 * useful when dealing with an int.
 */
class Integer final : public Number, public Comparable<Integer>, public Hashable {
public:
    /**
     * Construct new Integer instance
     */
    CORE_IMPLICIT Integer();

    /**
     * Construct new Integer instance and initialize with gint value
     * \param v 32 bits signed integer
     */
    CORE_IMPLICIT Integer(gint v);

    /**
     * Return value of this instance as int
     */
    gint intValue() const override;

    /**
     * Return value of this instance as long after widening conversion
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
            Class<gbool>::Require<Class<T>::isNumber()> = true,
            class S = typename Class<T>::NIVR, class U = typename Class<S>::Object>
    gbool equals(T &&v) const {
        return equals(U((T &&) v));
    }

    /**
     * Compares this instance with another numerically
     * \param i value to be comparing
     */
    gint compareTo(Integer const &i) const override;

    /**
     * Return value of this instance as long
     */
    operator gint() const;

    /**
     * Return value of this instance as int
     */
    operator gint &();

    /**
     * Return copy of this instance
     */
    Object &clone() const override;

    String toString() const override;

    static String toString(gint i);

    static String toString(gint i, gint base);

    static String toUnsignedString(gint i);

    static String toUnsignedString(gint i, gint base);

    static String toHexString(gint i);

    static String toOctalString(gint i);

    static String toBinaryString(gint i);

    static gint parseInt(String const& str);

    static gint parseInt(String const& str, gint base);

    static gint parseUnsignedInt(String const& str);

    static gint parseUnsignedInt(String const& str, gint base);

    static Integer valueOf(String const& str);

    static Integer valueOf(String const& str, gint base);

    /**
     * Decodes a String into a Integer.
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
    static Integer decode(String const& str);

protected:
    /**
     * Set Integer value
     * \param obj integer instance
     * \throw CastError if specified object is not Long instance
     */
    void set(const Object &obj) override;

public:

    /**
     * Compares value numerically
     * \param x the first operand
     * \param y the second operand
     */
    static gint compare(gint x, gint y);

    /**
     * Return new instance representing by specified literal value
     */
    static Integer valueOf(gint i);

    /**
     * Converts the argument to a long by an unsigned conversion.
     * \param i the value to convert to an unsigned long
     */
    static i64 toUnsignedLong(gint i);

    /**
     * Returns the value obtained by reversing the order of the bits
     * in the two's complement binary representation of the specified int value.
     */
    static gint reverseBits(gint i);

    /**
     * Returns the value obtained by reversing the order of the bytes
     * in the two's complement representation of the specified int value.
     */
    static gint reverseBytes(gint i);

    /**
     * Returns the number of zero bits preceding the highest-order ("leftmost")
     * one-bit in the two's complement binary representation of the specified int value.
     */
    static gint leadingZeros(gint i);

    /**
     * Returns the number of zero bits following the lowest-order ("rightmost")
     * one-bit in the two's complement binary representation of the specified int value.
     */
    static gint trailingZeros(gint i);

    /**
     * Returns the number of one-bits in the two's complement binary representation
     * of the specified int value.
     */
    static gint bitCount(gint i);

    /**
     * Returns the signum function of the specified int value.
     */
    static gint signum(gint i);

    /**
     * Returns the value obtained by rotating the two's complement
     * binary representation of the specified int value left by the
     * specified number of bits.
     */
    static gint rotateLeft(gint i, gint distance);

    /**
     * Returns the value obtained by rotating the two's complement
     * binary representation of the specified int value right by the
     * specified number of bits.
     */
    static gint rotateRight(gint i, gint distance);

    /**
     * Returns the value obtained by shift the two's complement
     * binary representation of the specified int value left by the
     * specified number of bits.
     */
    static gint shiftLeft(gint i, gint distance);

    /**
     * Returns the value obtained by shift the two's complement
     * binary representation of the specified int value right by the
     * specified number of bits.
     */
    static gint shiftRight(gint i, gint distance);

    /**
     * Returns the value obtained by compressing the bits of the specified
     * int value, i, in accordance with the specified bit mask.
     */
    static gint compressBits(gint i, gint mask);

    /**
     * Returns the value obtained by expanding the bits of the specified
     * int value, i, in accordance with the specified bit mask.
     */
    static gint expandBits(gint i, gint mask);

    /**
     * A constant holding the maximum value an int can have, 2^31-1.
     */
    CORE_FAST static gint MAX = 0b01111111111111111111111111111111;

    /**
     * A constant holding the minimum value an int can have, -2^31.
     */
    CORE_FAST static gint MIN = (gint) 0b10000000000000000000000000000000;

    glong hash() const override;

    static glong hash(gint i);

private:
    gint value;
};


#endif //CORE_INTEGER_H

//
// Created by brunshweeck on 2023/02/19.
//

#ifndef CORE_SHORT_H
#define CORE_SHORT_H


#include "Number.h"
#include "Comparable.h"
#include "Hashable.h"

/**
 * The Short class wraps a value of primitive type short in an object.
 * An object of type Short contains a single field whose type is short.
 * In addition, this class provides several methods for converting a short
 * to a String and a String to a short, as well as other constants and methods
 * useful when dealing with a short.
 */
class Short final : public Number, public Comparable<Short>, public Hashable {
public:
    /**
     * Construct new instance of Short
     */
    CORE_IMPLICIT Short();

    /**
     * Construct new instance of Short and Initialize
     * \param v 16 bits signed integer
     */
    CORE_IMPLICIT Short(gshort v);

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
    gint compareTo(Short const &i) const;

    /**
     * Compares two literal 64 bits signed integers numerically
     * \param x left value to be comparing
     * \param y right value to be comparing
     */
    static gint compare(gshort x, gshort y);

    /**
     * Return new instance representing by specified literal value
     */
    static Short valueOf(gshort i);

    /**
     * Return value of this instance as long
     */
    operator gshort() const;

    /**
     * Return value of this instance as long
     */
    operator gshort &();

    /**
     * Return copy of this instance
     */
    Object &clone() const override;

    /**
     * A constant holding the maximum value a short can have, 2^15-1.
     */
    CORE_FAST static gshort MAX = 0b0111111111111111;

    /**
     * A constant holding the minimum value a short can have, -2^15.
     */
    CORE_FAST static gshort MIN = (gshort) 0b1000000000000000;

    /**
     * Converts the argument to an int by an unsigned conversion.
     */
    static gint toUnsignedInt(gshort i);

    /**
     * Converts the argument to an long by an unsigned conversion.
     */
    static glong toUnsignedLong(gshort i);

    /**
     * Returns the value obtained by reversing the order of the bytes in the
     * two's complement representation of the specified short value.
     */
    static gshort reverseBytes(gshort i);

    String toString() const override;

    static String toString(gshort i);

    static String toString(gshort i, gint base);

    static String toUnsignedString(gshort i);

    static String toUnsignedString(gshort i, gint base);

    void set(const Object &obj) override;

    static glong hash(gshort i);

    static gshort parseShort(String const& str);

    static gshort parseShort(String const& str, gint base);

    static Short valueOf(String const& str);

    static Short valueOf(String const& str, gint base);

    /**
     * Decodes a String into a Short.
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
    static Short decode(String const& str);

private:
    glong hash() const override;

protected:


private:
    gshort value;

};


#endif //CORE_SHORT_H

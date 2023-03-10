//
// Created by brunshweeck on 2023/02/19.
//

#ifndef CORE_FLOAT_H
#define CORE_FLOAT_H


#include "Number.h"
#include "Hashable.h"

/**
 * The Float class wraps a value of primitive type float in an object.
 * An object of type Float contains a single field whose type is float.
 * In addition, this class provides several methods for converting a float
 * to a String and a String to a float, as well as other constants and methods
 * useful when dealing with a float.
 */
class Float final : public Number, public Comparable<Float>, public Hashable {
public:
    /**
     * Construct new instance of Float
     */
    CORE_IMPLICIT Float();

    /**
     * Construct new instance of Float and initialize
     * \param v 32 bits literal floating value
     */
    CORE_IMPLICIT Float(f32 v);

    /**
     * Return value of this instance as int after narrowing
     */
    gint intValue() const override;

    /**
     * Return value of this instance as long after narrowing conversion
     */
    glong longValue() const override;

    /**
     * Return value of this instance as float
     */
    gfloat floatValue() const override;

    /**
     * Return value of this instance as double after widening conversion
     */
    gdouble doubleValue() const override;

    /**
     * Return true if and only if value of this instance is infinitely large magnetude
     */
    gbool isInfinite() const;

    /**
     * Return true if and only if value of this instance is finite value
     */
    gbool isFinite() const;

    /**
     * Return true if and only if value of this instance is not a number
     */
    gbool isNaN() const;

    /**
     * Return true if specified 32 bits float is infinitely magnetude
     * \param v 32 bits floating number
     */
    static gbool isInfinite(f32 v);

    /**
     * Return true if specified 32 bits float is finite value
     * \param v 32 bits floating number
     */
    static gbool isFinite(f32 v);

    /**
     * Return true if specified 32 bits float is not a number
     * \param v 32 bits floating number
     */
    static gbool isNaN(f32 v);

    /**
     * Return 32 bits IEEE 754 'single format' representation of specified floating number
     * \param v decimal floating form
     * \return binary IEEE 754 'single format' (SIGN(1 bit) + EXPONENT(8 bits) + MANTISSA(23 bits))
     * \example +INF = 0 11111111 00000000000000000000000 = 0x7f800000
     * \example -INF = 1 11111111 00000000000000000000000 = 0xff800000
     * \example  NAN = 0 11111111 10000000000000000000000 = 0x7fc00000
     * \example +0.0 = 0 00000000 00000000000000000000000 = 0x00000000
     * \example -0.0 = 1 00000000 00000000000000000000000 = 0x80000000
     */
    static i32 toIntBits(f32 v);

    /**
     * Return 32 bits floating value represented by specified IEEE 754 'single format'
     * \param v binary IEEE 754 'single format' (SIGN(1 bit) + EXPONENT(8 bits) + MANTISSA(23 bits))
     * \return decimal 32 bits floating number
     * \example 0x7f800000 = 0 11111111 00000000000000000000000 = +INF
     * \example 0xff800000 = 1 11111111 00000000000000000000000 = -INF
     * \example 0x7fc00000 - 0x7fffffff = 0 11111111 10000000000000000000000 - 0 11111111 11111111111111111111111 = NaN
     * \example 0xffc00000 - 0xffffffff = 1 11111111 10000000000000000000000 - 1 11111111 11111111111111111111111 = NaN
     * \example 0x00000000 = 0 00000000 00000000000000000000000 = +0.0
     * \example 0x80000000 = 1 00000000 00000000000000000000000 = -0.0
     */
    static f32 fromIntBits(i32 v);

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
            class S = Class<T>::NIVR,
            class U = Class<S>::Object>
    gbool equals(T &&v) const {
        return equals(U((T &&) v));
    }

    /**
     * Compares this long instance with another numerically
     * \param i value to be comparing
     */
    gint compareTo(Float const &i) const override;

    /**
     * Return value of this instance as long
     */
    operator gfloat() const;

    /**
     * Return value of this instance as float
     */
    operator gfloat &();

    /**
     * Compares two float values numerically
     * \param x the first operand
     * \param y the second operand
     */
    static gint compare(f32 x, f32 y);

    /**
     * Return new instance representing by specified literal value
     */
    static Float valueOf(f32 f);

    /**
     * Return copy of this instance
     */
    Object &clone() const override;

    /**
     * Constant representing the max floating value represented in 32 bits
     */
    CORE_FAST static f32 MAX = 0x1.fffffeP127f;

    /**
     * Constant representing the min floating value represented in 32 bits
     */
    CORE_FAST static f32 MIN = 0x0.000002P-126f;

    /**
     * Constant representing the min normal floating value represented in 32 bits
     */
    CORE_FAST static f32 MIN_NORMAL = 0x1.0P-126f;

    /**
     * Constant representing the binary exponent bias.
     * 2^(8-1)-1 = 127
     */
    CORE_FAST static gint BIAS = 0b01111111;

    /**
     * Constant representing infinitely large magnetude represented in 32 bits
     */
    static f32 const INF;

    /**
     * Constant representing Not a Number
     */
    static f32 const NAN;

    String toString() const;

    static String toString(gfloat f);

    static String toHexString(gfloat f);

    glong hash() const override;

    static glong hash(gfloat f);

    static gfloat parseFloat(String const& str);

    static Float valueOf(String const& str);

protected:
    void set(const Object &obj) override;

private:
    f32 value;

    static gfloat _x10(gfloat result, gint pow);

    static gint signum(gfloat f);
};


#endif //CORE_FLOAT_H

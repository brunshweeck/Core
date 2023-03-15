//
// Created by brunshweeck on 2023/02/19.
//

#ifndef CORE_DOUBLE_H
#define CORE_DOUBLE_H


#include "Number.h"
#include "Hashable.h"

/**
 * The Double class wraps a value of the primitive type double (gdouble) in an object.
 * An object of type Double contains a single field whose type is double.
 * In addition, this class provides several methods for converting a double
 * to a String and a String to a double, as well as other constants and methods
 * useful when dealing with a double.
 * (-1)^s x 1.M x 2^(e-1023) if e != 0
 * (-1)^s x 0.M x 2^-1022 if e == 0
 */
class Double final: public Number, public Comparable<Double>, public Hashable {
public:
    /**
     * Construct new instance of Double
     */
    CORE_IMPLICIT Double();

    /**
     * Construct new instance of Double and initialize with gdouble
     * \param v 64 bits floating number
     */
    CORE_IMPLICIT Double(gdouble v);

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
     * Return true if specified 64 bits float is infinitely magnetude
     * \param v 64 bits floating number
     */
    static gbool isInfinite(gdouble v);

    /**
     * Return true if specified 64 bits float is finite value
     * \param v 64 bits floating number
     */
    static gbool isFinite(gdouble v);

    /**
     * Return true if specified 64 bits float is not a number
     * \param v 64 bits floating number
     */
    static gbool isNaN(gdouble v);

    /**
     * Return 64 bits IEEE 754 'double format' representation of specified floating number
     * \param v decimal floating form
     * \return binary IEEE 754 'double format' (SIGN(1 bit) + EXPONENT(11 bits) + MANTISSA(52 bits))
     * \example +INF = 0 11111111111 0000000000000000000000000000000000000000000000000000 = 0x7ff0000000000000
     * \example -INF = 1 11111111111 0000000000000000000000000000000000000000000000000000 = 0xfff0000000000000
     * \example  NAN = 0 11111111111 1000000000000000000000000000000000000000000000000000 = 0x7ff0000000000001
     * \example +0.0 = 0 00000000000 0000000000000000000000000000000000000000000000000000 = 0x0000000000000000
     * \example -0.0 = 1 00000000000 0000000000000000000000000000000000000000000000000000 = 0x8000000000000000
     */
    static i64 toLongBits(gdouble v);

    /**
     * Return 64 bits floating value represented by specified IEEE 754 'double format'
     * \param v binary IEEE 754 'double format' (SIGN(1 bit) + EXPONENT(11 bits) + MANTISSA(52 bits))
     * \return decimal 64 bits floating number
     * \example 0x7ff0000000000000 = 0 11111111111 0000000000000000000000000000000000000000000000000000 = +INF
     * \example 0xfff0000000000000 = 1 11111111111 0000000000000000000000000000000000000000000000000000 = -INF
     * \example 0x7ff0000000000001 - 0x7fffffffffffffff = 0 11111111111 1000000000000000000000000000000000000000000000000000
     *      - 0 11111111111 1111111111111111111111111111111111111111111111111111 = NaN
     * \example 0xfff0000000000001 - 0xffffffffffffffff = 1 11111111111 1000000000000000000000000000000000000000000000000000
     *      - 1 11111111111 1111111111111111111111111111111111111111111111111111 = NaN
     * \example 0x0000000000000000 = 0 00000000000 0000000000000000000000000000000000000000000000000000 = +0.0
     * \example 0x8000000000000000 = 1 00000000000 0000000000000000000000000000000000000000000000000000 = -0.0
     */
    static gdouble fromLongBits(i64 v);

    /**
     * Compares this instance with specified object
     * \param obj object to be comparing
     */
    gbool equals(const Object &obj) const override;

    /**
     * Compares this instance with value
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
    gint compareTo(Double const &i) const override;

    /**
     * Return value of this instance as long
     */
    operator gdouble () const;

    /**
     * Return value of this instance as double
     */
    operator gdouble& ();

    /**
     * Compares two double value numerically
     * \param x left value to be comparing
     * \param y right value to be comparing
     */
    static gint compare(gdouble x, gdouble y);

    /**
     * Return new instance representing by specified literal value
     */
    static Double valueOf(gdouble f);

    /**
     * Return copy of this instance
     */
    Object &clone() const override;

    /**
     * Constant representing the max floating value represented in 64 bits
     */
    CORE_FAST static gdouble MAX = 0x1.fffffffffffffP+1023;

    /**
     * Constant representing the min floating value represented in 64 bits
     */
    CORE_FAST static gdouble MIN = 0x0.0000000000001P-1022;

    /**
     * Constant representing the min normal floating value represented in 64 bits
     */
    CORE_FAST static gdouble MIN_NORMAL = 0x1.0p-1022;

    /**
     * Constant representing the binary exponent bias.
     * 2^(11-1)-1 = 1023
     */
    CORE_FAST static gint BIAS = 0b01111111111;

    /**
     * Constant representing infinitely large magnetude represented in 64 bits
     */
    static gdouble const INF;

    /**
     * Constant representing Not a Number
     */
    static gdouble const NAN;

    String toString() const override;

    static String toString(gdouble d);

    static String toHexString(gdouble d);

    glong hash() const override;

    static glong hash(gdouble d);

    static gdouble parseDouble(String const& str);

    static Double valueOf(String const& str);

    static gint signum(gdouble d);

protected:
    void set(const Object &obj) override;

private:
    gdouble value;

    static gdouble _x10(gdouble result, gint pow);
};


#endif //CORE_DOUBLE_H

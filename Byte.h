//
// Created by brunshweeck on 2023/02/19.
//

#ifndef CORE_BYTE_H
#define CORE_BYTE_H


#include "Number.h"
#include "Hashable.h"

/**
 * The Byte class wraps a value of primitive type byte in an object.
 * An object of type Byte contains a single field whose type is byte.
 * In addition, this class provides several methods for converting a
 * byte to a String and a String to a byte, as well as other constants
 * and methods useful when dealing with a byte.
 */
class Byte final : public Number, public Comparable<Byte>, public Hashable {
public:
    /**
     * Construct new instance of Byte
     */
    CORE_IMPLICIT Byte();

    /**
     * Construct new instance of Byte and initialize with gbyte
     * \param v literal 8 bits signed integer
     */
    CORE_IMPLICIT Byte(gbyte v);

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
     * Compares this object to the specified value.
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
     * Compares two Byte objects numerically.
     * \param i value to be comparing
     */
    gint compareTo(Byte const &b) const override;

    /**
     * Return value of this instance as byte
     */
    operator gbyte() const;

    /**
     * Return value of this instance as byte
     */
    operator gbyte &();

    /**
     * Compares two byte values numerically.
     * \param x left value to be comparing
     * \param y right value to be comparing
     */
    static gint compare(gbyte x, gbyte y);

    /**
     * Return new instance representing by specified literal value
     */
    static Byte valueOf(gbyte i);

    /**
     * Return copy of this instance
     */
    Object &clone() const override;

    /**
     * A constant holding the maximum value a byte can have, 2^7 - 1.
     */
    CORE_FAST static gbyte MAX = 0b01111111;

    /**
     * A constant holding the minimum value a byte can have, -2^7.
     */
    CORE_FAST static gbyte MIN = (gbyte) 0b10000000;

    String toString() const override;

    static String toString(gbyte i);

    static String toString(gbyte i, gint base);

    static String toUnsignedString(gbyte i);

    static String toUnsignedString(gbyte i, gint base);

    glong hash() const override;

    static glong hash(gbyte b);

protected:
    void set(const Object &obj) override;

private:
    gbyte value;
};


#endif //CORE_BYTE_H

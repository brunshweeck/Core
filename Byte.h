//
// Created by brunshweeck on 2023/02/19.
//

#ifndef CORE_BYTE_H
#define CORE_BYTE_H


#include "Number.h"
#include "String.h"

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
    CORE_FAST Byte() {}

    /**
     * Construct new instance of Byte and initialize with gbyte
     * \param v literal 8 bits signed integer
     */
    CORE_FAST Byte(gbyte v): value(v) {};

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
    template<class T, CORE_TEMPLATE_REQUIRE_PRIMITIVE(Object, T, Obj, )>
    gbool equals(T v) const {
        Obj o = v;
        return equals(o);
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
    CORE_FAST static gbyte MAX = 127;

    /**
     * A constant holding the minimum value a byte can have, -2^7.
     */
    CORE_FAST static gbyte MIN = -128;

    /**
     * Return string representation of this object
     */
    String toString() const override;

    /**
     * Return string representation of specified number
     * \param i byte
     */
    static String toString(gbyte i);

    /**
     * Return string representation of specified number in specified base
     * \param i byte
     * \param base conversion base
     * \throw ValueError If base great than 36 or less than 2
     */
    static String toString(gbyte i, gint base);

    /**
     * Return unsigned string representation of specified byte number
     * \param i byte
     */
    static String toUnsignedString(gbyte i);

    /**
     * Return unsigned string representation of specified byte number in specified base
     * \param i byte
     * \param base conversion base
     * \throw ValueError If base great than 36 or less than 2
     */
    static String toUnsignedString(gbyte i, gint base);

    /**
     * Return hash code of this object
     */
    glong hash() const override;

    /**
     * Return hash code of specified byte number
     */
    static glong hash(gbyte b);

    /**
     * Return byte number represented by specified string
     * \param str string representation  of byte number
     * \throw ValueError If specified string not represent byte number
     */
    static gbyte parseByte(String const &str);

    /**
     * Return byte number represented by specified string in specified base
     * \param str string representation  of byte number
     * \param base conversion base
     * \throw ValueError If base great than 36 or less than 2
     * \throw ValueError If specified string not represent byte number
     */
    static gbyte parseByte(String const &str, gint base);

    /**
     * Return byte number represented by specified string
     * \param str string representation  of byte number
     * \throw ValueError If specified string not represent byte number
     */
    static Byte valueOf(String const &str);

    /**
     * Return Byte object represented by specified string in specified base
     * \param str string representation  of byte number
     * \param base conversion base
     * \throw ValueError If base great than 36 or less than 2
     * \throw ValueError If specified string not represent byte number
     */
    static Byte valueOf(String const &str, gint base);

    /**
     * Decodes a String into a Byte.
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
    static Byte decode(String const &str);

private:
    gbyte value;
};


#endif //CORE_BYTE_H

//
// Created by brunshweeck on 2023/2/20.
//

#ifndef CORE_BOOLEAN_H
#define CORE_BOOLEAN_H


#include "Comparable.h"
#include "String.h"

/**
 * The Boolean class wraps a value of the primitive type boolean in an object.
 * An object of type Boolean contains a single field whose type is boolean.
 * In addition, this class provides many methods for converting a boolean to
 * a String and a String to a boolean, as well as other constants and methods
 * useful when dealing with a boolean.
 */
class Boolean final : public Object, public Comparable<Boolean> {
public:
    /**
     * Construct new instance of Boolean
     */
    CORE_FAST Boolean() {}

    /**
     * Construct new instance of Boolean and initialize with true/false
     * \param v literal true or false
     */
    CORE_FAST Boolean(gbool v): value(v) {}

    /**
     * Return value of this instance as boolean
     */
    gbool booleanValue() const;

    /**
     * Compares this instance with specified object
     * \param obj object to be compared
     */
    gbool equals(const Object &obj) const override;

    /**
     * Compares this instance with an other object
     * \param b object to compared
     */
    gint compareTo(Boolean const &b) const override;

    /**
     * Compares two boolean values
     * \param x first value to be compared
     * \param y second value to be compared
     */
    static gint compare(gbool x, gbool y);

    /**
     * Return new instance of Boolean represented by specified value
     * \param b boolean value
     */
    static Boolean valueOf(gbool b);

    /**
     * Returns the result of applying the logical AND operator to the specified boolean operands
     * \param x the first operand
     * \param y the second operand
     */
    static gbool logicalAnd(gbool x, gbool y);

    /**
     * Returns the result of applying the logical OR operator to the specified boolean operands
     * \param x the first operand
     * \param y the second operand
     */
    static gbool logicalOr(gbool x, gbool y);

    /**
     * Returns the result of applying the logical XOR operator to the specified boolean operands
     * \param x the first operand
     * \param y the second operand
     */
    static gbool logicalXor(gbool x, gbool y);

    /**
     * Return value of this instance as boolean
     */
    operator gbool() const;

    /**
     * Return value of this instance as boolean
     */
    operator gbool &() ;

    /**
     * Return copy of this instance
     */
    Object &clone() const override;

    /**
     * The Boolean object corresponding to the primitive value true.
     */
    static Boolean const TRUE;

    /**
     * The Boolean object corresponding to the primitive value false.
     */
    static Boolean const FALSE;

    String toString() const override;

private:
    gbool value = false;
};


#endif //CORE_BOOLEAN_H

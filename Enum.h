//
// Created by brunshweeck on 20/02/2023.
//

#ifndef CORE_ENUM_H
#define CORE_ENUM_H

#include "Integer.h"
#include "MemoryError.h"

/**
 * Enum class is object representing primitive enumeration type
 * \tparam E literal enum type
 */
template<class E>
class Enum final : public Object, public Comparable<Enum<E>>, public Hashable {
public:
    /**
     * Construct new instance of Enum<E>
     */
    CORE_FAST Enum() {}

    /**
     * Construct new instance of Enum<E>
     * \param v literal enumeration
     */
    CORE_FAST Enum(E v) : value(v) {}

    /**
     * Return integer representation of value of this instance
     */
    CORE_FAST gint ordinal() const {
        return ordinal(value);
    }

    /**
     * Return integer representation of specified value
     * \param v enumeration value to be converted
     */
    CORE_FAST static gint ordinal(E v) {
        return (gint) v;
    }

    /**
     * Compares this instance with an other object
     * \param e enum value to be compared
     */
    gint compareTo(Enum<E> const &e) const override {
        return compare(value, e.value);
    }

    /**
     * Compares two enum values
     * \param x first operand
     * \param y second operand
     */
    CORE_FAST static gint compare(E x, E y) {
        return x > y ? 1 : x < y ? -1 : 0;
    }

    /**
     * Return true if this instance equals to specified object
     * \param obj object to compared
     */
    gbool equals(const Object &obj) const override {
        if (this == &obj)
            return true;
        if (!Class<Enum>::hasInstance(obj))
            return false;
        Enum const &o = (Enum const &) obj;
        return value == o.value;
    }

    /**
     * Compares this instance with literal enum
     * \param v literal enumeration
     */
    template<class T, CORE_TEMPLATE_REQUIRE_PRIMITIVE(Object, T, Obj,)>
    CORE_FAST gbool equals(T v) const {
        return value == v;
    }

    /**
     * Return new instance representing by specified value
     * \param v enum value
     */
    CORE_FAST static Enum<E> valueOf(E v) {
        return v;
    }

    /**
     * Return new instance with ordinal value
     * \param i ordinal value
     */
    CORE_FAST static Enum<E> valueOf(gint i) {
        return (E) i;
    }

    /**
     * Return value of this instance
     */
    CORE_FAST operator E() const {
        return value;
    }

    /**
     * Return copy of this instance
     */
    Object &clone() const override {
        try { return *new Enum<E>(value); } catch (...) { throw MemoryError(); }
    }

    /**
     * It defined by user
     */
    static String (*alias)(E);

    String toString() const override {
        return toString(value);
    }

    static String toString(E v) {
        return alias != nullptr ? alias(v) : Integer::toString(ordinal(v));
    }

    glong hash() const override {
        return hash(value);
    }

    CORE_FAST static glong hash(E v) {
        return ordinal(v);
    }

protected:
    CORE_TEMPLATE_REQUIRE_UNREFERENCED(E);
    CORE_TEMPLATE_REQUIRE_MUTABLE(E);
    CORE_TEMPLATE_REQUIRE_NON_VOLATILE(E);
    CORE_REQUIRE(Class<E>::isEnum(), "E in Enum<E> must be enum type");

private:
    E value = E();
};

template<class E>
String (*Enum<E>::alias)(E) = nullptr;

#endif //CORE_ENUM_H

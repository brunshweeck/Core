//
// Created by brunshweeck on 20/02/2023.
//

#ifndef CORE_ENUM_H
#define CORE_ENUM_H

#include "Comparable.h"
#include "String.h"
#include "Integer.h"

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
    CORE_FAST Enum() : Enum<E>(E()) {}

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
    CORE_FAST gint compareTo(Enum<E> const &e) const override {
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
        Enum<E> const *e = dynamic_cast<Enum<E> const *>(&obj);
        if (!e) return false;
        return value == e->value;
    }

    /**
     * Compares this instance with literal enum
     * \param v literal enumeration
     */
    template<class T,
            Class<gbool>::Require<!Class<T>::isEnum()> = true,
            class U = typename Class<T>::NIVR>
    gbool equals(T &&v) const {
        return equals(Enum<U>((T &&) v));
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
        Enum<E> *e;
        try { e = new Enum<E>(value); } catch (...) {}
        return *e;
    }

    CORE_DEPRECATED static String (*customAlias)(E);

    String toString() const override {
        return toString(value);
    }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

    static String toString(E v) {
        return customAlias ? customAlias(v) : Integer::toString(ordinal(v));
    }

#pragma GCC diagnostic pop

    glong hash() const override {
        return ordinal();
    }

protected:
    /**
     * Set value of this instance
     * \param obj source of new value
     * \throw CastError if is not compatible
     */
    void set(const Object &obj) override {
        Enum<E> const *e = dynamic_cast<Enum<E> const *>(&obj);
        if (!e) {}
        value = e->value;
    }

    static_assert(!Class<E>::isReference(), "E in Enum<E> must be unreferenced type");

    static_assert(!Class<E>::isImmutable(), "E in Enum<E> must be mutable type");

    static_assert(!Class<E>::isVolatile(), "E in Enum<E> must be non volatile type");

    static_assert(Class<E>::isEnum(), "E in Enum<E> must be enum type");

private:
    E value;
};

template<class E>
String (*Enum<E>::customAlias)(E) = 0;

#endif //CORE_ENUM_H

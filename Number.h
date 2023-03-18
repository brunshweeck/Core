//
// Created by brunshweeck on 2023/02/19.
//

#ifndef CORE_NUMBER_H
#define CORE_NUMBER_H


#include "String.h"

class Number : public Object {
public:
    /**
     * Return value of this instance as byte.
     */
    virtual gbyte byteValue() const;

    /**
     * Return value of this instance as short.
     */
    virtual gshort shortValue() const;

    /**
     * Return value of this instance as int.
     */
    virtual gint intValue() const = 0;

    /**
     * Return value of this instance as long.
     */
    virtual glong longValue() const = 0;

    /**
     * Return value of this instance as float.
     */
    virtual gfloat floatValue() const = 0;

    /**
     * Return value of this instance as double.
     */
    virtual gdouble doubleValue() const = 0;

    /**
     * Compares this instance with literal number
     * \param v literal number
     */
    template<class T, CORE_TEMPLATE_REQUIRE_PRIMITIVE(Object, T, Obj,)>
    gbool equals(T v) const {
        Obj o = v;
        glong l = longValue();
        gdouble d = doubleValue();
        if (Class<T>::isNumber()) {
            if (d == (gdouble) l)
                return l == v;
            return d == (gdouble) v;
        }
        return false;
    }
};

#endif //CORE_NUMBER_H

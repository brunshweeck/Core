//
// Created by brunshweeck on 2023/02/19.
//

#ifndef CORE_NUMBER_H
#define CORE_NUMBER_H


#include "Comparable.h"

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
    template<class T,
            Class<gbool>::Require<!Class<T>::isNumber()> = true,
            class S = typename Class<T>::NIVR,
            class U = typename Class<S>::Object>
    gbool equals(T &&v) const {
        return equals(U((T &&) v));
    }

    String toString() const override;
};

#endif //CORE_NUMBER_H

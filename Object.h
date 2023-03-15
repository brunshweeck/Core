//
// Created by brunshweeck on 16/02/2023.
//

#ifndef CORE_OBJECT_H
#define CORE_OBJECT_H

#include "Class.h"

CORE_CLASS_DECLARATIONS

/**
 *  Object class is a base of class hierarchy
 */
class Object {
public:
    /**
     * Compares this instance with literal value
     * \param v - literal value
     */
    template<class T,
            Class<gbool>::Require<!Class<T>::isClass()> = true,
            class S = typename Class<T>::NIVR,
            class U = typename Class<S>::Object,
            Class<gbool>::Require<!Class<U>::isVoid()> = true>
    gbool equals(T &&v) const {
        return equals(U((T &&) v));
    }

    /**
     * Compares two objects
     */
    virtual gbool equals(Object const &obj) const = 0;

    /**
     * Return copy of this instance
     */
    virtual Object &clone() const = 0;

    /**
     * Set properties of object instance with properties of other objects
     * \param obj news properties
     */
    Object &operator=(Object const &obj);

    /**
     *  Destroy this instance
     */
    virtual ~Object() = default;

    /**
     * Return string representation of this object
     */
    virtual String toString() const;

protected:
    /**
     * Set properties of object instance with properties of other objects
     * \param obj news properties
     * \throw CastError thrown if specified object is not compatible to this instance
     */
    CORE_DEPRECATED virtual void set(Object const &obj) = 0;
};

extern gbool operator==(Object const &obj1, Object const &obj2);

extern gbool operator!=(Object const &obj1, Object const &obj2);

template<class T,
        Class<gbool>::Require<!Class<T>::isClass()> = true,
        class S = typename Class<T>::NIVR,
        class U = typename Class<S>::Object,
        Class<gbool>::Require<!Class<U>::isVoid()> = true,
        Class<gbool>::Require<!Class<Object>::isSuper<U>()> = true>
gbool operator==(T &&v, Object const &obj) {
    return U((T &&) v) == obj;
}

template<class T,
        Class<gbool>::Require<!Class<T>::isClass()> = true,
        class S = typename Class<T>::NIVR,
        class U = typename Class<S>::Object,
        Class<gbool>::Require<!Class<U>::isVoid()> = true,
        Class<gbool>::Require<!Class<Object>::isSuper<U>()> = true>
gbool operator!=(T &&v, Object const &obj) {
    return U((T &&) v) != obj;
}

template<class T,
        Class<gbool>::Require<!Class<T>::isClass()> = true,
        class S = typename Class<T>::NIVR,
        class U = typename Class<S>::Object,
        Class<gbool>::Require<!Class<U>::isVoid()> = true,
        Class<gbool>::Require<!Class<Object>::isSuper<U>()> = true>
gbool operator==(Object const &obj, T &&v) {
    return obj == U((T &&) v);
}

template<class T,
        Class<gbool>::Require<!Class<T>::isClass()> = true,
        class S = typename Class<T>::NIVR,
        class U = typename Class<S>::Object,
        Class<gbool>::Require<!Class<U>::isVoid()> = true,
        Class<gbool>::Require<!Class<Object>::isSuper<U>()> = true>
gbool operator!=(Object const &obj, T &&v) {
    return obj != U((T &&) v);
}


#endif //CORE_OBJECT_H

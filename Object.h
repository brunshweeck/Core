//
// Created by brunshweeck on 16/02/2023.
//

#ifndef CORE_OBJECT_H
#define CORE_OBJECT_H

#include "extern/Class.h"

CORE_CLASS_DECLARATIONS

/**
 *  Object class is a base of class hierarchy
 */
class Object {
public:
    /**
     * Construct new Object
     */
    CORE_FAST Object() {};

    /**
     * Return true if this object equals to specified object
     * \param obj object to be compared
     */
    virtual gbool equals(Object const &obj) const;

    /**
     * Return copy of this instance
     */
    virtual Object &clone() const;

    /**
     * Return string representation of this object
     */
    virtual String toString() const;

    /**
     * Return true if this object equals to specified object
     * \param obj object to be compared
     */
    virtual gbool operator==(Object const& obj) const;

    /**
     * Return true if this object not equals to specified object
     * \param obj object to be compared
     */
    virtual gbool operator!=(Object const& obj) const;

protected:
    template<class T>
    static gbool isPerfectlyInstanceOf(Object const& o) {
        return typeid(T) == typeid(o);
    }
};

#endif //CORE_OBJECT_H

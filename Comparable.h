//
// Created by brunshweeck on 2023/2/20.
//

#ifndef CORE_COMPARABLE_H
#define CORE_COMPARABLE_H

#include "Class.h"

/**
 * This interface imposes a total ordering on the objects of each class that implements it.
 * This ordering is referred to as the class's natural ordering, and the class's compareTo
 * method is referred to as its natural comparison method.
 * \tparam T the type of objects that this object may be compared to
 */
template<class T>
class Comparable /* interface */ {
public:
    CORE_TEMPLATE_REQUIRE_UNREFERENCED(T);
    CORE_TEMPLATE_REQUIRE_NON_VOLATILE(T);
    CORE_TEMPLATE_REQUIRE_MUTABLE(T);

    /**
     * Construct new comparable object
     */
    CORE_FAST Comparable() {}

    /**
     * Compares this object with the specified object for order.
     * Returns a negative integer, zero, or a positive integer as this object
     * is less than, equal to, or greater than the specified object.
     * \param obj object to be compared
     */
    virtual gint compareTo(T const &obj) const = 0;
};


#endif //CORE_COMPARABLE_H

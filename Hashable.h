//
// Created by brunshweeck on 01/03/2023.
//

#ifndef CORE_HASHABLE_H
#define CORE_HASHABLE_H

#include "Object.h"

/**
 * The Hashable class Represent all object that support hashing
 */
class Hashable {
public:
    /**
     * Construct new hashable object
     */
    CORE_FAST Hashable() {}

    /**
     * Return hash code of this object
     */
    virtual glong hash() const = 0;
};


#endif //CORE_HASHABLE_H

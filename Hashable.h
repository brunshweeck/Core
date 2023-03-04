//
// Created by brunshweeck on 01/03/2023.
//

#ifndef CORE_HASHABLE_H
#define CORE_HASHABLE_H

#include "Object.h"

class Hashable {
public:
    /**
     * Return hash code of this object
     */
    virtual glong hash() const = 0;
};


#endif //CORE_HASHABLE_H

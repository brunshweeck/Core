//
// Created by brunshweeck on 16/03/2023.
//

#ifndef CORE_KEY_ERROR_H
#define CORE_KEY_ERROR_H


#include "ValueError.h"

/**
 * Thrown to indicate that map key not found
 */
class KeyError : public ValueError {
public:
    /**
     * Construct new key error
     */
    KeyError() : ValueError("Key Not found") {}

    /**
     * Construct new key error
     */
    CORE_EXPLICIT KeyError(Object const &key): ValueError("Key not found: " + key.toString()) {}

    /**
     * Return copy of this object
     */
    Object &clone() const override;

};


#endif //CORE_KEY_ERROR_H

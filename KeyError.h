//
// Created by brunshweeck on 16/03/2023.
//

#ifndef CORE_KEY_ERROR_H
#define CORE_KEY_ERROR_H


#include "ValueError.h"

class KeyError : public ValueError {
public:
    /**
     * Construct new key error
     */
    KeyError();

    /**
     * Construct new key error
     */
    CORE_EXPLICIT KeyError(Object const &key);

};


#endif //CORE_KEY_ERROR_H

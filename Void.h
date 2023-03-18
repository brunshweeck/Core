//
// Created by brunshweeck on 07/03/2023.
//

#ifndef CORE_VOID_H
#define CORE_VOID_H


#include "Object.h"

/**
 * The Void class is an uninstantiable placeholder class to hold a
 * reference to the Class object representing the keyword void.
 */
class Void final : public Object {
private:
    /*
     * The Void class cannot be instantiated.
     */
    CORE_FAST Void() {};
};


#endif //CORE_VOID_H

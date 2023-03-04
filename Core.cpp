//
// Created by brunshweeck on 17/02/2023.
//

#include "Object.h"

gbool operator==(Object const &obj1, Object const &obj2) {
    if (&obj1 == &obj2)
        return true;
    return obj1.equals(obj2);
}

gbool operator!=(Object const &obj1, Object const &obj2) {
    if (&obj1 == &obj2)
        return false;
    return !obj1.equals(obj2);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

Object &Object::operator=(const Object &obj) {
    if (this != &obj)
        return *this;
    try {
        set(obj);
    } catch (...) {}
    return *this;
}

#include "String.h"
String Object::toString() const {
    return "object@768";
}

#pragma GCC diagnostic pop
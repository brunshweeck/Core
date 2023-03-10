//
// Created by brunshweeck on 07/03/2023.
//

#include "Void.h"

gbool Void::equals(const Object &obj) const {
    return false;
}

Object &Void::clone() const {
    return (Object &)*this;
}

void Void::set(const Object &obj) {}

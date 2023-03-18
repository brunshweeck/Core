//
// Created by brunshweeck on 2023/3/12.
//

#include "Break.h"

Object &Break::clone() const {
    static Break aBreak{};
    return aBreak;
}

gbool Break::equals(const Object &obj) const {
    if(this == &obj)
        return true;
    return Class<Break>::hasInstance(obj);
}

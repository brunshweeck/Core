//
// Created by brunshweeck on 07/03/2023.
//

#ifndef CORE_VOID_H
#define CORE_VOID_H


#include "Object.h"

class Void final: public Object {
public:
    CORE_FAST Void() = delete;

    gbool equals(const Object &obj) const override;

    Object &clone() const override;

private:
    virtual void set(const Object &obj);
};


#endif //CORE_VOID_H

//
// Created by brunshweeck on 10/03/2023.
//

#ifndef CORE_STATE_ERROR_H
#define CORE_STATE_ERROR_H


#include "Error.h"
#include "../String.h"

class StateError: public Error {
public:
    CORE_EXPLICIT StateError(const String &message);

    String message() const override;

    gbool equals(const Object &obj) const override;

    Object &clone() const override;

protected:
    void set(const Object &obj) override;

private:
    String _message;
};


#endif //CORE_STATE_ERROR_H

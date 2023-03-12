//
// Created by brunshweeck on 2023/3/12.
//

#ifndef CORE_ERROR_H
#define CORE_ERROR_H


#include <exception>
#include "Object.h"
#include "String.h"

class Error: public Object, protected std::exception {
private:
    /**
     * This field contains details of error
     */
    String _message;

public:
    /**
     * Construct new error without details message
     */
    Error();

    /**
     * Construct new error with details message or description
     * \param message details message
     */
    CORE_EXPLICIT Error(const String &message);

    /**
     * Return error description
     */
    virtual const String &message() const;

    /**
     * Return true if this instance equals to specified object
     * \param obj object to be compared
     */
    gbool equals(const Object &obj) const override;

    /**
     * Return copy of this object
     */
    Object &clone() const override;

    /**
     * Return string representation of this object
     */
    String toString() const override;

protected:
    void set(const Object &obj) override;

    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};


#endif //CORE_ERROR_H

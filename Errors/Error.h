//
// Created by brunshweeck on 25/02/2023.
//

#ifndef CORE_ERROR_H
#define CORE_ERROR_H


#include <exception>
#include "../Object.h"

class Error : public Object, public std::exception {
public:
    /**
     * Construct new instance of error
     */
    Error() CORE_NOTHROW;

    /**
     * Return error message
     */
    virtual String message() const;

    gbool equals(const Object &obj) const override;

    /**
     * Return copy of this instance
     * \deprecated not guaranteed that success of operation
     */
    CORE_DEPRECATED Object &clone() const override;

protected:
    CORE_DEPRECATED void set(const Object &obj) override;

private:
    /**
     * Return error message
     */
    CORE_DEPRECATED virtual const char *what() const CORE_NOTHROW override;
};


#endif //CORE_ERROR_H

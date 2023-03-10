//
// Created by brunshweeck on 07/03/2023.
//

#ifndef CORE_FUNCTIONAL_H
#define CORE_FUNCTIONAL_H

#include "../Void.h"
#include "../Boolean.h"
#include "../Byte.h"
#include "../Short.h"
#include "../Integer.h"
#include "../Long.h"
#include "../Float.h"
#include "../Double.h"
#include "../Character.h"
#include "../String.h"

template<class T, class R = Void>
class Functional {
private:
    using _1 = typename Class<R>::NIVR;
    using _2 = typename Class<R>::Primitive;
protected:
    using _R = typename Class<_2>::template Conditional<
            Class<_2>::isNumber() ||
            Class<_2>::isBoolean() ||
            Class<_2>::isCharacter() ||
            Class<_2>::isVoid(), R>;

#define CALL ()

    static_assert(Class<Object>::isSuper<T>(),

    "Only type deriving from Object are supported");

    static_assert(Class<Object>::isSuper<R>(),

    "Only type deriving from Object are supported");

public:
    /**
     * Invoke functional object
     * \param t argument parameter
     */
    virtual _R operator CALL(T t) const = 0;

#undef CALL
};


#endif //CORE_FUNCTIONAL_H

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

/**
 * Functional represent all object callable with one argument and returning value
 * \tparam T argument type
 * \tparam R return type
 */
template<class T, class R = Void>
class Functional {
private:
    CORE_TEMPLATE_REQUIRE_OBJECT(T);
    CORE_TEMPLATE_REQUIRE_OBJECT(R);

    using _1 = typename Class<R>::NIVR;
    using _2 = typename Class<R>::Primitive;
protected:
    /**
     * Check Valid Return type.
     * * If R is reference  -> _R = R
     * * If R is class number or class boolean or class character -> _R = Class<R>::Primitive
     * * If R is Abstract -> _R = Class<R>::Reference
     */
    using _R = typename Class<_2>::template Conditional<
            !Class<R>::isReference() && (
                    Class<_2>::isNumber() ||
                    Class<_2>::isBoolean() ||
                    Class<_2>::isCharacter() ||
                    Class<_1>::template isSame<Void>()),
            typename Class<R>::template Conditional<
                    Class<R>::isReference() ||
                    !Class<R>::isAbstract(), Class<R>::Reference>
    >;

public:
    /**
     * Invoke functional object
     * \param t argument parameter
     */
    virtual _R operator()(T t) const = 0;

};


#endif //CORE_FUNCTIONAL_H

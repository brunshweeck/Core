//
// Created by brunshweeck on 15/03/2023.
//

#ifndef CORE_BIFUNCTIONAL_H
#define CORE_BIFUNCTIONAL_H

#include "../Object.h"

/**
 * Functional represent all object callable with two arguments and returning value
 * \tparam T first argument type
 * \tparam U second argument type
 * \tparam R return type
 */
template<class T, class U, class R = Void>
class BiFunctional {
private:
    CORE_TEMPLATE_REQUIRE_OBJECT(T);
    CORE_TEMPLATE_REQUIRE_OBJECT(U);
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
            Class<_2>::isNumber() ||
            Class<_2>::isBoolean() ||
            Class<_2>::isCharacter() ||
            Class<_1>::template isSame<Void>(),
            typename Class<R>::template Conditional<
                    Class<R>::isReference() ||
                    !Class<R>::isAbstract()>
    >;

public:
    /**
     * Invoke functional object
     * \param t first argument
     * \param u second argument
     */
    virtual _R operator()(T t, U u) const = 0;
};


#endif //CORE_BIFUNCTIONAL_H

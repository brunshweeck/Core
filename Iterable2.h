//
// Created by brunshweeck on 17/03/2023.
//

#ifndef CORE_ITERABLE2_H
#define CORE_ITERABLE2_H

#include "Iterable.h"
#include "Object.h"


template<class E>
class Iterable2 {
public:
    CORE_TEMPLATE_REQUIREMENT(E);

    /**
     * Returns an iterator over elements of type
     */
    virtual Iterator2<E> &iterator2() = 0;

    /**
     * Returns an iterator over elements of type
     */
    virtual Iterator2<E> &iterator2() const = 0;

    /**
     * Performs the given action for each element of the Iterable
     * until all elements have been processed or the action throws an
     * exception.  Actions are performed in the order of iteration, if that
     * order is specified.  Exceptions thrown by the action are relayed to the
     * caller.
     * \param action The action to be performed for each element
     */
    virtual void forEach(Consumer<E const &> const &action) const {
        Iterator2<E> &it = iterator2();
        while (it.hasNext())
            action.accept(it.next());
    }
};

#endif//CORE_ITERABLE2_H

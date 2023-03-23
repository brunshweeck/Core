//
// Created by brunshweeck on 17/03/2023.
//

#ifndef CORE_ITERABLE_H
#define CORE_ITERABLE_H

#include "Collections/Iterator2.h"
#include "Object.h"


/**
 * The iterable class represent any object that support each operation
 * \tparam E item value type
 */
template<class E>
class Iterable {
public:
    CORE_TEMPLATE_REQUIREMENT(E)

    /**
     * Returns an iterator over elements of type
     */
    virtual Iterator<E> &iterator() = 0;

    /**
     * Performs the given action for each element of the Iterable
     * until all elements have been processed or the action throws an
     * exception.  Actions are performed in the order of iteration, if that
     * order is specified.  Exceptions thrown by the action are relayed to the
     * caller.
     * \param action The action to be performed for each element
     */
    virtual void forEach(Consumer<E &> const &action) {
        Iterator<E> &it = iterator();
        while (it.hasNext())
            action.accept(it.next());
    }
};


#endif//CORE_ITERABLE_H

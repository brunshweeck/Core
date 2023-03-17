//
// Created by brunshweeck on 17/03/2023.
//

#ifndef CORE_ITERABLE_H
#define CORE_ITERABLE_H

#include "Object.h"
#include "Collections/Iterator.h"
#include "Iterable2.h"

template<class T>
class Iterable {
public:
    CORE_TEMPLATE_REQUIREMENT(T)

    /**
     * Returns an iterator over elements of type
     */
    virtual Iterator<T const>&& iterator() const = 0;

    /**
     * Performs the given action for each element of the Iterable
     * until all elements have been processed or the action throws an
     * exception.  Actions are performed in the order of iteration, if that
     * order is specified.  Exceptions thrown by the action are relayed to the
     * caller.
     * \param action The action to be performed for each element
     */
     virtual void forEach(Consumer<T const&> const& action) const {
         iterator().forEach(action);
     }

};


#endif //CORE_ITERABLE_H

//
// Created by brunshweeck on 16/03/2023.
//

#ifndef CORE_ITERATOR_H
#define CORE_ITERATOR_H


#include "../Object.h"
#include "../StateError.h"
#include "../Function/Consumer.h"

/**
 * The Iterator2 class is used to each collection item
 * \tparam E item value type
 */
template<class E>
class Iterator : public Object {
public:
    CORE_TEMPLATE_REQUIREMENT(E);

    /**
     * Return true if iterator has more items
     */
    virtual gbool hasNext() const = 0;

    /**
     * Return current item of iterator
     */
    virtual E &next() = 0;

    /**
     * Removes from the underlying collection the last element returned
     * by this iterator
     */
    virtual void remove() {
        throw StateError("Unsupported operation");
    }

    /**
     * Performs the given action for each remaining element until all elements
     * have been processed or the action throws an exception.  Actions are
     * performed in the order of iteration, if that order is specified.
     * Exceptions thrown by the action are relayed to the caller.
     * \param action The action to be performed for each element
     */
    virtual void forEach(Consumer<E&> const& action) {
        while (hasNext())
            action.accept(next());
    }
};

#if __cpp_deduction_guides > 201565
Iterator() -> Iterator<Object>;

template<class E>
Iterator(Iterator<E> const&) -> Iterator<E>;

#endif //

#endif //CORE_ITERATOR_H

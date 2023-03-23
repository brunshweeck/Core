#ifndef CORE_ITERATOR2_H
#define CORE_ITERATOR2_H

#include "Iterator.h"

/**
 * The Iterator2 class is used to each collection item as immutable item
 * \tparam E item value type
 */
template<class E>
class Iterator2 : public Object {
public:
    CORE_TEMPLATE_REQUIREMENT(E)

    /**
     * Return true if an iterator has more item
     */
    virtual gbool hasNext() const = 0;

    /**
     * Return next item of iterator
     */
    virtual E const &next() = 0;

    /**
     * Removes from the underlying collection the last element returned
     * by this iterator
     */
    virtual void remove() {
        throw StateError("This iterator not support item removing");
    };

    virtual void forEach(Consumer<E const &> const &action) {
        while (hasNext())
            action.accept(next());
    }
};

#if __cpp_deduction_guides > 201565
Iterator2()->Iterator2<Object>;

template<class E>
Iterator2(Iterator2<E> const &) -> Iterator2<E>;

#endif//

#endif//CORE_ITERATOR2_H
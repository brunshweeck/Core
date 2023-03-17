//
// Created by brunshweeck on 16/03/2023.
//

#ifndef CORE_ITERATOR_H
#define CORE_ITERATOR_H


#include "../Object.h"
#include "../StateError.h"
#include "../Function/Consumer.h"

/**
 * \tparam E value type
 */
template<class E>
class Iterator : public Object {
public:
    CORE_TEMPLATE_REQUIRE_UNREFERENCED(E);
    CORE_TEMPLATE_REQUIRE_NON_VOLATILE(E);
    CORE_TEMPLATE_REQUIRE_OBJECT(E);

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
     * Return true if specified object equals to this iterator
     * \param obj object to be compared
     */
    gbool equals(const Object &obj) const override = 0;

    /**
     * Return copy of this object
     */
    Object &clone() const override = 0;

    /**
     * Performs the given action for each remaining element until all elements
     * have been processed or the action throws an exception.  Actions are
     * performed in the order of iteration, if that order is specified.
     * Exceptions thrown by the action are relayed to the caller.
     * \param action The action to be performed for each element
     */
    virtual void forEach(Consumer<E&> const& action) const {
        while (hasNext())
            action.accept(next());
    }

protected:
    void set(const Object &obj) override {}
};


#endif //CORE_ITERATOR_H

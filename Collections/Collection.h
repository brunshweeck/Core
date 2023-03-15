//
// Created by brunshweeck on 07/03/2023.
//

#ifndef CORE_COLLECTION_H
#define CORE_COLLECTION_H

#include "../String.h"
#include "../Integer.h"
#include "../Function/Consumer.h"
#include "../Break.h"
#include "../Function/Predicate.h"

template<class E>
class Collection : public Object {
public:
    CORE_TEMPLATE_REQUIREMENT(E)

    /**
     * Add specified object from the this collection
     * \param obj object to be add from this collection
     */
    virtual gbool add(E const &obj) = 0;

    template<class U, class _U = E, Class<gbool>::Require<Class<_U>::isAbstract()> = true, CORE_TEMPLATE_REQUIRE_PRIMITIVE(
            E, U, _E,)>
    gbool add(U &&v) {
        return add(_E((U &&) v));
    }

    /**
     * Add all of element of specified collection from the this collection
     * \param c collection containing elements to add from this collection
     */
    virtual gbool addAll(Collection<E> const &c) {
        if (c.isEmpty())
            return false;
        c.forEach([this](E const &obj) -> void { add(obj); });
        return true;
    }

    /**
     * Remove first occurrence of specified object from this list
     * \param obj object to be removed
     */
    virtual gbool remove(E const &obj) = 0;

    template<class U, class _U = E, Class<gbool>::Require<Class<_U>::isAbstract()> = true, CORE_TEMPLATE_REQUIRE_PRIMITIVE(
            E, U, _E,)>
    gbool remove(U &&v) {
        return remove(_E((U &&) v));
    }

    /**
     * Remove all of element of this collection that are contained in specified collection
     * \param c collection containing elements to remove from this collection
     */
    virtual gbool removeAll(Collection<E> const &c) {
        return removeIf([&c](E const &obj) -> gbool { return c.contains(obj); });
    };

    /**
     * Remove all elements of this collection that satisfy the giving predicate
     * \param p the predicate
     */
    virtual gbool removeIf(Predicate<E const &> const &p) = 0;

    /**
     * Remove all of element of this collection that are contained in specified collection
     * \param c collection containing elements to remove from this collection
     */
    template<class _E, Class<gbool>::Require<Class<E>::template isSuper<_E>()> = true>
    gbool removeAll(Collection<_E> const &c) {
        gint oldSize = size();
        removeIf(Predicate<E const &>(&Collection<_E>::contains, c));
        return oldSize > size();
    }

    /**
     * Return true if this collection contains specified value
     * \param obj object to search
     */
    virtual gbool contains(E const &obj) const {
        gbool b = false;
        forEach([&obj, &b](E const &obj2) {
            if ((b = obj.equals(obj2)))
                throw Break();
        });
        return b;
    }

    template<class U, class _U = E, Class<gbool>::Require<Class<_U>::isAbstract()> = true, CORE_TEMPLATE_REQUIRE_PRIMITIVE(
            E, U, _E,)>
    gbool contains(U &&v) const {
        return contains(_E((U &&) v));
    }

    /**
     * Return true if all of element of specified collection are contained into this collection
     * \param c collection containing element to search
     */
    virtual gbool containsAll(Collection<E> const &c) const {
        if (this == &c)
            return !isEmpty();
        if (c.isEmpty() || isEmpty())
            return false;
        gbool b = true;
        c.forEach([&](E const &obj) {
            if (!contains(obj)) {
                b = false;
                throw Break();
            }
        });
        return b && !c.isEmpty();
    }

    /**
     * Return true if all of element of specified collection are contained into this collection
     * \param c collection containing element to search
     */
    template<class _E, Class<gbool>::Require<Class<E>::template isSuper<_E>()> = true>
    gbool containsAll(Collection<_E> const &c) const {
        if (c.isEmpty() || isEmpty())
            return false;
        gbool b = true;
        c.forEach([&](_E const &obj) {
            if (!contains(obj)) {
                b = false;
                throw Break();
            }
        });
        return b;
    }

    /**
     * Remove all element from this collection that are not contained into specified collection
     * \param c collection containing element to not remove
     */
    virtual gbool retainAll(Collection<E> const &c) {
        return removeIf([&c](E const &obj) -> gbool { return !c.contains(obj); });
    };

    /**
     * Remove all element from this collection that are not contained into specified collection
     * \param c collection containing element to not remove
     */
    template<class _E, Class<gbool>::Require<Class<E>::template isSuper<_E>()> = true>
    gbool retainAll(Collection<_E> const &c) {
        return removeIf(Predicate<E const &>(&Collection<_E>::contains, c).logicalNot());
    }

    /**
     * Remove all of element from this collection
     */
    virtual void clear() = 0;

    /**
     * Return true if collection have not element
     */
    virtual gbool isEmpty() const {
        return size() == 0;
    }

    /**
     * Return number of element from this collection
     */
    virtual gint size() const = 0;

    /**
     * Performed action to each all of element of this collection
     * \param action performed action
     */
    virtual void forEach(Consumer<E const &> const &action) const = 0;

private:
    void set(const Object &obj) override {
        if (this != &obj)
            if (Class<Collection<E>>::hasInstance(obj)) {
                clear();
                addAll((Collection<E> const &) obj);
            }
    }

};

#if __cpp_deduction_guides > 201565
Collection() -> Collection<Object>;
template<class E> Collection(Collection<E> const &) -> Collection<E>;
#endif //

#endif //CORE_COLLECTION_H

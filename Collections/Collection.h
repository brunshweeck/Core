//
// Created by brunshweeck on 07/03/2023.
//

#ifndef CORE_COLLECTION_H
#define CORE_COLLECTION_H

#include "../String.h"
#include "../Integer.h"
#include "../Function/Consumer.h"
#include "../Errors/Break.h"

template<class E>
class Collection : public Object {
public:

    /**
     * Append specified object from the end of this collection
     * \param obj object to be add from this collection
     */
    virtual gbool add(E const &obj) = 0;

    /**
     * Append specified object from the end of this collection
     * \param obj object to be add from this collection
     */
    template<class _E, Class<gbool>::Require<Class<E>::template isSuper<_E>()> = true>
    gbool add(_E const &obj) {
        return add((E const &) obj);
    }

    /**
     * Append all of element of specified collection from the end of this collection
     * \param c collection containing elements to add from this collection
     */
    gbool addAll(Collection<E> const &c) {
        c.forEach(Consumer<E>(&Collection::add, *this));
        return !c.isEmpty();
    }

    /**
     * Append all of element of specified collection from the end of this collection
     * \param c collection containing elements to add from this collection
     */
    template<class _E, Class<gbool>::Require<Class<E>::template isSuper<_E>()> = true>
    gbool addAll(Collection<_E> const &c) {
        c.forEach(Consumer<E>(&Collection::add<_E>, *this));
        return !c.isEmpty();
    }

    /**
     * Remove first occurrence of specified object from this list
     * \param obj object to be removed
     */
    virtual gbool remove(E const &obj) = 0;

    /**
     * Remove first occurrence of specified object from this list
     * \param obj object to be removed
     */
    template<class _E, Class<gbool>::Require<Class<E>::template isSuper<_E>()> = true>
    gbool remove(_E const &obj) {
        return remove((E const &) obj);
    }

    /**
     * Remove all of element of this collection that are contained in specified collection
     * \param c collection containing elements to remove from this collection
     */
    virtual gbool removeAll(Collection<E> const &c) = 0;

    /**
     * Remove all of element of this collection that are contained in specified collection
     * \param c collection containing elements to remove from this collection
     */
    template<class _E, Class<gbool>::Require<Class<E>::template isSuper<_E>()> = true>
    gbool removeAll(Collection<_E> const &c) {
        if (isEmpty() || c.isEmpty())
            return false;
        c.forEach(Consumer<E>(&Collection::remove<_E>, *this));
    }

    /**
     * Return true if this collection contains specified value
     * \param obj object to search
     */
    virtual gbool contains(E const &obj) const = 0;

    /**
     * Return true if this collection contains specified value
     * \param obj object to search
     */
    template<class _E, Class<gbool>::Require<Class<E>::template isSuper<_E>()> = true>
    gbool contains(_E const &obj) const {
        return contains((E const &) obj);
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
        if (this == &c)
            return true;
        gbool b = false;
        forEach([&](E const &obj) {
            if (!c.contains(obj))
                b = b || remove(obj);
        });
        return b;
    };

    /**
     * Remove all element from this collection that are not contained into specified collection
     * \param c collection containing element to not remove
     */
    template<class _E, Class<gbool>::Require<Class<E>::template isSuper<_E>()> = true>
    gbool retainAll(Collection<_E> const &c) {
        gbool b = false;
        forEach([&](E const &obj) {
            if (!c.contains(obj))
                b = b || remove(obj);
        });
        return b;
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
    virtual void forEach(Consumer<E> &&action) const = 0;

private:
    void set(const Object &obj) override {
        if (this != &obj)
            if (dynamic_cast<Collection<E>>(&obj)) {
                setAll((Collection<E> const &) obj);
            }
    }
};


#endif //CORE_COLLECTION_H

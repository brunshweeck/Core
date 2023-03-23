//
// Created by brunshweeck on 07/03/2023.
//

#ifndef CORE_COLLECTION_H
#define CORE_COLLECTION_H

#include "../Break.h"
#include "../Function/Predicate.h"
#include "../Integer.h"
#include "../Iterable2.h"
#include "../StateError.h"


template<class E>
class Collection : public Object, public Iterable2<E> {
public:
    CORE_TEMPLATE_REQUIREMENT(E)

    /**
     * Add specified object from the this collection
     * \param obj object to be add from this collection
     */
    virtual gbool add(E const &obj) {
        throw StateError("Add Operation is not support by this collection");
    }

    /**
     * Add all of element of specified collection from the this collection
     * \param c collection containing elements to add from this collection
     */
    virtual gbool addAll(Collection<E> const &c) {
        Iterator2<E> &it = this->iterator2();
        gbool ok = false;
        while (it.hasNext()) {
            ok = true;
            add(it.next());
        }
        return ok;
    }

    /**
     * Remove first occurrence of specified object from this collection
     * \param obj object to be removed
     */
    virtual gbool remove(E const &obj) {
        throw StateError("Remove Operation is not supported by this collection");
    };

    /**
     * Remove all of element of this collection that are contained in specified collection
     * \param c collection containing elements to remove from this collection
     */
    virtual gbool removeAll(Collection<E> const &c) {
        Iterator2<E> &it = this->iterator2();
        gbool ok = false;
        while (it.hasNext()) {
            if (c.contains(it.next())) {
                it.remove();
                ok = true;
            }
        }
        return ok;
    };

    /**
     * Remove all elements of this collection that satisfy the giving predicate
     * \param p the predicate
     */
    virtual gbool removeIf(Predicate<E const &> const &p) {
        Iterator2<E> &it = this->iterator2();
        gbool ok = false;
        while (it.hasNext()) {
            if (p.test(it.next())) {
                it.remove();
                ok = true;
            }
        }
        return ok;
    };

    /**
     * Return true if this collection contains specified value
     * \param obj object to search
     */
    virtual gbool contains(E const &obj) const {
        Iterator2<E> &it = this->iterator2();
        while (it.hasNext())
            if (obj.equals(it.next()))
                return true;
        return false;
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
        Iterator2<E> &it = c.iterator2();
        gbool ok = false;
        while (it.hasNext()) {
            if (contains(it.next())) {
                it.remove();
                ok = true;
            }
        }
        return ok;
    }

    /**
     * Remove all element from this collection that are not contained into specified collection
     * \param c collection containing element to not remove
     */
    virtual gbool retainAll(Collection<E> const &c) {
        Iterator2<E> &it = this->iterator2();
        gbool ok = false;
        while (it.hasNext()) {
            if (!c.contains(it.next())) {
                it.remove();
                ok = true;
            }
        }
        return ok;
    };

    /**
     * Remove all of element from this collection
     */
    virtual void clear() {
        Iterator2<E> &it = this->iterator2();
        while (it.hasNext()) {
            it.next();
            it.remove();
        }
    }

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

    String toString() const override {
        if (isEmpty())
            return "[]";
        String string = "[";
        Iterator2<E> &it = this->iterator2();
        while (it.hasNext()) {
            string += it.next().toString();
            if (it.hasNext())
                string += ", ";
        }
        string += "]";
        return string;
    }
};

#if __cpp_deduction_guides > 201565
Collection()->Collection<Object>;

template<class E>
Collection(Collection<E> const &) -> Collection<E>;

#endif//

#endif//CORE_COLLECTION_H

//
// Created by brunshweeck on 14/03/2023.
//

#ifndef CORE_SET_H
#define CORE_SET_H


#include "Collection.h"

template<class E>
class Set : public Collection<E> {
public:
    gbool add(const E &obj) override {
        throw StateError("Unsupported operation");
    }

    gbool addAll(const Collection<E> &c) override {
        return Collection<E>::addAll(c);
    }

    gbool remove(const E &obj) override {
        return Collection<E>::remove(obj);
    }

    gbool removeAll(const Collection<E> &c) override {
        return Collection<E>::removeAll(c);
    }

    gbool removeIf(const Predicate<const E &> &p) override {
        return Collection<E>::removeIf(p);
    }

    gbool contains(const E &obj) const override {
        return Collection<E>::contains(obj);
    }

    gbool containsAll(const Collection<E> &c) const override {
        return Collection<E>::containsAll(c);
    }

    gbool retainAll(const Collection<E> &c) override {
        return Collection<E>::retainAll(c);
    }

    void clear() override {
        Collection<E>::clear();
    }

    gbool isEmpty() const override {
        return Collection<E>::isEmpty();
    }

    gint size() const override = 0;

    void forEach(const Consumer<const E &> &action) const override {
        Collection<E>::forEach(action);
    }

    String toString() const override {
        return Collection<E>::toString();
    }

    virtual /**
     * Return temporal set containing intersection of this instance with specified set
     * \param set
     */
    Set &interSet(Set const &set) const {
        throw StateError("Unsupported operation");
    };
};

#if __cpp_deduction_guides > 201565

Set() -> Set<Object>;

template<class E>
Set(Collection<E> const &) -> Set<E>;

#endif

#endif //CORE_SET_H

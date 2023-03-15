//
// Created by brunshweeck on 10/03/2023.
//

#ifndef CORE_LIST_H
#define CORE_LIST_H

#include "Collection.h"

template<class E>
class List : public Collection<E> {
public:
    CORE_TEMPLATE_REQUIREMENT(E)

    gbool add(const E &obj) override = 0;

    template<class U, class _U = E, Class<gbool>::Require<Class<_U>::isAbstract()> = true, CORE_TEMPLATE_REQUIRE_PRIMITIVE(E, U, _E,)>
    gbool add(U &&v) {
        return add(_E((U &&) v));
    }

    /**
     * Inserts the specified element at the specified position in this list
     * \param index index at which the specified element is to be inserted
     * \param obj element to be inserted
     */
    virtual void add(gint index, const E &obj) = 0;

    template<class U, class _U = E, Class<gbool>::Require<Class<_U>::isAbstract()> = true, CORE_TEMPLATE_REQUIRE_PRIMITIVE(E, U, _E,)>
    void add(gint index, U &&v) {
        add(index, _E((U &&) v));
    }

    gbool addAll(const Collection<E> &c) override {
        return addAll(size(), c);
    }

    /**
     * Inserts all of the elements in the specified collection into this list at the specified position
     * \param index index at which to insert the first element from the specified collection
     * \param c collection containing elements to be added to this list
     */
    virtual gbool addAll(gint index, Collection<E> const &c) = 0;

    gbool remove(const E &obj) override = 0;

    template<class U, class _U = E, Class<gbool>::Require<Class<_U>::isAbstract()> = true, CORE_TEMPLATE_REQUIRE_PRIMITIVE(E, U, _E,)>
    gbool remove(U &&v) {
        return remove(_E((U &&) v));
    }

    /**
     * Removes the element at the specified position in this list if and only if this element equals to specified value.
     * \param index the position if element to be removed
     * \param obj object to be removed
     */
    virtual gbool remove(gint index, const E &obj) = 0;

    template<class U, class _U = E, Class<gbool>::Require<Class<_U>::isAbstract()> = true, CORE_TEMPLATE_REQUIRE_PRIMITIVE(E, U, _E,)>
    gbool remove(gint index, U &&v) {
        return remove(index, _E((U &&) v));
    }

    /**
     * Removes the element at the specified position in this list.
     * \param index the position if element to be removed
     */
    virtual E &removeAt(gint index) = 0;

    virtual gbool removeAll(const Collection<E> &c) override {
        return Collection<E>::removeAll(c);
    }

    template<class _E, Class<gbool>::Require<Class<E>::template isSuper<_E>()> = true>
    gbool removeAll(Collection<_E> const &c) {
        return Collection<E>::retainAll(c);
    }

    gbool removeIf(const Predicate<const E &> &p) override = 0;

    gbool contains(const E &obj) const override {
        return Collection<E>::contains(obj);
    }

    template<class U, class _U = E, Class<gbool>::Require<Class<_U>::isAbstract()> = true, CORE_TEMPLATE_REQUIRE_PRIMITIVE(E, U, _E,)>
    gbool contains(U &&v) const {
        return contains(_E((U &&) v));
    }

    virtual gbool containsAll(const Collection<E> &c) const override {
        return Collection<E>::containsAll(c);
    }

    template<class _E, Class<gbool>::Require<Class<E>::template isSuper<_E>()> = true>
    gbool containsAll(Collection<_E> const &c) const {
        return Collection<E>::containsAll(c);
    }

    virtual gbool retainAll(const Collection<E> &c) override {
        return Collection<E>::retainAll(c);
    }

    template<class _E, Class<gbool>::Require<Class<E>::template isSuper<_E>()> = true>
    gbool retainAll(Collection<_E> const &c) {
        return Collection<E>::retainAll(c);
    }

    void clear() override = 0;

    gbool isEmpty() const override {
        return Collection<E>::isEmpty();
    }

    gint size() const override = 0;

    void forEach(Consumer<E const &> const &action) const override = 0;

    virtual void forEach(Consumer<E &> const &action) = 0;

    /**
     * Returns the element at the specified position in this list.
     * \param index the position of element to return
     * \throw IndexError if index out of range
     */
    virtual E &get(gint index) = 0;

    /**
     * Returns the element at the specified position in this list.
     * \param index the position of element to return
     * \throw IndexError if index out of range
     */
    virtual E const &get(gint index) const = 0;

    /**
     * Set element value at the specified position
     * \param index
     * \param obj
     */
    virtual E const &set(gint index, E const &obj) = 0;

    template<class U, class _U = E, Class<gbool>::Require<Class<_U>::isAbstract()> = true, CORE_TEMPLATE_REQUIRE_PRIMITIVE(E, U, _E,)>
    void set(gint index, U &&v) {
        set(index, _E((U &&) v));
    }

    /**
     * Returns the position of the first occurrence of the specified element in this list,
     * or -1 if this list does not contain the element.
     * \param obj element to search
     */
    virtual gint indexOf(E const &obj) const = 0;

    template<class U, class _U = E, Class<gbool>::Require<Class<_U>::isAbstract()> = true, CORE_TEMPLATE_REQUIRE_PRIMITIVE(E, U, _E,)>
    gint indexOf(U &&v) const {
        return indexOf(_E((U &&) v));
    }

    /**
     * Returns the position of the last occurrence of the specified element in this list,
     * or -1 if this list does not contain the element.
     * \param obj element to search
     */
    virtual gint lastIndexOf(E const &obj) const = 0;

    template<class U, class _U = E, Class<gbool>::Require<Class<_U>::isAbstract()> = true, CORE_TEMPLATE_REQUIRE_PRIMITIVE(E, U, _E,)>
    gint lastIndexOf(U &&v) const {
        return lastIndexOf(_E((U &&) v));
    }

    /**
     * Returns the element at the specified position in this list.
     * \param index the position of element to return
     * \throw IndexError if index out of range
     */
    virtual E const &operator[](gint index) const {
        return get(index);
    }

    /**
     * Returns the element at the specified position in this list.
     * \param index the position of element to return
     * \throw IndexError if index out of range
     */
    virtual E &operator[](gint index) {
        return get(index);
    }

    String toString() const override {
        if (isEmpty())
            return "[]";
        String s = "[";
        gint i = 0;
        gint limit = size();
        forEach([&s, &i, limit](E const &obj) -> void {
            i = i + 1;
            if (i < limit) {
                s += obj.toString() + ", ";
            } else {
                s += obj.toString() + "]";
            }
        });
        return s;
    }
};

#if __cpp_deduction_guides > 201565
List() -> List<Object>;
template<class E> List(Collection<E> const &) -> List<E>;
#endif //

#endif //CORE_LIST_H

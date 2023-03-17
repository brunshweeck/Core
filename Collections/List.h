//
// Created by brunshweeck on 10/03/2023.
//

#ifndef CORE_LIST_H
#define CORE_LIST_H

#include "Collection.h"

template<class E>
class List : public Collection<E>, public Iterable2<E> {
public:
    CORE_TEMPLATE_REQUIREMENT(E)

    /**
     * Append specified object from the this list
     * \param obj object to be add from this collection
     */
    gbool add(const E &obj) override = 0;

    /**
     * Inserts the specified element at the specified position in this list
     * \param index index at which the specified element is to be inserted
     * \param obj element to be inserted
     */
    virtual void add(gint index, const E &obj) = 0;

    /**
     * Add all of element of specified collection from the this list
     * \param c collection containing elements to add from this list
     */
    gbool addAll(const Collection<E> &c) override {
        return addAll(size(), c);
    }

    /**
     * Inserts all of the elements in the specified collection into this list at the specified position
     * \param index index at which to insert the first element from the specified collection
     * \param c collection containing elements to be added to this list
     */
    virtual gbool addAll(gint index, Collection<E> const &c) = 0;

    /**
     * Remove first occurrence of specified object from this list
     * \param obj object to be removed
     */
    gbool remove(const E &obj) override = 0;

    /**
     * Removes the element at the specified position in this list if and only if this element equals to specified value.
     * \param index the position if element to be removed
     * \param obj object to be removed
     */
    virtual gbool remove(gint index, const E &obj) = 0;

    /**
     * Removes the element at the specified position in this list.
     * \param index the position if element to be removed
     */
    virtual E &removeAt(gint index) = 0;

    /**
     * Remove all of element of this list that are contained in specified collection
     * \param c collection containing elements to remove from this collection
     */
    gbool removeAll(const Collection<E> &c) override {
        return Collection<E>::removeAll(c);
    }

    /**
     * Remove all elements of this collection that satisfy the giving predicate
     * \param p The filter
     */
    gbool removeIf(const Predicate<const E &> &p) override {
        return Collection<E>::removeIf(p);
    }

    /**
     * Return true if this list contains specified value
     * \param obj object to search
     */
    gbool contains(const E &obj) const override {
        return Collection<E>::contains(obj);
    }

    /**
     * Return true if all of element of specified collection are contained into this list
     * \param c collection containing element to search
     */
    gbool containsAll(const Collection<E> &c) const override {
        return Collection<E>::containsAll(c);
    }

    /**
     * Remove all element from this list that are not contained into specified collection
     * \param c collection containing element to not remove
     */
    gbool retainAll(const Collection<E> &c) override {
        return Collection<E>::retainAll(c);
    }

    /**
     * Remove all of element from this collection
     */
    void clear() override = 0;

    /**
     * Return true if list have not element
     */
    gbool isEmpty() const override {
        return Collection<E>::isEmpty();
    }

    /**
     * Return number of element from this list
     */
    gint size() const override = 0;

    /**
     * Performed action to each all of element of this collection
     * \param action performed action
     */
    void forEach(const Consumer<const E &> &action) const override {
        Collection<E>::forEach(action);
    }

    /**
     * Performed action to each all of element of this collection
     * \param action performed action
     */
    void forEach(const Consumer<E &> &action) override {
        Iterable2<E>::forEach(action);
    }

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
    virtual E& set(gint index, E const &obj) = 0;

    /**
     * Returns the position of the first occurrence of the specified element in this list,
     * or -1 if this list does not contain the element.
     * \param obj element to search
     */
    virtual gint indexOf(E const &obj) const = 0;

    /**
     * Returns the position of the last occurrence of the specified element in this list,
     * or -1 if this list does not contain the element.
     * \param obj element to search
     */
    virtual gint lastIndexOf(E const &obj) const = 0;

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

    /**
     * Return string representation of this object
     */
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

    /**
     * Returns an iterator over elements of type
     */
    Iterator<const E> &&iterator() const override = 0;

    /**
     * Returns an iterator over elements of type
     */
    virtual Iterator<E> &&iterator() = 0;

    /**
     * Return true if this list equals to specified object
     * \param obj object to be compared
     */
    gbool equals(const Object &obj) const override = 0;

    /**
     * Return copy of this object
     */
    Object &clone() const override = 0;

protected:
    void set(const Object &obj) override {}
};

#if __cpp_deduction_guides > 201565
List() -> List<Object>;
template<class E> List(Collection<E> const &) -> List<E>;
#endif //

#endif //CORE_LIST_H

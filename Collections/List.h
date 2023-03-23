//
// Created by brunshweeck on 10/03/2023.
//

#ifndef CORE_LIST_H
#define CORE_LIST_H

#include "Collection.h"
#include "ListIterator.h"

template<class E>
class List : public Collection<E>, public Iterable<E> {
public:
    CORE_TEMPLATE_REQUIREMENT(E)

    /**
     * Append specified object from the this list
     * \param obj object to be add from this collection
     */
    gbool add(const E &obj) override {
        gint index = this->size();
        add(index, obj);
        return true;
    }

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
        gint index = this->size();
        return addAll(index, c);
    }

    /**
     * Inserts all of the elements in the specified collection into this list at the specified position
     * \param index index at which to insert the first element from the specified collection
     * \param c collection containing elements to be added to this list
     */
    virtual gbool addAll(gint index, Collection<E> const &c) = 0;

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
     * Replace element value at the specified position with specified object
     * \param index the position of element
     * \param obj
     */
    virtual E &set(gint index, E const &obj) = 0;

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
     * Returns an iterator over elements of type
     */
    ListIterator2<E> &iterator2() override = 0;

    /**
     * Returns an iterator over elements of type
     */
    ListIterator2<E> &iterator2() const override = 0;

    /**
     * Returns an iterator over elements of type
     */
    virtual ListIterator<E> &iterator() = 0;

    virtual ListIterator2<E> &begin() const {
        return this->iterator2();
    }
    
    virtual ListIterator<E> &begin() {
        return this->iterator();
    }
};

#if __cpp_deduction_guides > 201565

List()->List<Object>;

template<class E>
List(Collection<E> const &) -> List<E>;

#endif//

#endif//CORE_LIST_H

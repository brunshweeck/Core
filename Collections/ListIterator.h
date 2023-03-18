//
// Created by brunshweeck on 17/03/2023.
//

#ifndef CORE_LISTITERATOR_H
#define CORE_LISTITERATOR_H


#include "Iterator.h"

template<class E>
class ListIterator : public Iterator<E> {
public:
    /**
     * Returns true if this list iterator has more elements when
     * traversing the list in the forward direction. (In other words,
     * returns true} if next() would return an element rather
     * than throwing an exception.)
     */
    gbool hasNext() const override = 0;


    /**
     * Returns the next element in the list and advances the cursor position.
     * This method may be called repeatedly to iterate through the list,
     * or intermixed with calls to previous() to go back and forth.
     * \throw StateError if the iteration has no next element
     */
    E &next() override = 0;

    /**
     * Returns true if this list iterator has more elements when
     * traversing the list in the reverse direction.  (In other words,
     * returns true if previous() would return an element
     * rather than throwing an exception.)
     */
    virtual gbool hasPrevious() const = 0;

    /**
     * Returns the previous element in the list and moves the cursor
     * position backwards.  This method may be called repeatedly to
     * iterate through the list backwards, or intermixed with calls to
     * next() to go back and forth.
     * \throw StateError if the iteration has no next element
     */
    virtual E &previous() = 0;

    /**
     * Returns the index of the element that would be returned by a
     * subsequent call to next. (Returns list size if the list
     * iterator is at the end of the list.)
     */
    virtual gint nextIndex() = 0;

    /**
     * Returns the index of the element that would be returned by a
     * subsequent call to previous. (Returns -1 if the list
     * iterator is at the beginning of the list.)
     */
    virtual gint previousIndex() = 0;

    /**
     * Removes from the list the last element that was returned by next() or previous().
     * \throw StateError If the remove operation not supported by this list iterator
     */
    void remove() override {
        Iterator<E>::remove();
    }

    /**
     * Replaces the last element returned by next() or
     * previous() with the specified element
     * \param obj the element with which to replace the last element returned by next() or previous()
     * \throw StateError If method add is not supported by this list iterator
     */
    virtual void set(E const &obj) = 0;

    /**
     * Inserts the specified element into the list.
     * The element is inserted immediately before the element that
     * would be returned by next(), if any, and after the element
     * that would be returned by previous(), if any.  (If the
     * list contains no elements, the new element becomes the sole element
     * on the list.)
     * \param obj object to insert
     * \throw StateError If method add is not supported by this list iterator
     */
    virtual void add(E const &obj) = 0;

    gbool equals(const Object &obj) const override = 0;

    Object &clone() const override = 0;

    void forEach(const Consumer<E &> &action) const override {
        Iterator<E>::forEach(action);
    }
};


#endif //CORE_LISTITERATOR_H

//
// Created by brunshweeck on 2023/3/12.
//

#ifndef CORE_LINKEDLIST_H
#define CORE_LINKEDLIST_H


#include "List.h"
#include "../String.h"
#include "../IndexError.h"
#include "../MemoryError.h"

/**
 * Doubly linked-list
 * \tparam E linked-list element type
 */
template<class E>
class LinkedList : public List<E> {
private:
    CORE_TEMPLATE_REQUIREMENT(E)

    class Node;

    using Element = typename Class<Node>::Pointer;

    /**
     * Tree structure used by doubly linked-list
     */
    class Node final {
    public:
        E &item;
        Element prev, next;

        CORE_EXPLICIT Node(E &item, Element prev, Element next) : item(item), prev(prev), next(next) {}
    };

    /**
     * Class used to construct list items
     * \tparam U class of current object
     */
    template<class U = E, gbool = Class<U>::isAbstract() || !Class<U>::template isConstruct<U const &>()>
    class ElementCreator;

    template<class U>
    class ElementCreator<U, true> {
    public:
        static U &newInstance(U const &obj) {
            try { return (U &) ((Object &) obj).clone(); } catch (std::bad_alloc const &) { throw MemoryError(); }
        }
    };

    template<class U>
    class ElementCreator<U, false> {
    public:
        static U &newInstance(U const &obj) {
            try { return *new U(obj); } catch (std::bad_alloc const &) { throw MemoryError(); }
        }
    };

    /**
     * First and last element of list
     */
    Element first = nullptr;
    /**
     * Last element of list
     */
    Element last = nullptr;

    /**
     * Size of list
     */
    gint len = 0;

    Element checkElement(gint index) const {
        gint limit = size();
        if (index <= limit / 2) {
            Element element = first;
            for (gint i = 0; i < index; ++i)
                element = element->next;
            return element;
        } else {
            Element element = last;
            for (gint i = limit - 1; i > index; --i)
                element = element->prev;
            return element;
        }
    }

    static void checkIndex(gint index, gint size) {
        if (index < 0 || index >= size)
            throw IndexError(index);
    }

    void linkFirst(E &item) {
        try {
            Element element = new Node(item, nullptr, first);
            (first == nullptr ? last : first->prev) = element;
            first = element;
            len += 1;
        } catch (...) {
            throw MemoryError();
        }
    }

    void linkLast(E &item) {
        try {
            Element element = new Node(item, last, nullptr);
            (last == nullptr ? first : last->next) = element;
            last = element;
            len += 1;
        } catch (...) {
            throw MemoryError();
        }
    }

    void linkBefore(E &item, Element element) {
        try {
            Element element1 = element->prev;
            Element element2 = new Node(item, element1, element);
            element->prev = element2;
            (element1 == nullptr ? first : element1->next) = element2;
            len += 1;
        } catch (...) {
            throw MemoryError();
        }
    }

    E &unlinkFirst() {
        Element element = first;
        first = first->next;
        element->next = nullptr;
        (first == nullptr ? last : first->prev) = nullptr;
        len -= 1;
        E &item = element->item;
        delete element;
        return item;
    }

    E &unlinkLast() {
        Element element = last;
        first = first->prev;
        element->next = nullptr;
        (last == nullptr ? first : last->next) = nullptr;
        len -= 1;
        E &item = element->item;
        delete element;
        return item;
    }

    E &unlink(Element element) {
        Element element1 = element->prev;
        Element element2 = element->next;
        element->next = element->prev = nullptr;
        (element1 == nullptr ? first : element1->next) = element2;
        (element2 == nullptr ? last : element2->prev) = element1;
        len -= 1;
        E &item = element->item;
        delete element;
        return item;
    }

    template<class U, class V>
    void swap(U &u, V &v) {
        U u2 = u;
        u = v;
        v = u2;
    }

public:
    /**
     * Construct new empty list
     */
    LinkedList() = default;

    template<gint S = 1>
    CORE_EXPLICIT LinkedList(E const(&&items)[S]) {
        for (E const &item: items) {
            add(item);
        }
    };

    template<class U, gint S, class _U = E, CORE_TEMPLATE_REQUIRE_PRIMITIVE(E, U, _E,)>
    CORE_EXPLICIT LinkedList(U(&&items)[S]) {
        for (U &item: items) {
            add(item);
        }
    };

    /**
     * Construct new list containing the elements of specified collection
     * in the order they are returned by the collection's iteration
     * \param c the collection whose elements are to be placed into this list
     */
    template<class _E, Class<gbool>::Require<Class<E>::template isSuper<_E>()> = true>
    CORE_EXPLICIT LinkedList(Collection<_E> const &c) {
        LinkedList::addAll(c);
    };

    LinkedList(LinkedList const &linkedList) {
        addAll(linkedList);
    }

    LinkedList(LinkedList &&linkedList) CORE_NOTHROW {
        LinkedList::swap(len, linkedList.len);
        LinkedList::swap(first, linkedList.first);
        LinkedList::swap(last, linkedList.last);
    }

    LinkedList &operator=(LinkedList &&linkedList) CORE_NOTHROW {
        LinkedList::swap(len, linkedList.len);
        LinkedList::swap(first, linkedList.first);
        LinkedList::swap(last, linkedList.last);
        return *this;
    }

    gbool add(const E &obj) override {
        E &copy = ElementCreator<E>::newInstance(obj);
        linkLast(copy);
        return true;
    }

    template<class U, class _U = E, Class<gbool>::Require<Class<_U>::isAbstract()> = true, CORE_TEMPLATE_REQUIRE_PRIMITIVE(
            E, U, _E,)>
    gbool add(U &&v) {
        return add(_E((U &&) v));
    }

    void add(gint index, const E &obj) override {
        checkIndex(index, len + 1);
        E &copy = ElementCreator<E>::newInstance(obj);
        if (index == 0)
            linkFirst(copy);
        else if (index == len)
            linkLast(copy);
        else
            linkBefore(copy, checkElement(index));
    }

    template<class U, class _U = E, Class<gbool>::Require<Class<_U>::isAbstract()> = true, CORE_TEMPLATE_REQUIRE_PRIMITIVE(
            E, U, _E,)>
    void add(gint index, U &&v) {
        add(index, _E((U &&) v));
    }

    gbool addAll(const Collection<E> &c) override {
        if (c.isEmpty())
            return false;
        if (Class<LinkedList>::hasInstance(c)) {
            LinkedList const &linkedList = (LinkedList const &) c;
            Element element = linkedList.first;
            gint limit = linkedList.len;
            for (gint i = 0; i < limit; ++i) {
                E &copy = ElementCreator<E>::newInstance(element->item);
                linkLast(copy);
                element = element->next;
            }
        } else {
            c.forEach([this](E const &item) -> void {
                E &copy = ElementCreator<E>::newInstance(item);
                linkLast(copy);
            });
        }
        return true;
    }

    gbool addAll(gint index, const Collection<E> &c) override {
        checkIndex(index, len + 1);
        if (c.isEmpty())
            return false;
        if (index == len)
            return addAll(c);
        if (Class<LinkedList>::hasInstance(c)) {
            LinkedList const &linkedList = (LinkedList const &) c;
            Element element = linkedList.first;
            Element element1 = checkElement(index);
            gint limit = linkedList.len;
            for (gint i = 0; i < limit; ++i) {
                E &copy = ElementCreator<E>::newInstance(element->item);
                linkBefore(copy, element1);
                element = element->next;
            }
        } else {
            Element element = checkElement(index);
            c.forEach([this, &element](E const &item) -> void {
                E &copy = ElementCreator<E>::newInstance(item);
                linkBefore(copy, element);
            });
        }
        return true;
    }

    gbool remove(const E &obj) override {
        Element element1 = nullptr;
        for (Element element = first; element != nullptr; element = element1)
            if (obj.equals(element->item)) {
                element1 = element->next;
                unlink(element);
                return true;
            }
        return false;
    }

    template<class U, class _U = E, Class<gbool>::Require<Class<_U>::isAbstract()> = true, CORE_TEMPLATE_REQUIRE_PRIMITIVE(
            E, U, _E,)>
    gbool remove(U &&v) {
        return remove(_E((U &&) v));
    }

    gbool remove(gint index, const E &obj) override {
        checkIndex(index, len);
        Element element = checkElement(index);
        if (obj.equals(element->item)) {
            unlink(element);
            return true;
        }
        return false;
    }

    template<class U, class _U = E, Class<gbool>::Require<Class<_U>::isAbstract()> = true, CORE_TEMPLATE_REQUIRE_PRIMITIVE(
            E, U, _E,)>
    gbool remove(gint index, U &&v) {
        return remove(index, _E((U &&) v));
    }

    E &removeAt(gint index) override {
        checkIndex(index, len);
        return unlink(checkElement(index));
    }

    gbool removeAll(const Collection<E> &c) override {
        gint oldSize = size();
        if (this == &c)
            clear();
        else {
            Element element1 = nullptr;
            for (Element element = first; element != nullptr; element = element1)
                if (c.contains(element->item)) {
                    element1 = element->next;
                    unlink(element);
                }
        }
        return oldSize > size();
    }

    gbool removeIf(const Predicate<const E &> &p) override {
        gint oldSize = size();
        Element element1 = nullptr;
        for (Element element = first; element != nullptr; element = element1)
            if (p.test(element->item)) {
                element1 = element->next;
                unlink(element);
            }
        return oldSize > size();
    }

    gbool contains(const E &obj) const override {
        for (Element element = first; element != nullptr; element = element->next)
            if (obj.equals(element->item))
                return true;
        return false;
    }

    template<class U, class _U = E, Class<gbool>::Require<Class<_U>::isAbstract()> = true, CORE_TEMPLATE_REQUIRE_PRIMITIVE(
            E, U, _E,)>
    gbool contains(U &&v) const {
        return contains(_E((U &&) v));
    }

    gbool containsAll(const Collection<E> &c) const override {
        gbool b = false;
        c.forEach([&b, this](E const &item) -> void {
            if (!contains(item)) {
                b = false;
                throw Break();
            } else
                b = true;
        });
        return b;
    }

    gbool retainAll(const Collection<E> &c) override {
        gint oldSize = size();
        Element element1 = nullptr;
        for (Element element = first; element != nullptr; element = element1)
            if (!c.contains(element->item)) {
                element1 = element->next;
                unlink(element);
            }
        return oldSize >= size();
    }

    void clear() override {
        while (first != nullptr)
            unlinkFirst();
    }

    gbool isEmpty() const override {
        return first == nullptr || last == nullptr;
    }

    gint size() const override {
        return len <= 0 ? 0 : len;
    }

    void forEach(const Consumer<const E &> &action) const override {
        gint limit = size();
        for (Element element = first; element != nullptr; element = element->next) {
            action.accept(element->item);
            if (len != size())
                throw MemoryError("Modification during each");
        }
    }

    void forEach(const Consumer<E &> &action) override {
        gint limit = size();
        for (Element element = first; element != nullptr; element = element->next) {
            action.accept(element->item);
            if (len != size())
                throw MemoryError("Modification during each");
        }
    }

    E &get(gint index) override {
        checkIndex(index, len);
        return checkElement(index)->item;
    }

    const E &get(gint index) const override {
        checkIndex(index, len);
        return checkElement(index)->item;
    }

    const E &set(gint index, const E &obj) override {
        return get(index) = obj;
    }

    template<class U, class _U = E, Class<gbool>::Require<Class<_U>::isAbstract()> = true, CORE_TEMPLATE_REQUIRE_PRIMITIVE(
            E, U, _E,)>
    void set(gint index, U &&v) {
        set(index, _E((U &&) v));
    }

    gint indexOf(const E &obj) const override {
        gint index = 0;
        for (Element element = first; element != nullptr; element = element->next) {
            if (obj.equals(element->item))
                return index;
            index = index + 1;
        }
        return -1;
    }

    template<class U, class _U = E, Class<gbool>::Require<Class<_U>::isAbstract()> = true, CORE_TEMPLATE_REQUIRE_PRIMITIVE(
            E, U, _E,)>
    gint indexOf(U &&v) const {
        return indexOf(_E((U &&) v));
    }

    gint lastIndexOf(const E &obj) const override {
        gint index = size() - 1;
        for (Element element = last; element != nullptr; element = element->prev) {
            if (obj.equals(element->item))
                return index;
            index = index - 1;
        }
        return -1;
    }

    template<class U, class _U = E, Class<gbool>::Require<Class<_U>::isAbstract()> = true, CORE_TEMPLATE_REQUIRE_PRIMITIVE(
            E, U, _E,)>
    gint lastIndexOf(U &&v) const {
        return lastIndexOf(_E((U &&) v));
    }

    String toString() const override {
        if (isEmpty())
            return "[]";
        String string = "[";
        for (Element element = last; element != nullptr; element = element->prev) {
            string += element->item.toString();
            if (element != last)
                string += ", ";
        }
        string += "]";
        return string;
    }

    gbool equals(const Object &obj) const override {
        if (this == &obj)
            return true;
        if (!Class<LinkedList>::hasInstance(obj))
            return false;
        LinkedList const &linkedList = (LinkedList const &) obj;
        if (len != linkedList.len)
            return false;
        for (Element element = first, element1 = linkedList.first;
             element != nullptr && element1 != nullptr; element = element->next, element1 = element1->next)
            if (!element->item.equals(element1->item))
                return false;
        return true;
    }

    Object &clone() const override {
        try { return *new LinkedList(*this); } catch (...) { throw MemoryError(); }
    }

    ~LinkedList() override {
        while (first != nullptr)
            unlinkFirst();
        first = last = nullptr;
        len = 0;
    }

protected:
    void set(const Object &obj) override {
        if (!Class<Collection<E>>::hasInstance(obj))
            throw CastError();
        *this = LinkedList((Collection<E> const &) obj);
    }
};

#if __cpp_deduction_guides > 201565
LinkedList() -> LinkedList<Object>;
template<class E> LinkedList(Collection<E> const&) -> LinkedList<E>;
#endif //


#endif //CORE_LINKEDLIST_H

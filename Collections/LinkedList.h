//
// Created by brunshweeck on 2023/3/12.
//

#ifndef CORE_LINKEDLIST_H
#define CORE_LINKEDLIST_H


#include "../IndexError.h"
#include "../MemoryError.h"
#include "../String.h"
#include "List.h"


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
        E *item;
        Element prev = nullptr;
        Element next = nullptr;

        CORE_EXPLICIT Node(E &item, Element prev, Element next) : item(&item), prev(prev), next(next) {}
    };

    /**
     * Class used to construct list items
     * \tparam U class of current object
     */
    template<class U = E, gbool = Class<U>::isAbstract() || !Class<U>::template isConstruct<U const &>()>
    class Maker;

    template<class U>
    class Maker<U, true> {
    public:
        static U &copyOf(U const &obj) {
            try {
                return (U &) ((Object const &) obj).clone();
            } catch (std::bad_alloc const &) { throw MemoryError(); }
        }
    };

    template<class U>
    class Maker<U, false> {
    public:
        static U &copyOf(U const &obj) {
            try {
                return *new U(obj);
            } catch (std::bad_alloc const &) { throw MemoryError(); }
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
        E *item = element->item;
        element->item = nullptr;
        delete element;
        return *item;
    }

    E &unlinkLast() {
        Element element = last;
        first = first->prev;
        element->next = nullptr;
        (last == nullptr ? first : last->next) = nullptr;
        len -= 1;
        E *item = element->item;
        element->item = nullptr;
        delete element;
        return *item;
    }

    E &unlink(Element element) {
        Element element1 = element->prev;
        Element element2 = element->next;
        element->next = element->prev = nullptr;
        (element1 == nullptr ? first : element1->next) = element2;
        (element2 == nullptr ? last : element2->prev) = element1;
        len -= 1;
        E *item = element->item;
        element->item = nullptr;
        delete element;
        return *item;
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
        E &copy = Maker<E>::copyOf(obj);
        linkLast(copy);
        return true;
    }

    void add(gint index, const E &obj) override {
        checkIndex(index, len + 1);
        E &copy = Maker<E>::copyOf(obj);
        if (index == 0)
            linkFirst(copy);
        else if (index == len)
            linkLast(copy);
        else
            linkBefore(copy, checkElement(index));
    }

    gbool addAll(const Collection<E> &c) override {
        gint size = c.size();
        if (size > 0) {
            Iterator2<E> &it = c.iterator2();
            if (Class<List<E>>::hasInstance(c))
                while (it.hasNext() && size > 0) {
                    linkLast((E &) it.next());
                    size -= 1;
                }
            else
                while (it.hasNext() && size > 0) {
                    linkLast(Maker<E>::copyOf(it.next()));
                    size -= 1;
                }
            return true;
        }
        return false;
    }

    gbool addAll(gint index, const Collection<E> &c) override {
        checkIndex(index, len + 1);
        if (c.isEmpty())
            return false;
        if (index == len)
            return addAll(c);
        Element element = checkElement(index);
        if (this == &c) {
            if (index == 0)
                return addAll(c);
            Element prev = element->prev;
            for (Element node = first; node != prev->next; node = node->next)
                linkBefore(*node->item, element);
            for (Element node = element; node != nullptr; node = node->next)
                linkBefore(*node->item, element);
            return true;
        }
        Iterator2<E> &it = c.iterator2();
        if (Class<List<E>>::hasInstance(c))
            while (it.hasNext())
                linkBefore((E &) it.next(), element);
        else
            while (it.hasNext())
                linkBefore(Maker<E>::copyOf(it.next()), element);
        return true;
    }

    gbool remove(const E &obj) override {
        Element element1 = nullptr;
        for (Element element = first; element != nullptr; element = element1)
            if (obj.equals(*element->item)) {
                element1 = element->next;
                unlink(element);
                return true;
            }
        return false;
    }

    gbool remove(gint index, const E &obj) override {
        checkIndex(index, len);
        Element element = checkElement(index);
        if (!obj.equals(*element->item))
            return false;
        unlink(element);
        return true;
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
                if (c.contains(*element->item)) {
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
            if (p.test(*element->item)) {
                element1 = element->next;
                unlink(element);
            }
        return oldSize > size();
    }

    gbool contains(const E &obj) const override {
        for (Element element = first; element != nullptr; element = element->next)
            if (obj.equals(*element->item))
                return true;
        return false;
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
            if (!c.contains(*element->item)) {
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
            action.accept(*element->item);
            if (len != size())
                throw MemoryError("Modification during each");
        }
    }

    void forEach(const Consumer<E &> &action) override {
        gint limit = size();
        for (Element element = first; element != nullptr; element = element->next) {
            action.accept(*element->item);
            if (len != size())
                throw MemoryError("Modification during each");
        }
    }

    E &get(gint index) override {
        checkIndex(index, len);
        return *checkElement(index)->item;
    }

    const E &get(gint index) const override {
        checkIndex(index, len);
        return *checkElement(index)->item;
    }

    E &set(gint index, const E &obj) override {
        return get(index) = obj;
    }

    gint indexOf(const E &obj) const override {
        gint index = 0;
        for (Element element = first; element != nullptr; element = element->next) {
            if (obj.equals(*element->item))
                return index;
            index = index + 1;
        }
        return -1;
    }

    gint lastIndexOf(const E &obj) const override {
        gint index = size() - 1;
        for (Element element = last; element != nullptr; element = element->prev) {
            if (obj.equals(*element->item))
                return index;
            index = index - 1;
        }
        return -1;
    }

    String toString() const override {
        if (isEmpty())
            return "[]";
        String string = "[";
        for (Element element = last; element != nullptr; element = element->prev) {
            string += element->item->toString();
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
            if (!element->item->equals(*element1->item))
                return false;
        return true;
    }

    ListIterator2<E> &iterator2() const override {
        Itr2 it = Itr2((LinkedList<E> &) *this, 0, true);
        return Maker<Itr2>::copyOf(it);
    }

    ListIterator2<E> &iterator2() override {
        Itr2 it = Itr2(*this, 0, false);
        return Maker<Itr2>::copyOf(it);
    }

    ListIterator<E> &iterator() override {
        Itr it = Itr(*this, 0);
        return Maker<Itr>::copyOf(it);
    }

    Object &clone() const override {
        try {
            return *new LinkedList(*this);
        } catch (...) { throw MemoryError(); }
    }

    virtual ~LinkedList() {
        while (first != nullptr)
            unlinkFirst();
        first = last = nullptr;
        len = 0;
    }

private:
    class Itr : public ListIterator<E> {
    public:
        LinkedList<E> &self;
        Element lastReturned = nullptr;
        Element nextElement = nullptr;
        gint index = 0;

        CORE_EXPLICIT Itr(LinkedList<E> &src, gint srcBegin) : self(src), index(srcBegin) {
            nextElement = srcBegin >= self.len ? nullptr : self.checkElement(srcBegin);
        }

        gbool hasNext() const override {
            return index < self.len;
        }

        E &next() override {
            if (!hasNext())
                throw StateError("No such item");
            lastReturned = nextElement;
            nextElement = nextElement->next;
            index += 1;
            return *lastReturned->item;
        }

        gbool hasPrevious() const override {
            return index > 0;
        }

        E &previous() override {
            if (!hasPrevious())
                throw StateError("No such item");
            lastReturned = nextElement = (nextElement == nullptr) ? self.last : nextElement->prev;
            index -= 1;
            return *lastReturned->item;
        }

        gint nextIndex() override {
            return index;
        }

        gint previousIndex() override {
            return index - 1;
        }

        void remove() override {
            if (lastReturned == nullptr)
                throw StateError("No such item");
            Element element = lastReturned->next;
            self.unlink(lastReturned);
            if (lastReturned == nextElement)
                nextElement = element;
            else
                index -= 1;
            lastReturned = nullptr;
        }

        void set(const E &obj) override {
            if (lastReturned == nullptr)
                throw StateError("No such item");
            lastReturned->item = &Maker<E>::copyOf(obj);
        }

        void add(const E &obj) override {
            lastReturned = nullptr;
            if (nextElement == nullptr)
                self.linkLast(Maker<E>::copyOf(obj));
            else
                self.linkBefore(Maker<E>::copyOf(obj), nextElement);
        }

        gbool equals(const Object &obj) const override {
            if (!Object::equals(obj))
                return false;
            if (!Class<Itr>::hasInstance(obj))
                return false;
            Itr const &itr = (Itr const &) obj;
            return &self == &itr.self && index == itr.index;
        }

        void forEach(const Consumer<E &> &action) override {
            for (; index < self.len; index++) {
                action.accept(*nextElement->item);
                lastReturned = nextElement;
                nextElement = nextElement->next;
            }
        }

        Object &clone() const override {
            try {
                return *new Itr(self, index);
            } catch (...) { throw MemoryError(); }
        }
    };

    class Itr2 : public ListIterator2<E> {
    public:
        LinkedList<E> &self;
        Element lastReturned = nullptr;
        Element nextElement = nullptr;
        gint index = 0;
        gbool isReadOnly = false;

        CORE_EXPLICIT Itr2(LinkedList<E> &src, gint srcBegin, gbool isReadOnly) : self(src), index(srcBegin), isReadOnly(isReadOnly) {
            nextElement = srcBegin >= self.len ? nullptr : self.checkElement(srcBegin);
        }

        gbool hasNext() const override {
            return index < self.len;
        }

        E &next() override {
            if (!hasNext())
                throw StateError("No such item");
            lastReturned = nextElement;
            nextElement = nextElement->next;
            index += 1;
            return *lastReturned->item;
        }

        gbool hasPrevious() const override {
            return index > 0;
        }

        E &previous() override {
            if (!hasPrevious())
                throw StateError("No such item");
            lastReturned = nextElement = (nextElement == nullptr) ? self.last : nextElement->prev;
            index -= 1;
            return *lastReturned->item;
        }

        gint nextIndex() const override {
            return index;
        }

        gint previousIndex() const override {
            return index - 1;
        }

        void remove() override {
            if (isReadOnly)
                throw StateError("Add operation is not supported by read-only LinkedList");
            if (lastReturned == nullptr)
                throw StateError("No such item");
            Element element = lastReturned->next;
            self.unlink(lastReturned);
            if (lastReturned == nextElement)
                nextElement = element;
            else
                index -= 1;
            lastReturned = nullptr;
        }

        void set(const E &obj) override {
            if (lastReturned == nullptr)
                throw StateError("No such item");
            lastReturned->item = &Maker<E>::copyOf(obj);
        }

        void add(const E &obj) override {
            if (isReadOnly)
                throw StateError("Remove operation is not supported by read-only LinkedList");
            lastReturned = nullptr;
            if (nextElement == nullptr)
                self.linkLast(Maker<E>::copyOf(obj));
            else
                self.linkBefore(Maker<E>::copyOf(obj), nextElement);
        }

        gbool equals(const Object &obj) const override {
            if (!Object::equals(obj))
                return false;
            if (!Class<Itr>::hasInstance(obj))
                return false;
            Itr const &itr = (Itr const &) obj;
            return &self == &itr.self && index == itr.index;
        }

        void forEach(const Consumer<E const &> &action) override {
            for (; index < self.len; index++) {
                action.accept(*nextElement->item);
                lastReturned = nextElement;
                nextElement = nextElement->next;
            }
        }

        Object &clone() const override {
            try {
                return *new Itr2(self, index, isReadOnly);
            } catch (...) { throw MemoryError(); }
        }
    };

    //
};

#if __cpp_deduction_guides > 201565
LinkedList()->LinkedList<Object>;
template<class E>
LinkedList(Collection<E> const &) -> LinkedList<E>;
#endif//


#endif//CORE_LINKEDLIST_H

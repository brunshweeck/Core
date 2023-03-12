//
// Created by brunshweeck on 10/03/2023.
//

#ifndef CORE_ARRAYLIST_H
#define CORE_ARRAYLIST_H


#include "List.h"
#include "../IndexError.h"
#include "../MemoryError.h"
#include "../Break.h"

template<class E>
class ArrayList : public List<E> {
private:
    using Element = Class<E>::Pointer;

    static Element EMPTY_DATA[0];
    CORE_FAST static gint DEFAULT_CAPACITY = 10;
    static Element UNINITIALIZED;

    Class<Element>::Pointer data = {};

    gint len = 0;

    gint capacity = DEFAULT_CAPACITY;

    template<class U = E, gbool = Class<U>::isAbstract() || !Class<U>::template isConstruct<U const &>()>
    class ElementCreator;

    template<class U>
    class ElementCreator<U, true> {
    public:
        static U &newInstance(U const &obj) {
            return (U &) ((Object &) obj).clone();
        }
    };

    template<class U>
    class ElementCreator<U, false> {
    public:
        static U &newInstance(U const &obj) {
            try {
                return *new U(obj);
            } catch (...) {
                throw MemoryError();
            }
        }
    };

public:
    /**
     *
     */
    ArrayList() : ArrayList(DEFAULT_CAPACITY) {}
    /**
     * Construct new empty list with specified initial capacity
     * \param initialCapacity
     * \throw ValueError if capacity is negative
     */
    CORE_EXPLICIT ArrayList(gint initialCapacity) {
        if (initialCapacity > 0) {
            try {
                data = new Element[initialCapacity];
                capacity = initialCapacity;
                UNINITIALIZED = data[0];
//                fillNull(data, 0, capacity);
            } catch (...) {}
        } else if (initialCapacity == 0) {
            data = EMPTY_DATA;
            capacity = 0;
        } else
            throw ValueError("Negative capacity: " + Integer::toString(initialCapacity));
    }

    /**
     * Construct new list contening the element of specified collection
     * \param
     */
    template<class _E, Class<gbool>::Require<Class<E>::template isSuper<_E>()> = true>
    CORE_EXPLICIT ArrayList(Collection<_E> const &c) {
        if ((capacity = c.size()) > 0) {
            try {
                data = new Element[capacity];
                UNINITIALIZED = data[0];
            } catch (...) {
                throw MemoryError();
            }
            if (Class<ArrayList>::hasInstance(c)) {
                ArrayList<E> const &arrayList = (ArrayList<E> const &) c;
                for (int i = 0; i < arrayList.len; ++i)
                    data[i] = ElementCreator<E>::newInstance(arrayList.get(i));
                len = arrayList.len;
            } else
                c.forEach([this](E const &obj) -> void { add(obj); });
        } else {
            data = EMPTY_DATA;
            capacity = 0;
        }
    }

    gbool add(const E &obj) override {
        if (len == capacity)
            resize();
        data[len] = &ElementCreator<E>::newInstance(obj);
        len = len + 1;
        return true;
    }

    void add(gint index, const E &obj) override {
        checkIndex(index, len + 1);
        if (len == capacity)
            resize();
        arrayCopy(data, index, data, index + 1, len - index);
        data[index] = &ElementCreator<E>::newInstance(obj);
    }

    gbool addAll(const Collection<E> &c) override {
        gint newOffset = c.size();
        if (newOffset == 0)
            return false;
        gint remaining = capacity - len;
        if (newOffset > remaining)
            resize(len + newOffset);
        if (this != &c)
            c.forEach([&](E const &obj) -> void { add(obj); });
        else {
            arrayCopy(data, 0, data, len, len);
            len = len * 2;
        }
        return true;
    }

    gbool addAll(gint index, const Collection<E> &c) override {
        checkIndex(index, len + 1);
        gint newOffset = c.size();
        if (newOffset == 0)
            return false;
        gint remaining = capacity - len;
        if (newOffset > remaining)
            resize(len + newOffset);
        if (this != &c) {
            gint i = 0;
            c.forEach([&i, this](E const &obj) -> void {
                add(i, obj);
                i = i + 1;
            });
        } else {
            if (len > index)
                arrayCopy(data, index, data, index + newOffset, len - index);
            arrayCopy(data, 0, data, index, index);
            arrayCopy(data, index + newOffset, data, index * 2, len - index);
            len = len * 2;
        }
        return true;
    }

    gbool remove(const E &obj) override {
        gint index = indexOf(obj);
        if (index < 0)
            return false;
        removeAt(index);
        return true;
    }

    gbool remove(gint index, const E &obj) override {
        if (0 <= index && index < len)
            if (obj.equals(get(index))) {
                removeAt(index);
                return true;
            }
        return false;
    }

    E &removeAt(gint index) override {
        checkIndex(index, len);
        Element oldValue = data[index];
        arrayCopy(data, index + 1, data, index, len - 1);
        fillNull(data, len = len - 1, 1);
        return *oldValue;
    }

    gbool removeAll(const Collection<E> &c) override {
        if (isEmpty() || c.isEmpty())
            return false;
        if (this == &c) {
            clear();
            return true;
        }
        int i, j;
        for (i = j = 0; i < len; ++i) {
            if (!c.contains(*data[i]))
                data[j++] = data[i];
        }
        fillNull(data, j, len);
        len = j;
        return true;
    }

    gbool removeIf(const Predicate<const E &> &p) override {
        if (isEmpty())
            return false;
        int i, j;
        for (i = j = 0; i < len; ++i) {
            if (!p.test(*data[i]))
                data[j++] = data[i];
        }
        fillNull(data, j, len);
        len = j;
        return true;
    }

    gbool contains(const E &obj) const override {
        return indexOf(obj) >= 0;
    }

    gbool containsAll(const Collection<E> &c) const override {
        gint limit = c.size();
        if (limit == 0)
            return false;
        if (this == &c)
            return true;
        if (Class<ArrayList>::hasInstance(c)) {
            ArrayList<E> const &arrayList = (ArrayList<E> const &) c;
            for (int i = 0; i < limit; ++i) {
                if (!contains(arrayList.get(i)))
                    return false;
            }
            return true;
        }
        c.forEach([&limit, this](E const &obj) -> void {
            if (!contains(obj)) {
                throw Break();
            }
            limit = limit - 1;
        });
        return limit == 0;
    }

    gbool retainAll(const Collection<E> &c) override {
        if (this == &c)
            clear();
        int i, j;
        for (i = j = 0; i < len; ++i) {
            if (c.contains(*data[i]))
                data[j++] = data[i];
        }
        fillNull(data, j, len);
        len = j;
        return true;
    }

    void clear() override {
        fillNull(data, 0, len);
        len = 0;
    }

    gbool isEmpty() const override {
        return List<E>::isEmpty();
    }

    gint size() const override {
        return len;
    }

    void forEach(Consumer<E const &> const &action) const override {
        for (int i = 0, limit = len; i < limit && limit == len; ++i)
            try { action.accept(get(i)); } catch (Break const &) { break; }
    }

    void forEach(const Consumer<E &> &action) override {
        for (int i = 0, limit = len; i < limit && limit == len; ++i)
            try { action.accept(get(i)); } catch (Break const &) { break; }
    }

    E &get(gint index) override {
        checkIndex(index, len);
        return *data[index];
    }

    const E &get(gint index) const override {
        checkIndex(index, len);
        return *data[index];
    }

    const E &set(gint index, const E &obj) override {
        checkIndex(index, len);
        Element oldValue = data[index];
        data[index] = &ElementCreator<E>::newInstance(obj);
        return *oldValue;
    }

    gint indexOf(const E &obj) const override {
        for (int i = 0, limit = len; i < limit; ++i) if (obj.equals(get(i))) return i;
        return -1;
    }

    gint lastIndexOf(const E &obj) const override {
        for (int i = len - 1; i >= 0; --i) if (obj.equals(get(i))) return i;
        return -1;
    }

    String toString() const override {
        if (isEmpty())
            return "[]";
        String s = "[";
        for (int i = 0, limit = len - 1; i <= limit; ++i) {
            Object const &obj = get(i);
            s += i < limit ? obj.toString() + ", " : obj.toString() + "]";
        }
        return s;
    }

    gbool equals(const Object &obj) const override {
        if (this == &obj)
            return true;
        if (!dynamic_cast<ArrayList const *>(&obj))
            return false;
        ArrayList<E> const &arrayList = (ArrayList<E> const &) obj;
        if (len != arrayList.len)
            return false;
        return containsAll(arrayList);
    }

    Object &clone() const override {
        try { return *new ArrayList(*this); } catch (...) { throw MemoryError(); }
    }

    ~ArrayList() override {
        fillNull(data, 0, capacity);
        delete[] data;
        len = 0;
        data = EMPTY_DATA;
    };

private:
    static gint newLength(gint oldLength, gint minOffset, gint prefOffset) {
        gint prefLength = oldLength + (minOffset < prefOffset ? prefOffset : minOffset);
        if (0 <= prefLength && prefLength <= Integer::MAX - 8)
            return prefLength;
        else {
            gint minLength = oldLength + minOffset;
            if (minLength < 0)
                throw MemoryError();
            else if (minLength < Integer::MAX - 8)
                return minLength;
            else
                return minLength;
        }
    }

    void resize(gint minCapacity) {
        if (capacity >= 0 && data != EMPTY_DATA) {
            gint newCapacity = newLength(capacity, minCapacity - capacity, capacity >> 1);
            Element *obj = new Element[newCapacity];
            arrayCopy(data, 0, obj, 0, len);
            fillNull(data, 0, len);
            UNINITIALIZED = obj[0];
//            fillNull(obj, len, newCapacity);
            delete[] data;
            data = obj;
            capacity = newCapacity;
        } else {
            gint newCapacity = minCapacity < 10 ? 10 : minCapacity;
            Element *obj = new Element[newCapacity];
            fillNull(data, 0, newCapacity);
            UNINITIALIZED = obj[0];
            delete[] data;
            data = obj;
            capacity = newCapacity;
        }
    }

    void resize() {
        resize(len + 1);
    }

    template<class U, class V>
    static void arrayCopy(U const src[], gint srcBegin, V dst[], gint dstBegin, gint length) {
        for (int i = 0; i < length; ++i)
            dst[i + dstBegin] = src[i + srcBegin];
    }

    template<class U>
    static void fillNull(U src[], gint srcBegin, gint length) {
        for (int i = 0; i < length; ++i)
            src[i + srcBegin] = UNINITIALIZED;
    }

    static void checkIndex(gint index, gint size) {
        if (index < 0 || index >= size)
            throw IndexError(index);
    }
};

template<class E>
ArrayList<E>::Element ArrayList<E>::EMPTY_DATA[0] = {};

template<class E>
ArrayList<E>::Element ArrayList<E>::UNINITIALIZED = {};

#endif //CORE_ARRAYLIST_H

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
    using Element = typename Class<E>::Pointer;

    CORE_FAST static gint DEFAULT_CAPACITY = 10;

    Element UNINITIALIZED = nullptr;

    typename Class<Element>::Pointer data = {};

    gint len = 0;

    gint capacity = DEFAULT_CAPACITY;

    template<class U = E, gbool = Class<U>::isAbstract() || !Class<U>::template isConstruct<U const &>()>
    class Maker;

    template<class U>
    class Maker<U, true> {
    public:
        static U &copyOf(U const &obj) {
            return (U &) ((Object &) obj).clone();
        }
    };

    template<class U>
    class Maker<U, false> {
    public:
        static U &copyOf(U const &obj) {
            try {
                return *new U(obj);
            } catch (...) {
                throw MemoryError();
            }
        }
    };

    template<class T, class U>
    static void swap(T &t, U &u) {
        T t2 = t;
        t = u;
        u = t2;
    }

    template<class T, class U>
    static void copy(T src, gint srcBegin, U dst, gint dstBegin, gint length) {
        for (int i = 0; i < length; ++i)
            dst[i + dstBegin] = src[i + srcBegin];
    }

public:
    /**
     * Construct new empty Array list
     */
    ArrayList() : ArrayList(DEFAULT_CAPACITY) {}
    /**
     * Construct new empty list with specified initial capacity
     * \param initialCapacity
     * \throw ValueError if capacity is negative
     */
    CORE_EXPLICIT ArrayList(gint initialCapacity) {
        if (initialCapacity > 0)
            try {
                data = new Element[initialCapacity];
                capacity = initialCapacity;
                UNINITIALIZED = data[0];
            } catch (...) {
                throw MemoryError();
            }
        else if (initialCapacity == 0)
            capacity = 0;
        else
            throw ValueError("Negative capacity: " + Integer::toString(initialCapacity));
    }

    CORE_EXPLICIT ArrayList(Collection<E> const &c) : ArrayList() {
        addAll(c);
    }

    /**
     * Construct new Array list with element of specified array list
     */
    ArrayList(ArrayList const &a) : ArrayList() {
        addAll(a);
    }

    ArrayList(ArrayList &&a) CORE_NOTHROW {
        swap(data, a.data);
        swap(len, a.len);
        swap(capacity, a.capacity);
        swap(UNINITIALIZED, a.UNINITIALIZED);
    }

    ArrayList &operator=(ArrayList const &a) {
        if (this != &a) {
            clear();
            addAll(a);
        }
        return *this;
    }

    ArrayList &operator=(ArrayList &&a) CORE_NOTHROW {
        if (this != &a) {
            swap(data, a.data);
            swap(len, a.len);
            swap(capacity, a.capacity);
            swap(UNINITIALIZED, a.UNINITIALIZED);
        }
        return *this;
    }

    gbool add(const E &obj) override {
        if (len == capacity)
            resize();
        data[len] = &Maker<E>::copyOf(obj);
        len = len + 1;
        return true;
    }

    void add(gint index, const E &obj) override {
        checkIndex(index, len + 1);
        if (len == capacity)
            resize();
        arrayCopy(data, index, data, index + 1, len - index);
        data[index] = &Maker<E>::copyOf(obj);
    }

    gbool addAll(const Collection<E> &c) override {
        gint newOffset = c.size();
        if (newOffset == 0)
            return false;
        gint remaining = capacity - len;
        if (newOffset > remaining)
            resize(len + newOffset);
        if (Class<ArrayList>::hasInstance(c)) {
            ArrayList const &a = (ArrayList const &) c;
            copy(a.data, 0, data, len, a.len);
            len += a.len;
        } else {
            Iterator<E const> &&it = c.iterator();
            if (Class<List<E>>::hasInstance(c))
                while (it.hasNext()) {
                    data[len] = (Element) &it.next();
                    len += 1;
                }
            else
                while (it.hasNext()) {
                    data[len] = &Maker<E>::copyOf(it.next());
                    len += 1;
                }
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
        if (len > index)
            copy(data, index, data, index + len, len - index);
        if (this == &c) {
            copy(data, 0, data, index, index);
            copy(data, index + len, data, index * 2, len - index);
            len = len * 2;
        } else if (Class<ArrayList>::hasInstance(c)) {
            ArrayList const &a = (ArrayList const &) c;
            copy(a.data, 0, data, index, a.len);
            len += a.len;
        } else {
            Iterator<E const> &&it = c.iterator();
            if (Class<List<E>>::hasInstance(c))
                while (it.hasNext()) {
                    data[index] = (Element) &it.next();
                    index += 1;
                }
            else
                while (it.hasNext()) {
                    data[index] = &Maker<E>::copyOf(it.next());
                    index += 1;
                }
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
        copy(data, index + 1, data, index, len - 1);
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
        gint i, j;
        for (i = j = 0; i < len; ++i)
            if (!c.contains(*data[i])) {
                data[j] = data[i];
                j += 1;
            }
        fillNull(data, j, i - j);
        len = j;
        return true;
    }

    gbool removeIf(const Predicate<const E &> &p) override {
        if (isEmpty())
            return false;
        gint i, j;
        for (i = j = 0; i < len; ++i)
            if (!p.test(*data[i])) {
                data[j] = data[i];
                j += 1;
            }
        fillNull(data, j, i - j);
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
            for (gint i = 0; i < limit; ++i)
                if (!contains(arrayList.get(i)))
                    return false;
            return true;
        }
        return List<E>::containsAll(c);
    }

    gbool retainAll(const Collection<E> &c) override {
        gint i, j;
        for (i = j = 0; i < len; ++i)
            if (c.contains(*data[i])) {
                data[j] = data[i];
                j += 1;
            }
        fillNull(data, j, i - j);
        len = j;
        return i > j;
    }

    void clear() override {
        fillNull(data, 0, len);
        len = 0;
    }

    gbool isEmpty() const override {
        return len == 0 || data == nullptr;
    }

    gint size() const override {
        return data == nullptr || len < 0 ? 0 : len;
    }

    void forEach(Consumer<E const &> const &action) const override {
        for (gint i = 0, limit = len; i < limit && limit == len; ++i)
            try { action.accept(get(i)); } catch (Break const &) { break; }
    }

    void forEach(const Consumer<E &> &action) override {
        for (gint i = 0, limit = len; i < limit && limit == len; ++i)
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
        data[index] = &Maker<E>::copyOf(obj);
        return *oldValue;
    }

    gint indexOf(const E &obj) const override {
        for (gint i = 0, limit = len; i < limit; ++i) if (obj.equals(get(i))) return i;
        return -1;
    }

    gint lastIndexOf(const E &obj) const override {
        for (gint i = len - 1; i >= 0; --i) if (obj.equals(get(i))) return i;
        return -1;
    }

    String toString() const override {
        if (isEmpty())
            return "[]";
        String s = "[";
        for (gint i = 0, limit = len - 1; i <= limit; ++i) {
            Object const &obj = get(i);
            s += obj.toString();
            if (i < limit)
                s += ", ";
        }
        s += "]";
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
        data = nullptr;
    };
private:
    template<class U>
    class Itr: public Iterator<U> {
        gint nextIndex;
        gint lastReturned = -1;
        friend ArrayList;

    };

public:
    Iterator<const E> &&iterator() const override {
        return Itr<E const>((ArrayList<E> &) *this);
    }

    Iterator<E> &&iterator() override {
        return Itr<E>(*this);
    }

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
        if (capacity > 0 && data != nullptr) {
            gint newCapacity = newLength(capacity, minCapacity - capacity, capacity >> 1);
            Element *obj = new Element[newCapacity];
            arrayCopy(data, 0, obj, 0, len);
            fillNull(data, 0, len);
            UNINITIALIZED = obj[0];
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

    template<class U>
    void fillNull(U src[], gint srcBegin, gint length) {
        for (gint i = 0; i < length; ++i)
            src[i + srcBegin] = UNINITIALIZED;
    }

    static void checkIndex(gint index, gint size) {
        if (index < 0 || index >= size)
            throw IndexError(index);
    }
};

#if __cpp_deduction_guides > 201565
ArrayList() -> ArrayList<Object>;
ArrayList(gint) -> ArrayList<Object>;
template<class E> ArrayList(Collection<E> const &) -> ArrayList<E>;
#endif //

#endif //CORE_ARRAYLIST_H

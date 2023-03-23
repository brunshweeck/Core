//
// Created by brunshweeck on 20/03/2023.
//

#ifndef CORE_HASHMAP_H
#define CORE_HASHMAP_H

#include "Map.h"
#include "../Hashable.h"

template<class K, class V>
class HashMap : public Map<K, V> {
private:
    /**
     * The default initial capacity
     */
    CORE_FAST static gint DEFAULT_CAPACITY = 1 << 4;

    /**
     * The maximum capacity
     */
    CORE_FAST static gint MAX_CAPACITY = 1 << 30;

    /**
     * The load factor
     */
    CORE_FAST static gfloat FACTOR = 0.75f;

    template<class _K, class _V>
    using AbstractEntry = typename Map<_K, _V>::Entry;

    class Entry;

    using Node = typename Class<Entry>::Pointer;

    template<class T, gbool = Class<T>::isAbstract() || !Class<T>::template isConstruct<T const &>()>
    class Maker;

    template<class T>
    class Maker<T, true> {
    public:
        static T &copyOf(T const &obj) {
            return (T &) obj.clone();
        }
    };

    template<class T>
    class Maker<T, false> {
    public:
        static T &copyOf(T const &obj) {
            if (Object::isPerfectlyInstanceOf<T>(obj))
                try { return *new T(obj); } catch (std::bad_alloc const &) { throw MemoryError(); }
            else {
                Object const &o = obj;
                return (T &) o.clone();
            }
        }
    };

    class Entry : public AbstractEntry<K, V> {
    public:
        gint const _hash;
        K const &_key;
        V *_value;
        Node next;

        /**
         * Construct new Map entry
         */
        Entry(const gint hash, const K &key, V &value, Node next) :
                _hash(hash), _key(key), _value(&value), next(next) {}

        const K &key() const override {
            return _key;
        }

        const V &value() const override {
            return *_value;
        }

        V &value() override {
            return *_value;
        }

        V &setValue(const V &value) override {
            if (_value == &value)
                return value();
            V &oldValue = *_value;
            _value = &Maker<V>::copyOf(value);
            return oldValue;
        }

        Object &clone() const override {
            try { return *new Entry(_hash, _key, *_value, next); } catch (...) { throw MemoryError(); }
        }
    };

    static gint hash(Hashable const &obj) {
        gint h;
        return (h = (gint) obj.hash()) ^ (h >> 0x10);
    }

    Node table[];

public:
};


#endif //CORE_HASHMAP_H

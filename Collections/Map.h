//
// Created by brunshweeck on 15/03/2023.
//

#ifndef CORE_MAP_H
#define CORE_MAP_H


#include "../Object.h"
#include "Iterator.h"
#include "../Function/BiConsumer.h"
#include "Collection.h"
#include "Set.h"

template<class K, class V>
class Map : public Object {
public:
    /**
     * Associates the specified value with the specified key in this map.
     * If the map previously contained a mapping for the old value is replaced by the specified value.
     * \param key key with which the specified value is to be associated
     * \param value value to be associated with the specified key
     * \return the previous value associated with key or current value if if there was no mapping for key.
     */
    virtual V &add(K const &key, V const &value) = 0;

    /**
     * Copies all of the mappings from the specified map to this map
     * \param m mappings to be stored in this map
     * \throw CastError if the class of a key or value in the specified
     * map prevents it from being stored in this map
     */
    virtual void addAll(Map<K, V> const &m) {
        Iterator<Entry const> &&it = m.iterator();
        while (it.hasNext()) {
            Entry const &entry = it.next();
            add(entry.key(), entry.value());
        }
    }

    /**
     * Removes the mapping for a key from this map if it is present.
     * \param key key whose mapping is to be removed from the map
     * \return the previous value associated with key
     * \throw KeyError if there was no mapping for key
     */
    virtual V &remove(K const &key) = 0;

    /**
     * Removes the entry for the specified key only if it is currently
     * mapped to the specified value.
     * \param key key with which the specified value is associated
     * \param value value expected to be associated with the specified key
     */
    virtual gbool remove(K const &key, V const &value) = 0;

    /**
     * Returns a Set view of the keys contained in this map.
     * The set is backed by the map, so changes to the map are reflected in the set, and vice-versa.
     */
    virtual Set<K> &&keys() const = 0;

    /**
     * Returns a Collection view of the values contained in this map.
     * The collection is backed by the map, so changes to the map are reflected in the collection, and vice-versa.
     */
    virtual Collection<V> &&values() const = 0;

    /**
     * A map entry (key-value pair). The Entry may be unmodifiable, or the
     * value may be modifiable
     */
    class Entry : public Object {
    public:
        /**
         * Return key of this entry
         */
        virtual K const &key() = 0;

        /**
         * Return value of this entry
         */
        virtual V const &value() const = 0;

        /**
         * Return value of this entry
         */
        virtual V &value() = 0;

        /**
         * Set entry value
         * \param value new value
         * \return old entry value
         */
        virtual V &setValue(V const &value) = 0;

        /**
         * Compares the specified object with this entry for equality.
         * \param obj object to be compared
         */
        gbool equals(const Object &obj) const override {
            if (this == &obj)
                return true;
            if (!Class<Entry>::hasInstance(obj))
                return false;
            Entry const &entry = (Entry const &) obj;
            if (!key().equals(entry.key()))
                return false;
            return value().equals(entry.value());
        }

        /**
         * Return copy of this entry
         */
        Object &clone() const override = 0;

        /**
         * Return string representation of this entry
         */
        String toString() const override {
            return key() + ": " + value();
        }
    };

    /**
     * Returns a Set view of the mappings contained in this map.
     * The set is backed by the map, so changes to the map are reflected in the set, and vice-versa.
     */
    virtual Set<Map<K, V>::Entry> &&entries() const = 0;

    /**
     * Compares the specified object with this map for equality.
     * \param obj object to be compared
     */
    gbool equals(const Object &obj) const override = 0;

    /**
     * Returns the value to which the specified key is mapped
     * \param key the key whose associated value is to be returned
     * \throw KeyError If specified key is not mapped
     */
    virtual V const &get(K const &key) const = 0;

    /**
     * Returns the value to which the specified key is mapped
     * \param key the key whose associated value is to be returned
     * \throw KeyError If specified key is not mapped
     */
    virtual V &get(K const &key) = 0;

    /**
     * Returns the value to which the specified key is mapped,
     * or defaultValue if this map contains no mapping for the key.
     * \param key the key whose associated value is to be returned
     * \param defaultValue the default mapping of the key
     */
    virtual V const &getOrDefault(K const &key, V const &defaultValue) const {
        if (containsKey(key))
            return get(key);
        return defaultValue;
    };

    /**
     * Returns the value to which the specified key is mapped,
     * or defaultValue if this map contains no mapping for the key.
     * \param key the key whose associated value is to be returned
     * \param defaultValue the default mapping of the key
     */
    virtual V &getOrDefault(K const &key, V &defaultValue) {
        if (containsKey(key))
            return get(key);
        return defaultValue;
    }

    /**
     * Performs the given action for each entry in this map until all entries
     * \param action The action to be performed for each entry
     */
    virtual void forEach(BiConsumer<K const &, V const &> const &action) const {
        Iterator<Entry const> &&it = iterator();
        while (it.hasNext()) {
            Entry const &entry = it.next();
            action.accept(entry.key(), entry.value());
        }
    };

    /**
     * Performs the given action for each entry in this map until all entries
     * \param action The action to be performed for each entry
     */
    virtual void forEach(BiConsumer<K const &, V &> const &action) {
        Iterator<Entry> &&it = iterator();
        while (it.hasNext()) {
            Entry &entry = it.next();
            action.accept(entry.key(), entry.value());
        }
    };

    /**
     * Return true if specified key is mapped
     * \param key key to be search
     */
    virtual gbool containsKey(K const &key) const = 0;

    /**
     * Return true if this map contains specified value
     * \param value value to be search
     */
    virtual gbool containsValue(V const &value) const = 0;

    /**
     * Return true if this map has no entry
     */
    virtual gbool isEmpty() const {
        return size() == 0;
    }

    /**
     * Return number of entry in this map
     */
    virtual gint size() const = 0;

    /**
     * Return true if this map contains specified value associated with specified key
     * \param key key to be search
     * \param value value to be search
     */
    virtual gbool containsValue(K const &key, V const &value) const {
        if (!containsKey(key))
            return false;
        return get(key).equals(value);
    }

    /**
     * Return string representation of this map
     */
    String toString() const override = 0;

    virtual Iterator<Entry const> &&iterator() const = 0;

    virtual Iterator<Entry> &&iterator() = 0;

    virtual void clear() {
        Iterator<Entry const> &&it = iterator();
        while (it.hasNext()) {
            it.next();
            it.remove();
        }
    }

    /**
     * Returns the value to which the specified key is mapped
     * \throw KeyError If specified key is not mapped
     */
    V const &operator[](K const &key) const {
        return get(key);
    }

    /**
     * Returns the value to which the specified key is mapped
     * \throw KeyError If specified key is not mapped
     */
    V &operator[](K const &key) {
        return get(key);
    }
};


#endif //CORE_MAP_H

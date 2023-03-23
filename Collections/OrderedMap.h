//
// Created by brunshweeck on 15/03/2023.
//

#ifndef CORE_ORDERED_MAP_H
#define CORE_ORDERED_MAP_H

#include "Map.h"
#include "../Function/Comparator.h"

template<class K, class V>
class OrderedMap: public Map<K, V> {
public:
    /**
     * Return key comparator of this map
     */
    virtual Comparator<K> const& comparator() const = 0;

    /**
     * Returns a Set view of the keys contained in this map.
     * The set is backed by the map, so changes to the map are reflected in the set, and vice-versa.
     */
    Set<K> &keys() const override = 0;

    /**
     * Returns a Collection view of the values contained in this map.
     * The collection is backed by the map, so changes to the map are reflected in the collection, and vice-versa.
     */
    Collection<V> &values() const override= 0;

    /**
     * Returns a Set view of the mappings contained in this map.
     * The set is backed by the map, so changes to the map are reflected in the set, and vice-versa.
     */
    Set<typename Map<K, V>::Entry> &entries() const override = 0;
};

#if __cpp_deduction_guides > 201565
OrderedMap() -> OrderedMap<Object, Object>;

template<class K, class V>
OrderedMap(Map<K, V> const&) -> OrderedMap<K, V>;

#endif //

#endif //CORE_ORDERED_MAP_H

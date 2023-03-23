//
// Created by brunshweeck on 15/03/2023.
//

#ifndef CORE_NATURAL_ORDER_COMPARATOR_H
#define CORE_NATURAL_ORDER_COMPARATOR_H


#include "Comparator.h"
#include "../Comparable.h"

template<class T>
class NaturalOrderComparator final : public Comparator<T> {
private:
    CORE_TEMPLATE_REQUIREMENT(T)
    CORE_REQUIRE(Class<Comparable<T>>::template isSuper<T>(), "Natural ordering require comparable type");

    CORE_FAST NaturalOrderComparator() = default;

public:
    gint compare(const T &obj1, const T &obj2) const override {
        return obj1.compareTo(obj2);
    }

    gbool equals(const Object &obj) const override {
        if (this == &obj)
            return true;
        return Class<NaturalOrderComparator<T>>::hasInstance(obj);
    }

    Comparator<T> &reverse() const override {
        class ReverseOrderComparator final : public Comparator<T> {
        public:
            CORE_FAST ReverseOrderComparator() = default;

            gint compare(const T &obj1, const T &obj2) const override {
                return NaturalOrderComparator<T>::INSTANCE.compare(obj2, obj1);
            }

            gbool equals(const Object &obj) const override {
                if (this == &obj)
                    return true;
                return Class<ReverseOrderComparator>::hasInstance(obj);
            }

            Comparator<T> &reverse() const override {
                return NaturalOrderComparator<T>::INSTANCE;
            }

            Object &clone() const override {
                return (Object &) *this;
            }
        };

        static ReverseOrderComparator REVERSE_ORDER = {};
        return REVERSE_ORDER;
    }

    Object &clone() const override {
        return INSTANCE;
    }

    String toString() const override {
        return Object::toString();
    }

    static NaturalOrderComparator INSTANCE;
};

template<class T>
NaturalOrderComparator<T> NaturalOrderComparator<T>::INSTANCE = {};


#endif //CORE_NATURAL_ORDER_COMPARATOR_H

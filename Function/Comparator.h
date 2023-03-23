//
// Created by brunshweeck on 15/03/2023.
//

#ifndef CORE_COMPARATOR_H
#define CORE_COMPARATOR_H

#include "../MemoryError.h"

/**
 * A comparison function, which imposes a total ordering on some collection of objects.
 * \tparam T the type of objects that may be compared by this comparator
 */
template<class T>
class Comparator : public Object {
public:
    CORE_TEMPLATE_REQUIREMENT(T)

    /**
     * Compares its two arguments for order. Returns a negative integer,
     * zero, or a positive integer as the first argument is less than, equal
     * to, or greater than the second.
     * \param obj1 the first object to be compared.
     * \param obj2 the second object to be compared.
     */
    virtual gint compare(T const &obj1, T const &obj2) const = 0;

    /**
     * Indicates whether some other object is equal to this comparator.
     * \param obj object to be compared
     */
    gbool equals(const Object &obj) const override {
        return Object::equals(obj);
    }

    /**
     * Returns a comparator that imposes the reverse ordering of this comparator
     */
    virtual Comparator<T> &reverse() const {
        class ReverseComparator : public Comparator<T> {
        private:
            Comparator<T> const &self;
        public:
            CORE_EXPLICIT ReverseComparator(const Comparator<T> &self) : self(self) {}

            gint compare(const T &obj1, const T &obj2) const override {
                return self.compare(obj2, obj1);
            }

            gbool equals(const Object &obj) const override {
                if (this == &obj)
                    return false;
                if (!Class<ReverseComparator>::hasInstance(obj))
                    return false;
                ReverseComparator const &_ = (ReverseComparator const &) obj;
                return self.equals(_.self);
            }

            Comparator<T> &reverse() const override {
                return (Comparator<T> &) self.clone();
            }

            Object &clone() const override {
                try { return *new ReverseComparator(self); } catch (...) { throw MemoryError(); }
            }
        };
    }

    /**
     * Returns a lexicographic-order comparator with another comparator.
     * If this Comparator considers two elements equal, i.e. compare(a, b) == 0,
     * other is used to determine the order.
     */
    virtual Comparator<T> &then(Comparator<T> const &c) const {
        class DoublyComparator : public Comparator<T> {
        private:
            Comparator<T> const &self;
            Comparator<T> const &other;
        public:
            CORE_EXPLICIT DoublyComparator(const Comparator<T> &self, const Comparator<T> &other) : self(self),
                                                                                                    other(other) {}

            gint compare(const T &obj1, const T &obj2) const override {
                gint ret = self.compare(obj1, obj2);
                return ret != 0 ? ret : other.compare(obj1, obj2);
            }

            gbool equals(const Object &obj) const override {
                if (this == &obj)
                    return true;
                if (!Class<DoublyComparator>::hasInstance(obj))
                    return false;
                DoublyComparator const &_ = (DoublyComparator const &) obj;
                if (!self.equals(_.self))
                    return false;
                return other.equals(_.other);
            }

            Object &clone() const override {
                try { return *new DoublyComparator(self, other); } catch (...) { throw MemoryError(); }
            }
        };

        try { return *new DoublyComparator(*this, c); } catch (...) { throw MemoryError(); }
    }

};

#if __cpp_deduction_guides > 201565
Comparator() -> Comparator<Object>;

template<class T>
Comparator(Comparator<T> const&) -> Comparator<T>;

#endif //

#endif //CORE_COMPARATOR_H

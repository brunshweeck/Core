//
// Created by brunshweeck on 15/03/2023.
//

#ifndef CORE_BICONSUMER_H
#define CORE_BICONSUMER_H

#include "../CastError.h"
#include "../Long.h"
#include "../MemoryError.h"
#include "../ValueError.h"
#include "BiFunctional.h"


/**
 * Binary Consumer
 */
template<class T, class U>
class BiConsumer : public Object, public BiFunctional<T, U, Void> {
public:
    /**
     * Construct new empty Binary Consumer
     */
    CORE_EXPLICIT BiConsumer() = default;

    /**
     * Construct new Binary Consumer with binary function
     * \param biFunc binary function
     * \throw ValueError If specified action function is null
     */
    template<class _BiFunc,
             Class<gbool>::Require<Class<_BiFunc>::isFunction() && Class<_BiFunc>::template isCallable<T, U>()> = true>
    CORE_IMPLICIT BiConsumer(_BiFunc &&biFunc) : manager(nullptr) {
        CORE_REQUIRE(!Class<_BiFunc>::isMember(), "Binary Function must be used with binary class member");
        if (biFunc == nullptr)
            throw ValueError("Illegal action");
        try {
            manager = new BiFunctionManager<_BiFunc>((_BiFunc &&) biFunc);
        } catch (...) { throw MemoryError(); }
    }

    /**
     * Construct new Binary Consumer with binary function member
     * \param biFunc binary function
     * \param target function member caller
     */
    template<class _BiFunc, class Target,
             Class<gbool>::Require<
                     Class<_BiFunc>::isMember() && Class<_BiFunc>::template isCallable<Target, T, U>()> = true>
    CORE_EXPLICIT BiConsumer(_BiFunc &&biFunc, Target &&target) : manager(nullptr) {
        try {
            manager = new BiMethodManager<_BiFunc, Target>((_BiFunc &&) biFunc, (Target &&) target);
        } catch (...) { throw MemoryError(); }
    }

    template<class _1, class _2, class _3, class _4, class _5, class _6 = T, class _7 = U>
    CORE_EXPLICIT BiConsumer(_1 (_2::*biFunc)(_3, _4), _5 &&target) {
        using _BiFunc = decltype(biFunc);
        using Target = decltype(target);
        CORE_FAST gbool requirement = Class<_BiFunc>::template isCallable<Target, T, U>();
        CORE_REQUIRE(requirement, "Support Binary Function Member");
        try {
            manager = new BiMethodManager<_BiFunc, Target>((_BiFunc &&) biFunc, (_5 &&) target);
        } catch (...) { throw MemoryError(); }
    }

    /**
     * Construct new Binary Consumer with binary object function
     * \param biFunc binary function
     */
    template<class _BiFunc,
             Class<gbool>::Require<Class<_BiFunc>::isClass() && !Class<Object>::isSuper<_BiFunc>() &&
                                   Class<_BiFunc>::template isCallable<T, U>()> = true>
    CORE_IMPLICIT BiConsumer(_BiFunc &&biFunc) : manager(nullptr) {
        try {
            manager = new BiLambdaManager<_BiFunc>((_BiFunc &&) biFunc);
        } catch (...) { throw MemoryError(); }
    }

    /**
     * Construct new Binary Consumer with action of other Consumer
     * \param c binary consumer
     */
    CORE_IMPLICIT BiConsumer(BiConsumer const &c) : manager(nullptr) {
        manager = &(c.manager == nullptr || c.manager == &EMPTY ? EMPTY : (BiManager &) c.manager->clone());
    }

    /**
     * Construct new Binary Consumer with action of other Consumer
     * \param c binary consumer
     */
    CORE_IMPLICIT BiConsumer(BiConsumer &&c) CORE_NOTHROW : manager(nullptr) {
        manager = c.manager == nullptr || c.manager == &EMPTY ? &EMPTY : c.manager;
        c.manager = &EMPTY;
    }

    BiConsumer &operator=(BiConsumer const &c) {
        if (this != &c && manager != c.manager) {
            if (manager != nullptr && manager != &EMPTY) {
                delete manager;
                manager = &EMPTY;
            }
            manager = &(c.manager == nullptr || c.manager == &EMPTY ? EMPTY : (BiManager &) c.manager->clone());
        }
        return *this;
    }

    BiConsumer &operator=(BiConsumer &&c) CORE_NOTHROW {
        if (this != &c && manager != c.manager) {
            typename Class<BiManager>::Pointer old = manager;
            manager = c.manager;
            c.manager = old;
        }
        return *this;
    }

    /**
     * Accept specified arguments parameters and launch action
     * \param t first argument
     * \param u second argument
     */
    virtual void accept(T t, U u) const {
        if (manager != nullptr && manager != &EMPTY)
            manager->launch(t, u);
    }

    /**
     * Invoke consumer action as function
     */
    void operator()(T t, U u) const override {
        return accept(t, u);
    }

    gbool equals(const Object &obj) const override {
        if (this == &obj)
            return true;
        if (!Class<BiConsumer>::hasInstance(obj))
            return false;
        BiConsumer const &c = (BiConsumer const &) obj;
        if (manager == nullptr || manager == &EMPTY)
            return c.manager == nullptr || c.manager == &EMPTY;
        if (c.manager == nullptr || c.manager == &EMPTY)
            return false;
        return manager->equals(*c.manager);
    }

    Object &clone() const override {
        try {
            return *new BiConsumer(*this);
        } catch (...) { throw MemoryError(); }
    }

    virtual ~BiConsumer() {
        if (manager != nullptr && manager != &EMPTY) {
            delete manager;
            manager = nullptr;
        }
    }

    String toString() const override {
        if (manager == nullptr || manager == &EMPTY)
            return "<BiConsumer>";
        return "<BiConsumer" + manager->toString() + ">";
    }

private:
    class BiManager : public Object {
    public:
        virtual void launch(T t, U u) const { /* ... */
        }

        gbool equals(const Object &obj) const override {
            if (this == &obj)
                return true;
            if (!Class<BiManager>::hasInstance(obj))
                return false;
            return true;
        }

        Object &clone() const override {
            return EMPTY;
        }

        String toString() const override {
            return "[?]";
        }
    };

    template<class _BiFunc>
    class BiFunctionManager : public BiManager {
    public:
        CORE_EXPLICIT BiFunctionManager(_BiFunc &&func) : func((_BiFunc &&) func) {}

        void launch(T t, U u) const override {
            return func(t, u);
        }

        gbool equals(const Object &obj) const override {
            if (!BiManager::equals(obj))
                return false;
            if (!Class<BiFunctionManager>::hasInstance(obj))
                return false;
            BiFunctionManager const &m = (BiFunctionManager const &) obj;
            return func == m.func;
        }

        Object &clone() const override {
            try {
                return *new BiFunctionManager(*this);
            } catch (...) { throw MemoryError(); }
        }

        String toString() const override {
            return "[action: func@" + Long::toHexString((glong) func) + "]";
        }

    private:
        _BiFunc func;
    };

    template<class _BiFunc, class Target>
    class BiMethodManager : public BiManager {
    public:
        CORE_EXPLICIT BiMethodManager(_BiFunc &&func, Target &&target) : func((_BiFunc &&) func),
                                                                         target((Target &&) target) {}

        void launch(T t, U u) const override {
            return (target.*func)(t, u);
        }

        gbool equals(const Object &obj) const override {
            if (!BiManager::equals(obj))
                return false;
            if (!Class<BiMethodManager>::hasInstance(obj))
                return false;
            BiMethodManager const &m = (BiMethodManager const &) obj;
            return func == m.func;
        }

        Object &clone() const override {
            try {
                return *new BiMethodManager(*this);
            } catch (...) { throw MemoryError(); }
        }

        String toString() const override {
            return "[action: object@" + Long::toHexString((glong)&target) + " - method$" + Long::toHexString((glong) &func) +
                   "]";
        }

    private:
        _BiFunc func;
        Target target;
    };

    template<class _BiFunc>
    class BiLambdaManager : public BiManager {
    public:
        CORE_EXPLICIT BiLambdaManager(_BiFunc &&func) : func((_BiFunc &&) func) {}

        void launch(T t, U u) const override {
            return func(t, u);
        }

        gbool equals(const Object &obj) const override {
            if (!BiManager::equals(obj))
                return false;
            if (!Class<BiLambdaManager>::hasInstance(obj))
                return false;
            BiLambdaManager const &m = (BiLambdaManager const &) obj;
            return &func == &m.func;
        }

        Object &clone() const override {
            try {
                return *new BiLambdaManager(*this);
            } catch (...) { throw MemoryError(); }
        }

        String toString() const override {
            return (!Class<typename Class<_BiFunc>::NIVR>::template isConstruct<_BiFunc>() ? "[action: lambda$" : "[action: object@") + Long::toHexString((glong) &func) + "]";
        }

    private:
        _BiFunc func;
    };

    static BiManager EMPTY;
    typename Class<BiManager>::Pointer manager = &EMPTY;
};

#if __cpp_deduction_guides > 201565
BiConsumer()->BiConsumer<Object, Object>;

template<class T, class U, class R>
BiConsumer(BiFunctional<T, U, R> const &) -> BiConsumer<T, U>;


template<class T, class U>
BiConsumer(BiConsumer<T, U> const &) -> BiConsumer<T, U>;

template<class T, class U>
BiConsumer(BiConsumer<T, U> &&) -> BiConsumer<T, U>;

template<class T, class U, class R>
BiConsumer(R (*)(T, U)) -> BiConsumer<
        typename Class<T>::template Conditional<Class<Object>::template isSuper<T>(), typename Class<T>::Object>,
        typename Class<U>::template Conditional<Class<Object>::template isSuper<U>(), typename Class<U>::Object>>;

template<class T, class U, class R, class V, class W>
BiConsumer(R (V::*)(T, U), W &&) -> BiConsumer<
        typename Class<T>::template Conditional<Class<Object>::template isSuper<T>(), typename Class<T>::Object>,
        typename Class<U>::template Conditional<Class<Object>::template isSuper<U>(), typename Class<U>::Object>>;

#endif//

template<class T, class U>
typename BiConsumer<T, U>::BiManager BiConsumer<T, U>::EMPTY = {};


#endif//CORE_BICONSUMER_H

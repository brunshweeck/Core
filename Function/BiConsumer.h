//
// Created by brunshweeck on 15/03/2023.
//

#ifndef CORE_BICONSUMER_H
#define CORE_BICONSUMER_H

#include "../Object.h"
#include "BiFunctional.h"
#include "../MemoryError.h"
#include "../CastError.h"
#include "../Long.h"
#include "../ValueError.h"

/**
 * Binary Consumer
 */
template<class T, class U>
class BiConsumer : public Object, public BiFunctional<T, U> {
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
    CORE_IMPLICIT BiConsumer(_BiFunc &&biFunc): manager(nullptr) {
        CORE_REQUIRE(!Class<_BiFunc>::isMember(), "Binary Function must be used with binary class member");
        if (biFunc == nullptr)
            throw ValueError("Illegal action");
        try { manager = new BiFunctionManager<_BiFunc>((_BiFunc &&) biFunc); } catch (...) { throw MemoryError(); }
    }

    /**
     * Construct new Binary Consumer with binary function member
     * \param biFunc binary function
     * \param target function member caller
     */
    template<class _BiFunc, class Target,
            Class<gbool>::Require<
                    Class<_BiFunc>::isMember() && Class<_BiFunc>::template isCallable<Target, T, U>()> = true>
    CORE_EXPLICIT BiConsumer(_BiFunc &&biFunc, Target &&target): manager(nullptr) {
        try { manager = new BiMethodManager<_BiFunc, Target>((_BiFunc &&) biFunc, (Target &&) target); }
        catch (...) { throw MemoryError(); }
    }

    /**
     * Construct new Binary Consumer with binary object function
     * \param biFunc binary function
     */
    template<class _BiFunc,
            Class<gbool>::Require<Class<_BiFunc>::isClass() && !Class<Object>::isSuper<_BiFunc>() &&
                                  Class<_BiFunc>::template isCallable<T, U>()> = true>
    CORE_IMPLICIT BiConsumer(_BiFunc &&biFunc): manager(nullptr) {
        try { manager = new BiLambdaManager<_BiFunc>((_BiFunc &&) biFunc); } catch (...) { throw MemoryError(); }
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
    CORE_IMPLICIT BiConsumer(BiConsumer &&c) CORE_NOTHROW: manager(nullptr) {
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
        try { return *new BiConsumer(*this); } catch (...) { throw MemoryError(); }
    }

    ~BiConsumer() override = default;

    String toString() const override {
        if (manager == nullptr || manager == &EMPTY)
            return "<BiConsumer[?]>";
        return "<BiConsumer" + manager->toString() + ">";
    }

private:
    class BiManager : public Object {
    public:
        virtual void launch(T t, U u) const {}

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
            try { return *new BiFunctionManager(*this); } catch (...) { throw MemoryError(); }
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
            try { return *new BiMethodManager(*this); } catch (...) { throw MemoryError(); }
        }

        String toString() const override {
            return "[action: object@" + Long::toHexString(&target) + " - method$" + Long::toHexString((glong) &func) +
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
            try { return *new BiLambdaManager(*this); } catch (...) { throw MemoryError(); }
        }

        String toString() const override {
            return (!Class<typename Class<_BiFunc>::NIVR>::template isConstruct<_BiFunc>() ?
                    "[action: lambda$" : "[action: object@") + Long::toHexString((glong) &func) + "]";
        }

    private:
        _BiFunc func;
    };

    static BiManager EMPTY;
    typename Class<BiManager>::Pointer manager;

};

template<class T, class U>
typename BiConsumer<T, U>::BiManager BiConsumer<T, U>::EMPTY = {};


#endif //CORE_BICONSUMER_H

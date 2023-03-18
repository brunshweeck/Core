//
// Created by brunshweeck on 07/03/2023.
//

#ifndef CORE_CONSUMER_H
#define CORE_CONSUMER_H

#include "../Object.h"
#include "Functional.h"
#include "../ValueError.h"
#include "../MemoryError.h"
#include "../CastError.h"
#include "../Long.h"

template<class T>
class Consumer : public Object, public Functional<T, Void> {
public:
    /**
     * Construct new empty Consumer
     */
    CORE_EXPLICIT Consumer() = default;

    /**
     * Construct new Consumer with function like action
     * \param func function
     * \throw ValueError if action function is null
     */
    template<class _Func,
            Class<gbool>::Require<Class<_Func>::isFunction() && Class<_Func>::template isCallable<T>()> = true>
    CORE_IMPLICIT Consumer(_Func &&func): manager(nullptr) {
        if (!func)
            throw ValueError("Invalid function");
        try {
            manager = new FunctionManager<_Func>((_Func &&) func);
        } catch (...) {
            throw MemoryError();
        }
    }

    /**
     * Construct new Consumer with function member like action and target object
     * \param func function member
     * \param target function member caller
     */
    template<class _Func, class Target,
            Class<gbool>::Require<Class<_Func>::isMember() && Class<_Func>::template isCallable<Target, T>()> = true>
    CORE_EXPLICIT Consumer(_Func &&func, Target &&target): manager(nullptr) {
        try {
            manager = new MethodManager<_Func, Target>((_Func &&) func, (Target &&) target);
        } catch (...) {
            throw MemoryError();
        }
    }

    /**
     * Construct new Consumer with callable object (lambda function) as action
     * \param func lambda function
     */
    template<class _Func,
            Class<gbool>::Require<Class<_Func>::isClass() &&
                                  !Class<Object>::isSuper<_Func>() &&
                                  Class<_Func>::template isCallable<T>()> = true>
    CORE_IMPLICIT Consumer(_Func &&func): manager(nullptr) {
        try {
            manager = new LambdaManager<_Func>((_Func &&) func);
        } catch (...) {
            throw MemoryError();
        }
    }

    /**
     * Construct new consumer with action of other consumer
     * \param c consumer
     */
    CORE_IMPLICIT Consumer(Consumer<T> const &c) : manager(nullptr) {
        if (!c.manager || c.manager == &EMPTY)
            manager = &EMPTY;
        else
            manager = &(Manager &) c.manager->clone();
    }

    /**
     * Construct new consumer with action of other consumer
     * \param c consumer
     */
    CORE_IMPLICIT Consumer(Consumer<T> &&c) CORE_NOTHROW: manager(nullptr) {
        manager = c.manager;
        c.manager = &EMPTY;
    }

    /**
     * Construct new consumer with action of other consumer
     * \param c consumer
     */
    template<class _T,
            Class<gbool>::Require<Class<_T>::template isSuper<T>()> = true>
    CORE_IMPLICIT Consumer(Consumer<_T> const &c): manager(nullptr) {
        if (!c.manager || &c == &Consumer<_T>::EMPTY_ACTION)
            manager = &EMPTY;
        else if (c.manager->isEmpty() || c.manager == &EMPTY)
            manager = &EMPTY;
        else
            manager = &(Manager &) c.manager->clone();
    }

    /**
     * Set consumer action with action of other consumer
     * \throw c consumer
     */
    Consumer &operator=(Consumer<T> const &c) {
        if (this != &c) {
            if (manager != &EMPTY)
                delete manager;
            manager = &(Manager &) c.manager->clone();
        }
        return *this;
    }

    /**
     * Set consumer action with action of other consumer
     * \throw c consumer
     */
    Consumer &operator=(Consumer<T> &&c) CORE_NOTHROW {
        typename Class<Manager>::Pointer old = manager;
        manager = c.manager;
        c.manager = old;
        return *this;
    }

    /**
     * Set consumer action with action of other consumer
     * \throw c consumer
     */
    template<class _T,
            Class<gbool>::Require<Class<_T>::template isSuper<T>()> = true>
    Consumer &operator=(Consumer<_T> const &c) {
        if (this != &c) {
            if (manager != &EMPTY)
                delete manager;
            manager = &(Manager &) c.manager->clone();
        }
        return *this;
    }

    /**
     * Accept specified argument parameter and launch action
     * \param t argument
     */
    virtual void accept(T t) const {
        if (manager && manager != &EMPTY) {
            manager->launch(t);
        }
    }

    /**
     * Invoke consumer action as function
     */
    void operator()(T t) const override {
        return accept(t);
    }

    /**
     * Return true if this consumer equals perfectly to specified object
     * \param obj object to be compared
     */
    gbool equals(const Object &obj) const override {
        if (this == &obj)
            return true;
        if (!Class<Consumer>::hasInstance(obj))
            return false;
        Consumer<T> const &c = (Consumer<T> const &) obj;
        if (c.manager == nullptr || c.manager == &EMPTY)
            return manager == nullptr || manager == &EMPTY;
        if (manager == nullptr || manager == &EMPTY)
            return c.manager == nullptr || c.manager == &EMPTY;
        return manager->equals(*c.manager);
    }

    /**
     * Return copy of this consumer
     */
    Object &clone() const override {
        try { return *new Consumer<T>(*this); } catch (...) { throw MemoryError(); }
    }

    /**
     * Return string representation of this consumer
     * \return consumer{action: ...}
     */
    String toString() const override {
        if (!manager == nullptr || manager == &EMPTY)
            return u"consumer" + EMPTY.toString();
        return u"consumer" + manager->toString();
    }

private:
    class Manager : public Object {
    public:
        virtual void launch(T t) const {}

        String toString() const override {
            return u"{action: EMPTY}";
        }

        gbool equals(Object const &obj) const override {
            if (this == &obj)
                return true;
            if (!Class<Manager>::hasInstance(obj))
                return false;
            return true;
        }

        Object &clone() const override {
            return EMPTY;
        }
    };

    template<class _Func>
    class FunctionManager final : public Manager {
    public:
        CORE_EXPLICIT FunctionManager(_Func &&func) : func((_Func &&) func) {}

        void launch(T t) const override {
            func(t);
        }

        String toString() const override {
            return u"{action: func@" + Long::toUnsignedString((glong) func, 16) + "}";
        }

        gbool equals(const Object &obj) const override {
            if (Manager::equals(obj)) {
                FunctionManager const &manager1 = (FunctionManager const &) obj;
                return manager1.func == func;
            }
            return false;
        }

        Object &clone() const override {
            try { return *new FunctionManager(func); } catch (...) { throw MemoryError(); }
        }

    private:
        _Func func;
    };

    template<class _Func, class Target>
    class MethodManager final : public Manager {
    public:
        CORE_EXPLICIT MethodManager(_Func &&func, Target &&target) :
                func((_Func &&) func), target((Target &&) target) {}

        void launch(T t) const override {
            (target.*func)(t);
        }

        String toString() const override {
            return u"{action: object@" + Long::toUnsignedString((glong) &target, 16) + u"- method@" +
                   Long::toUnsignedString((glong) &func, 16) + u"}";
        }

        gbool equals(const Object &obj) const override {
            if (Manager::equals(obj)) {
                MethodManager const &manager1 = (MethodManager const &) obj;
                return manager1.func == func && &target == &manager1.target;
            }
            return false;
        }

        Object &clone() const override {
            try { return *new MethodManager(*this); } catch (...) { throw MemoryError(); }
        }

    private:
        _Func func;
        Target target;
    };

    template<class _Func>
    class LambdaManager final : public Manager {
    private:
        using _Fn = typename Class<_Func>::NIVR;
    public:
        CORE_EXPLICIT LambdaManager(_Func &&func) : func((_Func &&) func) {}

        void launch(T t) const override {
            func(t);
        }

        String toString() const override {
            return (!Class<_Fn>::template isConstruct<_Func>() ?
                    u"{action: lambda$" : u"{action: object@") + Long::toUnsignedString((glong) &func, 16) + u"}";
        }

        gbool equals(const Object &obj) const override {
            if (Manager::equals(obj)) {
                LambdaManager const &manager1 = (LambdaManager const &) obj;
                return &manager1.func == &func;
            }
            return false;
        }

        Object &clone() const override {
            try { return *new LambdaManager(*this); } catch (...) { throw MemoryError(); }
        }

    private:
        _Func func;
    };

    static Manager EMPTY;

    typename Class<Manager>::Pointer manager = &EMPTY;

};

template<class T>
typename Consumer<T>::Manager Consumer<T>::EMPTY = Manager{};


#endif //CORE_CONSUMER_H

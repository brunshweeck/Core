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
    CORE_IMPLICIT Consumer(_Func &&func): manager() {
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
    CORE_EXPLICIT Consumer(_Func &&func, Target &&target): manager() {
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
    CORE_IMPLICIT Consumer(_Func &&func): manager() {
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
    CORE_IMPLICIT Consumer(Consumer<T> const &c) : manager() {
        if (!c.manager || &c == &EMPTY_ACTION)
            manager = &EMPTY;
        else if (c.manager->isEmpty() || c.manager == &EMPTY)
            manager = &EMPTY;
        else
            manager = &(Manager &) c.manager->clone();
    }

    /**
     * Construct new consumer with action of other consumer
     * \param c consumer
     */
    CORE_IMPLICIT Consumer(Consumer<T> &&c) CORE_NOTHROW: manager() {
        manager = c.manager;
        c.manager = &EMPTY;
    }

    /**
     * Construct new consumer with action of other consumer
     * \param c consumer
     */
    template<class _T,
            Class<gbool>::Require<Class<_T>::template isSuper<T>()> = true>
    CORE_IMPLICIT Consumer(Consumer<_T> const &c) {
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
        if (!dynamic_cast<Consumer<T> const *>(&obj))
            return false;
        return true;
    }

    /**
     * Return copy of this consumer
     */
    Object &clone() const override {
        if (!manager || this == &EMPTY_ACTION)
            return (Object &) EMPTY_ACTION;
        if (manager->isEmpty() || manager == &EMPTY)
            return (Object &) EMPTY_ACTION;
        try { return *new Consumer<T>(*this); } catch (...) { throw MemoryError(); }
    }

    /**
     * Return string representation of this consumer
     * \return consumer{action: ...}
     */
    String toString() const override {
        if (!manager || this == &EMPTY_ACTION)
            return u"consumer" + EMPTY.toString();
        if (manager->isEmpty() || manager == &EMPTY)
            return u"consumer" + EMPTY.toString();
        return u"consumer" + manager->toString();
    }

private:
    void set(const Object &obj) override {
        if (!dynamic_cast<Consumer<T> const *>(&obj))
            throw CastError();
        *this = (Consumer<T> const &) obj;
    }

private:
    class Manager : public Object {
    public:
        virtual gbool isEmpty() const { return true; }

        virtual gbool isMember() const { return false; }

        virtual gbool isFunction() const { return false; }

        virtual gbool isObject() const { return false; }

        virtual void launch(T t) const {}

        String toString() const override {
            return u"{action: EMPTY}";
        }

        gbool equals(Object const &obj) const override {
            if (this == &obj)
                return true;
            if (!dynamic_cast<Manager const *>(&obj))
                return false;
            Manager const &manager1 = (Manager const &) obj;
            return isEmpty() && manager1.isEmpty()
                   || isMember() && manager1.isMember()
                   || isFunction() && manager1.isFunction()
                   || isObject() && manager1.isObject();
        }

        Object &clone() const override {
            return EMPTY;
        }

    protected:
        void set(const Object &obj) override {}
    };

    template<class _Func>
    class FunctionManager final : public Manager {
    public:
        CORE_EXPLICIT FunctionManager(_Func &&func) : func((_Func &&) func) {}

        gbool isEmpty() const override {
            return false;
        }

        gbool isFunction() const override {
            return true;
        }

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

        gbool isEmpty() const override {
            return false;
        }

        gbool isMember() const override {
            return true;
        }

        void launch(T t) const override {
            (target.*func)(t);
        }

        String toString() const override {
            return u"{action: target@" + Long::toUnsignedString((glong) &target, 16) + u"- method@" +
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

        gbool isEmpty() const override {
            return false;
        }

        gbool isObject() const override {
            return true;
        }

        void launch(T t) const override {
            func(t);
        }

        String toString() const override {
            return (!Class<_Func>::template isConstruct<_Fn>() ?
                    u"{action: $lambda@" : u"{action: object@") + Long::toUnsignedString((glong) &func, 16) + u"}";
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

public:
    static const Consumer<T> EMPTY_ACTION;
};

template<class T>
typename Consumer<T>::Manager Consumer<T>::EMPTY = Manager{};

template<class T>
Consumer<T> const Consumer<T>::EMPTY_ACTION = Consumer<T>{};

#endif //CORE_CONSUMER_H

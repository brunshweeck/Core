//
// Created by brunshweeck on 08/03/2023.
//

#ifndef CORE_PREDICATE_H
#define CORE_PREDICATE_H


#include "../Object.h"
#include "Functional.h"
#include "../String.h"
#include "../MemoryError.h"
#include "../Long.h"
#include "../ValueError.h"

template<class T>
class Predicate : public Object, public Functional<T, Boolean> {
public:
    /**
     * Construct new empty predicate. By default is always false predicate
     */
    CORE_EXPLICIT Predicate() = default;

    /**
     * Construct new predicate with unary boolean compatible function (return type is interpreted as boolean)
     * \param func boolean function
     * \throw ValueError if specified function is null
     */
    template<class _Func,
            class _Ret = typename Class<_Func>::template Return<T>,
            Class<gbool>::Require<Class<_Func>::isFunction() && Class<gbool>::isConstruct<_Ret>()> = true>
    CORE_IMPLICIT Predicate(_Func &&func): tester() {
        if (!func)
            throw ValueError("Invalid function");
        try {
            tester = new FunctionTest<_Func>((_Func &&) func);
        } catch (...) {
            throw MemoryError();
        }
    }

    /**
     * Construct new Predicate with unary boolean compatible method with target object instance
     * \param func boolean method
     * \param target object instance
     */
    template<class _Func, class Target,
            class _Ret = typename Class<_Func>::template Return<Target, T>,
            Class<gbool>::Require<Class<_Func>::isMember() && Class<gbool>::isConstruct<_Ret>()> = true>
    CORE_EXPLICIT Predicate(_Func &&func, Target &&target): tester() {
        try {
            tester = new MethodTest<_Func, Target>((_Func &&) func, (Target &&) target);
        } catch (...) {
            throw MemoryError();
        }
    }

    /**
     * Construct new Predicate with callable object or lambda function as test
     */
    template<class _Func,
            class _Ret = typename Class<_Func>::template Return<T>,
            Class<gbool>::Require<Class<_Func>::isClass() &&
                                  !Class<Object>::isSuper<_Func>() &&
                                  Class<gbool>::isConstruct<_Ret>()> = true>
    CORE_IMPLICIT Predicate(_Func &&func): tester() {
        try {
            tester = new LambdaTest<_Func>((_Func &&) func);
        } catch (...) {
            throw MemoryError();
        }
    }

    /**
     * Construct new predicate with another
     * \param p predicate
     */
    CORE_IMPLICIT Predicate(Predicate<T> const &p) {
        if (!p.tester || p.tester == &TRUE)
            tester = &TRUE;
        else if (p.tester->isAlwaysTrue())
            tester = &TRUE;
        else if (p.tester == &FALSE || p.tester->isAlwaysFalse())
            tester = &FALSE;
        else
            tester = &(Test &) tester->clone();
    }

    /**
     * Construct new predicate with another
     * \param p predicate
     */
    CORE_IMPLICIT Predicate(Predicate<T> &&p) CORE_NOTHROW {
        tester = p.tester;
        p.tester = &TRUE;
    }

    /**
     * Construct new predicate with another
     * \param p predicate
     */
    template<class _T,
            Class<gbool>::Require<Class<_T>::template isSuper<T>()> = true>
    CORE_IMPLICIT Predicate(Predicate<_T> const &p) {
        if (!p.tester || &p == &Predicate<_T>::ALWAYS_TRUE)
            tester = &TRUE;
        else
            tester = &(Test &) p.tester->clone();
    }

    /**
     * Set predicate tester with another predicate teser
     * \param p predicate
     */
    Predicate &operator=(Predicate<T> const &p) {
        if (this != &p) {
            if (tester != &TRUE && tester != &FALSE)
                delete tester;
            tester = &(Test &) p.tester->clone();
        }
        return *this;
    }

    /**
     * Set predicate tester with another predicate teser
     * \param p predicate
     */
    Predicate &operator=(Predicate<T> &&p) CORE_NOTHROW {
        typename Class<Test>::Pointer old = tester;
        tester = p.tester;
        p.tester = old;
        return *this;
    }

    /**
     * Set predicate tester with another predicate teser
     * \param p predicate
     */
    template<class _T,
            Class<gbool>::Require<Class<_T>::template isSuper<T>()> = true>
    Predicate &operator=(Predicate<_T> const &p) {
        if (this != &p) {
            if (tester != &TRUE && tester != &FALSE)
                delete tester;
            tester = &(Test &) p.tester->clone();
        }
        return *this;
    }

    /**
     * Run predicate test with specified argument parameter
     * \param t argument
     */
    gbool test(T t) const {
        if (tester)
            return tester->execute(t);
        return true;
    }

    /**
     * Invoke predicate test as function
     */
    gbool operator()(T t) const override {
        return test(t);
    }

    /**
     * Return true if this predicate equals perfectly to specified object
     * \param obj object to be compared
     */
    gbool equals(const Object &obj) const override {
        if (this == &obj)
            return true;
        return false;
    }

    /**
     * Return copy of this predicate
     */
    Object &clone() const override {
        if (!tester || tester == &TRUE)
            return (Object &) ALWAYS_TRUE;
        if (tester == &FALSE)
            return (Object &) ALWAYS_FALSE;
        try { return *new Predicate<T>(*this); } catch (...) { throw MemoryError(); }
    }

    /**
     * Return string representation of this predicate
     */
    String toString() const override {
        if (!tester || tester == &TRUE)
            return "predicate{test: always - true}";
        if (tester == &FALSE || tester->isAlwaysFalse())
            return "predicate{test: always - false}";
        return "predicate" + tester->toString();
    }

    /**
     * Return predicated representing opposite of this predicate
     */
    virtual Predicate logicalNot() const {
        static Predicate p;
        if (!tester || tester == &TRUE)
            p.tester = &FALSE;
        else if (tester == &FALSE)
            p.tester = &TRUE;
        else if (dynamic_cast<ReverseTest const *>(tester)) {
            ReverseTest const&reverseTest = (ReverseTest const& )*tester;
            p.tester = &(Test &) reverseTest.lhs->clone();
        } else
            try { p.tester = new ReverseTest((Test &) *tester); } catch (...) { throw MemoryError(); }
        return p;
    }

    /**
     * Return new predicate that tester is logical AND between this predicate and specified predicate
     * \param p another predicate
     */
    virtual Predicate logicalAnd(Predicate<T> const &p) const {
        if (this == &ALWAYS_TRUE || !tester || tester == &TRUE)
            return p;
        if (&p == &ALWAYS_TRUE || !p.tester || tester == &TRUE)
            return *this;
        if (this == &ALWAYS_FALSE || tester == &FALSE || &p == &ALWAYS_FALSE || p.tester == &FALSE)
            return ALWAYS_FALSE;
        Predicate<T> p2;
        try { p2.tester = new LogicalTest(*tester, *p.tester, LogicalTest::LOGICAL_AND); }
        catch (...) { throw MemoryError(); }
        return p2;
    }

    /**
     * Return new predicate that tester is logical OR between this predicate and specified predicate
     * \param p another predicate
     */
    virtual Predicate logicalOr(Predicate<T> const &p) const {
        if (this == &ALWAYS_TRUE || !tester || tester == &TRUE)
            return ALWAYS_TRUE;
        if (&p == &ALWAYS_TRUE || !p.tester || tester == &TRUE)
            return ALWAYS_TRUE;
        if (this == &ALWAYS_FALSE || tester == &FALSE)
            return p;
        if (&p == &ALWAYS_FALSE || p.tester == &FALSE)
            return *this;
        Predicate<T> p2;
        try { p2.tester = new LogicalTest(*tester, *p.tester, LogicalTest::LOGICAL_OR); }
        catch (...) { throw MemoryError(); }
        return p2;
    }

    /**
     * Return new predicate that tester is logical XOR between this predicate and specified predicate
     * \param p another predicate
     */
    virtual Predicate logicalXor(Predicate<T> const &p) const {
        Predicate<T> p2;
        try { p2.tester = new LogicalTest(*tester, *p.tester, LogicalTest::LOGICAL_OR); }
        catch (...) { throw MemoryError(); }
        return p2;
    }

    ~Predicate() override {
        if (tester && tester != &TRUE && tester != &FALSE) {
            delete tester;
            tester = &TRUE;
        }
    }

private:
    class Test : public Object {
    public:
        virtual gbool isAlwaysTrue() const { return true; }

        virtual gbool isAlwaysFalse() const { return false; }

        virtual gbool isFunction() const { return false; }

        virtual gbool isMember() const { return false; }

        virtual gbool isObject() const { return false; }

        virtual gbool execute(T t) const { return true; }

        gbool equals(const Object &obj) const override {
            if (this == &obj)
                return true;
            if (!dynamic_cast<Test const *>(&obj))
                return false;
            Test const &test1 = (Test const &) obj;
            return isAlwaysTrue() && test1.isAlwaysTrue()
                   || isAlwaysFalse() && test1.isAlwaysFalse()
                   || isFunction() && test1.isFunction()
                   || isMember() && test1.isMember()
                   || isObject() && test1.isObject();
        }

        Object &clone() const override {
            return TRUE;
        }

        String toString() const override {
            return "constant[true]";
        }
    };

    template<class _Func>
    class FunctionTest final : public Test {
    public:
        CORE_EXPLICIT FunctionTest(_Func &&func) : func((_Func &&) func) {}

        gbool isAlwaysTrue() const override {
            return false;
        }

        gbool isFunction() const override {
            return true;
        }

        gbool execute(T t) const override {
            return (gbool) func(t);
        }

        gbool equals(const Object &obj) const override {
            if (Test::equals(obj)) {
                FunctionTest const &test1 = (FunctionTest const &) obj;
                return func == test1.func;
            }
            return false;
        }

        Object &clone() const override {
            try { return *new FunctionTest(func); } catch (...) { throw MemoryError(); }
        }

        String toString() const override {
            return u"function[0x" + Long::toHexString((glong) func) + "]";
        }

    private:
        _Func func;
    };

    template<class _Func, class Target>
    class MethodTest final : public Test {
    public:
        CORE_EXPLICIT MethodTest(_Func &&func, Target &&target) : func((_Func &&) func), target((Target &&) target) {}

        gbool isAlwaysTrue() const override {
            return false;
        }

        gbool isMember() const override {
            return true;
        }

        gbool execute(T t) const override {
            return (gbool) (target.*func)(t);
        }

        gbool equals(const Object &obj) const override {
            if (Test::equals(obj)) {
                MethodTest const &test1 = (MethodTest const &) obj;
                return func == test1.func && &target == &test1.target;
            }
            return false;
        }

        Object &clone() const override {
            try { return *new MethodTest(*this); } catch (...) { throw MemoryError(); }
        }

        String toString() const override {
            return u"method[target=0x" + Long::toHexString((glong) &target) + u", function=0x" +
                   Long::toHexString((glong) &func) + u"]";
        }

    private:
        _Func func;
        Target target;
    };

    template<class _Func>
    class LambdaTest final : public Test {
    public:
        CORE_EXPLICIT LambdaTest(_Func &&func) : func((_Func &&) func) {}

        gbool isAlwaysTrue() const override {
            return false;
        }

        gbool isObject() const override {
            return true;
        }

        gbool execute(T t) const override {
            return (gbool) func(t);
        }

        gbool equals(const Object &obj) const override {
            if (Test::equals(obj)) {
                LambdaTest const &test1 = (LambdaTest const &) obj;
                return &func == &test1.func;
            }
            return false;
        }

        Object &clone() const override {
            try { return *new LambdaTest(*this); } catch (...) { throw MemoryError(); }
        }

        String toString() const override {
            return "object[0x" + Long::toHexString((glong) &func) + "]";
        }

    private:
        _Func func;
    };

    class ReverseTest : public Test {
    public:
        CORE_EXPLICIT ReverseTest(const Test &lhs) : lhs(&(Test &) lhs.clone()) {}

        gbool isAlwaysTrue() const override {
            return lhs->isAlwaysFalse();
        }

        gbool isAlwaysFalse() const override {
            return lhs->isAlwaysTrue();
        }

        gbool execute(T t) const override {
            return !lhs->execute(t);
        }

        gbool equals(const Object &obj) const override {
            if (this == &obj)
                return true;
            if (!dynamic_cast<ReverseTest const *>(&obj))
                return false;
            ReverseTest const &reverseTest = (ReverseTest const &) obj;
            return lhs == reverseTest.lhs;
        }

        Object &clone() const override {
            try { return *new ReverseTest(*this); } catch (...) { throw MemoryError(); }
        }

        String toString() const override {
            if (isAlwaysFalse())
                return "constant[false]";
            return "logical[type=(not), lhs=" + lhs->toString() + "]";
        }

        ~ReverseTest() override {
            if (lhs != &TRUE && lhs != &FALSE) {
                delete lhs;
                lhs = 0;
            }
        }

        typename Class<Test const>::Pointer lhs;
    };

    class LogicalTest : public Test {
    public:
        CORE_EXPLICIT LogicalTest(const Test &lhs, const Test &rhs, gint op) :
                lhs(&(Test &) lhs.clone()), rhs(&(Test &) rhs.clone()), op(op) {}

        gbool isAlwaysTrue() const override {
            return false;
        }

        gbool isAlwaysFalse() const override {
            return false;
        }

        gbool execute(T t) const override {
            switch (op) {
                case LOGICAL_AND:
                    if (lhs->execute(t))
                        rhs->execute(t);
                case LOGICAL_OR:
                    if (lhs->execute(t))
                        return true;
                    if (rhs->execute(t))
                        return true;
                case LOGICAL_XOR:
                    if (lhs->execute(t))
                        return !rhs->execute(t);
                    return rhs->execute(t);
            }
            return false;
        }

        gbool equals(const Object &obj) const override {
            if (this == &obj)
                return true;
            if (!dynamic_cast<LogicalTest const *>(&obj))
                return false;
            LogicalTest const &logicalTest = (LogicalTest const &) obj;
            if (op != logicalTest.op)
                return false;
            if (lhs != logicalTest.lhs)
                return false;
            return rhs == logicalTest.rhs;
        }

        Object &clone() const override {
            try { return *new LogicalTest(*this); } catch (...) { throw MemoryError(); }
        }

        String toString() const override {
            switch (op) {
                case LOGICAL_AND:
                    return "logical[type=(and), lhs=" + lhs->toString() + ", rhs=" + rhs->toString() + "]";
                case LOGICAL_OR:
                    return "logical[type=(or), lhs=" + lhs->toString() + ", rhs=" + rhs->toString() + "]";
                case LOGICAL_XOR:
                    return "logical[type=(xor), lhs=" + lhs->toString() + ", rhs=" + rhs->toString() + "]";
            }
            return "logical[type=???]";
        }

        CORE_FAST static gint LOGICAL_AND = 11;
        CORE_FAST static gint LOGICAL_OR = 10;
        CORE_FAST static gint LOGICAL_XOR = 1001;

        ~LogicalTest() override {
            if (lhs != &TRUE && lhs != &FALSE && rhs != &TRUE && rhs != &FALSE) {
                delete lhs;
                delete rhs;
                lhs = rhs = 0;
            }
        }

    private:
        typename Class<Test const>::Pointer lhs;
        typename Class<Test const>::Pointer rhs;
        gint op;
    };

    static Test TRUE;
    static ReverseTest FALSE;

    typename Class<Test>::Pointer tester = &TRUE;

public:
    static const Predicate<T> ALWAYS_TRUE;
    static const Predicate<T> ALWAYS_FALSE;
};

template<class T> typename Predicate<T>::Test Predicate<T>::TRUE = Test();
template<class T> typename Predicate<T>::ReverseTest Predicate<T>::FALSE = ReverseTest(TRUE);
template<class T> const Predicate<T> Predicate<T>::ALWAYS_TRUE = Predicate<T>();
template<class T> const Predicate<T> Predicate<T>::ALWAYS_FALSE = ALWAYS_TRUE.logicalNot();


#endif //CORE_PREDICATE_H

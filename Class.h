//
// Created by brunshweeck on 16/02/2023.
//

#ifndef CORE_CLASS_H
#define CORE_CLASS_H

#include "extern/Class.h"

/**
 *  Class is used to do test on any type
 *
 *  \tparam T target for test
 */
template<class T>
class Class final {
public:
    /**
     * Cannot create instance of this type
     */
    Class() = delete;

    static String const& name() {
        return core::Class::className(&typeid(T));
    }

    /**
     * Constant version of target type
     * \example Class<gint>::Immutable -> gint const
     */
    using Immutable = typename core::Class::Constant<T>::Type;

    /**
     * Non constant version of target type
     * \example Class<gint const>::Mutable -> gint
     */
    using Mutable = typename core::Class::Constant<T>::Type2;

    /**
     * Reference version of target type
     * \example Class<gint>::Reference -> gint&
     */
    using Reference = typename core::Class::Reference<T>::Type;

    /**
     * Unreferenced version of target type
     * \example Class<gint&>::Unreferenced -> gint
     * \example Class<gint&&>::UnReferenced -> gint
     */
    using Unreferenced = typename core::Class::Reference<T>::Type2;

    /**
     * Reference version of target type
     * \example Class<gint>::MoveReference -> gint&&
     */
    using MoveReference = typename core::Class::Reference<T>::Type3;

    /**
     * Constant reference version of target type
     * \example Class<gint>::ImmutableReference -> gint const&
     * \example Class<gint&>::ImmutableReference -> gint const&
     */
    using ImmutableReference = typename core::Class::CR<T>::Type;

    /**
     * Constant reference version of target type
     * \example Class<gint>::ImmutableVolatile -> gint const volatile
     * \example Class<gint const>::ImmutableVolatile -> gint const volatile
     * \example Class<gint volatile>::ImmutableVolatile -> gint const volatile
     */
    using ImmutableVolatile = typename core::Class::CV<T>::Type;

    /**
     * Constant reference version of target type
     * \example Class<gint>::ImmutableVolatileReference -> gint const volatile&
     * \example Class<gint&>::ImmutableVolatileReference -> gint const volatile&
     * \example Class<gint const>::ImmutableVolatileReference -> gint const volatile&
     * \example Class<gint const&>::ImmutableVolatileReference -> gint const volatile&
     * \example Class<gint volatile>::ImmutableVolatileReference -> gint const volatile&
     * \example Class<gint volatile&>::ImmutableVolatileReference -> gint const volatile&
     * \example Class<gint const volatile>::ImmutableVolatileReference -> gint const volatile&
     */
    using ImmutableVolatileReference = typename core::Class::CVR<T>::Type;

    /**
     * Constant reference version of target type
     * \example Class<gint>::IR -> gint const&
     * \example Class<gint&>::IR -> gint const&
     */
    using IR = ImmutableReference;

    /**
     * Constant reference version of target type
     * \example Class<gint>::IV -> gint const volatile
     * \example Class<gint const>::IV -> gint const volatile
     * \example Class<gint volatile>::IV -> gint const volatile
     */
    using IV = ImmutableVolatile;

    /**
     * Constant reference version of target type
     * \example Class<gint>::IVR -> gint const volatile&
     * \example Class<gint&>::IVR -> gint const volatile&
     * \example Class<gint const>::IVR -> gint const volatile&
     * \example Class<gint const&>::IVR -> gint const volatile&
     * \example Class<gint volatile>::IVR -> gint const volatile&
     * \example Class<gint volatile&>::IVR -> gint const volatile&
     * \example Class<gint const volatile>::IVR -> gint const volatile&
     */
    using IVR = ImmutableVolatileReference;

    /**
     * Remove Constant reference version of target type
     * \example Class<gint&>::NIR -> gint
     * \example Class<gint const&>::NIR -> gint
     */
    using NIR = typename core::Class::CR<T>::Type2;

    /**
     * Remove Constant reference version of target type
     * \example Class<gint const>::NIV -> gint
     * \example Class<gint volatile>::NIV -> gint
     * \example Class<gint const volatile>::NIV -> gint
     */
    using NIV = typename core::Class::CV<T>::Type2;

    /**
     * Remove Constant reference version of target type
     * \example Class<gint&>::NIVR -> gint
     * \example Class<gint const>::NIVR -> gint
     * \example Class<gint const&>::NIVR -> gint
     * \example Class<gint volatile>::NIVR -> gint
     * \example Class<gint volatile&>::NIVR -> gint
     * \example Class<gint const volatile>::NIVR -> gint
     * \example Class<gint const volatile&>::NIVR -> gint
     */
    using NIVR = typename core::Class::CVR<T>::Type2;

    /**
     * Pointer version of target type
     * \example Class<gint>::Pointer -> gint *
     * \example Class<gint&>::Pointer -> gint *
     */
    using Pointer = typename core::Class::Pointer<T>::Type;

    /**
     * Remove Pointer version of target type
     * \example Class<gint*>::Pointer -> gint
     */
    using NoPointer = typename core::Class::Pointer<T>::Type2;

    template<CORE_SIZE S>
    using Array = typename core::Class::Array3<T, S>::Type;

    using ArrayElement = typename core::Class::Array2<T>::Type;

    /**
     * Return true if target type is immutable type. In other terms, if target has extension 'const'
     * \example gint const
     */
    CORE_FAST static gbool isImmutable() {
        return core::Class::Constant<T>::V;
    }

    /**
     * Return true if target type is reference type. In other terms, if target has extension '&' or '&&'
     * \example gint&
     */
    CORE_FAST static gbool isReference() {
        return core::Class::Reference<T>::V;
    }

    /**
     * Return true if target type is pointer type. In other terms, if target has extension '*' or '[n]'
     * \example gint *
     */
    CORE_FAST static gbool isPointer() {
        return core::Class::Pointer<NIVR>::V;
    }

    /**
     * Return true if target type is volatile type. In other terms, if target has extension 'volatile'
     * \example gint volatile
     */
    CORE_FAST static gbool isVolatile() {
        return core::Class::Volatile<T>::V;
    }

    /**
     * Return true if target type is template type. In other terms, if target is declared with 'template <...>'
     * \example Class<gint>
     */
    CORE_FAST static gbool isTemplate() {
        return core::Class::Template<NIVR>::V;
    }

    /**
     * Return true if target type is static sized array type. In other terms, if target has extension '[n]'
     * \example gint[100]
     */
    CORE_FAST static gbool isArray() {
        return core::Class::Array<NIVR>::V;
    }

    /**
     * Return true if target type is void type. In other terms, if target is same to 'void'
     *
     */
    CORE_FAST static gbool isVoid() {
        return core::Class::Similar<NIVR, void>::V;
    }

    /**
     * Return true if target type is primitive function type. In other terms, if target if defined like this 'Return(Args...)'
     * \example void(gint, gfloat)
     */
    CORE_FAST static gbool isFunction() {
        return !isVoid() && !isArray() && core::Class::Function<NIVR>::V;
    }

    /**
     * Return true if target type is class member type. in other terms, if target is defined like this 'A B::*'
     * \example Enum<Character::Category>::name
     */
    CORE_FAST static gbool isMember() {
        return core::Class::Member<NIV>::V;
    }

    /**
     * Return true if target type is non static class method type.
     * \example &Object::toString => String(Object::*)()
     * \example &Collection<Integer>::add => gbool(Collection<Integer>::*)(Integer const& i)
     */
    CORE_FAST static gbool isFunctionMember() {
        return core::Class::Member2<NIV>::V;
    }

    /**
     * Return true if target type is abstract type.
     */
    CORE_FAST static gbool isAbstract() {
        return core::Class::AbstractTest<NIVR>(0);
    }

    /**
     * Return true if target type is empty type.
     */
    CORE_FAST static gbool isEmpty() {
        return __is_empty(NIVR);
    }

    /**
     * Return true if target type is literal type.
     */
    CORE_FAST static gbool isLiteral() {
        return __is_literal_type(NIVR);
    }

    /**
     * Return true if target type is trivial type.
     */
    CORE_FAST static gbool isTrivial() {
        return __is_trivial(NIVR);
    }

    /**
     * Return true if target type is polymorphic type.
     */
    CORE_FAST static gbool isPolymorphic() {
        return __is_polymorphic(NIVR);
    }

    /**
     * Return true if target type is class type.
     */
    CORE_FAST static gbool isClass() {
        return __is_class(NIVR);
    }

    /**
     * Return true if target type is primitive enumeration type.
     */
    CORE_FAST static gbool isEnum() {
        return __is_enum(NIVR);
    }

    /**
     * Return true if target type is primitive integer number type.
     * \example gint, gbyte, glong, ...
     */
    CORE_FAST static gbool isIntegral() {
        return core::Class::Similar<NIVR, i8>::V ||
               core::Class::Similar<NIVR, i16>::V ||
               core::Class::Similar<NIVR, i32>::V ||
               core::Class::Similar<NIVR, i64>::V ||
               core::Class::Similar<NIVR, CORE_SIZE>::V;
    }

    /**
     * Return true if target type is primitive floating number type.
     * \example gfloat, gdouble
     */
    CORE_FAST static gbool isFloating() {
        return core::Class::Similar<NIVR, f32>::V ||
               core::Class::Similar<NIVR, f64>::V;
    }

    /**
     * Return true if target type is primitive number type.
     */
    CORE_FAST static gbool isNumber() {
        return isIntegral() || isFloating();
    }

    /**
     * Return true if target type is primitive boolean type.
     */
    CORE_FAST static gbool isBoolean() {
        return core::Class::Similar<NIVR, CORE_BOOL>::V;
    }

    /**
     * Return true if target type is primitive character type.
     */
    CORE_FAST static gbool isCharacter() {
        return core::Class::Similar<NIVR, wchar_t>::V ||
               core::Class::Similar<NIVR, CORE_CHAR8>::V ||
               core::Class::Similar<NIVR, CORE_CHAR16>::V ||
               core::Class::Similar<NIVR, CORE_CHAR32>::V;
    }

    /**
     * Return true if target type is primitive string type.
     */
    CORE_FAST static gbool isString() {
        using U = typename Class<NIVR>::NoPointer;
        using V = typename Class<NIVR>::ArrayElement;
        return Class<U>::isCharacter() || Class<V>::isCharacter();
    }

    /**
     * Return true if target type same to specified type
     */
    template<class To>
    CORE_FAST static gbool isSame() {
        return core::Class::Similar<NIVR, typename Class<To>::NIVR>::V;
    }

    /**
     * Return true if target type base of specified type
     */
    template<class Of>
    CORE_FAST static gbool isSuper() {
        return core::Class::SuperTest<NIVR, typename Class<Of>::NIVR>(0);
    }

    /**
     * Return true if target type is callable with specified arguments types
     */
    template<class ...With>
    CORE_FAST static gbool isCallable() {
        return core::Class::Return<NIV, With...>::V;
    }

    /**
     * Return true if target type can be assigned with specified type value
     */
    template<class With>
    CORE_FAST static gbool isAssignable() {
        return __is_assignable(NIVR, With);
    }

    /**
     * Return true if target type can be construct with specified type
     */
    template<class ...With>
    CORE_FAST static gbool isConstruct() {
        return __is_constructible(NIVR, With...);
    }

    template<class U>
    CORE_FAST static gbool hasInstance(U&& obj) {
        CORE_REQUIRE(isClass(), "This Function require object type");
        CORE_REQUIRE(Class<U>::isClass(), "This Function require object type");
        using _T = typename Class<NIVR>::Immutable;
        return dynamic_cast<_T*>(&obj);
    }

    /**
     * Require is a first type if and only if condition is true. In otherwise it not exists
     */
    template<gbool condition>
    using Require = typename core::Class::If<T, condition>::Type;

    /**
     * Conditional is a first type if and only if condition is true. In otherwise a second type
     */
    template<gbool condition, class Else>
    using Conditional = typename core::Class::IfElse<T, condition, Else>::Type;

    /**
     * Return is a return type of target type (if it callable with specified arguments type)
     */
    template<class ...Args>
    using Return = typename core::Class::Return<NIV, Args...>::Type::Type;

    using Primitive = typename core::Class::Primitive<NIVR>::Type;
    using Object = typename core::Class::Class<NIVR>::Type;
};


#endif //CORE_CLASS_H

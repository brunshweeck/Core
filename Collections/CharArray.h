//
// Created by brunshweeck on 09/03/2023.
//

#ifndef CORE_CHARARRAY_H
#define CORE_CHARARRAY_H


#include "../Object.h"
#include "../Comparable.h"
#include "CharBuffer.h"

class CharArray : public Object, public Comparable<CharArray> {
public:
    /**
     * Construct new charArray with specified length and default fill character
     * \param length number of character
     * \param fill default value
     */
    CORE_EXPLICIT CharArray(gint length, gchar fill = '\u0000');

    /**
     * Construct new charArray
     */
    CORE_EXPLICIT CharArray(CharBuffer const &buffer);

    template<CORE_SIZE S>
    CORE_EXPLICIT CharArray(gchar const(&array)[S]): CharArray(S) {
        gint index = 0;
        for (gchar c: array)
            set(index++, c);
    }

    template<CORE_SIZE S>
    CORE_EXPLICIT CharArray(gchar (&array)[S]): CharArray(S) {
        gint index = 0;
        for (gchar c: array)
            set(index++, c);
    }

    /**
     * Construct new charArray with another
     * \param array
     */
    CharArray(CharArray const &array);

    /**
     * Construct new charArray with another
     * \param array
     */
    CharArray(CharArray &&array) CORE_NOTHROW;

    /**
     * Set charArray value with other charArray
     * \param array
     */
    CharArray &operator=(CharArray const &array);

    /**
     * Set charArray value with other charArray
     * \param array
     */
    CharArray &operator=(CharArray &&array) CORE_NOTHROW;

    /**
     * Return number of character from this instance
     */
    gint length() const;

    /**
     * Return character at specified index
     * \param index
     * \throw IndexError if index out of range
     */
    gchar get(gint index) const;

    /**
     * Set character value at specified index
     * \param index
     * \param c new character value
     * \return old character value
     * \throw IndexError if index out if range
     */
    gchar set(gint index, gchar c);

    /**
     * Return character at specified index
     * \param index
     * \throw IndexError if index out of range
     */
    gchar const operator[](gint index) const;

    /**
     * Return character at specified index
     * \param index
     * \throw IndexError if index out of range
     */
    gchar &operator[](gint index);

    /**
     * Construct new charArray with one character
     * \param _0 first character
     */
    static CharArray of(gchar _0);

    /**
     * Construct new charArray with two character
     * \param _0 first character
     * \param _1 second character
     */
    static CharArray of(gchar _0, gchar _1);

    /**
     * Construct new charArray with three character
     * \param _0 first character
     * \param _1 second character
     * \param _2 third character
     */
    static CharArray of(gchar _0, gchar _1, gchar _2);

    /**
     * Construct new charArray with four character
     * \param _0 first character
     * \param _1 second character
     * \param _2 third character
     * \param _3 fourth character
     */
    static CharArray of(gchar _0, gchar _1, gchar _2, gchar _3);

    /**
     * Construct new charArray with five character
     * \param _0 first character
     * \param _1 second character
     * \param _2 third character
     * \param _3 fourth character
     * \param _4 fiftieth character
     */
    static CharArray of(gchar _0, gchar _1, gchar _2, gchar _3, gchar _4);

    /**
     * Construct new charArray with six character
     * \param _0 first character
     * \param _1 second character
     * \param _2 third character
     * \param _3 fourth character
     * \param _4 fiftieth character
     * \param _5 sixth character
     */
    static CharArray of(gchar _0, gchar _1, gchar _2, gchar _3, gchar _4, gchar _5);

    /**
     * Construct new charArray with seven character
     * \param _0 first character
     * \param _1 second character
     * \param _2 third character
     * \param _3 fourth character
     * \param _4 fiftieth character
     * \param _5 sixth character
     * \param _6 seventh character
     */
    static CharArray of(gchar _0, gchar _1, gchar _2, gchar _3, gchar _4, gchar _5, gchar _6);

    /**
     * Construct new charArray with height character
     * \param _0 first character
     * \param _1 second character
     * \param _2 third character
     * \param _3 fourth character
     * \param _4 fiftieth character
     * \param _5 sixth character
     * \param _6 seventh character
     * \param _7 height character
     */
    static CharArray of(gchar _0, gchar _1, gchar _2, gchar _3, gchar _4, gchar _5, gchar _6, gchar _7);

    /**
     * Construct new charArray with nine character
     * \param _0 first character
     * \param _1 second character
     * \param _2 third character
     * \param _3 fourth character
     * \param _4 fiftieth character
     * \param _5 sixth character
     * \param _6 seventh character
     * \param _7 height character
     * \param _8 ninth character
     */
    static CharArray of(gchar _0, gchar _1, gchar _2, gchar _3, gchar _4, gchar _5, gchar _6, gchar _7, gchar _8);

    /**
     * Construct new charArray with ten character
     * \param _0 first character
     * \param _1 second character
     * \param _2 third character
     * \param _3 fourth character
     * \param _4 fiftieth character
     * \param _5 sixth character
     * \param _6 seventh character
     * \param _7 height character
     * \param _8 ninth character
     * \param _9 tenth character
     */
    static CharArray of(gchar _0, gchar _1, gchar _2, gchar _3, gchar _4,
                        gchar _5, gchar _6, gchar _7, gchar _8, gchar _9);

    /**
     * Construct new charArray with any character
     * \param _0 first character
     * \param _1 second character
     * \param _2 third character
     * \param _3 fourth character
     * \param _4 fiftieth character
     * \param _5 sixth character
     * \param _6 seventh character
     * \param _7 height character
     * \param _8 ninth character
     * \param _9 tenth character
     * \param otherChars...
     */
    template<class ..._Char>
    static CharArray of(gchar _0, gchar _1, gchar _2, gchar _3, gchar _4,
                        gchar _5, gchar _6, gchar _7, gchar _8, gchar _9, _Char ...otherChars) {
        gchar c[] = {_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, otherChars...};
        return CharArray(c);
    }

    gint compareTo(const CharArray &obj) const override;

    gbool equals(const Object &obj) const override;

    Object &clone() const override;

    ~CharArray() override = default;

    String toString() const override;

    CORE_EXPLICIT operator CharBuffer();

protected:
    void set(const Object &obj) override;

private:
    Class<gchar>::Pointer value;
    gint len;
};


#endif //CORE_CHARARRAY_H

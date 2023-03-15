//
// Created by brunshweeck on 24/02/2023.
//

#ifndef CORE_STRING_H
#define CORE_STRING_H

#include "Comparable.h"
#include "Hashable.h"

/**
 * The class String includes methods for examining individual characters of the sequence, for
 * comparing strings, for searching strings, for extracting substrings, and for creating a copy of
 * a string with all characters translated to uppercase or to lowercase. Case mapping is based on
 * the Unicode Standard version specified by the Character class.
 */
class String final : public Object, public Comparable<String>, public Hashable {
public:
    /**
     * Construct new empty string
     */
    String();

    /**
     * Initializes a newly created String object so that it represents
     * the same sequence of characters as the argument; in other words, the
     * newly created string is a copy of the argument string. Unless an
     * explicit copy of original is needed, use of this constructor is
     * unnecessary since Strings are immutable.
     * \param original
     */
    String(String const &original);

    /**
     * Initializes a newly created String object so that it represents
     * the same sequence of characters as the argument; in other words, the
     * newly created string is a copy of the argument string. Unless an
     * explicit copy of original is needed, use of this constructor is
     * unnecessary since Strings are immutable.
     * \param original
     */
    String(String &&original) CORE_NOTHROW;

    /**
     * Allocates a new String so that it represents the sequence of
     * characters currently contained in the character array argument. The
     * contents of the character array are copied; subsequent modification of
     * the character array does not affect the newly created string.
     * \param value initial value of the string
     * \throw ValueError If value is null
     */
    template<class _String, Class<gbool>::Require<Class<_String>::isString()> = true>
    String(_String &&value): String(arrayOrPointerToString((_String &&) value)) {}

    template<CORE_SIZE S>
    CORE_EXPLICIT String(gbyte const (&bytes)[S], Charset const &charset): String(bytes, S, charset) {}

    template<CORE_SIZE S>
    CORE_EXPLICIT String(gbyte const (&bytes)[S], gint begin, gint end, Charset const &charset):
            String(bytes + begin, end - begin + 1, charset) {}

    CORE_EXPLICIT String(gbyte const bytes[], gint length, Charset const &charset);

    /**
     * Allocates a new String that contains characters from a subarray
     * of the character array argument. The offset argument is the
     * index of the first character of the subarray and the count
     * argument specifies the length of the subarray. The contents of the
     * subarray are copied; subsequent modification of the character array does
     * not affect the newly created string.
     * \param value Array that is the source of characters
     * \param begin The initial offset
     * \param len The length
     * \throw ValueError If value is null
     * \throw IndexError If begin is negative or len is negative
     */
    template<class _String, Class<gbool>::Require<Class<_String>::isString()> = true>
    CORE_EXPLICIT String(_String &&value, gint begin, gint length): String(
            arrayOrPointerToString((_String &&) value, begin, length)) {}

    /**
     *
     */
    String &operator=(String const &str);

    String &operator=(String &&str) CORE_NOTHROW;

    String &operator+=(String const &str);

    /**
     * Concatenates the specified string to the end of this string.
     * If the length of the argument string is 0, then this
     * String object is returned. Otherwise, a
     * String object is returned that represents a character
     * sequence that is the concatenation of the character sequence
     * represented by this String object and the character
     * sequence represented by the argument string.
     * \param str the String that is concatenated to the end of this String.
     */
    String concat(const String &str) const;

    /**
     * Returns a string resulting from replacing all occurrences of
     * oldChar in this string with newChar.
     *
     * If the character oldChar does not occur in the
     * character sequence represented by this String object,
     * then a reference to this String object is returned.
     * Otherwise, a String object is returned that
     * represents a character sequence identical to the character sequence
     * represented by this String object, except that every
     * occurrence of oldChar is replaced by an occurrence
     * of newChar.
     * \param oldChar the old character.
     * \param newChar the new character.
     */
    String replace(gchar oldChar, gchar newChar) const;

    /**
     * Returns a string whose value is this string, with all leading
     * and trailing space removed.
     *
     * If this String object represents an empty character
     * sequence, or the first and last characters of character sequence
     * represented by this String object both have codes
     * that are not space (as defined above), then a
     * reference to this String object is returned.
     *
     * Otherwise, if all characters in this string are space (as
     * defined above), then a  String object representing an
     * empty string is returned.
     *
     * Otherwise, let k be the index of the first character in the
     * string whose code is not a space (as defined above) and let
     * m be the index of the last character in the string whose code
     * is not a space (as defined above). A String
     * object is returned, representing the substring of this string that
     * begins with the character at index k and ends with the
     * character at index m-that is, the result of String::substring(k, m + 1).
     *
     * This method may be used to trim space (as defined above) from
     * the beginning and end of a string.
     *
     * \see Character::isSpace
     */
    String strip() const;

    /**
     * Returns a string whose value is this string, with all leading space removed.
     *
     * If this String object represents an empty character
     * sequence, or the first characters of character sequence
     * represented by this String object both have codes
     * that are not space (as defined above), then a
     * reference to this String object is returned.
     *
     * Otherwise, if all characters in this string are space (as
     * defined above), then a  String object representing an
     * empty string is returned.
     *
     * Otherwise, let k be the index of the first character in the
     * string whose code is not a space (as defined above). A String
     * object is returned, representing the substring of this string that
     * begins with the character at index k that is, the result of String::substring(k).
     *
     * This method may be used to trim space (as defined above) from
     * the beginning and end of a string.
     *
     * \see Character::isSpace
     */
    String stripLeading() const;

    /**
     * Returns a string whose value is this string, with all trailing space removed.
     *
     * If this String object represents an empty character
     * sequence, or the first and last characters of character sequence
     * represented by this String object both have codes
     * that are not space (as defined above), then a
     * reference to this String object is returned.
     *
     * Otherwise, if all characters in this string are space (as
     * defined above), then a  String object representing an
     * empty string is returned.
     *
     * Otherwise, let m be the index of the last character in the string whose code
     * is not a space (as defined above). A String
     * object is returned, representing the substring of this string that
     * begins with the character at index 0 and ends with the
     * character at index m-that is, the result of String::substring(0, m + 1).
     *
     * This method may be used to trim space (as defined above) from
     * the beginning and end of a string.
     *
     * \see Character::isSpace
     */
    String stripTrailing() const;

    /**
     * Replaces each substring of this string that matches the given regular expression with the
     * given replacement.
     * \param regex the regular expression to which this string is to be matched
     * \param replacement the string to be substituted for each match
     */
    String replace(const String &regex, const String &replacement) const;

    /**
     * Returns a string whose value is the concatenation of this
     * string repeated count times.
     *
     * If this string is empty or count is zero then the empty
     * string is returned.
     * \param count number of times to repeat
     * \throw ValueError if the count is negative
     */
    String repeat(gint count) const;

    /**
     * Converts all of the characters in this String to upper case
     */
    String toUpperCase() const;

    /**
     * Converts all of the characters in this String to lower case
     */
    String toLowerCase() const;

    /**
     * Converts all of the characters in this String to title case
     */
    String toTitleCase() const;

    /**
     * Return itself
     */
    String toString() const override;

    /**
     * Return true if all of character in this string are ascii character
     */
    gbool isAscii() const;

public:
    /**
     * Returns a string that is a substring of this string. The
     * substring begins with the character at the specified index and
     * extends to the end of this string.
     * \param begin the beginning index, inclusive.
     */
    String subString(gint begin) const;

    /**
     * Returns a string that is a substring of this string. The
     * substring begins at the specified beginIndex and
     * extends to the character at index endIndex - 1.
     * Thus the length of the substring is endIndex-beginIndex.
     * \param begin the beginning index, inclusive.
     * \param end the ending index, exclusive.
     */
    String subString(gint begin, gint end) const;

    /**
     * Returns the char value at the specified index. An index ranges from 0 to
     * length() - 1. The first char value of the sequence
     * is at index 0, the next at index 1,
     * and so on, as for array indexing.
     *
     * If the char value specified by the index is a surrogate, the surrogate value is returned.
     * \param index the index to the char values
     * \throw IndexError if the index argument is negative or not less than the length of this string.
     */
    gchar charAt(gint index) const;

    /**
     * Returns the character (Unicode code point) at the specified
     * index. The index refers to char values
     * (Unicode code units) and ranges from 0 to String::length() - 1.
     *
     * If the char value specified at the given index
     * is in the high-surrogate range, the following index is less
     * than the length of this String, and the
     * char value at the following index is in the
     * low-surrogate range, then the supplementary code point
     * corresponding to this surrogate pair is returned. Otherwise,
     * the char value at the given index is returned.
     * \param index the index to the char values
     * \throw IndexError if the index argument is negative or not less than the length of this string.
     */
    gint codepointAt(gint index) const;

    /**
     * Returns true if, and only if, String::length() is 0.
     */
    gbool isEmpty() const;

    /**
     * Returns the length of this string.
     * The length is equal to the number of Unicode code units in the string.
     */
    gint length() const;

    /**
     * Copy character bytes from this string into dst starting at begin.
     * \param dst destination array
     * \param begin index of first character in the string copy
     * \param end index after the last character in the string copy
     * \param length destination capacity
     */
    gint bytes(gbyte dst[], gint length, gint begin, gint end) const;

    /**
     * Return array of all character contained from this string
     */
    CharArray chars() const;

    /**
     * Return array of all character contained from delimited part of this string
     * \param begin index of first character
     * \param end index of last character
     * \throw IndexError if one if two indexes out of range
     */
    CharArray chars(gint begin, gint end) const;

    /**
     * Construct new string with array of character
     * \param chars character array
     */
    CORE_EXPLICIT String(CharArray const &chars);

    /**
     * Construct new string with array of character
     * \param chars character array
     */
    CORE_EXPLICIT String(CharArray const &chars, gint offset);

    /**
     * Compares this string to the specified object.
     * The result is true if and only if the argument is a String object
     * that represents the same sequence of characters as this object.
     * \param obj The object to compare this String
     */
    gbool equals(Object const &obj) const override;

    /**
     * Compares this instance with literal value
     * \param v - literal value
     */
    template<class T,
            Class<gbool>::Require<!Class<T>::isClass()> = true,
            class S = typename Class<T>::NIVR,
            class U = typename Class<S>::Object,
            Class<gbool>::Require<!Class<U>::isVoid()> = true>
    gbool equals(T &&v) const {
        return equals(U((T &&) v));
    }

    /**
     * Compares this String to another String, ignoring case considerations.
     * Two strings are considered equal ignoring case if they
     * are of the same length and corresponding Unicode code points in the two
     * strings are equal ignoring case.
     *
     * <p> Two Unicode code points are considered the same
     * ignoring case if at least one of the following is true:
     * <ul>
     *   <li> The two Unicode code points are the same (as compared by the == operator)
     *   <li> Calling Character::toLowerCase(Character::toUpperCase(gint))
     *        on each Unicode code point produces the same result
     * </ul>
     */
    gbool equalsIgnoreCase(String const &str) const;

    /**
     * Compares two strings lexicographically.
     * The comparison is based on the Unicode value of each character in
     * the strings. The character sequence represented by this
     * String object is compared lexicographically to the
     * character sequence represented by the argument string. The result is
     * a negative integer if this String object
     * lexicographically precedes the argument string. The result is a
     * positive integer if this String object lexicographically
     * follows the argument string. The result is zero if the strings
     * are equal; compareTo returns 0 exactly when
     * the String::equals method would return true.
     * <p>
     * This is the definition of lexicographic ordering. If two strings are
     * different, then either they have different characters at some index
     * that is a valid index for both strings, or their lengths are different,
     * or both. If they have different characters at one or more index
     * positions, let k be the smallest such index; then the string
     * whose character at position k has the smaller value, as
     * determined by using the < operator, lexicographically precedes the
     * other string. In this case, compareTo returns the
     * difference of the two character values at position k in
     * the two string -- that is, the value: this.charAt(k)- s.charAt(k)
     * \param s the string to be compared
     */
    gint compareTo(String const &s) const override;

    /**
     * Compares two strings lexicographically, ignoring case
     * differences. This method returns an integer whose sign is that of
     * calling compareTo with case folded versions of the strings
     * where case differences have been eliminated by calling
     * Character::toLowerCase(Character::toUpperCase(char)) on
     * each Unicode code point.
     */
    gint compareToIgnoreCase(String const &str) const;

    /**
     * Tests if the substring of this string beginning at the
     * specified index starts with the specified prefix.
     * \param prefix the prefix
     * \param begin where to begin looking in this string.
     */
    gbool startsWith(const String &prefix, gint begin) const;

    /**
     * Tests if this string starts with the specified prefix.
     * \param prefix the prefix
     */
    gbool startsWith(String const &prefix) const;

    /**
     * Tests if this string ends with the specified suffix.
     */
    gbool endsWith(String const &suffix) const;

    /**
     * Returns a hash code for this string. The hash code for a
     * String object is computed as s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]
     *
     * using gint arithmetic, where s[i] is the
     * i th character of the string, n is the length of
     * the string, and ^ indicates exponentiation.
     * (The hash value of the empty string is zero.)
     */
    glong hash() const override;

    /**
     * Returns the index within this string of the first occurrence of
     * the specified character. If a character with value ch
     * occurs in the character sequence represented by
     * this String object, then the index (in Unicode
     * code units) of the first such occurrence is returned. For
     * values of ch in the range from 0 to 0xFFFF
     * (inclusive), this is the smallest value k such that: this.charAt(k) == ch
     * is true. For other values of ch}, it is the
     * smallest value k such that: this.codePointAt(k) == ch
     * is true. In either case, if no such character occurs in this
     * string, then -1 is returned.
     * \param ch a character (Unicode code point).
     */
    gint indexOf(gint ch) const;

    /**
     * Returns the index within this string of the first occurrence of
     * the specified character. If a character with value ch
     * occurs in the character sequence represented by
     * this String object, then the index (in Unicode
     * code units) of the first such occurrence is returned. For
     * values of ch in the range from 0 to 0xFFFF
     * (inclusive), this is the smallest value k such that: this.charAt(k) == ch && (k >= begin)
     * is true. For other values of ch}, it is the
     * smallest value k such that: this.codePointAt(k) == ch && (k >= begin)
     * is true. In either case, if no such character occurs in this
     * string, then -1 is returned.
     * \param ch a character (Unicode code point).
     * \param begin the index to start the search from.
     */
    gint indexOf(gint ch, gint begin) const;

    /**
     * Returns the index within this string of the first occurrence of the
     * specified substring.
     *
     * The returned index is the smallest value k for which: this.startsWith(str, k)
     * If no such value of k exists, then -1 is returned.
     */
    gint indexOf(const String &str) const;

    /**
     * Returns the index within this string of the first occurrence of the
     * specified substring, starting at the specified index.
     *
     * The returned index is the smallest value k for which:
     *      k >= Math.min(fromIndex, this.length()) && this.startsWith(str, k)
     * If no such value of k exists, then -1 is returned.
     */
    gint indexOf(String const &str, gint begin) const;

    /**
     * Returns the index within this string of the last occurrence of
     * the specified character. For values of ch in the
     * range from 0 to 0xFFFF (inclusive), the index (in Unicode code
     * units) returned is the largest value k such that:
     * this.charAt(k) == ch
     * is true. For other values of ch, it is the
     * largest value k such that:
     * this.codePointAt(k) == ch
     * is true.  In either case, if no such character occurs in this
     * string, then -1 is returned.  The String is searched backwards starting at the last
     * character.
     * \param ch a character (Unicode code point).
     */
    gint lastIndexOf(gint ch) const;

    /**
     * Returns the index within this string of the last occurrence of
     * the specified character. For values of ch in the
     * range from 0 to 0xFFFF (inclusive), the index (in Unicode code
     * units) returned is the largest value k such that:
     * this.charAt(k) == ch
     * is true. For other values of ch, it is the
     * largest value k such that:
     * this.codePointAt(k) == ch
     * is true.  In either case, if no such character occurs in this
     * string, then -1 is returned.
     * The String is searched backwards starting at or before position 'begin'
     * \param ch a character (Unicode code point).
     * \param begin the index to start the search from.
     * There is no restriction on the value of 'begin'.
     * If it is greater than or equal to the length of this string,
     * it has the same effect as if it were equal to one less than the
     * length of this string: this entire string may be searched.
     * If it is negative, it has the same effect as if it were -1: -1 is returned.
     */
    gint lastIndexOf(gint ch, gint begin) const;

    /**
     * Returns the index within this string of the last occurrence of the
     * specified substring.  The last occurrence of the empty string ""
     * is considered to occur at the index value this.length().
     *
     * The returned index is the largest value k for which:
     * this.startsWith(str, k)
     * If no such value of k exists, then -1 is returned.
     * \param str the substring to search for.
     */
    gint lastIndexOf(String const &str) const;

    /**
     * Returns the index within this string of the last occurrence of the
     * specified substring.  The last occurrence of the empty string ""
     * is considered to occur at the index value this.length().
     *
     * The returned index is the largest value k for which:
     * k <= Integer::min(fromIndex, this.length()) && this.startsWith(str, k)
     * If no such value of k exists, then -1 is returned.
     * \param str the substring to search for.
     * \param begin the index to start the search from.
     */
    gint lastIndexOf(String const &str, gint begin) const;

    /**
     * Return number of occurrence of specified substring into this string
     * \param str the substring to search for.
     */
    gint count(String const &str) const;

    /**
     * Returns true if the string is empty or contains only
     * Character::isSpace(gint) white space codepoints,otherwise false.
     * \see Character::isSpace
     */
    gbool isBlank() const;

    /**
     * Return true if all of character of this string are uppercase form
     * \see Character::isUpperCase
     */
    gbool isUpperCase() const;

    /**
     * Return true if all of character of this string are lowercase form
     * \see Character::isLowerCase
     */
    gbool isLowerCase() const;

    /**
     * Return true if all of character of this string are uppercase form
     * \see Character::isTitleCase
     */
    gbool isTitleCase() const;

    /**
     * Return copy of this object
     */
    Object &clone() const override;

private:
    /**
     * set string properties
     * \param obj
     */
    void set(Object const &obj) override;

    template<class T>
    static String arrayOrPointerToString(T &&arrayOrPointer) {
        CORE_FAST gbool isArray = Class<T>::isArray();
        gbyte const *bytes = (gbyte *) arrayOrPointer;
        gint memoryCharSize;
        gint memorySize;
        if (isArray) {
            memorySize = sizeof(T); // number of bytes
            if (memorySize == 0)
                // char8[0] or char16[0] or char32[0]
                return {};
            else
                memoryCharSize = sizeof(arrayOrPointer[0]); // number of bytes per char
            // remove last character (by default all literal string end with Null character ('\u0000')
            memorySize -= memoryCharSize;
        } else if (!arrayOrPointer)
            // null pointer
            return {};
        else {
            memoryCharSize = sizeof(*arrayOrPointer);
            gint numberOfChars = 0;
            while (arrayOrPointer[numberOfChars] != '\u0000')
                numberOfChars += 1;
            if (numberOfChars == 0)
                return {};
            memorySize = numberOfChars * memoryCharSize;
        }
        return String(bytes, memorySize, memoryCharSize, memoryCharSize == 1 ? 1 : memoryCharSize == 2 ? 2 : 4);
    }

    template<class T>
    static String arrayOrPointerToString(T &&arrayOrPointer, gint begin, gint length) {
        CORE_FAST gbool isArray = Class<T>::isArray();
        if (isArray) {
            if (begin < 0)
                begin = 0;
        }
        gbyte const *bytes = (gbyte *) (arrayOrPointer + begin);
        gint memoryCharSize;
        gint memorySize;
        if (isArray) {
            memorySize = sizeof(T); // number of bytes
            if (memorySize == 0)
                // char8[0] or char16[0] or char32[0]
                return {};
            else
                memoryCharSize = sizeof(arrayOrPointer[0]); // number of bytes per char
            // remove last character (by default all literal string end with Null character ('\u0000')
            memorySize -= memoryCharSize;
            if (memorySize > memoryCharSize * length)
                memorySize = length;
        } else if (!arrayOrPointer)
            // null pointer (error)
            return String(bytes, -1, -1, -1);
        else {
            memoryCharSize = sizeof(*arrayOrPointer);
            gint numberOfChars = length;
            if (numberOfChars == 0)
                return {};
            memorySize = numberOfChars * memoryCharSize;
        }
        return String(bytes, memorySize, memoryCharSize, memoryCharSize == 1 ? 1 : memoryCharSize == 2 ? 2 : 4);
    }

public:
    ~String() override;

private:

    CORE_EXPLICIT String(gbyte const *b, gint memorySize, gint memoryCharSize, gint codec);

    /**
     * The value is used for character storage.
     * this field is automatically modified to minimize the use of memory.
     * Overwriting this field after construction will cause problems.
     * it encoded to UTF-16BE
     */
    Class<gbyte>::Pointer value;

    /**
     * the number of bytes for the string
     */
    gint len;
};

extern String operator+(String const &lhs, String const &rhs);

#endif //CORE_STRING_H

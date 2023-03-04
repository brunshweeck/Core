//
// Created by brunshweeck on 22/02/2023.
//

#ifndef CORE_CHARACTER_H
#define CORE_CHARACTER_H

#include "Object.h"
#include "Comparable.h"
#include "Integer.h"
#include "Hashable.h"

/**
 *
 *
 */
class Character final : public Object, public Comparable<Character>, public Hashable {
public:
    /**
     * Construct new instance of Character
     */
    CORE_IMPLICIT Character();

    /**
     * Construct new instance of Character and initialize
     * \param v primitive utf16 character
     */
    CORE_IMPLICIT Character(gchar v);

    /**
     * Construct new instance of Character and initialize with two bytes of utf16 character
     * \param h high byte
     * \param l low byte
     */
    CORE_EXPLICIT Character(gbyte h, gbyte l);

    /**
     * Return value of this instance as char
     */
    gchar charValue() const;

    /**
     * Return high byte of this instance
     */
    gbyte highByte() const;

    /**
     * Return low byte of this instance
     */
    gbyte lowByte() const;

    /**
     * Return number represented by this instance or -1 if is not number
     * \see Character::isNumber
     */
    gchar numericValue() const;

    /**
     * Return lowercase form of this instance
     */
    gchar toLowerCase() const;

    /**
     * Return uppercase form of this instance
     */
    gchar toUpperCase() const;

    /**
     * Return title case form of this instance
     */
    gchar toTitleCase() const;

    /**
     * Return mirror character of this instance
     * \see Character::isMirrored
     */
    gchar mirror() const;

    /**
     * Return unicode codepoint of this instance
     */
    gint codepoint() const;

    /**
     * Return true if value of this instance is ASCII
     */
    gbool isAscii() const;

    /**
     * Return true if value of this instance represent a digit (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ...)
     */
    gbool isDigit() const;

    /**
     * Return true if value of this instance represent a high part of supplementary character
     */
    gbool isHighSurrogate() const;

    /**
     * Return true if value of this instance is BASIC LATIN
     */
    gbool isLatin() const;

    /**
     * Return true if value of this instance is a letter (alphabetic)
     */
    gbool isLetter() const;

    /**
     * Return true if value of this instance is a letter of number (alphanumeric)
     */
    gbool isLetterOrNumber() const;

    /**
     * Return true if value of this instance represent lower case form of one character
     */
    gbool isLowerCase() const;

    /**
     * Return true if value of this instance represent a low part of supplementary character
     */
    gbool isLowSurrogate() const;

    /**
     * Return true if value of this instance represent a mark
     */
    gbool isMark() const;

    /**
     * Return true if value of this instance represent a mirrored character
     */
    gbool isMirrored() const;

    /**
     * Return true if value of this instance not represent character
     */
    gbool isNonCharacter() const;

    /**
     * Return true if value of this instance represent a number
     */
    gbool isNumber() const;

    /**
     * Return true if value of this instance is printable
     */
    gbool isPrintable() const;

    /**
     * Return true if value of this instance represent punctuation
     */
    gbool isPunctuation() const;

    /**
     * Return true if value of this instance represent a white space
     */
    gbool isSpace() const;

    /**
     * Return true if value of this instance represent part of supplementary character
     */
    gbool isSurrogate() const;

    /**
     * Return true if value of this instance represent a symbol
     */
    gbool isSymbol() const;

    /**
     * Return true if value of this instance represent title case form of one character
     */
    gbool isTitleCase() const;

    /**
     * Return true if value of this instance represent upper case form of one character
     */
    gbool isUpperCase() const;

    /**
     *  General character type
     *
     */
    enum class Category : gbyte {
        /**
        * General category "Cn" in the Unicode specification.
        *
        */
        UNASSIGNED = 13,

        /**
        * General category "Lu" in the Unicode specification.
        *
        */
        UPPERCASE_LETTER = 14,

        /**
        * General category "Ll" in the Unicode specification.
        *
        */
        LOWERCASE_LETTER = 15,

        /**
        * General category "Lt" in the Unicode specification.
        *
        */
        TITLECASE_LETTER = 16,

        /**
        * General category "Lm" in the Unicode specification.
        *
        */
        MODIFIER_LETTER = 17,

        /**
        * General category "Lo" in the Unicode specification.
        *
        */
        OTHER_LETTER = 18,

        /**
        * General category "Mn" in the Unicode specification.
        *
        */
        NON_SPACING_MARK = 0,

        /**
        * General category "Me" in the Unicode specification.
        *
        */
        ENCLOSING_MARK = 2,

        /**
        * General category "Mc" in the Unicode specification.
        *
        */
        COMBINING_SPACING_MARK = 1,

        /**
        * General category "Nd" in the Unicode specification.
        *
        */
        DECIMAL_DIGIT_NUMBER = 3,

        /**
        * General category "Nl" in the Unicode specification.
        *
        */
        LETTER_NUMBER = 4,

        /**
        * General category "No" in the Unicode specification.
        *
        */
        OTHER_NUMBER = 5,

        /**
        * General category "Zs" in the Unicode specification.
        *
        */
        SPACE_SEPARATOR = 6,

        /**
        * General category "Zl" in the Unicode specification.
        *
        */
        LINE_SEPARATOR = 7,

        /**
        * General category "Zp" in the Unicode specification.
        *
        */
        PARAGRAPH_SEPARATOR = 8,

        /**
        * General category "Cc" in the Unicode specification.
        *
        */
        CONTROL = 9,

        /**
        * General category "Cf" in the Unicode specification.
        *
        */
        FORMAT = 10,

        /**
        * General category "Co" in the Unicode specification.
        *
        */
        PRIVATE_USE = 12,

        /**
        * General category "Cs" in the Unicode specification.
        *
        */
        SURROGATE = 11,

        /**
        * General category "Pd" in the Unicode specification.
        *
        */
        DASH_PUNCTUATION = 20,

        /**
        * General category "Ps" in the Unicode specification.
        *
        */
        START_PUNCTUATION = 21,

        /**
        * General category "Pe" in the Unicode specification.
        *
        */
        END_PUNCTUATION = 22,

        /**
        * General category "Pc" in the Unicode specification.
        *
        */
        CONNECTOR_PUNCTUATION = 19,

        /**
        * General category "Po" in the Unicode specification.
        *
        */
        OTHER_PUNCTUATION = 25,

        /**
        * General category "Sm" in the Unicode specification.
        *
        */
        MATH_SYMBOL = 26,

        /**
        * General category "Sc" in the Unicode specification.
        *
        */
        CURRENCY_SYMBOL = 27,

        /**
        * General category "Sk" in the Unicode specification.
        *
        */
        MODIFIER_SYMBOL = 28,

        /**
        * General category "So" in the Unicode specification.
        *
        */
        OTHER_SYMBOL = 29,

        /**
        * General category "Pi" in the Unicode specification.
        *
        */
        INITIAL_QUOTE_PUNCTUATION = 23,

        /**
        * General category "Pf" in the Unicode specification.
        *
        */
        FINAL_QUOTE_PUNCTUATION = 24
    };

    /**
     *  Character combining class
     *
     */
    enum class Combining : gshort {
        BELOW_LEFT_ATTACHED = 200,
        BELOW_ATTACHED = 202,
        BELOW_RIGHT_ATTACHED = 204,
        LEFT_ATTACHED = 208,
        RIGHT_ATTACHED = 210,
        ABOVE_LEFT_ATTACHED = 212,
        ABOVE_ATTACHED = 214,
        ABOVE_RIGHT_ATTACHED = 216,

        BELOW_LEFT = 218,
        BELOW = 220,
        BELOW_RIGHT = 222,
        LEFT = 224,
        RIGHT = 226,
        ABOVE_LEFT = 228,
        ABOVE = 230,
        ABOVE_RIGHT = 232,

        DOUBLE_BELOW = 233,
        DOUBLE_ABOVE = 234,
        IOTA_SUBSCRIPT = 240
    };

    /**
     *  Character decomposition style
     */
    enum class Decomposition : gbyte {
        /**
         * None specify that character is not decomposable or it is invalid character
         */
        NONE,
        CANONICAL,
        FONT,
        NO_BREAK,
        INITIAL,
        MEDIAL,
        FINAL,
        ISOLATED,

        /**
         * Circle is used for character into circle
         */
        CIRCLE,

        /**
         * Super is used form the exponent character (u'\u00b2' => "2")
         */
        SUPER,

        /**
         * Sub is used from the sub exponent character (u'\u00bc' => "1/4")
         */
        SUB,
        VERTICAL,
        WIDE,
        NARROW,
        SMALL,

        /**
         * Circle is used for character into square
         */
        SQUARE,
        COMPAT,

        /**
         * Fraction is used to decompose fraction character
         */
        FRACTION
    };

    /**
     *  Directionality of character
     *
     */
    enum class Directionality : gbyte {
        /**
        * Undefined Directionality character type. Undefined char
        * values have undefined directionality in the Unicode specification.
        * \since 1.4
        */
        UNDEFINED = -1,

        /**
        * Strong Directionality character type "L" in the Unicode specification.
        * \since 1.4
        */
        LEFT_TO_RIGHT = 0,

        /**
        * Strong Directionality character type "R" in the Unicode specification.
        * \since 1.4
        */
        RIGHT_TO_LEFT = 1,

        /**
        * Strong Directionality character type "AL" in the Unicode specification.
        * \since 1.4
        */
        RIGHT_TO_LEFT_ARABIC = 2,

        /**
        * Weak Directionality character type "EN" in the Unicode specification.
        * \since 1.4
        */
        EUROPEAN_NUMBER = 3,

        /**
        * Weak Directionality character type "ES" in the Unicode specification.
        * \since 1.4
        */
        EUROPEAN_NUMBER_SEPARATOR = 4,

        /**
        * Weak Directionality character type "ET" in the Unicode specification.
        * \since 1.4
        */
        EUROPEAN_NUMBER_TERMINATOR = 5,

        /**
        * Weak Directionality character type "AN" in the Unicode specification.
        * \since 1.4
        */
        ARABIC_NUMBER = 6,

        /**
        * Weak Directionality character type "CS" in the Unicode specification.
        * \since 1.4
        */
        COMMON_NUMBER_SEPARATOR = 7,

        /**
        * Weak Directionality character type "NSM" in the Unicode specification.
        * \since 1.4
        */
        NONSPACING_MARK = 8,

        /**
        * Weak Directionality character type "BN" in the Unicode specification.
        * \since 1.4
        */
        BOUNDARY_NEUTRAL = 9,

        /**
        * Neutral Directionality character type "B" in the Unicode specification.
        * \since 1.4
        */
        PARAGRAPH_SEPARATOR = 10,

        /**
        * Neutral Directionality character type "S" in the Unicode specification.
        * \since 1.4
        */
        SEGMENT_SEPARATOR = 11,

        /**
        * Neutral Directionality character type "WS" in the Unicode specification.
        * \since 1.4
        */
        WHITESPACE = 12,

        /**
        * Neutral Directionality character type "ON" in the Unicode specification.
        * \since 1.4
        */
        OTHER_NEUTRALS = 13,

        /**
        * Strong Directionality character type "LRE" in the Unicode specification.
        * \since 1.4
        */
        LEFT_TO_RIGHT_EMBEDDING = 14,

        /**
        * Strong Directionality character type "LRO" in the Unicode specification.
        * \since 1.4
        */
        LEFT_TO_RIGHT_OVERRIDE = 15,

        /**
        * Strong Directionality character type "RLE" in the Unicode specification.
        * \since 1.4
        */
        RIGHT_TO_LEFT_EMBEDDING = 16,

        /**
        * Strong Directionality character type "RLO" in the Unicode specification.
        * \since 1.4
        */
        RIGHT_TO_LEFT_OVERRIDE = 17,

        /**
        * Weak Directionality character type "PDF" in the Unicode specification.
        * \since 1.4
        */
        POP_DIRECTIONAL_FORMAT = 18,

        /**
        * Weak Directionality character type "LRI" in the Unicode specification.
        * \since 9
        */
        LEFT_TO_RIGHT_ISOLATE = 19,

        /**
        * Weak Directionality character type "RLI" in the Unicode specification.
        * \since 9
        */
        RIGHT_TO_LEFT_ISOLATE = 20,

        /**
        * Weak Directionality character type "FSI" in the Unicode specification.
        * \since 9
        */
        FIRST_STRONG_ISOLATE = 21,

        /**
        * Weak Directionality character type "PDI" in the Unicode specification.
        * \since 9
        */
        POP_DIRECTIONAL_ISOLATE = 22,
    };

    /**
     *  unicode script of character
     *
     */
    enum class UnicodeScript : gshort {
        /**
        * Unicode script "Common".
        */
        COMMON = 2,

        /**
        * Unicode script "Latin".
        */
        LATIN,

        /**
        * Unicode script "Greek".
        */
        GREEK,

        /**
        * Unicode script "Cyrillic".
        */
        CYRILLIC,

        /**
        * Unicode script "Armenian".
        */
        ARMENIAN,

        /**
        * Unicode script "Hebrew".
        */
        HEBREW,

        /**
        * Unicode script "Arabic".
        */
        ARABIC,

        /**
        * Unicode script "Syriac".
        */
        SYRIAC,

        /**
        * Unicode script "Thaana".
        */
        THAANA,

        /**
        * Unicode script "Devanagari".
        */
        DEVANAGARI,

        /**
        * Unicode script "Bengali".
        */
        BENGALI,

        /**
        * Unicode script "Gurmukhi".
        */
        GURMUKHI,

        /**
        * Unicode script "Gujarati".
        */
        GUJARATI,

        /**
        * Unicode script "Oriya".
        */
        ORIYA,

        /**
        * Unicode script "Tamil".
        */
        TAMIL,

        /**
        * Unicode script "Telugu".
        */
        TELUGU,

        /**
        * Unicode script "Kannada".
        */
        KANNADA,

        /**
        * Unicode script "Malayalam".
        */
        MALAYALAM,

        /**
        * Unicode script "Sinhala".
        */
        SINHALA,

        /**
        * Unicode script "Thai".
        */
        THAI,

        /**
        * Unicode script "Lao".
        */
        LAO,

        /**
        * Unicode script "Tibetan".
        */
        TIBETAN,

        /**
        * Unicode script "Myanmar".
        */
        MYANMAR,

        /**
        * Unicode script "Georgian".
        */
        GEORGIAN,

        /**
        * Unicode script "Hangul".
        */
        HANGUL,

        /**
        * Unicode script "Ethiopic".
        */
        ETHIOPIC,

        /**
        * Unicode script "Cherokee".
        */
        CHEROKEE,

        /**
        * Unicode script "Canadian_Aboriginal".
        */
        CANADIAN_ABORIGINAL,

        /**
        * Unicode script "Ogham".
        */
        OGHAM,

        /**
        * Unicode script "Runic".
        */
        RUNIC,

        /**
        * Unicode script "Khmer".
        */
        KHMER,

        /**
        * Unicode script "Mongolian".
        */
        MONGOLIAN,

        /**
        * Unicode script "Hiragana".
        */
        HIRAGANA,

        /**
        * Unicode script "Katakana".
        */
        KATAKANA,

        /**
        * Unicode script "Bopomofo".
        */
        BOPOMOFO,

        /**
        * Unicode script "Han".
        */
        HAN,

        /**
        * Unicode script "Yi".
        */
        YI,

        /**
        * Unicode script "Old_Italic".
        */
        OLD_ITALIC,

        /**
        * Unicode script "Gothic".
        */
        GOTHIC,

        /**
        * Unicode script "Deseret".
        */
        DESERET,

        /**
        * Unicode script "Inherited".
        */
        INHERITED = 1,

        /**
        * Unicode script "Tagalog".
        */
        TAGALOG = 42,

        /**
        * Unicode script "Hanunoo".
        */
        HANUNOO,

        /**
        * Unicode script "Buhid".
        */
        BUHID,

        /**
        * Unicode script "Tagbanwa".
        */
        TAGBANWA,

        /**
        * Unicode script "Limbu".
        * \since 4
        */
        LIMBU,

        /**
        * Unicode script "Tai_Le".
        * \since 4
        */
        TAI_LE,

        /**
        * Unicode script "Linear_B".
        * \since 4
        */
        LINEAR_B,

        /**
        * Unicode script "Ugaritic".
        * \since 4
        */
        UGARITIC,

        /**
        * Unicode script "Shavian".
        * \since 4
        */
        SHAVIAN,

        /**
        * Unicode script "Osmanya".
        * \since 4
        */
        OSMANYA,

        /**
        * Unicode script "Cypriot".
        * \since 4
        */
        CYPRIOT,

        /**
        * Unicode script "Braille".
        * \since 4
        */
        BRAILLE,

        /**
        * Unicode script "Buginese".
        * \since 4.1
        */
        BUGINESE,

        /**
        * Unicode script "Coptic".
        */
        COPTIC = 46,

        /**
        * Unicode script "New_Tai_Lue".
        * \since 4.1
        */
        NEW_TAI_LUE = 55,

        /**
        * Unicode script "Glagolitic".
        * \since 4.1
        */
        GLAGOLITIC,

        /**
        * Unicode script "Tifinagh".
        * \since 4.1
        */
        TIFINAGH,

        /**
        * Unicode script "Syloti_Nagri".
        * \since 4.1
        */
        SYLOTI_NAGRI,

        /**
        * Unicode script "Old_Persian".
        * \since 4.1
        */
        OLD_PERSIAN,

        /**
        * Unicode script "Kharoshthi".
        * \since 4.1
        */
        KHAROSHTHI,

        /**
        * Unicode script "Balinese".
        * \since 5.0
        */
        BALINESE,

        /**
        * Unicode script "Cuneiform".
        * \since 5.0
        */
        CUNEIFORM,

        /**
        * Unicode script "Phoenician".
        * \since 5.0
        */
        PHOENICIAN,

        /**
        * Unicode script "Phags_Pa".
        * \since 5.0
        */
        PHAGS_PA,

        /**
        * Unicode script "Nko".
        * \since 5.0
        */
        NKO,

        /**
        * Unicode script "Sundanese".
        * \since 5.1
        */
        SUNDANESE,

        /**
        * Unicode script "Batak".
        * \since 5.1
        */
        BATAK = 92,

        /**
        * Unicode script "Lepcha".
        * \since 5.1
        */
        LEPCHA = 67,

        /**
        * Unicode script "Ol_Chiki".
        * \since 5.1
        */
        OL_CHIKI,

        /**
        * Unicode script "Vai".
        * \since 5.1
        */
        VAI,

        /**
        * Unicode script "Saurashtra".
        * \since 5.1
        */
        SAURASHTRA,

        /**
        * Unicode script "Kayah_Li".
        * \since 5.1
        */
        KAYAH_LI,

        /**
        * Unicode script "Rejang".
        * \since 5.1
        */
        REJANG,

        /**
        * Unicode script "Lycian".
        * \since 5.1
        */
        LYCIAN,

        /**
        * Unicode script "Carian".
        * \since 5.1
        */
        CARIAN,

        /**
        * Unicode script "Lydian".
        * \since 5.1
        */
        LYDIAN,

        /**
        * Unicode script "Cham".
        * \since 5.1
        */
        CHAM,

        /**
        * Unicode script "Tai_Tham".
        * \since 5.2
        */
        TAI_THAM,

        /**
        * Unicode script "Tai_Viet".
        * \since 5.2
        */
        TAI_VIET,

        /**
        * Unicode script "Avestan".
        * \since 5.2
        */
        AVESTAN,

        /**
        * Unicode script "Egyptian_Hieroglyphs".
        * \since 5.2
        */
        EGYPTIAN_HIEROGLYPHS,

        /**
        * Unicode script "Samaritan".
        * \since 5.2
        */
        SAMARITAN,

        /**
        * Unicode script "Mandaic".
        * \since 6.0
        */
        MANDAIC = 94,

        /**
        * Unicode script "Lisu".
        * \since 5.2
        */
        LISU = 82,

        /**
        * Unicode script "Bamum".
        * \since 5.2
        */
        BAMUM,

        /**
        * Unicode script "Javanese".
        * \since 5.2
        */
        JAVANESE,

        /**
        * Unicode script "Meetei_Mayek".
        * \since 5.2
        */
        MEETEI_MAYEK,

        /**
        * Unicode script "Imperial_Aramaic".
        * \since 5.2
        */
        IMPERIAL_ARAMAIC,

        /**
        * Unicode script "Old_South_Arabian".
        * \since 5.2
        */
        OLD_SOUTH_ARABIAN,

        /**
        * Unicode script "Inscriptional_Parthian"
        * \since 5.2.
        */
        INSCRIPTIONAL_PARTHIAN,

        /**
        * Unicode script "Inscriptional_Pahlavi".
        * \since 5.2
        */
        INSCRIPTIONAL_PAHLAVI,

        /**
        * Unicode script "Old_Turkic".
        * \since 5.2
        */
        OLD_TURKIC,

        /**
        * Unicode script "Brahmi".
        * \since 6
        */
        BRAHMI = 93,

        /**
        * Unicode script "Kaithi".
        * \since 5.2
        */
        KAITHI = 91,

        /**
        * Unicode script "Meroitic Hieroglyphs".
        * \since 6.1
        */
        MEROITIC_HIEROGLYPHS = 97,

        /**
        * Unicode script "Meroitic Cursive".
        * \since 6.1
        */
        MEROITIC_CURSIVE = 96,

        /**
        * Unicode script "Sora Sompeng".
        * \since 6.1
        */
        SORA_SOMPENG = 100,

        /**
        * Unicode script "Chakma".
        * \since 6.1
        */
        CHAKMA = 95,

        /**
        * Unicode script "Sharada".
        * \since 6.1
        */
        SHARADA = 99,

        /**
        * Unicode script "Takri".
        * \since 6.1
        */
        TAKRI = 101,

        /**
        * Unicode script "Miao".
        * \since 6.1
        */
        MIAO = 98,

        /**
        * Unicode script "Caucasian Albanian".
        * \since 7
        */
        CAUCASIAN_ALBANIAN = 102,

        /**
        * Unicode script "Bassa Vah".
        * \since 7
        */
        BASSA_VAH,

        /**
        * Unicode script "Duployan".
        * \since 7
        */
        DUPLOYAN,

        /**
        * Unicode script "Elbasan".
        * \since 7
        */
        ELBASAN,

        /**
        * Unicode script "Grantha".
        * \since 7
        */
        GRANTHA,

        /**
        * Unicode script "Pahawh Hmong".
        * \since 7
        */
        PAHAWH_HMONG,

        /**
        * Unicode script "Khojki".
        * \since 7
        */
        KHOJKI,

        /**
        * Unicode script "Linear A".
        * \since 7
        */
        LINEAR_A,

        /**
        * Unicode script "Mahajani".
        * \since 7
        */
        MAHAJANI,

        /**
        * Unicode script "Manichaean".
        * \since 7
        */
        MANICHAEAN,

        /**
        * Unicode script "Mende Kikakui".
        * \since 7
        */
        MENDE_KIKAKUI,

        /**
        * Unicode script "Modi".
        * \since 7
        */
        MODI,

        /**
        * Unicode script "Mro".
        * \since 7
        */
        MRO,

        /**
        * Unicode script "Old North Arabian".
        * \since 7
        */
        OLD_NORTH_ARABIAN,

        /**
        * Unicode script "Nabataean".
        * \since 7
        */
        NABATAEAN,

        /**
        * Unicode script "Palmyrene".
        * \since 7
        */
        PALMYRENE,

        /**
        * Unicode script "Pau Cin Hau".
        * \since 7
        */
        PAU_CIN_HAU,

        /**
        * Unicode script "Old Permic".
        * \since 7
        */
        OLD_PERMIC,

        /**
        * Unicode script "Psalter Pahlavi".
        * \since 7
        */
        PSALTER_PAHLAVI,

        /**
        * Unicode script "Siddham".
        * \since 7
        */
        SIDDHAM,

        /**
        * Unicode script "Khudawadi".
        * \since 7
        */
        KHUDAWADI,

        /**
        * Unicode script "Tirhuta".
        * \since 7
        */
        TIRHUTA,

        /**
        * Unicode script "Warang Citi".
        * \since 7
        */
        WARANG_CITI,

        /**
        * Unicode script "Ahom".
        * \since 8
        */
        AHOM,

        /**
        * Unicode script "Anatolian Hieroglyphs".
        * \since 8
        */
        ANATOLIAN_HIEROGLYPHS,

        /**
        * Unicode script "Hatran".
        * \since 8
        */
        HATRAN,

        /**
        * Unicode script "Multani".
        * \since 8
        */
        MULTANI,

        /**
        * Unicode script "Old Hungarian".
        * \since 8
        */
        OLD_HUNGARIAN,

        /**
        * Unicode script "SignWriting".
        * \since 8
        */
        SIGNWRITING,

        /**
        * Unicode script "Adlam".
        * \since 9
        */
        ADLAM,

        /**
        * Unicode script "Bhaiksuki".
        * \since 9
        */
        BHAIKSUKI,

        /**
        * Unicode script "Marchen".
        * \since 9
        */
        MARCHEN,

        /**
        * Unicode script "Newa".
        * \since 9
        */
        NEWA,

        /**
        * Unicode script "Osage".
        * \since 9
        */
        OSAGE,

        /**
        * Unicode script "Tangut".
        * \since 9
        */
        TANGUT,

        /**
        * Unicode script "Masaram Gondi".
        * \since 10
        */
        MASARAM_GONDI,

        /**
        * Unicode script "Nushu".
        * \since 10
        */
        NUSHU,

        /**
        * Unicode script "Soyombo".
        * \since 10
        */
        SOYOMBO,

        /**
        * Unicode script "Zanabazar Square".
        * \since 10
        */
        ZANABAZAR_SQUARE,

        /**
        * Unicode script "Hanifi Rohingya".
        * \since 12.1
        */
        HANIFI_ROHINGYA = 143,

        /**
        * Unicode script "Old Sogdian".
        * \since 12.1
        */
        OLD_SOGDIAN = 146,

        /**
        * Unicode script "Sogdian".
        * \since 12.1
        */
        SOGDIAN,

        /**
        * Unicode script "Dogra".
        * \since 12.1
        */
        DOGRA = 141,

        /**
        * Unicode script "Gunjala Gondi".
        * \since 12.1
        */
        GUNJALA_GONDI,

        /**
        * Unicode script "Makasar".
        * \since 12.1
        */
        MAKASAR = 144,

        /**
        * Unicode script "Medefaidrin".
        * \since 12.1
        */
        MEDEFAIDRIN,

        /**
        * Unicode script "Elymaic".
        * \since 12.1
        */
        ELYMAIC = 148,

        /**
        * Unicode script "Nandinagari".
        * \since 12.1
        */
        NANDINAGARI,

        /**
        * Unicode script "Nyiakeng Puachue Hmong".
        * \since 12.1
        */
        NYIAKENG_PUACHUE_HMONG,

        /**
        * Unicode script "Wancho".
        * \since 12.1
        */
        WANCHO,

        /**
        * Unicode script "Yezidi".
        * \since 13
        */
        YEZIDI = 155,

        /**
        * Unicode script "Chorasmian".
        * \since 13
        */
        CHORASMIAN = 152,

        /**
        * Unicode script "Dives Akuru".
        * \since 13
        */
        DIVES_AKURU,

        /**
        * Unicode script "Khitan Small Script".
        * \since 13
        */
        KHITAN_SMALL_SCRIPT,

        /**
        * Unicode script "Cypro Minoan".
        * \since 14
        */
        CYPRO_MINOAN = 156,

        /**
        * Unicode script "Old Oyghur".
        * \since 14
        */
        OLD_UYGHUR,

        /**
        * Unicode script "Tangsa".
        * \since 14
        */
        TANGSA,

        /**
        * Unicode script "Toto".
        * \since 14
        */
        TOTO,

        /**
        * Unicode script "Vithkuqi".
        * \since 14
        */
        VITHKUQI,

        /**
        * Unicode script "Script Count".
        */
        SCRIPT_COUNT,

        /**
        * Unicode script "Unknown".
        */
        UNKNOWN = 0
    };

    /**
     * Return generic character of this instance
     */
    Category category() const;

    /**
     * Return combining class of this instance
     */
    Combining combining() const;

    /**
     * Return Decomposition style of this instance
     */
    Decomposition decomposition() const;

    /**
     * Return reading direction of this instance
     */
    Directionality directionality() const;

    /**
     * Return unicode script of this instance
     */
    UnicodeScript script() const;

    /**
     * Return high Byte of specified character
     * \param c utf16 character
     */
    static gbyte highByte(gchar c);

    /**
     * Return low Byte of specified character
     * \param c utf16 character
     */
    static gbyte lowByte(gchar c);

    /**
     * Return number represented by specified character
     * \param c utf16 character
     */
    static gint numericValue(gchar c);

    /**
     * Return lowercase form of specified character
     * \param c utf16 character
     */
    static gchar toLowerCase(gchar c);

    /**
     * Return uppercase from of specified character
     * \param c utf16 character
     */
    static gchar toUpperCase(gchar c);

    /**
     * Return title case form of specified character
     * \param c utf16 character
     */
    static gchar toTitleCase(gchar c);

    /**
     * Return mirror character of specified character
     * \param c utf16 character
     */
    static gchar mirror(gchar c);

    /**
     * Return supplementary character composed by specified surrogates codepoints
     * \param h high surrogate
     * \param l low surrogate
     */
    static gint joinSurrogates(gchar h, gchar l);

    /**
     * Return true if specified surrogates is high and low surrogates
     * \param h high surrogate
     * \param l low surrogate
     */
    static gbool isSurrogatesPair(gchar h, gchar l);

    /**
     * Return true if specified character represent a ASCII character
     * \param c utf16 character
     */
    static gbool isAscii(gchar c);

    /**
     * Return true if specified character represent a digit number
     * \param c utf16 character
     */
    static gbool isDigit(gchar c);

    /**
     * Return true if specified character represent the high part of supplementary character
     * \param c utf16 character
     */
    static gbool isHighSurrogate(gchar c);

    /**
     * Return true if specified character represent a BASIC LATIN character
     * \param c utf16 character
     */
    static gbool isLatin(gchar c);

    /**
     * Return true if specified character represent a letter (alphabetic)
     * \param c utf16 character
     */
    static gbool isLetter(gchar c);

    /**
     * Return true if specified character represent a letter or number (alphanumeric)
     * \param c utf16 character
     */
    static gbool isLetterOrNumber(gchar c);

    /**
     * Return true if specified character represent lowercase form of one character
     * \param c utf16 character
     */
    static gbool isLowerCase(gchar c);

    /**
     * Return true if specified character represent low part of supplementary character
     * \param c utf16 character
     */
    static gbool isLowSurrogate(gchar c);

    /**
     * Return true if specified character represent a mark
     * \param c utf16 character
     */
    static gbool isMark(gchar c);

    /**
     * Return true if specified character represent a mirrored character
     * \param c utf16 character
     */
    static gbool isMirrored(gchar c);

    /**
     * Return true if specified character not represent character
     * \param c utf16 character
     */
    static gbool isNonCharacter(gchar c);

    /**
     * Return true if specified character represent a number
     * \param c utf16 character
     */
    static gbool isNumber(gchar c);

    /**
     * Return true if specified character is representable character
     * \param c utf16 character
     */
    static gbool isPrintable(gchar c);

    /**
     * Return true if specified character represent a punctuation
     * \param c utf16 character
     */
    static gbool isPunctuation(gchar c);

    /**
     * Return true if specified character represent a white space
     * \param c utf16 character
     */
    static gbool isSpace(gchar c);

    /**
     * Return true if specified character represent a part of supplementary character
     * \param c utf16 character
     */
    static gbool isSurrogate(gchar c);

    /**
     * Return true if specified character represent a symbol
     * \param c utf16 character
     */
    static gbool isSymbol(gchar c);

    /**
     * Return true if specified character represent a title case form of one character
     * \param c utf16 character
     */
    static gbool isTitleCase(gchar c);

    /**
     * Return true if specified character represent a uppercase form of one character
     * \param c utf16 character
     */
    static gbool isUpperCase(gchar c);

    /**
     * Return generic category of specified character
     * \param c utf16 character
     */
    static Category category(gchar c);

    /**
     * Return generic combining class of specified character
     * \param c utf16 character
     */
    static Combining combining(gchar c);

    /**
     * Return decomposition style of specified character
     * \param c utf16 character
     */
    static Decomposition decomposition(gchar c);

    /**
     * Return reading direction of specified character
     * \param c utf16 character
     */
    static Directionality directionality(gchar c);

    /**
     * Return unicode script of specified character
     * \param c utf16 character
     */
    static UnicodeScript script(gchar c);

    /**
     * Return number represented by specified codepoint
     * \param c unicode codepoint
     */
    static gint numericValue(gint c);

    /**
     * Return lowercase form of character represented by specified codepoint
     * \param c unicode codepoint
     */
    static gint toLowerCase(gint c);

    /**
     * Return uppercase form of character represented by specified codepoint
     * \param c unicode codepoint
     */
    static gint toUpperCase(gint c);

    /**
     * Return title case form of character represented by specified codepoint
     * \param c unicode codepoint
     */
    static gint toTitleCase(gint c);

    /**
     * Return mirror character of character represented by specified codepoint
     * \param c unicode codepoint
     */
    static gint mirror(gint c);

    /**
     * Return high part of specified supplementary codepoint or -1 if is it not requires surrogates
     * \param c unicode codepoint
     */
    static gchar highSurrogate(gint c);

    /**
     * Return low part of specified supplementary codepoint or -1 if is it not requires surrogates
     * \param c unicode codepoint
     */
    static gchar lowSurrogate(gint c);

    /**
     * Return true if specified codepoint is valid unicode codepoint
     * \param c unicode codepoint
     */
    static gbool isValidCodePoint(gint c);

    /**
     * Return true if specified surrogates codepoint is high and low surrogates
     * \param h codepoint of high surrogate
     * \param l codepoint of low surrogate
     */
    static gbool isSurrogatesPair(gint h, gint l);

    /**
     * Return true if specified character codepoint represent codepoint of ASCII character
     * \param c unicode codepoint
     */
    static gbool isAscii(gint c);

    /**
     * Return true if specified character codepoint represent codepoint of digit character
     * \param c unicode codepoint
     */
    static gbool isDigit(gint c);

    /**
     * Return true if specified character codepoint represent codepoint of high part of supplementary character
     * \param c unicode codepoint
     */
    static gbool isHighSurrogate(gint c);

    /**
     * Return true if specified character codepoint represent codepoint of BASIC LATIN character
     * \param c unicode codepoint
     */
    static gbool isLatin(gint c);

    /**
     * Return true if specified character codepoint represent codepoint of letter (alpha) character
     * \param c unicode codepoint
     */
    static gbool isLetter(gint c);

    /**
     * Return true if specified character codepoint represent codepoint of letter or number
     * \param c unicode codepoint
     */
    static gbool isLetterOrNumber(gint c);

    /**
     * Return true if specified character codepoint represent codepoint of lowercase form of one character
     * \param c unicode codepoint
     */
    static gbool isLowerCase(gint c);

    /**
     * Return true if specified character codepoint represent codepoint of low part of supplementary character
     * \param c unicode codepoint
     */
    static gbool isLowSurrogate(gint c);

    /**
     * Return true if specified character codepoint represent codepoint of the mark
     * \param c unicode codepoint
     */
    static gbool isMark(gint c);

    /**
     * Return true if specified character codepoint represent codepoint of mirrored character
     * \param c unicode codepoint
     */
    static gbool isMirrored(gint c);

    /**
     * Return true if specified character codepoint represent codepoint of non character
     * \param c unicode codepoint
     */
    static gbool isNonCharacter(gint c);

    /**
     * Return true if specified character codepoint represent codepoint of number
     * \param c unicode codepoint
     */
    static gbool isNumber(gint c);

    /**
     * Return true if specified character codepoint represent codepoint of printable character
     * \param c unicode codepoint
     */
    static gbool isPrintable(gint c);

    /**
     * Return true if specified character codepoint represent codepoint of punctuation
     * \param c unicode codepoint
     */
    static gbool isPunctuation(gint c);

    /**
     * Return true if specified character codepoint represent codepoint of white space character
     * \param c unicode codepoint
     */
    static gbool isSpace(gint c);

    /**
     * Return true if specified character codepoint represent codepoint of part of supplementary character
     * \param c unicode codepoint
     */
    static gbool isSurrogate(gint c);

    /**
     * Return true if specified character codepoint represent codepoint of symbol
     * \param c unicode codepoint
     */
    static gbool isSymbol(gint c);

    /**
     * Return true if specified character codepoint represent codepoint of title case form of one character
     * \param c unicode codepoint
     */
    static gbool isTitleCase(gint c);

    /**
     * Return true if specified character codepoint represent codepoint of uppercase form of one character character
     * \param c unicode codepoint
     */
    static gbool isUpperCase(gint c);

    /**
     * Return generic category of character represented by specified unicode codepoint
     * \param c unicode codepoint
     */
    static Category category(gint c);

    /**
     * Return generic combining class of character represented by specified unicode codepoint
     * \param c unicode codepoint
     */
    static Combining combining(gint c);

    /**
     * Return decomposition style of character represented by specified unicode codepoint
     * \param c unicode codepoint
     */
    static Decomposition decomposition(gint c);

    /**
     * Return reading direction of character represented by specified unicode codepoint
     * \param c unicode codepoint
     */
    static Directionality directionality(gint c);

    /**
     * Return script of character represented by specified codepoint
     * \param c unicode codepoint
     */
    static UnicodeScript script(gint c);

    /**
     * Compare this instance with specified object
     * \param obj object to be compared
     */
    gint compareTo(Character const &obj) const override;

    /**
     * Compare two character codepoint
     * \param x the first operand
     * \param y the second operand
     */
    static gint compare(gchar x, gchar y);

    /**
     * Return value of this instance as char16
     */
    operator gchar() const;

    /**
     * Return value of this instance as char16
     */
    operator gchar &();

    /**
     * Return copy of this instance
     */
    Object &clone() const override;

    /**
     * Return new instance represented by specified utf16 character
     * \param c utf16 character
     */
    static Character valueOf(gchar c);

    /**
     * Return true if this instance equals specified object
     * \param obj object to be compared
     */
    gbool equals(const Object &obj) const override;

    static gbool isSupplementary(gint c);

    static gbool isBMP(gint c);

    static String toString(gint ch);

    String decompose() const;

    static String decompose(gint ch);

    glong hash() const override;

    CORE_FAST static gchar MIN = u'\u0000';

    CORE_FAST static gchar MAX = u'\uffff';

    CORE_FAST static gint MAX_CODEPOINT = 0x10ffff;

    CORE_FAST static gint MIN_SUPPLEMENTARY = 0x10000;

protected:
    /**
     * Set value of this instance with specified object
     */
    CORE_DEPRECATED void set(Object const &obj) override;

private:
    static const String UCD00;
    static const String UCD01;
    static const String UCD02;
    static const String UCD03;
    static const String UCD04;
    static const String UCD05;

    gchar value;
};


#endif //CORE_CHARACTER_H

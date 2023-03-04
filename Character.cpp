//
// Created by brunshweeck on 22/02/2023.
//

#include "Character.h"
#include "String.h"
#include "Enum.h"

Character::Character() : Character('\u0000') {}

Character::Character(u16 v) : value(v) {}

Character::Character(gbyte h, gbyte l) : value((u16) ((h & 0xFF) << 8 | (l & 0xFF))) {}

gchar Character::charValue() const {
    return value;
}


gbool Character::isAscii() const {
    return Character::isAscii(value);
}

gbool Character::isDigit() const {
    return Character::isDigit(value);
}

gbyte Character::highByte() const {
    return Character::highByte(value);
}

gbyte Character::lowByte() const {
    return Character::lowByte(value);
}

gchar Character::numericValue() const {
    return Character::numericValue(value);
}

gchar Character::toLowerCase() const {
    return Character::toLowerCase(value);
}

gchar Character::toUpperCase() const {
    return Character::toUpperCase(value);
}

gchar Character::toTitleCase() const {
    return Character::toTitleCase(value);
}

gchar Character::mirror() const {
    return Character::mirror(value);
}

gint Character::codepoint() const {
    return value;
}

gbool Character::isHighSurrogate() const {
    return Character::isHighSurrogate(value);
}

gbool Character::isLatin() const {
    return Character::isLatin(value);
}

gbool Character::isLetter() const {
    return Character::isLetter(value);
}

gbool Character::isLetterOrNumber() const {
    return Character::isLetterOrNumber(value);
}

gbool Character::isLowerCase() const {
    return Character::isLowerCase(value);
}

gbool Character::isLowSurrogate() const {
    return Character::isLowSurrogate(value);
}

gbool Character::isMark() const {
    return Character::isMark(value);
}

gbool Character::isMirrored() const {
    return Character::isMirrored(value);
}

gbool Character::isNonCharacter() const {
    return Character::isNonCharacter(value);
}

gbool Character::isNumber() const {
    return Character::isNumber(value);
}

gbool Character::isPrintable() const {
    return Character::isPrintable(value);
}

gbool Character::isPunctuation() const {
    return Character::isPunctuation(value);
}

gbool Character::isSpace() const {
    return Character::isSpace(value);
}

gbool Character::isSurrogate() const {
    return Character::isSurrogate(value);
}

gbool Character::isSymbol() const {
    return Character::isSymbol(value);
}

gbool Character::isTitleCase() const {
    return Character::isTitleCase(value);
}

gbool Character::isUpperCase() const {
    return Character::isUpperCase(value);
}

Character::Category Character::category() const {
    return Character::category(value);
}

Character::Combining Character::combining() const {
    return Character::combining(value);
}

Character::Decomposition Character::decomposition() const {
    return Character::decomposition(value);
}

Character::Directionality Character::directionality() const {
    return Character::directionality(value);
}

Character::UnicodeScript Character::script() const {
    return Character::script(value);
}

gbyte Character::highByte(u16 c) {
    return (gbyte) Integer::shiftRight(c, 8);
}

gbyte Character::lowByte(u16 c) {
    return (gbyte) (c & 0xFF);
}

gint Character::numericValue(u16 c) {
    return Character::numericValue(c & 0xFFFF);
}

gchar Character::toLowerCase(u16 c) {
    return Character::toLowerCase(c & 0xFFFF);
}

gchar Character::toUpperCase(u16 c) {
    return Character::toUpperCase(c & 0xFFFF);
}

gchar Character::toTitleCase(u16 c) {
    return Character::toTitleCase(c & 0xFFFF);
}

gchar Character::mirror(u16 c) {
    return Character::mirror(c & 0xFFFF);
}

gbool Character::isSurrogatesPair(u16 h, u16 l) {
    return Character::isHighSurrogate(h) && Character::isLowerCase(l);
}

gbool Character::isAscii(u16 c) {
    return Character::isAscii(c & 0xFFFF);
}

gbool Character::isDigit(u16 c) {
    return Character::isDigit(c & 0xFFFF);
}

gbool Character::isHighSurrogate(u16 ch) {
    return 0xD800 <= ch && ch < 0xDC00;
}

gbool Character::isLatin(u16 c) {
    return Character::isLatin(c & 0xFFFF);
}

gbool Character::isLetter(u16 c) {
    return Character::isLetter(c & 0xFFFF);
}

gbool Character::isLetterOrNumber(u16 c) {
    return Character::isLetterOrNumber(c & 0xFFFF);
}

gbool Character::isLowerCase(u16 c) {
    return Character::isLowerCase(c & 0xFFFF);
}

gbool Character::isLowSurrogate(u16 c) {
    return Character::isLowSurrogate(c & 0xFFFF);
}

gbool Character::isMark(u16 c) {
    return Character::isMark(c & 0xFFFF);
}

gbool Character::isMirrored(u16 c) {
    return Character::isMirrored(c & 0xFFFF);
}

gbool Character::isNonCharacter(u16 c) {
    return Character::isNonCharacter(c & 0xFFFF);
}

gbool Character::isNumber(u16 c) {
    return Character::isNumber(c & 0xFFFF);
}

gbool Character::isPrintable(u16 c) {
    return Character::isPrintable(c & 0xFFFF);
}

gbool Character::isPunctuation(u16 c) {
    return Character::isPunctuation(c & 0xFFFF);
}

gbool Character::isSpace(u16 c) {
    return Character::isSpace(c & 0xFFFF);
}

gbool Character::isSurrogate(u16 c) {
    return Character::isSurrogate(c & 0xFFFF);
}

gbool Character::isSymbol(u16 c) {
    return Character::isSymbol(c & 0xFFFF);
}

gbool Character::isTitleCase(u16 c) {
    return Character::isTitleCase(c & 0xFFFF);
}

gbool Character::isUpperCase(u16 c) {
    return Character::isUpperCase(c & 0xFFFF);
}

Character::Category Character::category(u16 c) {
    return Character::category(c & 0xFFFF);
}

Character::Combining Character::combining(u16 c) {
    return Character::combining(c & 0xFFFF);
}

Character::Decomposition Character::decomposition(u16 c) {
    return Character::decomposition(c & 0xFFFF);
}

Character::Directionality Character::directionality(u16 c) {
    return Character::directionality(c & 0xFFFF);
}

Character::UnicodeScript Character::script(u16 c) {
    return Character::script(c & 0xFFFF);
}

gint Character::compareTo(const Character &obj) const {
    return Character::compare(value, obj.value);
}

gint Character::compare(gchar x, gchar y) {
    return x - y;
}

Character::operator gchar() const {
    return charValue();
}

Character::operator gchar &() {
    return value;
}

gbool Character::equals(const Object &obj) const {
    if (this == &obj)
        return true;
    if (!dynamic_cast<Character const *>(&obj))
        return false;
    return compareTo((const Character &) obj) == 0;
}

Object &Character::clone() const {
    Character *c;
    try { c = new Character(value); } catch (...) {}
    return *c;
}

Character Character::valueOf(gchar c) {
    return c;
}

void Character::set(const Object &obj) {
    Character const *c = dynamic_cast<Character const *>(&obj);
    if (!c) {}
    value = c->value;
}

gbool Character::isSupplementary(gint c) {
    return 0xFFFF < c && c < 0x10FFFF;
}

gbool Character::isBMP(gint c) {
    return 0 < c && c < 0xFFFF;
}

#define SHOW_INDEX_1(ch, db) (gint)(db).charAt( \
        (ch) < 0x11000 ? (db).charAt((ch) >> 5) + ((ch) &0x001F) : (db).charAt((((ch) -0x11000) >> 8) + 0x0800) + ((ch) &0x00FF))

#define SHOW_INDEX_2(ch, db) (gint)(db).charAt(                                                                                                    \
        (ch) < 0x3400 ? (db).charAt((ch) >> 4) + ((ch) &0x000F) : (ch) < 0x00030000 ? (db).charAt((((ch) -0x3400) >> 8) + 0x0340) + ((ch) &0x00FF) \
                                                                                    : 0xFFFF)

#define GET_CATEGORY 0
#define GET_DIRECTION 1
#define GET_COMBINING 2
#define GET_JOINING 3
#define GET_NUMERIC 4
#define GET_MIRROR 5
#define GET_VERSION 6
#define GET_EAW 7
#define GET_NF_QC 8
#define IS_SPECIAL_LOWER 9
#define GET_LOWER 10
#define IS_SPECIAL_UPPER 11
#define GET_UPPER 12
#define IS_SPECIAL_TITLE 13
#define GET_TITLE 14
#define IS_SPECIAL_CASE_FOLD 15
#define GET_CASE_FOLD 16
#define GET_GBC 17
#define GET_WBC 18
#define GET_LBC 19
#define GET_SBC 20
#define GET_ID_NAS 21
#define GET_SCRIPT 22

#define SHOW_PROPERTY(index, name, db) (gint)(db).charAt(23 * (index) + (name))
#define SHOW_DATA(index, db) db.charAt(index)

gint Character::toLowerCase(gint ch) {
    if (!isValidCodePoint(ch))
        return ch;
    if (ch <= 0x007F)
        return 0x0041 <= ch && ch <= 0x005A ? ch + 0x0020 : ch;
    gint index = SHOW_INDEX_1(ch, UCD01);
    gbool isSpecialChar = (gbool) SHOW_PROPERTY(index, IS_SPECIAL_LOWER, UCD00);
    gint offset = SHOW_PROPERTY(index, GET_LOWER, UCD00);
    if (isSpecialChar) {
        gint specialOffset = UCD02.charAt(offset);
        if (specialOffset == 1) {
            gint specialChar = UCD02.charAt(offset + 1);
            return specialChar;
        }
        return ch;
    }
    return ch + offset;
}

gint Character::toTitleCase(gint ch) {
    if (!isValidCodePoint(ch))
        return ch;
    gint index = SHOW_INDEX_1(ch, UCD01);
    gbool isSpecialChar = (gbool) SHOW_PROPERTY(index, IS_SPECIAL_TITLE, UCD00);
    gint offset = SHOW_PROPERTY(index, GET_TITLE, UCD00);
    if (isSpecialChar) {
        gint specialOffset = UCD02.charAt(offset);
        if (specialOffset == 1) {
            gint specialChar = UCD02.charAt(offset + 1);
            return specialChar;
        }
        return ch;
    }
    return ch + offset;
}

gint Character::toUpperCase(gint ch) {
    if (!isValidCodePoint(ch))
        return ch;
    if (ch <= 0x007F)
        return 0x0061 <= ch && ch <= 0x007A ? ch - 0x0020 : ch;
    gint index = SHOW_INDEX_1(ch, UCD01);
    gbool isSpecialChar = (gbool) SHOW_PROPERTY(index, IS_SPECIAL_UPPER, UCD00);
    gint offset = SHOW_PROPERTY(index, GET_UPPER, UCD00);
    if (isSpecialChar) {
        gint specialOffset = UCD02.charAt(offset);
        if (specialOffset == 1) {
            gint specialChar = UCD02.charAt(offset + 1);
            return specialChar;
        }
        return ch;
    }
    return ch + offset;
}

gint Character::mirror(gint ch) {
    if (!isValidCodePoint(ch))
        return ch;
    gint index = SHOW_INDEX_1(ch, UCD01);
    gint offset = SHOW_PROPERTY(index, GET_MIRROR, UCD00);
    return ch + offset;
}

gint Character::numericValue(gint ch) {
    if (!isValidCodePoint(ch))
        return -1;
    if ('0' <= ch && ch <= '9')
        return ch - '0';
    if ('A' <= ch && ch <= 'Z')
        return ch - 'A';
    if ('a' <= ch && ch <= 'z')
        return ch - 'a';
    gint index = SHOW_INDEX_1(ch, UCD01);
    gint numeric = SHOW_PROPERTY(index, GET_NUMERIC, UCD00);
    return numeric;
}

gint Character::joinSurrogates(gchar high, gchar low) {
    if (!isSurrogatesPair(high, low))
        return -1;
    return (high << 10) + low - 0xDC00;
}

gbool Character::isDigit(gint ch) {
    if (!isValidCodePoint(ch))
        return false;
    return 0x0030 <= ch && ch <= 0x0039 || ch > 0x007F && category(ch) == Category::DECIMAL_DIGIT_NUMBER;
}

gbool Character::isLetter(gint ch) {
    if (!isValidCodePoint(ch))
        return false;
    if (isAscii(ch))
        return 0x0041 <= ch && ch <= 0x005A || 0x0061 <= ch && ch <= 0x007A;
    gint index = SHOW_INDEX_1(ch, UCD01);
    gint type = SHOW_PROPERTY(index, GET_CATEGORY, UCD00);
    return type & (1 << Enum<Category>::ordinal(Category::LOWERCASE_LETTER) |
                   1 << Enum<Category>::ordinal(Category::UPPERCASE_LETTER) |
                   1 << Enum<Category>::ordinal(Category::TITLECASE_LETTER) |
                   1 << Enum<Category>::ordinal(Category::MODIFIER_LETTER) |
                   1 << Enum<Category>::ordinal(Category::OTHER_LETTER));
}

gbool Character::isLetterOrNumber(gint ch) {
    if (!isValidCodePoint(ch))
        return false;
    if (isAscii(ch))
        return 0x0030 <= ch && ch <= 0x0039 || 0x0041 <= ch && ch <= 0x005A || 0x0061 <= ch && ch <= 0x007A;
    gint index = SHOW_INDEX_1(ch, UCD01);
    gint type = SHOW_PROPERTY(index, GET_CATEGORY, UCD00);
    return type & (1 << Enum<Category>::ordinal(Category::LOWERCASE_LETTER) |
                   1 << Enum<Category>::ordinal(Category::UPPERCASE_LETTER) |
                   1 << Enum<Category>::ordinal(Category::TITLECASE_LETTER) |
                   1 << Enum<Category>::ordinal(Category::MODIFIER_LETTER) |
                   1 << Enum<Category>::ordinal(Category::LETTER_NUMBER) |
                   1 << Enum<Category>::ordinal(Category::DECIMAL_DIGIT_NUMBER) |
                   1 << Enum<Category>::ordinal(Category::OTHER_NUMBER));
}

gbool Character::isLowerCase(gint ch) {
    if (!isValidCodePoint(ch))
        return false;
    if (isAscii(ch))
        return 0x0061 <= ch && ch <= 0x007A;
    return category(ch) == Category::LOWERCASE_LETTER;
}

gbool Character::isLowSurrogate(gint ch) {
    return 0xDC00 <= ch && ch < 0xE000;
}


gbool Character::isHighSurrogate(gint ch) {
    return 0xD800 <= ch && ch < 0xDC00;
}

gbool Character::isMark(gint ch) {
    if (!isValidCodePoint(ch))
        return false;
    gint index = SHOW_INDEX_1(ch, UCD01);
    gint type = SHOW_PROPERTY(index, GET_CATEGORY, UCD00);
    return type & (1 << Enum<Category>::ordinal(Category::ENCLOSING_MARK) |
                   1 << Enum<Category>::ordinal(Category::NON_SPACING_MARK) |
                   1 << Enum<Category>::ordinal(Category::COMBINING_SPACING_MARK));
}

gbool Character::isMirrored(gint ch) {
    if (!isValidCodePoint(ch))
        return false;
    gint index = SHOW_INDEX_1(ch, UCD01);
    gint offset = SHOW_PROPERTY(index, GET_CATEGORY, UCD00);
    return offset == 0;
}

gbool Character::isNonCharacter(gint ch) {
    return 0xFDD0 <= ch && ch <= 0xFDEF || 0xFFFE <= ch && ch <= 0x0010FFFF && (ch & 0xFFFE) == 0xFFFE;
}

gbool Character::isNumber(gint ch) {
    if (!isValidCodePoint(ch))
        return false;
    if (isAscii(ch))
        return 0x0030 <= ch && ch <= 0x0039;
    gint index = SHOW_INDEX_1(ch, UCD01);
    gint type = SHOW_PROPERTY(index, GET_CATEGORY, UCD00);
    return type & (1 << Enum<Category>::ordinal(Category::LETTER_NUMBER) |
                   1 << Enum<Category>::ordinal(Category::DECIMAL_DIGIT_NUMBER) |
                   1 << Enum<Category>::ordinal(Category::OTHER_NUMBER));
}

gbool Character::isPunctuation(gint ch) {
    if (!isValidCodePoint(ch))
        return false;
    gint index = SHOW_INDEX_1(ch, UCD01);
    gint type = SHOW_PROPERTY(index, GET_CATEGORY, UCD00);
    return type & (1 << Enum<Category>::ordinal(Category::INITIAL_QUOTE_PUNCTUATION) |
                   1 << Enum<Category>::ordinal(Category::FINAL_QUOTE_PUNCTUATION) |
                   1 << Enum<Category>::ordinal(Category::START_PUNCTUATION) |
                   1 << Enum<Category>::ordinal(Category::END_PUNCTUATION) |
                   1 << Enum<Category>::ordinal(Category::DASH_PUNCTUATION) |
                   1 << Enum<Category>::ordinal(Category::CONNECTOR_PUNCTUATION) |
                   1 << Enum<Category>::ordinal(Category::OTHER_PUNCTUATION));
}

gbool Character::isPrintable(gint ch) {
    if (!isValidCodePoint(ch))
        return false;
    gint index = SHOW_INDEX_1(ch, UCD01);
    gint type = SHOW_PROPERTY(index, GET_CATEGORY, UCD00);
    return (type & (1 << Enum<Category>::ordinal(Category::CONTROL) |
                    1 << Enum<Category>::ordinal(Category::FORMAT) |
                    1 << Enum<Category>::ordinal(Category::SURROGATE) |
                    1 << Enum<Category>::ordinal(Category::UNASSIGNED))) == 0;
}

gbool Character::isSpace(gint ch) {
    if (!isValidCodePoint(ch))
        return false;
    if (isAscii(ch))
        return ch == 0x0020 || 0x0009 <= ch && ch <= 0x000D;
    if (ch == 0x0085 || ch == 0x00A0)
        return true;
    gint index = SHOW_INDEX_1(ch, UCD01);
    gint type = SHOW_PROPERTY(index, GET_CATEGORY, UCD00);
    return type & (1 << Enum<Category>::ordinal(Category::SPACE_SEPARATOR) |
                   1 << Enum<Category>::ordinal(Category::LINE_SEPARATOR) |
                   1 << Enum<Category>::ordinal(Category::PARAGRAPH_SEPARATOR));
}

gbool Character::isSurrogate(gint ch) {
    return 0xD800 <= ch && ch < 0xE000;
}

gbool Character::isSymbol(gint ch) {
    if (!isValidCodePoint(ch))
        return false;
    gint index = SHOW_INDEX_1(ch, UCD01);
    gint type = SHOW_PROPERTY(index, GET_CATEGORY, UCD00);
    return type & (1 << Enum<Category>::ordinal(Category::CURRENCY_SYMBOL) |
                   1 << Enum<Category>::ordinal(Category::MATH_SYMBOL) |
                   1 << Enum<Category>::ordinal(Category::MODIFIER_SYMBOL) |
                   1 << Enum<Category>::ordinal(Category::OTHER_SYMBOL));
}

gbool Character::isTitleCase(gint ch) {
    if (!isValidCodePoint(ch))
        return false;
    return !isAscii(ch) && category(ch) == Category::TITLECASE_LETTER;
}

gbool Character::isUpperCase(gint ch) {
    if (!isValidCodePoint(ch))
        return false;
    if (isAscii(ch))
        return 0x0041 <= ch && ch <= 0x005A;
    return category(ch) == Category::UPPERCASE_LETTER;
}

gbool Character::isValidCodePoint(gint codepoint) {
    return 0 <= codepoint && codepoint < 0x00110000;
}

Character::Category Character::category(gint ch) {
    if (!isValidCodePoint(ch))
        return Category::UNASSIGNED;
    gint index = SHOW_INDEX_1(ch, UCD01);
    gint type = SHOW_PROPERTY(index, GET_CATEGORY, UCD00);
    return (Category) type;
}

Character::UnicodeScript Character::script(gint c) {
    if (!isValidCodePoint(c))
        return UnicodeScript::UNKNOWN;
    gint index = SHOW_INDEX_1(c, UCD01);
    gint type = SHOW_PROPERTY(index, GET_SCRIPT, UCD00);
    return (UnicodeScript) type;
}

Character::Directionality Character::directionality(i32 ch) {
    if (!isValidCodePoint(ch))
        return Directionality::UNDEFINED;
    gint index = SHOW_INDEX_1(ch, UCD01);
    gint dir = SHOW_PROPERTY(index, GET_DIRECTION, UCD00);
    return (Directionality) dir;
}

Character::Decomposition Character::decomposition(gint ch) {
    if (!isValidCodePoint(ch))
        return Decomposition::NONE;
    if (0xAC00 <= ch && ch <= 0xD7A4)
        return Decomposition::CANONICAL;
    gint index = SHOW_INDEX_2(ch, UCD04);
    if (index == 0xFFFF)
        return Decomposition::NONE;
    return (Decomposition) (SHOW_DATA(index, UCD03) & 0xFF);
}

Character::Combining Character::combining(gint ch) {
    if (!isValidCodePoint(ch))
        return Combining::IOTA_SUBSCRIPT;
    gint index = SHOW_INDEX_1(ch, UCD01);
    gint ccc = SHOW_PROPERTY(index, GET_COMBINING, UCD00);
    return (Combining) ccc;
}

String Character::toString(gint ch) {
    if (!isValidCodePoint(ch))
        return {};
    else if (ch < 0x00010000) {
        gchar c[] = {(gchar) ch, 0};
        return c;
    } else {
        gchar h = highSurrogate(ch);
        gchar l = lowSurrogate(ch);
        gchar chs[3] = {h, l, 0x0000};
        return chs;
    }
}

String Character::decompose() const {
    return decompose(value);
}

String Character::decompose(gint ch) {
    if (!isValidCodePoint(ch))
        return {};
    if (0xAC00 <= ch && ch <= 0xD7A4) {
        gint i = ch - 0xAC00;
        gchar chs[4] = {
                (gchar) (0x1100 + i / (21 * 28)),       // L
                (gchar) (0x1161 + (i % (21 * 28)) / 28),// V
                (gchar) (0x11A7 + i % 28),              // T
                (gchar) 0,                              // END
        };
        return String(chs, 0, chs[2] == 0x11A7 ? 2 : 3);
    }
    gint index = SHOW_INDEX_2(ch, UCD04);
    if (index == 0xFFFF)
        return {};
    gint len = SHOW_DATA(index, UCD03) >> 8;

    static gchar chs[64] = {
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0};
    gint i = 0;
    for (i = 0; i < len; ++i)
        chs[i] = SHOW_DATA(i, UCD03);
    chs[i] = 0x0000;
    return String(chs, 0, len);
}

glong Character::hash() const {
    return codepoint();
}

gbool Character::isAscii(gint ch) {
    return 0 <= ch && ch < 0x0080;
}

gbool Character::isLatin(gint ch) {
    return 0x0000 <= ch && ch <= 0x00FF;
}

gchar Character::lowSurrogate(gint c) {
    return (gchar) (!isValidCodePoint(c) ? -1 : (c % 0x0400) + 0xDC00);
}

gchar Character::highSurrogate(gint c) {
    return (gchar) (!isValidCodePoint(c) ? -1 : (c >> 10) - 0xD7C0);
}

gbool Character::isSurrogatesPair(gint h, gint l) {
    return isHighSurrogate(h) && isLowerCase(l) && isBMP(h) && isBMP(l);
}

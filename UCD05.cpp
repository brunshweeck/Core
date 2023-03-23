//
// Created by brunshweeck on 02/03/2023.
//

#include "Character.h"
#include "String.h"
#include "Enum.h"

static gint function() {
    Enum<Character::Category>::alias = [](Character::Category value) -> String {
        switch (value) {
            case Character::Category::UNASSIGNED:
                return u"UNASSIGNED";
            case Character::Category::UPPERCASE_LETTER:
                return u"UPPERCASE LETTER";
            case Character::Category::LOWERCASE_LETTER:
                return u"LOWERCASE LETTER";
            case Character::Category::TITLECASE_LETTER:
                return u"TITLECASE LETTER";
            case Character::Category::MODIFIER_LETTER:
                return u"MODIFIER LETTER";
            case Character::Category::OTHER_LETTER:
                return u"OTHER LETTER";
            case Character::Category::NON_SPACING_MARK:
                return u"NON SPACING MARK";
            case Character::Category::ENCLOSING_MARK:
                return u"ENCLOSING MARK";
            case Character::Category::COMBINING_SPACING_MARK:
                return u"COMBINING SPACING MARK";
            case Character::Category::DECIMAL_DIGIT_NUMBER:
                return u"DECIMAL DIGIT NUMBER";
            case Character::Category::LETTER_NUMBER:
                return u"LETTER NUMBER";
            case Character::Category::OTHER_NUMBER:
                return u"OTHER NUMBER";
            case Character::Category::SPACE_SEPARATOR:
                return u"SPACE SEPARATOR";
            case Character::Category::LINE_SEPARATOR:
                return u"LINE SEPARATOR";
            case Character::Category::PARAGRAPH_SEPARATOR:
                return u"PARAGRAPH SEPARATOR";
            case Character::Category::CONTROL:
                return u"CONTROL";
            case Character::Category::FORMAT:
                return u"FORMAT";
            case Character::Category::PRIVATE_USE:
                return u"PRIVATE USE";
            case Character::Category::SURROGATE:
                return u"SURROGATE";
            case Character::Category::DASH_PUNCTUATION:
                return u"DASH PUNCTUATION";
            case Character::Category::START_PUNCTUATION:
                return u"START PUNCTUATION";
            case Character::Category::END_PUNCTUATION:
                return u"END PUNCTUATION";
            case Character::Category::CONNECTOR_PUNCTUATION:
                return u"CONNECTOR PUNCTUATION";
            case Character::Category::OTHER_PUNCTUATION:
                return u"OTHER PUNCTUATION";
            case Character::Category::MATH_SYMBOL:
                return u"MATH SYMBOL";
            case Character::Category::CURRENCY_SYMBOL:
                return u"CURRENCY SYMBOL";
            case Character::Category::MODIFIER_SYMBOL:
                return u"MODIFIER SYMBOL";
            case Character::Category::OTHER_SYMBOL:
                return u"OTHER SYMBOL";
            case Character::Category::FINAL_QUOTE_PUNCTUATION:
                return u"FINAL QUOTE PUNCTUATION";
            case Character::Category::INITIAL_QUOTE_PUNCTUATION:
                return u"INITIAL QUOTE PUNCTUATION";
            default:
                return u"";
        }
    };
    Enum<Character::Decomposition>::alias = [](Character::Decomposition value) -> String {
        switch (value) {
            case Character::Decomposition::NONE:
                return u"NOT REGISTERED";
            case Character::Decomposition::CANONICAL:
                return u"CANONICAL";
            case Character::Decomposition::FONT:
                return u"FONT";
            case Character::Decomposition::NO_BREAK:
                return u"NO_BREAK";
            case Character::Decomposition::INITIAL:
                return u"INITIAL";
            case Character::Decomposition::MEDIAL:
                return u"MEDIAL";
            case Character::Decomposition::FINAL:
                return u"FINAL";
            case Character::Decomposition::ISOLATED:
                return u"ISOLATED";
            case Character::Decomposition::CIRCLE:
                return u"CIRCLE";
            case Character::Decomposition::SUPER:
                return u"SUPER";
            case Character::Decomposition::SUB:
                return u"SUB";
            case Character::Decomposition::VERTICAL:
                return u"VERTIAL";
            case Character::Decomposition::WIDE:
                return u"WIDE";
            case Character::Decomposition::NARROW:
                return u"NARROW";
            case Character::Decomposition::SMALL:
                return u"SMALL";
            case Character::Decomposition::SQUARE:
                return u"SQUARE";
            case Character::Decomposition::COMPAT:
                return u"COMPACT";
            case Character::Decomposition::FRACTION:
                return u"FRACTION";
            default:
                return u"";
        }
    };
    Enum<Character::Combining>::alias = [](Character::Combining value) -> String {
        switch (value) {
            case Character::Combining::BELOW_LEFT_ATTACHED:
                return u"BELOW LEFT ATTACHED";
            case Character::Combining::BELOW_ATTACHED:
                return u"BELOW ATTACHED";
            case Character::Combining::BELOW_RIGHT_ATTACHED:
                return u"BELOW RIGHT ATTACHED";
            case Character::Combining::LEFT_ATTACHED:
                return u"LEFT ATTACHED";
            case Character::Combining::RIGHT_ATTACHED:
                return u"RIGHT ATTACHED";
            case Character::Combining::ABOVE_LEFT_ATTACHED:
                return u"ABOVE LEFT ATTACHED";
            case Character::Combining::ABOVE_ATTACHED:
                return u"ABOVE ATTACHED";
            case Character::Combining::ABOVE_RIGHT_ATTACHED:
                return u"ABOVE RIGHT ATTACHED";
            case Character::Combining::BELOW_LEFT:
                return u"BELOW LEFT";
            case Character::Combining::BELOW:
                return u"BELOW";
            case Character::Combining::BELOW_RIGHT:
                return u"BELOW RIGHT";
            case Character::Combining::LEFT:
                return u"LEFT";
            case Character::Combining::RIGHT:
                return u"RIGHT";
            case Character::Combining::ABOVE_LEFT:
                return u"ABOVE LEFT";
            case Character::Combining::ABOVE:
                return u"ABOVE";
            case Character::Combining::ABOVE_RIGHT:
                return u"ABOVE RIGHT";
            case Character::Combining::DOUBLE_BELOW:
                return u"DOUBLE BELOW";
            case Character::Combining::DOUBLE_ABOVE:
                return u"DOUBLE ABOVE";
            case Character::Combining::IOTA_SUBSCRIPT:
                return u"ITOA SUBSCRIPT";
            default:
                return u"";
        }
    };
    Enum<Character::UnicodeScript>::alias = [](Character::UnicodeScript value) -> String {
        switch (value) {
            case Character::UnicodeScript::COMMON:
                return u"COMMON";
            case Character::UnicodeScript::LATIN:
                return u"LATIN";
            case Character::UnicodeScript::GREEK:
                return u"GREEK";
            case Character::UnicodeScript::CYRILLIC:
                return u"CYRILLIC";
            case Character::UnicodeScript::ARMENIAN:
                return u"ARMENIAN";
            case Character::UnicodeScript::HEBREW:
                return u"HEBREW";
            case Character::UnicodeScript::ARABIC:
                return u"ARABIC";
            case Character::UnicodeScript::SYRIAC:
                return u"SYRIAC";
            case Character::UnicodeScript::THAANA:
                return u"THAANA";
            case Character::UnicodeScript::DEVANAGARI:
                return u"DEVANAGARI";
            case Character::UnicodeScript::BENGALI:
                return u"BENGALI";
            case Character::UnicodeScript::GURMUKHI:
                return u"GURMUKHI";
            case Character::UnicodeScript::GUJARATI:
                return u"GUJARATI";
            case Character::UnicodeScript::ORIYA:
                return u"ORIYA";
            case Character::UnicodeScript::TAMIL:
                return u"TAMIL";
            case Character::UnicodeScript::TELUGU:
                return u"TELUGU";
            case Character::UnicodeScript::KANNADA:
                return u"KANNADA";
            case Character::UnicodeScript::MALAYALAM:
                return u"MALAYALAM";
            case Character::UnicodeScript::SINHALA:
                return u"SINHALA";
            case Character::UnicodeScript::THAI:
                return u"THAI";
            case Character::UnicodeScript::LAO:
                return u"LAO";
            case Character::UnicodeScript::TIBETAN:
                return u"TIBETAN";
            case Character::UnicodeScript::MYANMAR:
                return u"MYANMAR";
            case Character::UnicodeScript::GEORGIAN:
                return u"GEORGIAN";
            case Character::UnicodeScript::HANGUL:
                return u"HANGUL";
            case Character::UnicodeScript::ETHIOPIC:
                return u"ETHIOPIC";
            case Character::UnicodeScript::CHEROKEE:
                return u"CHEROKEE";
            case Character::UnicodeScript::CANADIAN_ABORIGINAL:
                return u"CANADIAN ABORIGINAL";
            case Character::UnicodeScript::OGHAM:
                return u"OGHAM";
            case Character::UnicodeScript::RUNIC:
                return u"RUNIC";
            case Character::UnicodeScript::KHMER:
                return u"KHMER";
            case Character::UnicodeScript::MONGOLIAN:
                return u"MONGOLIAN";
            case Character::UnicodeScript::HIRAGANA:
                return u"HIRAGANA";
            case Character::UnicodeScript::KATAKANA:
                return u"KATAKANA";
            case Character::UnicodeScript::BOPOMOFO:
                return u"BOPOMOFO";
            case Character::UnicodeScript::HAN:
                return u"HAN";
            case Character::UnicodeScript::YI:
                return u"YI";
            case Character::UnicodeScript::OLD_ITALIC:
                return u"OLD ITALIC";
            case Character::UnicodeScript::GOTHIC:
                return u"GOTHIC";
            case Character::UnicodeScript::DESERET:
                return u"DESERET";
            case Character::UnicodeScript::INHERITED:
                return u"INHERITED";
            case Character::UnicodeScript::TAGALOG:
                return u"TAGALOG";
            case Character::UnicodeScript::HANUNOO:
                return u"HANUNOO";
            case Character::UnicodeScript::BUHID:
                return u"BUHID";
            case Character::UnicodeScript::TAGBANWA:
                return u"TAGBANWA";
            case Character::UnicodeScript::LIMBU:
                return u"LIMBU";
            case Character::UnicodeScript::TAI_LE:
                return u"TAI LE";
            case Character::UnicodeScript::LINEAR_B:
                return u"LINEAR B";
            case Character::UnicodeScript::UGARITIC:
                return u"UGARITIC";
            case Character::UnicodeScript::SHAVIAN:
                return u"SHAVIAN";
            case Character::UnicodeScript::OSMANYA:
                return u"OSMANYA";
            case Character::UnicodeScript::CYPRIOT:
                return u"CYPRIOT";
            case Character::UnicodeScript::BRAILLE:
                return u"BRAILLE";
            case Character::UnicodeScript::BUGINESE:
                return u"BUGINESE";
            case Character::UnicodeScript::NEW_TAI_LUE:
                return u"NEW TAI LUE";
            case Character::UnicodeScript::GLAGOLITIC:
                return u"GLAGOLITIC";
            case Character::UnicodeScript::TIFINAGH:
                return u"TIFINAGH";
            case Character::UnicodeScript::SYLOTI_NAGRI:
                return u"SYLOTI NAGRI";
            case Character::UnicodeScript::OLD_PERSIAN:
                return u"OLD PERSIAN";
            case Character::UnicodeScript::KHAROSHTHI:
                return u"KHAROSHTHI";
            case Character::UnicodeScript::BALINESE:
                return u"BALINESE";
            case Character::UnicodeScript::CUNEIFORM:
                return u"CUNEIFORM";
            case Character::UnicodeScript::PHOENICIAN:
                return u"PHOENICIAN";
            case Character::UnicodeScript::PHAGS_PA:
                return u"PHAGS PA";
            case Character::UnicodeScript::NKO:
                return u"NKO";
            case Character::UnicodeScript::SUNDANESE:
                return u"SUNDANESE";
            case Character::UnicodeScript::BATAK:
                return u"BATAK";
            case Character::UnicodeScript::LEPCHA:
                return u"LEPCHA";
            case Character::UnicodeScript::OL_CHIKI:
                return u"OL CHIKI";
            case Character::UnicodeScript::VAI:
                return u"VAI";
            case Character::UnicodeScript::SAURASHTRA:
                return u"SAURASHTRA";
            case Character::UnicodeScript::KAYAH_LI:
                return u"KAYAH LI";
            case Character::UnicodeScript::REJANG:
                return u"REJANG";
            case Character::UnicodeScript::LYCIAN:
                return u"LYCIAN";
            case Character::UnicodeScript::CARIAN:
                return u"CARIAN";
            case Character::UnicodeScript::LYDIAN:
                return u"LYDIAN";
            case Character::UnicodeScript::CHAM:
                return u"CHAM";
            case Character::UnicodeScript::TAI_THAM:
                return u"TAI_THAM";
            case Character::UnicodeScript::TAI_VIET:
                return u"TAI VIET";
            case Character::UnicodeScript::AVESTAN:
                return u"AVESTAN";
            case Character::UnicodeScript::EGYPTIAN_HIEROGLYPHS:
                return u"EGYPTIAN HIEROGLYPHS";
            case Character::UnicodeScript::SAMARITAN:
                return u"SAMARITAN";
            case Character::UnicodeScript::MANDAIC:
                return u"MANDAIC";
            case Character::UnicodeScript::LISU:
                return u"LISU";
            case Character::UnicodeScript::BAMUM:
                return u"BAMUM";
            case Character::UnicodeScript::JAVANESE:
                return u"JAVANESE";
            case Character::UnicodeScript::MEETEI_MAYEK:
                return u"MEETEI MAYEK";
            case Character::UnicodeScript::IMPERIAL_ARAMAIC:
                return u"IMPERIAL ARAMAIC";
            case Character::UnicodeScript::OLD_SOUTH_ARABIAN:
                return u"OLD SOUTH ARABIAN";
            case Character::UnicodeScript::INSCRIPTIONAL_PARTHIAN:
                return u"INSCRIPTIONAL PARTHIAN";
            case Character::UnicodeScript::INSCRIPTIONAL_PAHLAVI:
                return u"INSCRIPTIONAL PAHLAVI";
            case Character::UnicodeScript::OLD_TURKIC:
                return u"OLD TURKIC";
            case Character::UnicodeScript::BRAHMI:
                return u"BRAHMI";
            case Character::UnicodeScript::KAITHI:
                return u"KAITHI";
            case Character::UnicodeScript::MEROITIC_HIEROGLYPHS:
                return u"MEROITIC HIEROGLYPHS";
            case Character::UnicodeScript::MEROITIC_CURSIVE:
                return u"MEROITIC CURSIVE";
            case Character::UnicodeScript::SORA_SOMPENG:
                return u"SORA SOMPENG";
            case Character::UnicodeScript::CHAKMA:
                return u"CHAKMA";
            case Character::UnicodeScript::SHARADA:
                return u"SHARADA";
            case Character::UnicodeScript::TAKRI:
                return u"TAKRI";
            case Character::UnicodeScript::MIAO:
                return u"MIAO";
            case Character::UnicodeScript::CAUCASIAN_ALBANIAN:
                return u"CAUCASIAN ALBANIAN";
            case Character::UnicodeScript::BASSA_VAH:
                return u"BASSA VAH";
            case Character::UnicodeScript::DUPLOYAN:
                return u"DUPLOYAN";
            case Character::UnicodeScript::ELBASAN:
                return u"GRANTHA";
            case Character::UnicodeScript::GRANTHA:
                return u"CARIAN";
            case Character::UnicodeScript::PAHAWH_HMONG:
                return u"PAHAWH HMONG";
            case Character::UnicodeScript::KHOJKI:
                return u"KHOJKI";
            case Character::UnicodeScript::LINEAR_A:
                return u"LINEAR A";
            case Character::UnicodeScript::MAHAJANI:
                return u"MAHAJANI";
            case Character::UnicodeScript::MANICHAEAN:
                return u"MANICHAEAN";
            case Character::UnicodeScript::MENDE_KIKAKUI:
                return u"MENDE KIKAKUI";
            case Character::UnicodeScript::MODI:
                return u"MODI";
            case Character::UnicodeScript::MRO:
                return u"MRO";
            case Character::UnicodeScript::OLD_NORTH_ARABIAN:
                return u"OLD NORTH ARABIAN";
            case Character::UnicodeScript::NABATAEAN:
                return u"NABATAEAN";
            case Character::UnicodeScript::PALMYRENE:
                return u"PALMYRENE";
            case Character::UnicodeScript::PAU_CIN_HAU:
                return u"OLD PERMIC";
            case Character::UnicodeScript::OLD_PERMIC:
                return u"CARIAN";
            case Character::UnicodeScript::PSALTER_PAHLAVI:
                return u"PSALTER PAHLAVI";
            case Character::UnicodeScript::SIDDHAM:
                return u"SIDDHAM";
            case Character::UnicodeScript::KHUDAWADI:
                return u"KHUDAWADI";
            case Character::UnicodeScript::TIRHUTA:
                return u"TIRHUTA";
            case Character::UnicodeScript::WARANG_CITI:
                return u"WARANG CITI";
            case Character::UnicodeScript::AHOM:
                return u"AHOM";
            case Character::UnicodeScript::ANATOLIAN_HIEROGLYPHS:
                return u"ANATOLIAN HIEROGLYPHS";
            case Character::UnicodeScript::HATRAN:
                return u"HATRAN";
            case Character::UnicodeScript::MULTANI:
                return u"MULTANI";
            case Character::UnicodeScript::OLD_HUNGARIAN:
                return u"OLD HUNGARIAN";
            case Character::UnicodeScript::SIGNWRITING:
                return u"SIGNWRITING";
            case Character::UnicodeScript::ADLAM:
                return u"ADLAM";
            case Character::UnicodeScript::BHAIKSUKI:
                return u"BHAIKSUKI";
            case Character::UnicodeScript::MARCHEN:
                return u"MARCHEN";
            case Character::UnicodeScript::NEWA:
                return u"NEWA";
            case Character::UnicodeScript::OSAGE:
                return u"OSAGE";
            case Character::UnicodeScript::TANGUT:
                return u"TANGUT";
            case Character::UnicodeScript::MASARAM_GONDI:
                return u"MASARAM GONDI";
            case Character::UnicodeScript::NUSHU:
                return u"NUSHU";
            case Character::UnicodeScript::SOYOMBO:
                return u"SOYOMBO";
            case Character::UnicodeScript::ZANABAZAR_SQUARE:
                return u"ZANABAZAR SQUARE";
            case Character::UnicodeScript::HANIFI_ROHINGYA:
                return u"HANIFI ROHINGYA";
            case Character::UnicodeScript::OLD_SOGDIAN:
                return u"OLD SOGDIAN";
            case Character::UnicodeScript::SOGDIAN:
                return u"SOGDIAN";
            case Character::UnicodeScript::DOGRA:
                return u"DOGRA";
            case Character::UnicodeScript::GUNJALA_GONDI:
                return u"GUNJALA GONDI";
            case Character::UnicodeScript::MAKASAR:
                return u"MAKASAR";
            case Character::UnicodeScript::MEDEFAIDRIN:
                return u"MEDEFAIDRIN";
            case Character::UnicodeScript::ELYMAIC:
                return u"ELYMAIC";
            case Character::UnicodeScript::NANDINAGARI:
                return u"NANDINAGARI";
            case Character::UnicodeScript::NYIAKENG_PUACHUE_HMONG:
                return u"NYIAKENG PUACHUE HMONG";
            case Character::UnicodeScript::WANCHO:
                return u"WANCHO";
            case Character::UnicodeScript::YEZIDI:
                return u"YEZIDI";
            case Character::UnicodeScript::CHORASMIAN:
                return u"CHORASMIAN";
            case Character::UnicodeScript::DIVES_AKURU:
                return u"DIVES AKURU";
            case Character::UnicodeScript::KHITAN_SMALL_SCRIPT:
                return u"KHITAN SMALL SCRIPT";
            case Character::UnicodeScript::CYPRO_MINOAN:
                return u"CYPRO MINOAN";
            case Character::UnicodeScript::OLD_UYGHUR:
                return u"OLD UYGHUR";
            case Character::UnicodeScript::TANGSA:
                return u"TANGSA";
            case Character::UnicodeScript::TOTO:
                return u"TOTO";
            case Character::UnicodeScript::VITHKUQI:
                return u"VITHKUQI";
            case Character::UnicodeScript::SCRIPT_COUNT:
                return u"SCRIPT COUNT";
            case Character::UnicodeScript::UNKNOWN:
                return u"UNKNOWN";
            default:
                return u"";
        }
    };
    Enum<Character::Category> __var0000000000234567891 = Character::Category::DECIMAL_DIGIT_NUMBER;
    Enum<Character::Decomposition> __var0000000000345678912 = Character::Decomposition::FRACTION;
    Enum<Character::Combining> __var0000000000456789123 = Character::Combining::BELOW_LEFT_ATTACHED;
    Enum<Character::UnicodeScript> __var0000000000567891234 = Character::UnicodeScript::ANATOLIAN_HIEROGLYPHS;
    String __str0000000000000234567891 = __var0000000000234567891.toString();
    String __str0000000000000345678912 = __var0000000000345678912.toString();
    String __str0000000000000456789123 = __var0000000000456789123.toString();
    String __str0000000000000567891234 = __var0000000000567891234.toString();
    return 0;
}

static gint _ = function();

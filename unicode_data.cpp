#include "./unicode_data.h"

namespace langdetect {

UnicodeBlock UnicodeData::unicodeblock(uint32_t const &code) {
    if(code <= 0x7f) {
        return UNICODE_BLOCK_BASIC_LATIN;
    } else if(code <= 0xff) {
        return UNICODE_BLOCK_LATIN_1_SUPPLEMENT;
    } else if(code <= 0x0fff) {
        if(code <= 0x02ff) {
            if(code <= 0x017f) return UNICODE_BLOCK_LATIN_EXTENDED_A;
            else if(code <= 0x024f) return UNICODE_BLOCK_LATIN_EXTENDED_B;
            else if(code <= 0x02af) return UNICODE_BLOCK_IPA_EXTENSIONS;
            else return UNICODE_BLOCK_SPACING_MODIFIER_LETTERS;
        } else if(code <= 0x03ff) {
            if(code <= 0x036f) return UNICODE_BLOCK_COMBINING_DIACRITICAL_MARKS;
            else return UNICODE_BLOCK_GREEK_AND_COPTIC;
        } else if(code <= 0x04ff) {
            return UNICODE_BLOCK_CYRILLIC;
        } else if(code <= 0x05ff) {
            if(code <= 0x052f) return UNICODE_BLOCK_CYRILLIC_SUPPLEMENT;
            else if(code <= 0x058f) return UNICODE_BLOCK_ARMENIAN;
            else return UNICODE_BLOCK_HEBREW;
        } else if(code <= 0x06ff) {
            return UNICODE_BLOCK_ARABIC;
        } else if(code <= 0x07ff) {
            if(code <= 0x074f) return UNICODE_BLOCK_SYRIAC;
            else if(code <= 0x077f) return UNICODE_BLOCK_ARABIC_SUPPLEMENT;
            else if(code <= 0x07bf) return UNICODE_BLOCK_THAANA;
            else return UNICODE_BLOCK_NKO;
        } else if(code <= 0x08ff) {
            if(code <= 0x083f) return UNICODE_BLOCK_SAMARITAN;
            else if(code <= 0x085f) return UNICODE_BLOCK_MANDAIC;
            else return UNICODE_BLOCK_ARABIC_EXTENDED_A;
        } else if(code <= 0x09ff) {
            if(code <= 0x097f) return UNICODE_BLOCK_DEVANAGARI;
            else return UNICODE_BLOCK_BENGALI;
        } else if(code <= 0x0aff) {
            if(code <= 0x0a7f) return UNICODE_BLOCK_GURMUKHI;
            else return UNICODE_BLOCK_GUJARATI;
        } else if(code <= 0x0bff) {
            if(code <= 0x0b7f) return UNICODE_BLOCK_ORIYA;
            else return UNICODE_BLOCK_TAMIL;
        } else if(code <= 0x0cff) {
            if(code <= 0x0c7f) return UNICODE_BLOCK_TELUGU;
            else return UNICODE_BLOCK_KANNADA;
        } else if(code <= 0x0dff) {
            if(code <= 0x0d7f) return UNICODE_BLOCK_MALAYALAM;
            else return UNICODE_BLOCK_SINHALA;
        } else if(code <= 0x0eff) {
            if(code <= 0x0e7f) return UNICODE_BLOCK_THAI;
            else return UNICODE_BLOCK_LAO;
        } else {
            return UNICODE_BLOCK_TIBETAN;
        }
    } else if(code <= 0x1fff) {
        if(code <= 0x10ff) {
            if(code <= 0x109f) return UNICODE_BLOCK_MYANMAR;
            else return UNICODE_BLOCK_GEORGIAN;
        } else if(code <= 0x11ff) {
            return UNICODE_BLOCK_HANGUL_JAMO;
        } else if(code <= 0x13ff) {
            if(code <= 0x137f) return UNICODE_BLOCK_ETHIOPIC;
            else if(code <= 0x139f) return UNICODE_BLOCK_ETHIOPIC_SUPPLEMENT;
            else return UNICODE_BLOCK_CHEROKEE;
        } else if(code <= 0x16ff) {
            if(code <= 0x167f) return UNICODE_BLOCK_UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS;
            else if(code <= 0x169f) return UNICODE_BLOCK_OGHAM;
            else return UNICODE_BLOCK_RUNIC;
        } else if(code <= 0x17ff) {
            if(code <= 0x171f) return UNICODE_BLOCK_TAGALOG;
            else if(code <= 0x173f) return UNICODE_BLOCK_HANUNOO;
            else if(code <= 0x175f) return UNICODE_BLOCK_BUHID;
            else if(code <= 0x177f) return UNICODE_BLOCK_TAGBANWA;
            else return UNICODE_BLOCK_KHMER;
        } else if(code <= 0x18ff) {
            if(code <= 0x18af) return UNICODE_BLOCK_MONGOLIAN;
            else return UNICODE_BLOCK_UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS_EXTENDED;
        } else if(code <= 0x19ff) {
            if(code <= 0x194f) return UNICODE_BLOCK_LIMBU;
            else if(code <= 0x197f) return UNICODE_BLOCK_TAI_LE;
            else if(code <= 0x19df) return UNICODE_BLOCK_NEW_TAI_LUE;
            else  return UNICODE_BLOCK_KHMER_SYMBOLS;
        } else if(code <= 0x1bff) {
            if(code <= 0x1a1f) return UNICODE_BLOCK_BUGINESE;
            else if(code <= 0x1aaf) return UNICODE_BLOCK_TAI_THAM;
            else if(code <= 0x1b7f) return UNICODE_BLOCK_BALINESE;
            else if(code <= 0x1bbf) return UNICODE_BLOCK_SUNDANESE;
            else return UNICODE_BLOCK_BATAK;
        } else if(code <= 0x1cff) {
            if(code <= 0x1c4f) return UNICODE_BLOCK_LEPCHA;
            else if(code <= 0x1c7f) return UNICODE_BLOCK_OL_CHIKI;
            else if(code <= 0x1ccf) return UNICODE_BLOCK_SUNDANESE_SUPPLEMENT;
            else return UNICODE_BLOCK_VEDIC_EXTENSIONS;
        } else if(code <= 0x1dff) {
            if(code <= 0x1d7f) return UNICODE_BLOCK_PHONETIC_EXTENSIONS;
            else if(code <= 0x1d8f) return UNICODE_BLOCK_PHONETIC_EXTENSIONS_SUPPLEMENT;
            else return UNICODE_BLOCK_COMBINING_DIACRITICAL_MARKS_SUPPLEMENT;
        } else if(code <= 0x1eff) {
            return UNICODE_BLOCK_LATIN_EXTENDED_ADDITIONAL;
        } else {
            return UNICODE_BLOCK_GREEK_EXTENDED;
        }
    } else if(code <= 0x2fff) {
        if(code <= 0x20ff) {
            if(code <= 0x206f) return UNICODE_BLOCK_GENERAL_PUNCTUATION;
            else if(code <= 0x209f) return UNICODE_BLOCK_SUPERSCRIPTS_AND_SUBSCRIPTS;
            else if(code <= 0x20cf) return UNICODE_BLOCK_CURRENCY_SYMBOLS;
            else return UNICODE_BLOCK_COMBINING_DIACRITICAL_MARKS_FOR_SYMBOLS;
        } else if(code <= 0x21ff) {
            if(code <= 0x214f) return UNICODE_BLOCK_LETTERLIKE_SYMBOLS;
            else if(code <= 0x218f) return UNICODE_BLOCK_NUMBER_FORMS;
            else return UNICODE_BLOCK_ARROWS;
        } else if(code <= 0x22ff) {
            return UNICODE_BLOCK_MATHEMATICAL_OPERATORS;
        } else if(code <= 0x23ff) {
            return UNICODE_BLOCK_MISCELLANEOUS_TECHNICAL;
        } else if(code <= 0x24ff) {
            if(code <= 0x243f) return UNICODE_BLOCK_CONTROL_PICTURES;
            else if(code <= 0x245f) return UNICODE_BLOCK_OPTICAL_CHARACTER_RECOGNITION;
            else return UNICODE_BLOCK_ENCLOSED_ALPHANUMERICS;
        } else if(code <= 0x25ff) {
            if(code <= 0x257f) return UNICODE_BLOCK_BOX_DRAWING;
            else if(code <= 0x259f) return UNICODE_BLOCK_BLOCK_ELEMENTS;
            else return UNICODE_BLOCK_GEOMETRIC_SHAPES;
        } else if(code <= 0x26ff) {
            return UNICODE_BLOCK_MISCELLANEOUS_SYMBOLS;
        } else if(code <= 0x27ff) {
            if(code <= 0x27bf) return UNICODE_BLOCK_DINGBATS;
            else if(code <= 0x27ef) return UNICODE_BLOCK_MISCELLANEOUS_MATHEMATICAL_SYMBOLS_A;
            else return UNICODE_BLOCK_SUPPLEMENTAL_ARROWS_A;
        } else if(code <= 0x28ff) {
            return UNICODE_BLOCK_BRAILLE_PATTERNS;
        } else if(code <= 0x29ff) {
            if(code <= 0x297f) return UNICODE_BLOCK_SUPPLEMENTAL_ARROWS_B;
            else return UNICODE_BLOCK_MISCELLANEOUS_MATHEMATICAL_SYMBOLS_B;
        } else if(code <= 0x2aff) {
            return UNICODE_BLOCK_SUPPLEMENTAL_MATHEMATICAL_OPERATORS;
        } else if(code <= 0x2bff) {
            return UNICODE_BLOCK_MISCELLANEOUS_SYMBOLS_AND_ARROWS;
        } else if(code <= 0x2cff) {
            if(code <= 0x2c5f) return UNICODE_BLOCK_GLAGOLITIC;
            else return UNICODE_BLOCK_COPTIC;
        } else if(code <= 0x2dff) {
            if(code <= 0x2d2f) return UNICODE_BLOCK_GEORGIAN_SUPPLEMENT;
            else if(code <= 0x2d7f) return UNICODE_BLOCK_TIFINAGH;
            else if(code <= 0x2ddf) return UNICODE_BLOCK_ETHIOPIC_EXTENDED;
            else return UNICODE_BLOCK_CYRILLIC_EXTENDED_A;
        } else if(code <= 0x2eff) {
            if(code <= 0x2e7f) return UNICODE_BLOCK_SUPPLEMENTAL_PUNCTUATION;
            else return UNICODE_BLOCK_CJK_RADICALS_SUPPLEMENT;
        } else {
            if(code <= 0x2fdf) return UNICODE_BLOCK_KANGXI_RADICALS;
            else return UNICODE_BLOCK_IDEOGRAPHIC_DESCRIPTION_CHARACTERS;
        }
    } else if(code <= 0x9fff) {
        if(code <= 0x30ff) {
            if(code <= 0x303f) return UNICODE_BLOCK_CJK_SYMBOLS_AND_PUNCTUATION;
            else if(code <= 0x309f) return UNICODE_BLOCK_HIRAGANA;
            else return UNICODE_BLOCK_KATAKANA;
        } else if(code <= 0x31ff) {
            if(code <= 0x312f) return UNICODE_BLOCK_BOPOMOFO;
            else if(code <= 0x318f) return UNICODE_BLOCK_HANGUL_COMPATIBILITY_JAMO;
            else if(code <= 0x319f) return UNICODE_BLOCK_KANBUN;
            else if(code <= 0x31bf) return UNICODE_BLOCK_BOPOMOFO_EXTENDED;
            else if(code <= 0x31ef) return UNICODE_BLOCK_CJK_STROKES;
            else return UNICODE_BLOCK_KATAKANA_PHONETIC_EXTENSIONS;
        } else if(code <= 0x32ff) {
            return UNICODE_BLOCK_ENCLOSED_CJK_LETTERS_AND_MONTHS;
        } else if(code <= 0x33ff) {
            return UNICODE_BLOCK_CJK_COMPATIBILITY;
        } else if(code <= 0x4dff) {
            if(code <= 0x4dbf) return UNICODE_BLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_A;
            else return UNICODE_BLOCK_YIJING_HEXAGRAM_SYMBOLS;
        } else {
            return UNICODE_BLOCK_CJK_UNIFIED_IDEOGRAPHS;
        }
    } else if(code <= 0xdfff) {
        if(code <= 0xa4ff) {
            if(code <= 0xa48f) return UNICODE_BLOCK_YI_SYLLABLES;
            else if(code <= 0xa4cf) return UNICODE_BLOCK_YI_RADICALS;
            else return UNICODE_BLOCK_LISU;
        } else if(code <= 0xa6ff) {
            if(code <= 0xa63f) return UNICODE_BLOCK_VAI;
            else if(code <= 0xa69f) return UNICODE_BLOCK_CYRILLIC_EXTENDED_B;
            else return UNICODE_BLOCK_BAMUM;
        } else if(code <= 0xa7ff) {
            if(code <= 0xa71f) return UNICODE_BLOCK_MODIFIER_TONE_LETTERS;
            else return UNICODE_BLOCK_LATIN_EXTENDED_B;
        } else if(code <= 0xa8ff) {
            if(code <= 0xa82f) return UNICODE_BLOCK_SYLOTI_NAGRI;
            else if(code <= 0xa83f) return UNICODE_BLOCK_COMMON_INDIC_NUMBER_FORMS;
            else if(code <= 0xa87f) return UNICODE_BLOCK_PHAGS_PA;
            else if(code <= 0xa8df) return UNICODE_BLOCK_SAURASHTRA;
            else return UNICODE_BLOCK_DEVANAGARI_EXTENDED;
        } else if(code <= 0xaaff) {
            if(code <= 0xa92f) return UNICODE_BLOCK_KAYAH_LI;
            else if(code <= 0xa95f) return UNICODE_BLOCK_REJANG;
            else if(code <= 0xa97f) return UNICODE_BLOCK_HANGUL_JAMO_EXTENDED_A;
            else if(code <= 0xa9df) return UNICODE_BLOCK_JAVANESE;
            else if(code <= 0xaa5f) return UNICODE_BLOCK_CHAM;
            else if(code <= 0xaa7f) return UNICODE_BLOCK_MYANMAR_EXTENDED_A;
            else if(code <= 0xaadf) return UNICODE_BLOCK_TAI_VIET;
            else return UNICODE_BLOCK_MEETEI_MAYEK_EXTENSIONS;
        } else if(code <= 0xabff) {
            if(code <= 0xab2f) return UNICODE_BLOCK_ETHIOPIC_EXTENDED_A;
            else return UNICODE_BLOCK_MEETEI_MAYEK;
        } else if(code <= 0xd7ff) {
            if(code <= 0xd7af) return UNICODE_BLOCK_HANGUL_SYLLABLES;
            else return UNICODE_BLOCK_HANGUL_JAMO_EXTENDED_B;
        } else if(code <= 0xdbff) {
            if(code <= 0xdb7f) return UNICODE_BLOCK_HIGH_SURROGATES;
            else return UNICODE_BLOCK_HIGH_PRIVATE_USE_SURROGATES;
        } else {
            return UNICODE_BLOCK_LOW_SURROGATES;
        }
    } else if(code <= 0xffff) {
        if(code <= 0xf8ff) {
            return UNICODE_BLOCK_PRIVATE_USE_AREA;
        } else if(code <= 0xfaff) {
            return UNICODE_BLOCK_CJK_COMPATIBILITY_IDEOGRAPHS;
        } else if(code <= 0xfdff) {
            if(code <= 0xfb4f) return UNICODE_BLOCK_ALPHABETIC_PRESENTATION_FORMS;
            else return UNICODE_BLOCK_ARABIC_PRESENTATION_FORMS_A;
        } else if(code <= 0xfeff) {
            if(code <= 0xfe0f) return UNICODE_BLOCK_VARIATION_SELECTORS;
            if(code <= 0xfe1f) return UNICODE_BLOCK_VERTICAL_FORMS;
            if(code <= 0xfe2f) return UNICODE_BLOCK_COMBINING_HALF_MARKS;
            if(code <= 0xfe4f) return UNICODE_BLOCK_CJK_COMPATIBILITY_FORMS;
            if(code <= 0xfe6f) return UNICODE_BLOCK_SMALL_FORM_VARIANTS;
            else return UNICODE_BLOCK_ARABIC_PRESENTATION_FORMS_B;
        } else {
            if(code <= 0xffef) return UNICODE_BLOCK_HALFWIDTH_AND_FULLWIDTH_FORMS;
            else return UNICODE_BLOCK_SPECIALS;
        }
    } else if(code <= 0xfffff) {
        if(code <= 0x100ff) {
            if(code <= 0x1007f) return UNICODE_BLOCK_LINEAR_B_SYLLABARY;
            else return UNICODE_BLOCK_LINEAR_B_IDEOGRAMS;
        } else if(code <= 0x101ff) {
            if(code <= 0x1013f) return UNICODE_BLOCK_AEGEAN_NUMBERS;
            else if(code <= 0x1018f) return UNICODE_BLOCK_ANCIENT_GREEK_NUMBERS;
            else if(code <= 0x101cf) return UNICODE_BLOCK_ANCIENT_SYMBOLS;
            else return UNICODE_BLOCK_PHAISTOS_DISC;
        } else if(code <= 0x109ff) {
            if(code <= 0x1029f) return UNICODE_BLOCK_LYCIAN;
            else if(code <= 0x102df) return UNICODE_BLOCK_CARIAN;
            else if(code <= 0x1032f) return UNICODE_BLOCK_OLD_ITALIC;
            else if(code <= 0x1034f) return UNICODE_BLOCK_GOTHIC;
            else if(code <= 0x1039f) return UNICODE_BLOCK_UGARITIC;
            else if(code <= 0x103df) return UNICODE_BLOCK_OLD_PERSIAN;
            else if(code <= 0x1044f) return UNICODE_BLOCK_DESERET;
            else if(code <= 0x1047f) return UNICODE_BLOCK_SHAVIAN;
            else if(code <= 0x104af) return UNICODE_BLOCK_OSMANYA;
            else if(code <= 0x1083f) return UNICODE_BLOCK_CYPRIOT_SYLLABARY;
            else if(code <= 0x1085f) return UNICODE_BLOCK_IMPERIAL_ARAMAIC;
            else if(code <= 0x1091f) return UNICODE_BLOCK_PHOENICIAN;
            else if(code <= 0x1093f) return UNICODE_BLOCK_LYDIAN;
            else if(code <= 0x1099f) return UNICODE_BLOCK_MEROITIC_HIEROGLYPHS;
            else return UNICODE_BLOCK_MEROITIC_CURSIVE;
        } else if(code <= 0x110ff) {
            if(code <= 0x10a5f) return UNICODE_BLOCK_KHAROSHTHI;
            else if(code <= 0x10a7f) return UNICODE_BLOCK_OLD_SOUTH_ARABIAN;
            else if(code <= 0x10b3f) return UNICODE_BLOCK_AVESTAN;
            else if(code <= 0x10b5f) return UNICODE_BLOCK_INSCRIPTIONAL_PARTHIAN;
            else if(code <= 0x10b7f) return UNICODE_BLOCK_INSCRIPTIONAL_PAHLAVI;
            else if(code <= 0x10c4f) return UNICODE_BLOCK_OLD_TURKIC;
            else if(code <= 0x10e7f) return UNICODE_BLOCK_RUMI_NUMERAL_SYMBOLS;
            else if(code <= 0x1107f) return UNICODE_BLOCK_BRAHMI;
            else if(code <= 0x110cf) return UNICODE_BLOCK_KAITHI;
            else return UNICODE_BLOCK_SORA_SOMPENG;
        } else if(code <= 0x123ff) {
            if(code <= 0x1114f) return UNICODE_BLOCK_CHAKMA;
            else if(code <= 0x111df) return UNICODE_BLOCK_SHARADA;
            else if(code <= 0x116cf) return UNICODE_BLOCK_TAKRI;
            else return UNICODE_BLOCK_CUNEIFORM;
        } else if(code <= 0x1b0ff) {
            if(code <= 0x1247f) return UNICODE_BLOCK_CUNEIFORM_NUMBERS_AND_PUNCTUATION;
            else if(code <= 0x1342f) return UNICODE_BLOCK_EGYPTIAN_HIEROGLYPHS;
            else if(code <= 0x16a3f) return UNICODE_BLOCK_BAMUM_SUPPLEMENT;
            else if(code <= 0x16f9f) return UNICODE_BLOCK_MIAO;
            else return UNICODE_BLOCK_KANA_SUPPLEMENT;
        } else if(code <= 0x1d0ff) {
            return UNICODE_BLOCK_BYZANTINE_MUSICAL_SYMBOLS;
        } else if(code <= 0x1d1ff) {
            return UNICODE_BLOCK_MUSICAL_SYMBOLS;
        } else if(code <= 0x1d7ff) {
            if(code <= 0x1d24f) return UNICODE_BLOCK_ANCIENT_GREEK_MUSICAL_NOTATION;
            else if(code <= 0x1d35f) return UNICODE_BLOCK_TAI_XUAN_JING_SYMBOLS;
            else if(code <= 0x1d37f) return UNICODE_BLOCK_COUNTING_ROD_NUMERALS;
            else return UNICODE_BLOCK_MATHEMATICAL_ALPHANUMERIC_SYMBOLS;
        } else if(code <= 0x1eeff) {
            return UNICODE_BLOCK_ARABIC_MATHEMATICAL_ALPHABETIC_SYMBOLS;
        } else if(code <= 0x1f0ff) {
            if(code <= 0x1f02f) return UNICODE_BLOCK_MAHJONG_TILES;
            if(code <= 0x1f09f) return UNICODE_BLOCK_DOMINO_TILES;
            else return UNICODE_BLOCK_PLAYING_CARDS;
        } else if(code <= 0x1f1ff) {
            return UNICODE_BLOCK_ENCLOSED_ALPHANUMERIC_SUPPLEMENT;
        } else if(code <= 0x1f2ff) {
            return UNICODE_BLOCK_ENCLOSED_IDEOGRAPHIC_SUPPLEMENT;
        } else if(code <= 0x1f5ff) {
            return UNICODE_BLOCK_MISCELLANEOUS_SYMBOLS_AND_PICTOGRAPHS;
        } else if(code <= 0x1f6ff) {
            if(code <= 0x1f64f) return UNICODE_BLOCK_EMOTICONS;
            else return UNICODE_BLOCK_TRANSPORT_AND_MAP_SYMBOLS;
        } else {
            if(code <= 0x1f77f) return UNICODE_BLOCK_ALCHEMICAL_SYMBOLS;
            else if(code <= 0x2a6df) return UNICODE_BLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_B;
            else if(code <= 0x2b73f) return UNICODE_BLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_C;
            else if(code <= 0x2b81f) return UNICODE_BLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_D;
            else if(code <= 0x2fa1f) return UNICODE_BLOCK_CJK_COMPATIBILITY_IDEOGRAPHS_SUPPLEMENT;
            else if(code <= 0xe007f) return UNICODE_BLOCK_TAGS;
            else if(code <= 0xe01ef) return UNICODE_BLOCK_VARIATION_SELECTORS_SUPPLEMENT;
            else return UNICODE_BLOCK_SUPPLEMENTARY_PRIVATE_USE_AREA_A;
        }
    } else {
        return UNICODE_BLOCK_SUPPLEMENTARY_PRIVATE_USE_AREA_B;
    }
}
}

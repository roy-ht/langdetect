#include "./gram_sequence.h"
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include "./exception.h"
#include "./unicodedata.h"

using std::string;
using std::vector;
using std::unordered_map;
namespace langdetect {
    vector<GramSequence::Code> const GramSequence::LATIN1_EXCLUDED = {0x00A0, 0x00AB, 0x00B0, 0x00BB};
    GramSequence::GramSequence(char const *data, size_t const &length) {
        size_t readbyte(0);
        size_t cursor(0);
        while(true) {
            Code code = readchar_(data + cursor, length - cursor, readbyte);
            code = normalize_(code);
            if(readbyte == 0) break;
            codes_.push_back(code);
            cursor += readbyte;
            if(cursor == length) break;
        }
    }

    size_t GramSequence::size() {
        return codes_.size();
    }

    string GramSequence::getngram(size_t const &idx, size_t const &n) {
        if(n == 0) return "";
        if(idx + n > codes_.size()) throw DetectError("invalid range");
        string s;
        for(size_t i = 0; i < n; ++i) {
            s += string(reinterpret_cast<char *>(&codes_[idx + i]), 4);
        }
        return s;
    }

    GramSequence::Code GramSequence::normalize_(uint32_t const &code) {
        Code normcode = code;
        UnicodeBlock block = UnicodeData::unicodeblock(code);
        if(block == UNICODE_BLOCK_BASIC_LATIN) {
            if(code <= 0x0040 || (0x005b <= code && code <= 0x0060) || 0x007b <= code) normcode = 0x0020;
        } else if(block == UNICODE_BLOCK_LATIN_1_SUPPLEMENT) {
            if(hascode_(LATIN1_EXCLUDED, code)) normcode = 0x0020;
        } else if(block == UNICODE_BLOCK_LATIN_EXTENDED_B) {
            // normalization for Romanian
            if(code == 0x0219) normcode = 0x015f;  // Small S with comma below => with cedilla
            if(code == 0x021b) normcode = 0x0163; // Small T with comma below => with cedilla
        } else if(block == UNICODE_BLOCK_GENERAL_PUNCTUATION) {
            normcode = 0x0020;
        } else if(block == UNICODE_BLOCK_ARABIC) {
            if(code == 0x06cc) normcode = 0x064a;  // Farsi yeh => Arabic yeh
        } else if(block == UNICODE_BLOCK_LATIN_EXTENDED_ADDITIONAL) {
            if(code == 0x1ea0) normcode = 0x1ec3;
        } else if(block == UNICODE_BLOCK_HIRAGANA) {
            normcode = 0x3042;
        } else if(block == UNICODE_BLOCK_KATAKANA) {
            normcode = 0x30a2;
        } else if(block == UNICODE_BLOCK_BOPOMOFO || block == UNICODE_BLOCK_BOPOMOFO_EXTENDED) {
            normcode = 0x3105;
        } else if(block == UNICODE_BLOCK_CJK_UNIFIED_IDEOGRAPHS) {
            if(CJK_REPLACE_MAP.find(code) != CJK_REPLACE_MAP.end()) normcode = CJK_REPLACE_MAP.at(code);
        } else if(block == UNICODE_BLOCK_HANGUL_SYLLABLES) {
            normcode = 0xac00;
        }
        return normcode;
    }

    uint32_t GramSequence::readchar_(char const *data, size_t const &len, size_t &readbyte) {
        if(len == 0) throw DetectError("invalid data size");
        size_t clen(0);
        uint32_t code(data[0]);
        if((data[0] & 0x80) == 0) clen = 1;
        else if((data[0] & 0xe0) == 0xc0) {
            clen = 2;
            code &= 0x1f;
        } else if((data[0] & 0xf0) == 0xe0) {
            clen = 3;
            code &= 0xf;
        } else if((data[0] & 0xfc) == 0xf0) {
            clen = 4;
            code &= 0x7;
        } else {
            throw DetectError("can't encode string: may not utf-8 encoding");
        }
        if(clen > len) {  // 中途半端なバイト列が末尾にある。例外は投げないで、失敗を伝える。
            readbyte = 0;
            return 0U;
        }
        for(size_t i = 1; i < clen; ++i) {
            code = (code << 6) | (data[i] & 0x3f);
        }
        readbyte = clen;
        return code;
    }

    bool GramSequence::hascode_(vector<Code> const &data, Code const &code) {
        return std::find(data.begin(), data.end(), code) != data.end();
    }
}

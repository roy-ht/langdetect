#include "./gram_sequence.h"
#include <string>
#include <iostream>
#include "./exception.h"

using std::string;

namespace langdetect {

    GramSequence::GramSequence(char const *data, size_t const &length) {
        size_t readbyte(0);
        size_t cursor(0);
        while(true) {
            uint32_t code = readchar_(data + cursor, length - cursor, readbyte);
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
}

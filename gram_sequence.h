#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace langdetect {

/// 言語判定に使う為の文字列配列を表現するコンテナクラス
/// 内部で正規化され、Unicodeコードポイントの配列になる
/// UTF-8のみに対応
class GramSequence {
    public:
        typedef uint32_t Code;
        static std::vector<Code> const LATIN1_EXCLUDED;
        static std::unordered_map<Code, Code> const CJK_REPLACE_MAP;
        GramSequence(char const *data, size_t const &length);
        size_t size();
        std::string getngram(size_t const &idx, size_t const &n);
    private:
        std::vector<Code> codes_;
        /// lengthの長さを持つchar文字列から一文字分読み込んで
        /// code pointを返す
        /// readbyteに読み込んだバイト数が返される。
        uint32_t readchar_(char const *data, size_t const &length, size_t &readbyte);

        /// 文字正規化
        Code normalize_(Code const &code);

        /// 配列中にCodeが含まれるか
        bool hascode_(std::vector<Code> const &data, Code const &code);
};

}

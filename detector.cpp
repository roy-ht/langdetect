#include <cstdlib>
#include <math.h>
#include <string>
#include <map>
#include "./detector.h"
#include "./ngram_storage.h"

#define MSG_FAIL_EMPTY "fail_empty_data"

using std::string;
using std::map;
using std::vector;

namespace langdetect {
    int const Detector::DEFAULT_TRIAL = 7;
    double const Detector::DEFAULT_ALPHA = 0.5;
    double const Detector::ALPHA_WIDTH = 0.05;
    int const Detector::ITERATION_LIMIT = 1000;
    double const Detector::PROB_THRESHOLD = 0.1;
    double const Detector::CONV_THRESHOLD = 0.99999;
    int const Detector::BASE_FREQ = 10000;
    std::string const Detector::UNKNOWN_LANG = "unknown";

    string Detector::detect(char const *data, size_t const &length) {
        if(length == 0) return MSG_FAIL_EMPTY;
        NgramStorage& storage = NgramStorage::instance();
        for(int i = 0; i < trial_; ++i) {
            vector<double> scores(0, 1.0 / storage.langnum_);  // priorはuniformに固定する
            double alpha = alpha_ + random_(ALPHA_WIDTH * 2) - ALPHA_WIDTH;
            for(int j = 0;;) {
                // 乱数からどのn-gramを使うかを決定する
                // 乱数はdataの位置と、どのn-gramサイズを使うかを決定する。
                // [0, length * 3)の乱数から、
                // idx -> floor(r / 3), gramsize = r / length
                double r = random_(static_cast<double>(length * 3 - 1));
                size_t tgt_idx = floor(r / 3);
                size_t gramsize = floor(r / length) + 1;
                // indexが決まったら、先頭バイトから指定文字数読み込む
                // 端っこだと失敗する可能性あり（その場合はノーカウント）
                string ngram = read_ngram(data, length, tgt_idx, gramsize);
                if(ngram.empty()) continue;
                if(storage.has(ngram)) {
                    for(auto l: storage.get(ngram)) {
                        for(auto score: l) {
                            scores[score.first] = score.second;
                        }
                    }
                }
                if( j % 5 == 0) {
                    if(normalize_(scores) > CONV_THRESHOLD || i >= ITERATION_LIMIT) break;
                }
                //  for(int j=0;j<langprob.length;++j) langprob[j] += prob[j] / n_trial;
                j += 1; // count up
            }
        }
    }

    /// idxからnum文字取り出して返す
    /// dataの範囲外になってしまったら空文字を返す（失敗）
    /// UTF-8のみに対応する。簡易版なので適当に切り出し
    string Detector::read_ngram_(char const *data, size_t const &len, size_t const &idx, size_t const &num) {
        // 遡って先頭を探す
        size_t csr = idx;
        while(True) {
            if(data[csr] & 0x80 == 0 || data[csr] & 0xc0 == 0xc0) break;
            if(csr == 0) return "";  // failed
            csr -= 1;
        }
        size_t start = csr;
        size_t cur_num = 0;
        while(cur_num < num) {
            size_t clen = 0;
            if(data[csr] & 0x80 == 0) clen = 1;
            else if(data[csr] & 0xe0 == 0xc0) clen = 2;
            else if(data[csr] & 0xf0 == 0xe0) clen = 3;
            else if(data[csr] & 0xfc == 0xf0) clen = 4;
            if(clen == 0) return ""; // invalid encoding (guess not utf-8)
            csr += clen;
            if(csr > len) return ""; // overflow
            cur_num += 1;
        }
        return string(data + start, csr - start);
    }

    double Detector::normalize_(map<string, double> &scores) {
        double total = 0.0;
        double maxp = 0.0;
        for(auto p: scores) total += p.second;
        for(auto p: scores) {
            double norm = p.second / total;
            if(maxp < norm) maxp = norm;
            scores[p.first] = norm;
        }
        return maxp;
    }

    double Detector::random_(double const &dmax) {
        if(dmax < 0) return 0.0;
        return static_cast<double>(rand()) / RAND_MAX * dmax);
    }
}

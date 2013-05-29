#include <vector>
#include <string>
#include <iostream>
#include "./ngram_storage.h"

using std::string;
using std::vector;

namespace langdetect {
    NgramStorage::NgramStorage() {
        // langlist_の作成
        size_t idx = 0;
        while(true) {
            size_t next_idx = langdata_.find(" ", idx);
            langlist_.push_back(langdata_.substr(idx, next_idx - idx));
            if(next_idx == string::npos) break;
            idx = next_idx + 1;
        }
        // probmap_の作成
        // std::cout << "ngramdata_.size() = " << ngramdata_.size() << std::endl;
        size_t cur = 0;
        while(cur < ngramdata_.size()) {
            uint8_t ngramsize = ngramdata_[cur++];
            string ngram(ngramdata_.data() + cur, ngramsize);
            cur += ngramsize;
            // std::cout << "ngram(size=" << (int)ngramsize << "): " << ngram << std::endl;
            probmap_[ngram] = ProbList(langlist_.size(), 0.0);
            uint8_t freqsize = ngramdata_[cur++];
            // std::cout << "freqsize: " << (int)freqsize << std::endl;
            for(size_t i = 0; i < freqsize; ++i) {
                uint8_t langidx = ngramdata_[cur++];
                // std::cout << "langidx: " << (int)langidx << std::endl;
                double prob = *reinterpret_cast<double const *>(ngramdata_.data() + cur);
                // std::cout << "prob: " << prob << std::endl;
                cur += sizeof(double);
                probmap_[ngram][langidx] = prob;
            }
        }
    }

    NgramStorage& NgramStorage::instance() {
        static NgramStorage instance_;
        return instance_;
    }

    NgramStorage::ProbList const & NgramStorage::get(string const &s) {
        return probmap_.at(s);
    }

    bool NgramStorage::has(string const &s) {
        return probmap_.find(s) != probmap_.end();
    }

    vector<string> const & NgramStorage::langlist() {
        return langlist_;
    }
}

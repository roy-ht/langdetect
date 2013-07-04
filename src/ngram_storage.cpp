#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include "./ngram_storage.h"

using std::string;
using std::vector;

namespace langdetect {

    NgramStorage::NgramStorage() {
        // probmap_の作成
        // std::cout << "ngramdata_.size() = " << ngramdata_.size() << std::endl;
        size_t cur = 0;
        while(cur < ngramdata_.size()) {
            uint8_t ngramsize = ngramdata_[cur++];
            string ngram(ngramdata_.data() + cur, ngramsize);
            cur += ngramsize;
            // std::cout << "ngram(size=" << (int)ngramsize << "): " << ngram << std::endl;
            probmap_[ngram] = ProbList(langsize(), 0.0);
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

    size_t NgramStorage::langindex(string const &name) {
        for(size_t i = 0; i < langsize(); ++i) {
            if(langlist_[i] == name) return i;
        }
        return langsize();  // exceeds maximum language size if error
    }

    string NgramStorage::lang_fromindex(size_t const &idx) {
        if(idx >= langsize()) throw std::runtime_error("language index range over flow");
        return langlist_[idx];
    }

    size_t NgramStorage::langsize() {
        return langlist_.size();
    }
}

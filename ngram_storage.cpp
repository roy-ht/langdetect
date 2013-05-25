#include <string>
#include "./ngram_storage.h"

using std::string;

namespace langdetect {
    NgramStorage::ProbList& NgramStorage::get(string const &s) {
        return probmap_[s];
    }

    bool NgramStorage::has(string const &s) {
        return probmap_.find(s) != probmap_.end();
    }

}

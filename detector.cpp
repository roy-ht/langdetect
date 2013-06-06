#include <string>
#include <map>
#include <random>
#include <algorithm>
#include <iostream>
#include <iomanip>

#include "./detector.h"
#include "./ngram_storage.h"
#include "./code_sequence.h"

#define LANG_FAIL_EMPTY Detected("fail_empty_data", 0.0)

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

    Detector::Detector() : trial_(DEFAULT_TRIAL), alpha_(DEFAULT_ALPHA) {}

    Detected Detector::detect(char const *data, size_t const &length) {
        if(length == 0) return LANG_FAIL_EMPTY;
        NgramStorage& storage = NgramStorage::instance();
        CodeSequence codesequence(data, length);
        vector<string> grams = codesequence.tongram();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> gaussian;
        std::uniform_int_distribution<> uniform_idx(0, grams.size() - 1);
        vector<double> finalscores(storage.langlist().size(), 0);
        for(int i = 0; i < trial_; ++i) {
            vector<double> scores(storage.langlist().size(), 1.0 / storage.langlist().size());  // priorはuniformに固定する
            double alpha = alpha_ + gaussian(gen) * ALPHA_WIDTH;
            for(int j = 0;;) {
                // 乱数からどのn-gramを使うかを決定する
                size_t tgt_idx = uniform_idx(gen);
                string ngram = grams[tgt_idx];
                if(ngram.empty()) continue;
                update_scores_(ngram, scores, alpha);
                if( j % 5 == 0) {
                    if(normalize_(scores) > CONV_THRESHOLD || j >= ITERATION_LIMIT) break;
                }
                j += 1; // count up
            }
            for(size_t j = 0; j < finalscores.size(); ++j) {
                finalscores[j] += scores[j] / trial_;
            }
        }

        vector<Detected> detecteds(storage.langlist().size());
        for(size_t i = 0; i < finalscores.size(); ++i) {
            detecteds[i].name(storage.langlist()[i]);
            detecteds[i].score(finalscores[i]);
        }
        // for(auto &d : detecteds) {
        //     std::cout << d.name() << ", " << d.score() << std::endl;
        // }
        // sort
        std::sort(detecteds.begin(), detecteds.end());
        return detecteds.back();
    }

    void Detector::update_scores_(string const &ngram, vector<double> &scores, double const &alpha) {
        NgramStorage& storage = NgramStorage::instance();
        if(storage.has(ngram)) {
            double weight = alpha / BASE_FREQ;
            auto plist = storage.get(ngram);
            // if(ngram.length() == 4) std::cout << reinterpret_cast<uint32_t *>(*ngram.data());
            // else if(ngram.length() == 8) std::cout << reinterpret_cast<uint32_t *>(*ngram.data()) << " " << reinterpret_cast<uint32_t *>(*ngram.data() + 4);
            // else if(ngram.length() == 12) std::cout << reinterpret_cast<uint32_t *>(*ngram.data()) << " " << reinterpret_cast<uint32_t *>(*ngram.data() + 4) << " " << reinterpret_cast<uint32_t *>(*ngram.data() + 8);
            // std::cout << std::endl;
            for(size_t i = 0; i < plist.size(); ++i) {
                // std::cout << " [" << storage.langlist()[i] << "]= " << plist[i];
                scores[i] *= weight + plist[i];
            }
            // std::cout << std::endl;
        }
    }

    double Detector::normalize_(vector<double> &scores) {
        double total = 0.0;
        double maxp = 0.0;
        for(size_t i = 0; i < scores.size(); ++i) total += scores[i];
        for(size_t i = 0; i < scores.size(); ++i) {
            double norm = scores[i] / total;
            if(maxp < norm) maxp = norm;
            scores[i] = norm;
        }
        return maxp;
    }


    Detected::Detected(string const &name, double const &score)
    : name_(name), score_(score) {}

    Detected::Detected() {};

    bool Detected::operator==(Detected const &other) const {
        return score_ == other.score_;
    }
    bool Detected::operator!=(Detected const &other) const {
        return score_ != other.score_;
    }
    bool Detected::operator<(Detected const &other) const {
        return score_ < other.score_;
    }
    bool Detected::operator>(Detected const &other) const {
        return score_ > other.score_;
    }
    bool Detected::operator<=(Detected const &other) const {
        return score_ <= other.score_;
    }
    bool Detected::operator>=(Detected const &other) const {
        return score_ >= other.score_;
    }

    void Detected::name(std::string const &name) {name_ = name;}
    std::string const & Detected::name() const {return name_;}
    void Detected::score(double const &score) {score_ = score;}
    double const & Detected::score() const {return score_;}
}

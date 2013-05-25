// 言語判定器
// UTF-8文字列であることを仮定する
#pragma once

#include <string>

namespace langdetect {

class Detector {
    public:
        static int const DEFAULT_TRIAL;
        static double const DEFAULT_ALPHA;
        static double const ALPHA_WIDTH;
        static int const ITERATION_LIMIT;
        static double const PROB_THRESHOLD;
        static double const CONV_THRESHOLD;
        static int const BASE_FREQ;
        static std::string const UNKNOWN_LANG;

        std::string detect(char const *data, size_t const &length);
    private:
        int trial_;
        double alpha_;
        /// utility function, returns [0 max) random value
        double random_(double const &nmax);
};

}

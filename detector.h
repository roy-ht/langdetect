// 言語判定器
// UTF-8文字列であることを仮定する
#pragma once

#include <string>

namespace langdetect {


class Detected {
    public:
        Detected(std::string const &name, double const &score);
        Detected();
        bool operator==(Detected const &);
        bool operator!=(Detected const &);
        bool operator<(Detected const &);
        bool operator>(Detected const &);
        bool operator<=(Detected const &);
        bool operator>=(Detected const &);
        void name(std::string &name);
        std::string const & name();
        void score(double const &score);
        double const & score();
    private:
        std::string name_;
        double score_;
};

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
};

}

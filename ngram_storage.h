// NgramStorage class contain a probability information

#pragma once
#include <unordered_map>
#include <vector>
#include <string>

namespace langdetect {

class NgramStorage {
    public:
        typedef std::vector<double> ProbList;
        typedef std::unordered_map<std::string, ProbList> ProbMap;
    private:
        static std::string const langdata_;
        static std::string const ngramdata_;
        std::vector<std::string> langlist_;
        ProbMap probmap_;
        NgramStorage();
        NgramStorage(NgramStorage const &) = default;
        NgramStorage& operator=(NgramStorage const &) = default;
    public:
        static NgramStorage& instance();
        ProbList const & get(std::string const &s);
        bool has(std::string const &s);
        std::vector<std::string> const & langlist();
};

}

// NgramStorage class contain a probability information

#pragma once
#include <map>
#include <vector>
#include <string>

namespace langdetect {

class NgramStorage {
    public:
        typedef std::vector<double> ProbList;
        typedef std::map<std::string, ProbList> ProbMap;
    private:
        static size_t const langnum_;
        static std::vector<std::string> const langlist_;
        static ProbMap probmap_;
        NgramStorage();
        NgramStorage(NgramStorage const &);
        NgramStorage& operator=(NgramStorage const &);
    public:
        static NgramStorage& instance() {
            static NgramStorage instance_;
            return instance_;
        }
        ProbList& get(std::string const &s);
        bool has(std::string const &s);
};

}

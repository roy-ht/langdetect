// NgramStorage class contain a probability information

#pragma once
#include <map>
#include <vector>
#include <string>

namespace langdetect {

class NgramStorage {
    typedef std::vector<std::pair<std::string, double> > ProbList;
    private:
        std::map<std::string, ProbList> probmap_;
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

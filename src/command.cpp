// langdetect コマンドのエントリポイント

#include <iostream>
#include <fstream>
#include "./langdetect.h"

using langdetect::Detector;
using std::ifstream;
using std::string;

size_t const MAX_READ_SIZE = 4096;

void message(char const *path, char const *msg) {
    std::cout << path << ": " << msg << std::endl;
}

void message(char const *path, char const *msg, double const &score) {
    std::cout << path << ": " << msg << ", " << score << std::endl;
}

int main(int argc, char const *argv[]) {
    Detector detector;
    for(int i = 1; i < argc; ++i) {
        char const *path = argv[i];
        ifstream ifs(path);
        if(!ifs.is_open()) {
            message(path, "failed to open");
        } else {
            char buf[MAX_READ_SIZE];  // read max 4k bytes
            ifs.read(buf, MAX_READ_SIZE);
            std::streamsize readcount = ifs.gcount();
            langdetect::Detected result = detector.detect(buf, readcount);
            message(path, result.name().c_str(), result.score());
        }
    }
}

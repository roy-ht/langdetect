#pragma once

#include <stdexcept>
#include <string>

namespace langdetect {
    class DetectError: public std::runtime_error {
        public:
            explicit DetectError(std::string const &wh);
            explicit DetectError(char const *wh);
    };
}

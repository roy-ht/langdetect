#include "./exception.h"

namespace langdetect {
    DetectError::DetectError(std::string const &wh) : std::runtime_error(wh) {}
    DetectError::DetectError(char const *wh) : std::runtime_error(wh) {}
}

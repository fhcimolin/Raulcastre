#ifndef RAULCASTRE_UTILS_H
#define RAULCASTRE_UTILS_H

#include <type_traits>

namespace utils {

template <typename Enum>
constexpr auto value_of(Enum e) {
    return static_cast<std::underlying_type_t<Enum>>(e);
}

}

#endif

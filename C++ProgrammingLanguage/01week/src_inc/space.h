#pragma once

#include <cctype>

inline bool is_space(int c) { return std::isspace(c); }

inline bool not_space(int c) { return !std::isspace(c); }


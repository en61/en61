#pragma once

#include <type_traits>

namespace common {

template <typename _Type, typename ..._Allowed>
constexpr bool is_one_of = (std::is_same_v<_Type, _Allowed> || ...);

constexpr float pi = 3.14159265358979;

} // namespace common

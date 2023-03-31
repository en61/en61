#pragma once

#include <type_traits>

namespace common {

template <typename _Type, typename ..._Allowed>
constexpr bool IsOneOf= (std::is_same_v<_Type, _Allowed> || ...);

constexpr float Pi = 3.14159265358979;

} // namespace common

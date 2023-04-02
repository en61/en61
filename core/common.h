#pragma once

#include <type_traits>

namespace en61 {

namespace constants {

constexpr float Pi = 3.14159265358979;

} // namespace constants

template <typename _Type, typename ..._Allowed>
constexpr bool IsOneOf = (std::is_same_v<_Type, _Allowed> || ...);

typedef signed char    i8;
typedef signed short   i16;
typedef signed int	   i32;
typedef signed long    i64;

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef unsigned long  u64;

} // namespace en61

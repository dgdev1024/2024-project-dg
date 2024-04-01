/** @file DG/Common.hpp */

#pragma once

// C++ Includes
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <memory>
#include <chrono>
#include <random>
#include <bitset>
#include <algorithm>
#include <utility>
#include <tuple>
#include <filesystem>
#include <functional>

// C Includes
#include <cstdlib>
#include <cstdint>
#include <cmath>
#include <ctime>
#include <cassert>

namespace fs = std::filesystem;

namespace dg
{

  // Integer Typedefs
  using I8  = std::int8_t;
  using I16 = std::int16_t;
  using I32 = std::int32_t;
  using I64 = std::int64_t;
  using U8  = std::uint8_t;
  using U16 = std::uint16_t;
  using U32 = std::uint32_t;
  using U64 = std::uint64_t;

  // Floating-point Typedefs
  using F32 = float;
  using F64 = double;

  // Other Typedefs
  using Bln = bool;
  using String = std::string;
  using StringView = std::string_view;
  using Path = fs::path;
  using Char = char;
  using Index = std::size_t;
  using Size = std::size_t;
  using Count = std::size_t;
  
  // Templated Typedefs
  template <typename T>                 using Collection = std::vector<T>;
  template <typename T, typename U>     using Map = std::unordered_map<T, U>;
  template <typename T>                 using Dictionary = Map<String, T>;
  template <typename T, typename... Us> using Function = std::function<T(Us&&...)>;
  template <typename T, typename... Us> using LValueFunction = std::function<T(Us...)>;
  template <typename T>                 using Unique = std::unique_ptr<T>;
  template <typename T>                 using Shared = std::shared_ptr<T>;

}
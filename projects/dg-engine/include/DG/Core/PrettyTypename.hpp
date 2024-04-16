/** @file DG/Core/PrettyTypename.hpp */

#pragma once

#include <DG_Pch.hpp>
#if defined(__GNUC__)
  #include <cxxabi.h>
#endif

namespace dg
{

  template <typename T>
  inline String getPrettyTypename ()
  {
    #if defined(__GNUC__)

      I32 status = 0;
      UniqueWithFree<Char> realName(
        abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, &status),
        &std::free
      );

      return (status == 0) ? realName.get() : typeid(T).name();

    #endif
  }

}
/** @file DG/Core/FileIo.hpp */

#pragma once

#include <DG_Pch.hpp>

namespace dg
{

  using LineFunction = LValueFunction<bool, StringView, Index>;

  class FileIo
  {
  public:
    static Path getAbsolute (const Path& path);
    static bool loadTextFile (const Path& path, const LineFunction& lineFunction);
    static bool loadBinaryFile (const Path& path, Collection<U8>& contents);

  };

}

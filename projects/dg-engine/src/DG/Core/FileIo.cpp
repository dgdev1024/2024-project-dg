/** @file DG/Core/FileIo.cpp */

#include <DG/Core/FileIo.hpp>

namespace dg
{

  Path FileIo::getAbsolute (const Path& path)
  {
    return fs::absolute(path).lexically_normal();
  }

  bool FileIo::loadTextFile (const Path& path, const LineFunction& lineFunction)
  {
    if (path.empty()) {
      DG_ENGINE_ERROR("No text filename specified for loading.");
      return false;
    }

    if (lineFunction == nullptr) {
      DG_ENGINE_ERROR("No line processing function specified.");
      return false;
    }

    if (fs::exists(path) == false) {
      DG_ENGINE_ERROR("Text file '{}' not found.", path);
      return false;
    }

    std::fstream file { path, std::ios::in };
    if (file.is_open() == false) {
      DG_ENGINE_ERROR("Could not open text file '{}' for reading.", path);
      return false;
    }

    String line = "";
    Index lineNumber = 0;
    while (std::getline(file, line)) {
      lineNumber++;
      if (lineFunction(line, lineNumber) == false) {
        DG_ENGINE_ERROR("Error processing line #{} of text file '{}'.",
          lineNumber, path);
        return false;
      }
    }

    return true;    
  }

  bool FileIo::loadBinaryFile (const Path& path, Collection<U8>& contents)
  {
    if (path.empty()) {
      DG_ENGINE_ERROR("No text filename specified for loading.");
      return false;
    }

    if (fs::exists(path) == false) {
      DG_ENGINE_ERROR("Binary file '{}' not found.", path);
      return false;
    }

    std::fstream file { path, std::ios::in | std::ios::binary };
    if (file.is_open() == false) {
      DG_ENGINE_ERROR("Could not open binary file '{}' for reading.", path);
      return false;
    }

    file.seekg(0, file.end);
    auto size = file.tellg();
    file.seekg(0, file.beg);

    contents.resize(size);
    file.read(reinterpret_cast<char*>(contents.data()), contents.size());

    file.close();
    return true;
  }

}
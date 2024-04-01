/** @file DG/Core/FileLexer.hpp */

#pragma once

#include <DG/Core/FileToken.hpp>

namespace dg
{

  class FileLexer
  {
  public:
    FileLexer () = default;
    FileLexer (const Path& filepath);
    ~FileLexer ();

  public:
    bool loadFromFile (const Path& filepath);
    const FileToken& getNextToken () const;
    void ungetToken () const;
    void seek (Index offset, bool fromEnd = false) const;
    bool hasMoreTokens () const;
    bool isEmpty () const;

  private:
    int collectSymbol (I32& character);
    int collectNumber (I32& character);
    int collectString (I32& character);
    int collectIdentifier (I32& character);
    int collectToken ();

  private:
    std::fstream m_file;
    Collection<FileToken> m_tokens;
    Collection<Path> m_lexedPaths;
    Path m_currentPath;
    Index m_currentLine = 0;
    mutable Index m_readPointer = 0;
    Index m_writePointer = 0;

  };

}

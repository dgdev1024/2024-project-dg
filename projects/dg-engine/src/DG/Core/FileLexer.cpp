/** @file DG/Core/FileLexer.cpp */

#include <DG/Core/FileLexer.hpp>

namespace dg
{

  FileLexer::FileLexer (const Path& filepath)
  {
    loadFromFile(filepath);
  }

  FileLexer::~FileLexer ()
  {
    m_tokens.clear();
    m_lexedPaths.clear();
  }

  bool FileLexer::loadFromFile (const Path& filepath)
  {

    if (fs::exists(filepath) == false) {
      DG_ENGINE_ERROR("FileLexer: File '{}' not found.", filepath);
      return false;
    }

    Path resolvedPath = fs::absolute(filepath).lexically_normal();
    if (std::find(m_lexedPaths.begin(), m_lexedPaths.end(), resolvedPath) != m_lexedPaths.end()) {
      return true;
    } else {
      m_lexedPaths.push_back(resolvedPath);
    }

    m_file.open(resolvedPath, std::ios::in);
    if (m_file.is_open() == false) {
      DG_ENGINE_ERROR("FileLexer: Could not open file '{}' for reading.", filepath);
      return false;
    }

    m_currentPath = filepath;
    m_currentLine = 1;
    m_writePointer = m_readPointer;

    while (true) {
      int result = collectToken();
      if (result == -1) {
        DG_ENGINE_ERROR("FileLexer: Error parsing file '{}' at line #{}.", filepath, m_currentLine);
        m_file.close();
        return false;
      } else if (result == 0) {
        m_file.close();
        return true;
      }
    }
  }

  const FileToken& FileLexer::getNextToken () const
  {
    if (m_readPointer >= m_tokens.size()) { return m_tokens.back(); }
    else { return m_tokens.at(m_readPointer++); }
  }

  void FileLexer::ungetToken () const
  {
    if (m_readPointer > 0) { m_readPointer--; }
  }

  void FileLexer::seek (Index offset, bool fromEnd) const
  {
    if (fromEnd == true) { m_readPointer = (m_tokens.size() - 1) - offset; }
    else { m_readPointer = offset; }
  }

  bool FileLexer::hasMoreTokens () const
  {
    return m_readPointer < m_tokens.size();
  }

  bool FileLexer::isEmpty () const
  {
    return m_tokens.empty();
  }

  #define DG_EMPLACE(type, contents) \
    m_tokens.emplace(m_tokens.begin() + m_writePointer, m_currentPath, m_currentLine, type, contents); \
    m_writePointer++;

  int FileLexer::collectSymbol (I32& character)
  {
    FileTokenType type = FileTokenType::Unknown;
    switch (character)
    {
      case '.': type = FileTokenType::Period; break;
      case ',': type = FileTokenType::Comma; break;
      case ':': type = FileTokenType::Colon; break;
      case ';': type = FileTokenType::Semicolon; break;
      case '@': type = FileTokenType::At; break;
      case '#': type = FileTokenType::Pound; break;
      case '$': type = FileTokenType::Dollar; break;
      case '%': type = FileTokenType::Percent; break;
      case '^': type = FileTokenType::Carat; break;
      case '&': type = FileTokenType::Ampersand; break;
      case '*': type = FileTokenType::Asterisk; break;
      case '+': type = FileTokenType::Plus; break;
      case '-': type = FileTokenType::Minus; break;
      case '/': type = FileTokenType::Backslash; break;
      case '\\': type = FileTokenType::ForwardSlash; break;
      case '(': type = FileTokenType::OpenParen; break;
      case ')': type = FileTokenType::CloseParen; break;
      case '[': type = FileTokenType::OpenBracket; break;
      case ']': type = FileTokenType::CloseBracket; break;
      case '{': type = FileTokenType::OpenBrace; break;
      case '}': type = FileTokenType::CloseBrace; break;
      case '<': type = FileTokenType::OpenArrow; break;
      case '>': type = FileTokenType::CloseArrow; break;
      default:
        DG_ENGINE_ERROR("Unexpected character '{}'.", static_cast<Char>(character));
        return -1;
    }

    DG_EMPLACE(type, "");
    return 1;
  }

  int FileLexer::collectNumber (I32& character)
  {
    String contents = "";
    bool isFloat = false;
    
    do {
      if (character == '.') {
        if (isFloat == true) { break; } 
        else { isFloat = true; }
      }

      contents += static_cast<Char>(character);
      character = m_file.get();
    } while (
      std::isdigit(character) || 
      character == '.'
    );

    m_file.unget();
    DG_EMPLACE(FileTokenType::Number, contents);
    return 1;
  }

  int FileLexer::collectString (I32& character)
  {
    String contents = "";
    character = m_file.get();

    while (character != '"') {
      contents += static_cast<Char>(character);
      character = m_file.get();
    }

    DG_EMPLACE(FileTokenType::String, contents);
    return 1;
  }

  int FileLexer::collectIdentifier (I32& character)
  {
    String contents = "";

    do {
      contents += static_cast<Char>(character);
      character = m_file.get();
    } while (std::isalnum(character) || character == '_');

    m_file.unget();
    if (contents == "true" || contents == "false") {
      DG_EMPLACE(FileTokenType::Boolean, contents);
    } else {
      DG_EMPLACE(FileTokenType::Identifier, contents);
    }

    return 1;
  }

  int FileLexer::collectToken ()
  {
    I32 character = m_file.get();
    while (std::isspace(character)) {
      if (character == '\n') {
        DG_EMPLACE(FileTokenType::NewLine, "");
        m_currentLine++;
        return 1;
      }

      character = m_file.get();
    }

    if (character == std::char_traits<Char>::eof()) {
      DG_EMPLACE(FileTokenType::EndOfFile, "");
      return 0;
    }

    if (std::isalpha(character) || character == '_') {
      return collectIdentifier(character);
    } else if (character == '"') {
      return collectString(character);
    } else if (std::isdigit(character)) {
      return collectNumber(character);
    } else {
      return collectSymbol(character);
    }
  }

  #undef DG_EMPLACE

}

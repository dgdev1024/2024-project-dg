/** @file DG/Core/FileToken.hpp */

#pragma once

#include <DG_Pch.hpp>

namespace dg
{

  enum class FileTokenType
  {
    Invalid,
    Unknown,
    Identifier,
    Boolean,
    String,
    Number,
    Period,
    Comma,
    Colon,
    Semicolon,
    At,
    Pound,
    Dollar,
    Percent,
    Carat,
    Ampersand,
    Asterisk,
    Plus,
    Minus,
    Backslash,
    ForwardSlash,
    OpenParen,
    CloseParen,
    OpenBracket,
    CloseBracket,
    OpenBrace,
    CloseBrace,
    OpenArrow,
    CloseArrow,
    NewLine,
    EndOfFile
  };

  struct FileToken
  {

    String sourceFile;
    Index sourceLine;
    FileTokenType type;
    String contents;
    U64 integer;
    F64 real;
    bool boolean;

    FileToken (
      const String& sourceFile,
      const Index sourceLine,
      FileTokenType type,
      const String& contents = ""
    ) :
      sourceFile  { sourceFile },
      sourceLine  { sourceLine },
      type        { type },
      contents    { contents }
    {
      if (type == FileTokenType::Number) {
        integer = std::stoul(contents);
        real = std::stod(contents);
        boolean = (integer != 0);
      } else if (type == FileTokenType::Boolean) {
        boolean = (contents == "true");
        integer = boolean;
        real = boolean;
      } else {
        integer = 0;
        real = 0;
        boolean = false;
      }
    }

    inline const char* typeToString () const
    {
      switch (type)
      {
        case FileTokenType::Identifier: return "Identifier";
        case FileTokenType::Boolean: return "Boolean";
        case FileTokenType::String: return "String";
        case FileTokenType::Number: return "Number";
        case FileTokenType::Period: return "Period";
        case FileTokenType::Comma: return "Comma";
        case FileTokenType::Colon: return "Colon";
        case FileTokenType::Semicolon: return "Semicolon";
        case FileTokenType::At: return "At";
        case FileTokenType::Pound: return "Pound";
        case FileTokenType::Dollar: return "Dollar";
        case FileTokenType::Percent: return "Percent";
        case FileTokenType::Carat: return "Carat";
        case FileTokenType::Ampersand: return "Ampersand";
        case FileTokenType::Asterisk: return "Asterisk";
        case FileTokenType::Plus: return "Plus";
        case FileTokenType::Minus: return "Minus";
        case FileTokenType::Backslash: return "Backslash";
        case FileTokenType::ForwardSlash: return "ForwardSlash";
        case FileTokenType::OpenParen: return "OpenParen";
        case FileTokenType::CloseParen: return "CloseParen";
        case FileTokenType::OpenBracket: return "OpenBracket";
        case FileTokenType::CloseBracket: return "CloseBracket";
        case FileTokenType::OpenBrace: return "OpenBrace";
        case FileTokenType::CloseBrace: return "CloseBrace";
        case FileTokenType::OpenArrow: return "OpenArrow";
        case FileTokenType::CloseArrow: return "CloseArrow";
        case FileTokenType::NewLine: return "NewLine";
        case FileTokenType::EndOfFile: return "EndOfFile";
        default: return "Unknown";
      }
    }

  };

}

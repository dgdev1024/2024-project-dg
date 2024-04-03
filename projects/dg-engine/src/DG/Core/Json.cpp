/** @file DG/Core/Json.cpp */

#include <DG/Core/Json.hpp>

namespace dg
{

  static constexpr String JSON_BLANK_STRING = "";
  static constexpr StrongBool JSON_BLANK_BOOL = StrongBool::False;
  static constexpr F64 JSON_BLANK_NUMBER = 0;

  Json::Json (StrongBool value) :
    m_type { JsonDataType::Boolean },
    m_boolean { value }
  {

  }

  Json::Json (F64 value) :
    m_type { JsonDataType::Number },
    m_number { value }
  {

  }

  Json::Json (const Char* value) :
    m_type { JsonDataType::String }
  {
    if (value != nullptr) { m_string = value; }
  }

  Json::Json (const String& value) :
    m_type { JsonDataType::String },
    m_string { value }
  {

  }

  Json::Json (const InitList<Json>& array) :
    m_type { JsonDataType::Array }
  {
    m_array.insert(m_array.end(), array.begin(), array.end());
  }

  Json::Json (std::nullptr_t) :
    m_type { JsonDataType::Null }
  {

  }

  bool Json::loadFromFile (const Path& path)
  {
    if (fs::exists(path) == false) {
      DG_ENGINE_ERROR("[Json] File '{}' not found.", path);
      return false;
    }

    FileLexer lexer;
    if (lexer.loadFromFile(path, true) == false) {
      DG_ENGINE_ERROR("[Json] Error loading file '{}'.", path);
      return false;
    }

    if (loadFromTokens(lexer) == false) {
      DG_ENGINE_ERROR("[Json] Error parsing file '{}'.", path);
      return false;
    }
    
    return true;
  }

  bool Json::loadFromTokens (const FileLexer& lexer)
  {
    const auto& token = lexer.getNextToken();
    switch (token.type) {
      case FileTokenType::Identifier: {
        if (token.contents == "null") {
          m_type = JsonDataType::Null;
        } else {
          DG_ENGINE_ERROR("[Json] Unexpected identifier '{}' at line #{}.", token.contents,
            token.sourceLine);
          return false;
        }
      } break;
      case FileTokenType::Boolean: {
        m_type = JsonDataType::Boolean;
        m_boolean = token.boolean;
      } break;
      case FileTokenType::String: {
        m_type = JsonDataType::String;
        m_string = token.contents;
      } break;
      case FileTokenType::Integer: {
        m_type = JsonDataType::Number;
        m_number = token.integer;
      } break;
      case FileTokenType::Number: {
        m_type = JsonDataType::Number;
        m_number = token.real;
      } break;
      case FileTokenType::OpenBracket: {
        return loadArray(lexer);
      } break;
      case FileTokenType::OpenBrace: {
        return loadObject(lexer);
      };
      default: {
        DG_ENGINE_ERROR("[Json] Unexpected '{}' token at line #{}.", token.typeToString(),
          token.sourceLine);
        return false;
      }
    }

    return true;
  }

  String Json::dumpToString () const
  {
    std::stringstream sstr;

    switch (m_type) {
      case JsonDataType::Null: sstr << "null"; break;
      case JsonDataType::Boolean: {
        sstr << (m_boolean == StrongBool::True ? "true" : "false");
      } break;
      case JsonDataType::Number: {
        sstr << m_number;
      } break;
      case JsonDataType::String: {
        sstr << "\"" << m_string << "\"";
      } break;
      case JsonDataType::Object: {
        sstr << "{";
        for (auto it = m_object.begin(); it != m_object.end();) {
          sstr << "\"" << it->first << "\":" << it->second.dumpToString();

          if (++it != m_object.end()) {
            sstr << ",";
          }
        }
        sstr << "}";
      } break;
      case JsonDataType::Array: {
        sstr << "[";
        for (Index i = 0; i < m_array.size(); ++i) {
          sstr << m_array[i].dumpToString();
          if (i + 1 < m_array.size()) {
            sstr << ",";
          }
        }
        sstr << "]";
      } break;
      default: break;
    }

    return sstr.str();
  }

  bool Json::saveToFile (const Path& path)
  {
    std::fstream file { path, std::ios::out };
    if (file.is_open() == false) {
      DG_ENGINE_ERROR("[Json] Cannot open file '{}' for writing.", path);
      return false;
    }

    file << dumpToString() << std::endl;
    return true;
  }

  JsonDataType Json::getType () const
  {
    return m_type;
  }

  const StrongBool& Json::getBoolean () const
  {
    if (m_type != JsonDataType::Boolean) {
      DG_ENGINE_THROW(std::runtime_error,
        "[Json] Attempt to retrieve boolean from non-boolean JSON entity!");  
    }

    return m_boolean;
  }

  const F64& Json::getNumber () const
  {
    if (m_type != JsonDataType::Number) {
      DG_ENGINE_THROW(std::runtime_error,
        "[Json] Attempt to retrieve number from non-numeric JSON entity!");  
    }

    return m_number;
  }

  const String& Json::getString () const
  {
    if (m_type != JsonDataType::String) {
      DG_ENGINE_THROW(std::runtime_error,
        "[Json] Attempt to retrieve string from non-string JSON entity!");  
    }

    return m_string;
  }

  const Dictionary<Json>& Json::getObject () const
  {
    if (m_type != JsonDataType::Object) {
      DG_ENGINE_THROW(std::runtime_error,
        "[Json] Attempt to retrieve object from non-object JSON entity!");  
    }

    return m_object;
  }

  const Collection<Json>& Json::getArray () const
  {
    if (m_type != JsonDataType::Array) {
      DG_ENGINE_THROW(std::runtime_error,
        "[Json] Attempt to retrieve array from non-array JSON entity!");  
    }

    return m_array;
  }

  template <>
  I32 Json::to<I32> () const
  {
    return static_cast<I32>(getNumber());
  }

  template <>
  F32 Json::to<F32> () const
  {
    return static_cast<F32>(getNumber());
  }

  template <>
  bool Json::to<bool> () const
  {
    return getBoolean() == StrongBool::True;
  }

  void Json::setBoolean (StrongBool value)
  {
    if (m_type == JsonDataType::Undefined) {
      m_type = JsonDataType::Boolean;
    } else if (m_type != JsonDataType::Boolean) {
      DG_ENGINE_THROW(std::runtime_error,
        "[Json] Attempt to assign boolean value to non-boolean JSON entity!");
    }

    m_boolean = value;
  }

  void Json::setBoolean (WeakBool value)
  {
    setBoolean(value == true ? StrongBool::True : StrongBool::False);
  }

  void Json::setNumber (F64 value)
  {
    if (m_type == JsonDataType::Undefined) {
      m_type = JsonDataType::Number;
    } else if (m_type != JsonDataType::Number) {
      DG_ENGINE_THROW(std::runtime_error,
        "[Json] Attempt to assign numeric value to non-numeric JSON entity!");
    }

    m_number = value;
  }

  void Json::setString (const String& value)
  {
    if (m_type == JsonDataType::Undefined) {
      m_type = JsonDataType::String;
    } else if (m_type != JsonDataType::String) {
      DG_ENGINE_THROW(std::runtime_error,
        "[Json] Attempt to assign string value to non-string JSON entity!");
    }

    m_string = value;
  }

  Json& Json::tryEmplace (const String& key)
  {
    if (m_type == JsonDataType::Undefined) {
      m_type = JsonDataType::Object;
    } else if (m_type != JsonDataType::Object) {
      DG_ENGINE_THROW(std::runtime_error,
        "[Json] Attempt to emplace JSON entry into non-object JSON entity!");
    }

    if (key.empty()) {
      DG_ENGINE_THROW(std::invalid_argument,
        "[Json] Attempt to emplace JSON entry with blank string key!");
    }

    return m_object[key];
  }

  Json& Json::getObjectEntry (const String& key)
  {
    if (m_type != JsonDataType::Object) {
      DG_ENGINE_THROW(std::runtime_error,
        "[Json] Attempt to retrieve JSON entry from non-object JSON entity!");
    }

    if (key.empty()) {
      DG_ENGINE_THROW(std::invalid_argument,
        "[Json] Attempt to retrieve JSON entry with blank string key!");
    }

    auto iter = m_object.find(key);
    if (iter == m_object.end()) {
      DG_ENGINE_THROW(std::out_of_range,
        "[Json] Attempt to retrieve non-existant JSON entry with key '{}'!", key);
    }

    return iter->second;
  }

  const Json& Json::getObjectEntry (const String& key) const
  {
    if (m_type != JsonDataType::Object) {
      DG_ENGINE_THROW(std::runtime_error,
        "[Json] Attempt to retrieve JSON entry from non-object JSON entity!");
    }

    if (key.empty()) {
      DG_ENGINE_THROW(std::invalid_argument,
        "[Json] Attempt to retrieve JSON entry with blank string key!");
    }

    auto iter = m_object.find(key);
    if (iter == m_object.end()) {
      DG_ENGINE_THROW(std::out_of_range,
        "[Json] Attempt to retrieve non-existant JSON entry with key '{}'!", key);
    }

    return iter->second;
  }

  bool Json::removeObjectEntry (const String& key)
  {
    if (m_type != JsonDataType::Object) {
      DG_ENGINE_THROW(std::runtime_error,
        "[Json] Attempt to remove JSON entry from non-object JSON entity!");
    }

    if (key.empty()) {
      DG_ENGINE_THROW(std::invalid_argument,
        "[Json] Attempt to remove JSON entry with blank string key!");
    }

    auto iter = m_object.find(key);
    if (iter == m_object.end()) {
      return false;
    }

    m_object.erase(iter);
    return true;
  }

  Json& Json::pushArrayEntry ()
  {
    if (m_type == JsonDataType::Undefined) {
      m_type = JsonDataType::Array;
    } else if (m_type != JsonDataType::Array) {
      DG_ENGINE_THROW(std::runtime_error,
        "[Json] Attempt to push element into non-array JSON entity!");
    }

    return m_array.emplace_back();
  }

  void Json::popArrayEntry ()
  {
    if (m_type != JsonDataType::Array) {
      DG_ENGINE_THROW(std::runtime_error,
        "[Json] Attempt to pop element from non-array JSON entity!");
    }

    m_array.pop_back();
  }

  Json& Json::getArrayEntry (const Index index)
  {
    if (m_type != JsonDataType::Array) {
      DG_ENGINE_THROW(std::runtime_error,
        "[Json] Attempt to retrieve element from non-array JSON entity!");
    }

    if (index >= m_array.size()) {
      DG_ENGINE_THROW(std::out_of_range,
        "[Json] Attempt to retrieve element from array at out-of-range index {}!", index);
    }

    return m_array.at(index);
  }

  const Json& Json::getArrayEntry (const Index index) const
  {
    if (m_type != JsonDataType::Array) {
      DG_ENGINE_THROW(std::runtime_error,
        "[Json] Attempt to retrieve element from non-array JSON entity!");
    }

    if (index >= m_array.size()) {
      DG_ENGINE_THROW(std::out_of_range,
        "[Json] Attempt to retrieve element from array at out-of-range index {}!", index);
    }

    return m_array.at(index);
  }

  Json& Json::getArrayFront ()
  {
    if (m_type != JsonDataType::Array) {
      DG_ENGINE_THROW(std::runtime_error,
        "[Json] Attempt to retrieve first element from non-array JSON entity!");
    }

    if (m_array.empty()) {
      DG_ENGINE_THROW(std::out_of_range,
        "[Json] Attempt to retrieve first element from empty JSON array!");
    }

    return m_array.front();
  }

  const Json& Json::getArrayFront () const
  {
    if (m_type != JsonDataType::Array) {
      DG_ENGINE_THROW(std::runtime_error,
        "[Json] Attempt to retrieve first element from non-array JSON entity!");
    }

    if (m_array.empty()) {
      DG_ENGINE_THROW(std::out_of_range,
        "[Json] Attempt to retrieve first element from empty JSON array!");
    }

    return m_array.front();
  }

  Json& Json::getArrayBack ()
  {
    if (m_type != JsonDataType::Array) {
      DG_ENGINE_THROW(std::runtime_error,
        "[Json] Attempt to retrieve last element from non-array JSON entity!");
    }

    if (m_array.empty()) {
      DG_ENGINE_THROW(std::out_of_range,
        "[Json] Attempt to retrieve last element from empty JSON array!");
    }

    return m_array.back();
  }

  const Json& Json::getArrayBack () const
  {
    if (m_type != JsonDataType::Array) {
      DG_ENGINE_THROW(std::runtime_error,
        "[Json] Attempt to retrieve last element from non-array JSON entity!");
    }

    if (m_array.empty()) {
      DG_ENGINE_THROW(std::out_of_range,
        "[Json] Attempt to retrieve last element from empty JSON array!");
    }

    return m_array.back();
  }

  Json& Json::operator[] (const String& key)
  {
    return tryEmplace(key);
  }

  const Json& Json::operator[] (const String& key) const
  {
    return getObjectEntry(key);
  }
  
  Json& Json::operator[] (const Index index)
  {
    return getArrayEntry(index);
  }

  const Json& Json::operator[] (const Index index) const
  {
    return getArrayEntry(index);
  }

  bool Json::loadObject (const FileLexer& lexer)
  {
    auto token = lexer.getNextToken();
    if (token.type == FileTokenType::CloseBrace) {
      m_type = JsonDataType::Object;
      return true;
    } else {
      lexer.ungetToken();
    }

    while (true) {
      token = lexer.getNextToken();
      if (token.type != FileTokenType::String) {
        DG_ENGINE_ERROR("[Json] Expected string token for JSON object key at line #{}.",
          token.sourceLine);
        return false;
      }

      if (lexer.getNextToken().type != FileTokenType::Colon) {
        DG_ENGINE_ERROR("[Json] Expected ':' after JSON object key at line #{}.", token.sourceLine);
        return false;
      }

      bool result = m_object[token.contents].loadFromTokens(lexer);
      if (result == false) {
        DG_ENGINE_ERROR("[Json] Error parsing value of JSON object at line #{}.", token.sourceLine);
        return false;
      }

      token = lexer.getNextToken();
      if (token.type == FileTokenType::Comma) { continue; }
      else if (token.type == FileTokenType::CloseBrace) { break; }
      else {
        DG_ENGINE_ERROR("[Json] Expected ',' or '}' after JSON object entry at line #{}.",
          token.sourceLine);
        return false;
      }
    }

    m_type = JsonDataType::Object;
    return true;
  }

  bool Json::loadArray (const FileLexer& lexer)
  {
    auto token = lexer.getNextToken();
    if (token.type == FileTokenType::CloseBracket) {
      m_type = JsonDataType::Array;
      return true;
    } else {
      lexer.ungetToken();
    }

    while (true) {
      bool result = m_array.emplace_back().loadFromTokens(lexer);
      if (result == false) {
        DG_ENGINE_ERROR("[Json] Error parsing element of JSON array at line #{}.", token.sourceLine);
        return false;
      }

      token = lexer.getNextToken();
      if (token.type == FileTokenType::Comma) { continue; }
      else if (token.type == FileTokenType::CloseBracket) { break; }
      else {
        DG_ENGINE_ERROR("[Json] Expected ',' or ']' after JSON array element at line #{}.",
          token.sourceLine);
        return false;
      }
    }

    m_type = JsonDataType::Array;
    return true;
  }

}
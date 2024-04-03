/** @file DG/Core/Json.hpp */

#pragma once

#include <DG/Core/FileLexer.hpp>

namespace dg
{

  enum class JsonDataType
  {
    Undefined,
    Null,
    Boolean,
    Number,
    String,
    Object,
    Array
  };

  class Json
  {
  public:
    Json () = default;
    Json (StrongBool value);
    Json (F64 value);
    Json (const Char* value);
    Json (const String& value);
    Json (const InitList<Json>& array);
    Json (std::nullptr_t);
    ~Json () = default;

  public:
    bool loadFromFile (const Path& path);
    bool loadFromTokens (const FileLexer& lexer);
    String dumpToString () const;
    bool saveToFile (const Path& path);

  public:
    JsonDataType getType () const;
    const StrongBool& getBoolean () const;
    const F64& getNumber () const;
    const String& getString () const;
    const Dictionary<Json>& getObject () const;
    const Collection<Json>& getArray () const;

  public:
    template <typename T>
    T to () const;

  public:
    void setBoolean (StrongBool value);
    void setBoolean (WeakBool value);
    void setNumber (F64 value);
    void setString (const String& value);

  public:
    Json& tryEmplace (const String& key);
    Json& getObjectEntry (const String& key);
    const Json& getObjectEntry (const String& key) const;
    bool removeObjectEntry (const String& key);

  public:
    Json& pushArrayEntry ();
    void popArrayEntry ();
    Json& getArrayEntry (const Index index);
    const Json& getArrayEntry (const Index index) const;
    Json& getArrayFront ();
    const Json& getArrayFront () const;
    Json& getArrayBack ();
    const Json& getArrayBack () const;

  public:
    Json& operator[] (const String& key);
    const Json& operator[] (const String& key) const;
    Json& operator[] (const Index index);
    const Json& operator[] (const Index index) const;

  private:
    bool loadObject (const FileLexer& lexer);
    bool loadArray (const FileLexer& lexer);

  private:
    JsonDataType m_type = JsonDataType::Undefined;
    StrongBool m_boolean = StrongBool::False;
    F64 m_number = 0;
    String m_string = "";
    Dictionary<Json> m_object;
    Collection<Json> m_array;

  };

}

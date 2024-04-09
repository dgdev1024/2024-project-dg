/** @file DG/Graphics/Shader.hpp */

#pragma once

#include <DG_Pch.hpp>
#include <DG/Math/Matrix4.hpp>

namespace dg
{

  class Shader
  {
  protected:
    Shader () = default;

  public:
    virtual ~Shader () = default;

  public:
    static Shared<Shader> make (const Path& path);
    static Shared<Shader> make (const String& vertexCode, const String& fragmentCode);

  public:
    virtual void bind () const = 0;
    virtual void unbind () const = 0;

  public:
    virtual bool setInteger (const String&, I32) = 0;
    virtual bool setUnsignedInteger (const String&, U32) = 0;
    virtual bool setFloat (const String&, F32) = 0;
    virtual bool setDouble (const String&, F64) = 0;
    virtual bool setBoolean (const String&, bool) = 0;

    virtual bool setVector2i (const String&, const Vector2i&) = 0;
    virtual bool setVector2u (const String&, const Vector2u&) = 0;
    virtual bool setVector2f (const String&, const Vector2f&) = 0;
    virtual bool setVector2d (const String&, const Vector2d&) = 0;
    virtual bool setVector2b (const String&, const Vector2b&) = 0;

    virtual bool setVector3i (const String&, const Vector3i&) = 0;
    virtual bool setVector3u (const String&, const Vector3u&) = 0;
    virtual bool setVector3f (const String&, const Vector3f&) = 0;
    virtual bool setVector3d (const String&, const Vector3d&) = 0;
    virtual bool setVector3b (const String&, const Vector3b&) = 0;

    virtual bool setVector4i (const String&, const Vector4i&) = 0;
    virtual bool setVector4u (const String&, const Vector4u&) = 0;
    virtual bool setVector4f (const String&, const Vector4f&) = 0;
    virtual bool setVector4d (const String&, const Vector4d&) = 0;
    virtual bool setVector4b (const String&, const Vector4b&) = 0;

    virtual bool setMatrix2f (const String&, const Matrix2f&) = 0;
    virtual bool setMatrix3f (const String&, const Matrix3f&) = 0;
    virtual bool setMatrix4f (const String&, const Matrix4f&) = 0;

    virtual bool setMatrix2d (const String&, const Matrix2d&) = 0;
    virtual bool setMatrix3d (const String&, const Matrix3d&) = 0;
    virtual bool setMatrix4d (const String&, const Matrix4d&) = 0;

  public:
    inline bool isValid () const { return m_valid; }

  protected:
    bool m_valid = false;

  };

}

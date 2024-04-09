/** @file DG/OpenGL/GLShader.hpp */

#pragma once

#if !defined(DG_USING_OPENGL)
  #error "Do not #include this file if you are not using OpenGL!"
#endif

#include <DG/Graphics/Shader.hpp>

namespace dg::OpenGL
{

  class ShaderImpl : public Shader
  {
  public:
    ShaderImpl (const Path& path);
    ShaderImpl (const String& vertexCode, const String& fragmentCode);
    ~ShaderImpl ();

  public:
    void bind () const override;
    void unbind () const override;

  public:
    bool setInteger (const String& key, I32 value) override;
    bool setUnsignedInteger (const String& key, U32 value) override;
    bool setFloat (const String& key, F32 value) override;
    bool setDouble (const String& key, F64 value) override;
    bool setBoolean (const String& key, bool value) override;

    bool setVector2i (const String& key, const Vector2i& value) override;
    bool setVector2u (const String& key, const Vector2u& value) override;
    bool setVector2f (const String& key, const Vector2f& value) override;
    bool setVector2d (const String& key, const Vector2d& value) override;
    bool setVector2b (const String& key, const Vector2b& value) override;

    bool setVector3i (const String& key, const Vector3i& value) override;
    bool setVector3u (const String& key, const Vector3u& value) override;
    bool setVector3f (const String& key, const Vector3f& value) override;
    bool setVector3d (const String& key, const Vector3d& value) override;
    bool setVector3b (const String& key, const Vector3b& value) override;

    bool setVector4i (const String& key, const Vector4i& value) override;
    bool setVector4u (const String& key, const Vector4u& value) override;
    bool setVector4f (const String& key, const Vector4f& value) override;
    bool setVector4d (const String& key, const Vector4d& value) override;
    bool setVector4b (const String& key, const Vector4b& value) override;

    bool setMatrix2f (const String& key, const Matrix2f& value) override;
    bool setMatrix3f (const String& key, const Matrix3f& value) override;
    bool setMatrix4f (const String& key, const Matrix4f& value) override;

    bool setMatrix2d (const String& key, const Matrix2d& value) override;
    bool setMatrix3d (const String& key, const Matrix3d& value) override;
    bool setMatrix4d (const String& key, const Matrix4d& value) override;

  private:
    bool build ();
    I32 findUniform (StringView key);

  private:
    U32 m_handle = 0;
    String m_vertexCode = "";
    String m_fragmentCode = "";

  };

}

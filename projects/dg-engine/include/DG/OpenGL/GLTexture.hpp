/** @file DG/OpenGL/GLTexture.hpp */

#pragma once

#if !defined(DG_USING_OPENGL)
  #error "Do not #include this file if you are not using OpenGL!"
#endif

#include <DG/Graphics/Texture.hpp>

namespace dg::OpenGL
{

  class TextureImpl : public Texture
  {
  public:
    TextureImpl (const Path& path);
    TextureImpl (const TextureSpecification& spec);
    ~TextureImpl ();

  public:
    void bind (const Index slot = 0) const override;
    void unbind (const Index slot = 0) const override;
    void upload (const void* data, const Size size) override;
    void* getPointer () const override;

  private:
    bool initializeTexture () override;
    bool onImageDataLoaded (const void* data) override;

  private:
    U32 m_handle = 0;
    GLenum m_internalFormat = 0;
    GLenum m_pixelFormat = 0;

  };

}

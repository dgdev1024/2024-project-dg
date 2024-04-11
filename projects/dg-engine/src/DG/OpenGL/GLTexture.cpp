/** @file DG/OpenGL/GLTexture.cpp */

#include <DG/OpenGL/GLTexture.hpp>

namespace dg
{

  Shared<Texture> Texture::make (const Path& path)
  {
    return std::make_shared<OpenGL::TextureImpl>(path);
  }

}

namespace dg::OpenGL
{

  static GLenum resolveTextureWrap (TextureWrapMode mode)
  {
    switch (mode) {
      case TextureWrapMode::REPEAT:           return GL_REPEAT;
      case TextureWrapMode::MIRRORED_REPEAT:  return GL_MIRRORED_REPEAT;
      case TextureWrapMode::CLAMP_TO_EDGE:    return GL_CLAMP_TO_EDGE;
      default: return 0;
    }
  }

  static GLenum resolveTextureFilter (TextureFilterMode mode)
  {
    switch (mode) {
      case TextureFilterMode::LINEAR:         return GL_LINEAR;
      case TextureFilterMode::NEAREST:        return GL_NEAREST;
      default: return 0;
    }
  }

  static bool resolveTextureFormat (I32 channelCount, GLenum& internalFormat, 
    GLenum& pixelFormat)
  {
    switch (channelCount) {
      case 1: internalFormat = GL_R8;     pixelFormat = GL_RED;   break;
      case 2: internalFormat = GL_RG8;    pixelFormat = GL_RG;    break;
      case 3: internalFormat = GL_RGB8;   pixelFormat = GL_RGB;   break;
      case 4: internalFormat = GL_RGBA8;  pixelFormat = GL_RGBA;  break;
      default: return false;
    }

    return true;
  }

  TextureImpl::TextureImpl (const Path& path) :
    Texture {}
  {
    glGenTextures(1, &m_handle);
    loadFromFile(path);
  }

  TextureImpl::TextureImpl (const TextureSpecification& spec) :
    Texture { spec }
  {
    glGenTextures(1, &m_handle);
    initializeTexture();
  }

  TextureImpl::~TextureImpl ()
  {
    glDeleteTextures(1, &m_handle);
  }

  void TextureImpl::bind (const Index slot) const
  {
    if (slot >= TEXTURE_SLOT_COUNT) {
      DG_ENGINE_THROW(std::invalid_argument,
        "Attempt to bind texture to invalid slot number {}!", slot);
    }  

    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_handle);
  }

  void TextureImpl::unbind (const Index slot) const
  {
    if (slot >= TEXTURE_SLOT_COUNT) {
      DG_ENGINE_THROW(std::invalid_argument,
        "Attempt to unbind texture from invalid slot number {}!", slot);
    }

    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  bool TextureImpl::initializeTexture ()
  {
    if (resolveTextureFormat(m_colorChannelCount, m_internalFormat, m_pixelFormat) == false) {
      DG_ENGINE_ERROR("Texture has invalid color channel count {}.", m_colorChannelCount);
      return false;
    }

    glBindTexture(GL_TEXTURE_2D, m_handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, resolveTextureWrap(m_wrap));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, resolveTextureWrap(m_wrap));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, resolveTextureFilter(m_minify));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, resolveTextureFilter(m_magnify));

    return true;
  }

  bool TextureImpl::onImageDataLoaded (const void* data)
  {
    if (data == nullptr) {
      return false;
    }

    if (initializeTexture() == false) {
      return false;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_size.x, m_size.y, 0, m_pixelFormat,
      GL_UNSIGNED_BYTE, data);

    return true;
  }

}

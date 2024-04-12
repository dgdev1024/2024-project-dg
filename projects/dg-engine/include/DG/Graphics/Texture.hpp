/** @file DG/Graphics/Texture.hpp */

#pragma once

#include <DG/Math/Vector2.hpp>

namespace dg
{

  constexpr Count TEXTURE_SLOT_COUNT = 16;

  enum class TextureWrapMode
  {
    REPEAT,
    MIRRORED_REPEAT,
    CLAMP_TO_EDGE
  };

  enum class TextureFilterMode
  {
    NEAREST,
    LINEAR
  };

  struct TextureSpecification
  {
    Vector2i size = { 1, 1 };
    I32 colorChannelCount = 4;
    TextureWrapMode wrap = TextureWrapMode::REPEAT;
    TextureFilterMode magnify = TextureFilterMode::NEAREST;
    TextureFilterMode minify = TextureFilterMode::NEAREST;
  };

  class Texture
  {
  protected:
    Texture (const TextureSpecification& spec = {});

  public:
    virtual ~Texture () = default;

  public:
    static Shared<Texture> make (const TextureSpecification& spec = {});
    static Shared<Texture> make (const Path& path);

  public:
    virtual void bind (const Index slot = 0) const = 0;
    virtual void unbind (const Index slot = 0) const = 0;
    virtual void upload (const void*, const Size) = 0;

  public:
    bool loadFromFile (const Path& path);

  public:
    inline bool isValid () const { return m_valid; }
    inline const Vector2i& getSize () const { return m_size; }
    inline I32 getColorChannelCount () const { return m_colorChannelCount; }
    inline TextureWrapMode getWrapMode () const { return m_wrap; }
    inline TextureFilterMode getMagnifyFilterMode () const { return m_magnify; }
    inline TextureFilterMode getMinifyFilterMode () const { return m_minify; }

  protected:
    virtual bool initializeTexture () = 0;
    virtual bool onImageDataLoaded (const void*) = 0;

  protected:
    bool m_valid = false;
    Vector2i m_size;
    I32 m_colorChannelCount;
    TextureWrapMode m_wrap;
    TextureFilterMode m_magnify;
    TextureFilterMode m_minify;

  };

}

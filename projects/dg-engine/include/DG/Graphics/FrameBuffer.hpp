/** @file DG/Graphics/FrameBuffer.hpp */

#pragma once

#include <DG/Math/Vector2.hpp>

namespace dg
{

  constexpr Count FRAMEBUFFER_COLOR_ATTACHMENT_COUNT = 4;

  enum class FrameBufferTextureFormat
  {
    NONE = 0,
    COLOR_R32I,
    COLOR_RGBA8,
    DEPTH_24_STENCIL_8,

    COLOR = COLOR_RGBA8,
    DEPTH_STENCIL = DEPTH_24_STENCIL_8,
    DEPTH = DEPTH_24_STENCIL_8
  };

  enum class FrameBufferBindTarget
  {
    DRAW,
    READ,
    BOTH
  };

  struct FrameBufferTextureSpecification
  {
    FrameBufferTextureSpecification () = default;
    FrameBufferTextureSpecification (FrameBufferTextureFormat format) :
      format { format }
    {}
    FrameBufferTextureFormat format = FrameBufferTextureFormat::NONE;
    
    inline bool isDepthTextureFormat () const
    {
      switch (format)
      {
        case FrameBufferTextureFormat::DEPTH_24_STENCIL_8:
          return true;

        default: return false;
      }
    }
  };

  struct FrameBufferAttachmentSpecification
  {
    FrameBufferAttachmentSpecification () = default;
    FrameBufferAttachmentSpecification (const InitList<FrameBufferTextureSpecification>& specs) :
      attachments { specs }
    {}
    Collection<FrameBufferTextureSpecification> attachments;
  };

  struct FrameBufferSpecification
  {
    Vector2u size = { 1280, 720 };
    Count sampleCount = 1;
    bool swapChainTarget = false;
    FrameBufferAttachmentSpecification attachmentSpec;
  };

  class FrameBuffer
  {
  protected:
    FrameBuffer (const FrameBufferSpecification& spec) :
      m_spec { spec }
    {}

  public:
    virtual ~FrameBuffer () = default;

  public:
    static Shared<FrameBuffer> make (const FrameBufferSpecification& spec = {});

  public:
    virtual void bind (FrameBufferBindTarget target = FrameBufferBindTarget::DRAW) const = 0;
    virtual void unbind (FrameBufferBindTarget target = FrameBufferBindTarget::DRAW) const = 0;
    virtual U32 getColorHandle (const Index index = 0) const = 0;
    virtual U32 getDepthHandle () const = 0;
    virtual void* getColorPointer (const Index index = 0) const = 0;
    virtual I32 readPixelI32 (const Index index, const Vector2i& position) const = 0;
    virtual I32 readPixelI32 (const Index index, const Vector2f& position) const = 0;

  public:
    inline const Vector2u& getSize () const { return m_spec.size; }
    inline U32 getWidth () const { return m_spec.size.x; }
    inline U32 getHeight () const { return m_spec.size.y; }

    inline bool setSize (const Vector2u& size)
    {
      if (size.x > 0 && size.y > 0 && size != m_spec.size) {
        m_spec.size = size;
        onSizeChanged();
        return true;
      }

      return false;
    }

    inline bool setSize (const U32 width, const U32 height) 
    {
      return setSize({ width, height });
    }

  protected:
    virtual void onSizeChanged () = 0;

  protected:
    FrameBufferSpecification m_spec;
    Collection<FrameBufferTextureSpecification> m_colorAttachmentSpecs;
    FrameBufferTextureSpecification m_depthAttachmentSpec;

  };

}
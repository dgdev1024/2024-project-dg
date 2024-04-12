/** @file DG/OpenGL/GLFrameBuffer.cpp */

#include <DG/Graphics/RenderCommand.hpp>
#include <DG/OpenGL/GLFrameBuffer.hpp>

namespace dg
{

  Shared<FrameBuffer> FrameBuffer::make (const FrameBufferSpecification& spec)
  {
    return std::make_shared<OpenGL::FrameBufferImpl>(spec);
  }

}

namespace dg::OpenGL
{

  static GLenum resolveTextureTarget (bool multisampled)
  {
    return (multisampled == true) ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
  }

  static void resolveTextureFormat (const FrameBufferTextureFormat format,
    GLenum& internalFormat, GLenum& pixelFormat, GLenum& dataType)
  {
    switch (format)
    {
      case FrameBufferTextureFormat::COLOR_R32I:
        internalFormat = GL_R32I;
        pixelFormat = GL_RED_INTEGER;
        dataType = GL_INT;
        break;

      case FrameBufferTextureFormat::COLOR_RGBA8:
        internalFormat = GL_RGBA8;
        pixelFormat = GL_RGBA;
        dataType = GL_UNSIGNED_BYTE;
        break;

      case FrameBufferTextureFormat::DEPTH_24_STENCIL_8:
        internalFormat = GL_DEPTH24_STENCIL8;
        pixelFormat = GL_DEPTH_STENCIL;
        dataType = GL_UNSIGNED_INT_24_8;
        break;

      default:
        internalFormat = 0;
        pixelFormat = 0;
        dataType = 0;
        break;
    }
  }

  static GLenum resolveAttachmentPoint (const FrameBufferTextureFormat format)
  {
    switch (format)
    {
      case FrameBufferTextureFormat::DEPTH_24_STENCIL_8:
        return GL_DEPTH_STENCIL_ATTACHMENT;

      default: return 0;
    }
  }

  static GLenum resolveBindTarget (FrameBufferBindTarget target)
  {
    switch (target) {
      case FrameBufferBindTarget::DRAW: return GL_DRAW_FRAMEBUFFER;
      case FrameBufferBindTarget::READ: return GL_READ_FRAMEBUFFER;
      case FrameBufferBindTarget::BOTH: return GL_FRAMEBUFFER;
      default: return 0;
    }
  }

  static void generateAttachmentTextures (U32* handles, Count count)
  {
    glGenTextures(count, handles);
  }

  static void bindAttachmentTexture (U32 handle, bool multisampled)
  {
    glBindTexture(resolveTextureTarget(multisampled), handle);
  }

  static void attachColorTexture (U32 handle, Index index, 
    const FrameBufferSpecification& framebufferSpec, 
    const FrameBufferTextureSpecification& textureSpec)
  {
    bool multisampled = (framebufferSpec.sampleCount > 1);
    GLenum internalFormat = 0, pixelFormat = 0, dataType = 0;
    resolveTextureFormat(textureSpec.format, internalFormat, pixelFormat, dataType);

    if (multisampled == true) {
      glTexImage2DMultisample(
        GL_TEXTURE_2D_MULTISAMPLE,
        framebufferSpec.sampleCount,
        internalFormat,
        framebufferSpec.size.x,
        framebufferSpec.size.y,
        GL_FALSE
      );
    } else {
      glTexImage2D(
        GL_TEXTURE_2D,
        0,
        internalFormat,
        framebufferSpec.size.x,
        framebufferSpec.size.y,
        0,
        pixelFormat,
        dataType,
        nullptr
      );

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index,
      resolveTextureTarget(multisampled), handle, 0);
  }

  static void attachDepthTexture (U32 handle, const FrameBufferSpecification& framebufferSpec,
    const FrameBufferTextureSpecification& textureSpec)
  {
    bool multisampled = (framebufferSpec.sampleCount > 1);
    GLenum internalFormat = 0, pixelFormat = 0, dataType = 0;
    resolveTextureFormat(textureSpec.format, internalFormat, pixelFormat, dataType);

    if (multisampled == true) {
      glTexImage2DMultisample(
        GL_TEXTURE_2D_MULTISAMPLE,
        framebufferSpec.sampleCount,
        internalFormat,
        framebufferSpec.size.x,
        framebufferSpec.size.y,
        GL_FALSE
      );
    } else {
      glTexImage2D(
        GL_TEXTURE_2D,
        0,
        internalFormat,
        framebufferSpec.size.x,
        framebufferSpec.size.y,
        0,
        pixelFormat,
        dataType,
        nullptr
      );

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    glFramebufferTexture2D(GL_FRAMEBUFFER, resolveAttachmentPoint(textureSpec.format),
      resolveTextureTarget(multisampled), handle, 0);
  }

  FrameBufferImpl::FrameBufferImpl (const FrameBufferSpecification& spec) :
    FrameBuffer { spec }
  {
    for (const auto& attachment : m_spec.attachmentSpec.attachments) {
      if (attachment.isDepthTextureFormat() == true) {
        m_depthAttachmentSpec = attachment;
      } else {
        m_colorAttachmentSpecs.push_back(attachment);
      }
    }

    build();
  }

  FrameBufferImpl::~FrameBufferImpl ()
  {
    if (m_handle == 0) {
      glDeleteFramebuffers(1, &m_handle);
      glDeleteTextures(m_colorHandles.size(), m_colorHandles.data());
      glDeleteTextures(1, &m_depthHandle);

      m_colorHandles.clear();
      m_depthHandle = 0;
      m_handle = 0;
    }
  }

  void FrameBufferImpl::bind (FrameBufferBindTarget target) const
  {
    glBindFramebuffer(resolveBindTarget(target), m_handle);

    if (
      target == FrameBufferBindTarget::DRAW ||
      target == FrameBufferBindTarget::BOTH
    ) {
      RenderCommand::setViewport(m_spec.size.x, m_spec.size.y);
      RenderCommand::clear();
    }
  }

  void FrameBufferImpl::unbind (FrameBufferBindTarget target) const
  {
    glBindFramebuffer(resolveBindTarget(target), 0);
  }

  U32 FrameBufferImpl::getColorHandle (const Index index) const
  {
    if (index >= m_colorHandles.size()) {
      DG_ENGINE_THROW(std::out_of_range,
        "Attempt to get GL framebuffer color attachment at out of range index {}!", index);
    }

    return m_colorHandles.at(index);
  }

  U32 FrameBufferImpl::getDepthHandle () const
  {
    return m_depthHandle;
  }

  void* FrameBufferImpl::getColorPointer (const Index index) const
  {
    if (index >= m_colorHandles.size()) {
      DG_ENGINE_THROW(std::out_of_range,
        "Attempt to point to GL framebuffer color attachment at out of range index {}!", index);
    }

    return (void*) (intptr_t) m_colorHandles.at(index);
  }

  I32 FrameBufferImpl::readPixelI32 (const Index index, const Vector2i& position) const
  {
    if (index >= m_colorHandles.size()) {
      DG_ENGINE_THROW(std::out_of_range,
        "Attempt to read pixel data from GL framebuffer color attachment at out of range index {}!", 
          index);
    }

    if (position.x >= m_spec.size.x || position.y >= m_spec.size.y) {
      return -1;
    }

    const auto& textureSpec = m_colorAttachmentSpecs.at(index);
    GLenum pixelFormat = 0, pixelDataType = 0, internalFormat = 0;
    resolveTextureFormat(textureSpec.format, internalFormat, pixelFormat, pixelDataType);

    I32 pixelData = 0;
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_handle);
    glReadBuffer(GL_COLOR_ATTACHMENT0 + index);
    glReadPixels(position.x, position.y, 1, 1, pixelFormat, pixelDataType, &pixelData);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

    return pixelData;
  }

  I32 FrameBufferImpl::readPixelI32 (const Index index, const Vector2f& position) const
  {
    return readPixelI32(index, position.cast<I32>());
  }

  void FrameBufferImpl::onSizeChanged ()
  {
    build();
  }

  void FrameBufferImpl::build ()
  {
    if (m_handle == 0) {
      glDeleteFramebuffers(1, &m_handle);
      glDeleteTextures(m_colorHandles.size(), m_colorHandles.data());
      glDeleteTextures(1, &m_depthHandle);

      m_colorHandles.clear();
      m_depthHandle = 0;
      m_handle = 0;
    }

    glCreateFramebuffers(1, &m_handle);
    glBindFramebuffer(GL_FRAMEBUFFER, m_handle);

    bool multisampled = (m_spec.sampleCount > 1);
    if (m_colorAttachmentSpecs.empty() == false) {
      m_colorHandles.resize(m_colorAttachmentSpecs.size());
      generateAttachmentTextures(m_colorHandles.data(), m_colorHandles.size());

      for (Index i = 0; i < m_colorAttachmentSpecs.size(); ++i) {
        bindAttachmentTexture(multisampled, m_colorHandles.at(i));
        attachColorTexture(m_colorHandles.at(i), i, m_spec, m_colorAttachmentSpecs.at(i));
      }
    }

    if (m_depthAttachmentSpec.format != FrameBufferTextureFormat::NONE) {
      generateAttachmentTextures(&m_depthHandle, 1);
      bindAttachmentTexture(m_depthHandle, multisampled);
      attachDepthTexture(m_depthHandle, m_spec, m_depthAttachmentSpec);
    }

    if (m_colorHandles.empty() == false) {
      if (m_colorHandles.size() > FRAMEBUFFER_COLOR_ATTACHMENT_COUNT) {
        DG_ENGINE_THROW(std::runtime_error,
          "Attempt to build GL framebuffer with too many color attachments (max is {}; got {} instead)!",
            FRAMEBUFFER_COLOR_ATTACHMENT_COUNT, m_colorHandles.size());
      }

      U32 colorAttachmentBuffers[FRAMEBUFFER_COLOR_ATTACHMENT_COUNT] = {
        GL_COLOR_ATTACHMENT0,
        GL_COLOR_ATTACHMENT1,
        GL_COLOR_ATTACHMENT2,
        GL_COLOR_ATTACHMENT3
      };

      glDrawBuffers(m_colorHandles.size(), colorAttachmentBuffers);
    } else {
      glDrawBuffer(GL_NONE);
    }

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
      DG_ENGINE_THROW(std::runtime_error, "Error building complete GL framebuffer!");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

}

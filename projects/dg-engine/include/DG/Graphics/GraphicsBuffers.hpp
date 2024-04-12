/** @file DG/Graphics/GraphicsBuffers.hpp */

#pragma once

#include <DG/Graphics/VertexLayout.hpp>

namespace dg
{

  class VertexBuffer
  {
  protected:
    VertexBuffer () = default;

  public:
    virtual ~VertexBuffer () = default;

  public:
    static Shared<VertexBuffer> make (const void* data, const Size size, bool dynamic = false);
    static Shared<VertexBuffer> allocate (const Size size);

  public:
    virtual void bind () const = 0;
    virtual void unbind () const = 0;
    virtual void upload (const void*, const Size) = 0;

  public:
    template <typename T>
    inline static Shared<VertexBuffer> makeFrom (const Collection<T>& vertices,
      bool dynamic = false)
    {
      static_assert(std::is_standard_layout_v<T>,
        "[VertexBuffer] 'T' must be of a standard layout.");

      return make(vertices.data(), vertices.size() * sizeof(T), dynamic);
    }

    template <typename T>
    inline static Shared<VertexBuffer> allocateFrom (const Count count)
    {
      static_assert(std::is_standard_layout_v<T>,
        "[VertexBuffer] 'T' must be of a standard layout.");

      return allocate(count * sizeof(T));
    }

    template <typename T>
    inline void uploadFrom (const Collection<T>& vertices, Count count = -1)
    {
      static_assert(std::is_standard_layout_v<T>,
        "[VertexBuffer] 'T' must be of a standard layout.");

      if (vertices.empty()) { return; }

      if (count > vertices.size()) {
        count = vertices.size();
      }

      upload(vertices.data(), vertices.size() * sizeof(T));
    }

  public:
    inline bool isDynamic () const { return m_dynamic; }
    inline Size getByteSize () const { return m_byteSize; }
    inline const VertexLayout& getLayout () const { return m_layout; }

    inline void setLayout (const VertexLayout& layout) { m_layout = layout; }

  protected:
    bool m_dynamic = false;
    Size m_byteSize = 0;
    VertexLayout m_layout;

  };

  class IndexBuffer
  {
  protected:
    IndexBuffer () = default;

  public:
    virtual ~IndexBuffer () = default;

  public:
    static Shared<IndexBuffer> make (const Collection<U32>& indices, bool dynamic = false);
    static Shared<IndexBuffer> allocate (const Count count);

  public:
    virtual void bind () const = 0;
    virtual void unbind () const = 0;

  public:
    inline bool isDynamic () const { return m_dynamic; }
    inline Count getIndexCount () const { return m_indexCount; }

  protected:
    bool m_dynamic = false;
    Count m_indexCount = 0;

  };

}

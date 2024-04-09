/** @file DG/Graphics/VertexArray.hpp */

#pragma once

#include <DG/Graphics/GraphicsBuffers.hpp>

namespace dg
{

  class VertexArray
  {
  protected:
    VertexArray () = default;

  public:
    virtual ~VertexArray () = default;

  public:
    static Shared<VertexArray> make ();

  public:
    virtual void bind () const = 0;
    virtual void unbind () const = 0;
    virtual void addVertexBuffer (const Shared<VertexBuffer>&) = 0;
    virtual void setIndexBuffer (const Shared<IndexBuffer>&) = 0;

  public:
    inline bool isLayoutDefined () const { return m_vbos.empty() == false; }
    inline const Shared<IndexBuffer>& getIndexBuffer () const { return m_ibo; }

  protected:
    Collection<Shared<VertexBuffer>> m_vbos;
    Shared<IndexBuffer> m_ibo = nullptr;

  };

}

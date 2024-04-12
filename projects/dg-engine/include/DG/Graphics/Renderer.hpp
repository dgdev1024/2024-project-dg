/** @file DG/Graphics/Renderer.hpp */

#pragma once

#include <DG/Math/Matrix4.hpp>
#include <DG/Graphics/VertexArray.hpp>
#include <DG/Graphics/Shader.hpp>
#include <DG/Graphics/FrameBuffer.hpp>
#include <DG/Graphics/Texture.hpp>
#include <DG/Graphics/RenderCommand.hpp>

namespace dg
{

  struct QuadVertex2D
  {
    Vector3f  position;
    Vector2f  texCoords;
    Vector4f  color;
    F32       texIndex;
    F32       entityId;
  };

  struct RenderData2D
  {
    static constexpr Count  QUADS_PER_BATCH = 25000;
    static constexpr Count  VERTICES_PER_BATCH = QUADS_PER_BATCH * 4;
    static constexpr Count  INDICES_PER_BATCH = QUADS_PER_BATCH * 6;

    bool  sceneStarted = false;
    Count sceneVertexCount = 0;
    Count sceneIndexCount = 0;
    Count sceneBatchCount = 0;
    Count batchVertexCount = 0;
    Count batchIndexCount = 0;
    Count batchTextureCount = 1;
    Count quadVertexCount = 0;
    Count quadIndexCount = 0;

    Matrix4f cameraProduct = Matrix4f::IDENTITY;

    Shared<Texture> blankTexture = nullptr;
    Shared<Shader> quadShader = nullptr;
    Shared<FrameBuffer> framebuffer = nullptr;
    Shared<VertexArray> quadVertexArray = nullptr;
    Shared<VertexBuffer> quadVertexBuffer = nullptr;

    Vector4f quadVertexPositions[4];
    Vector2f quadTexCoords[4];

    Collection<QuadVertex2D> quadVertices;
    Collection<Shared<Texture>> textures;
  };

  struct RenderSpecification2D
  {
    Vector4f color = Color::WHITE;
    Shared<Texture> texture = nullptr;
    I32 entityId = -1;
  };

  class Renderer
  {
  public:
    Renderer ();
    ~Renderer ();

  public:
    static Unique<Renderer> make ();

  public:
    void useFrameBuffer2D (const Shared<FrameBuffer>& framebuffer);
    void useQuadShader2D (const Shared<Shader>& shader);

  public:
    void beginScene2D (const Matrix4f& projection, const Matrix4f& view);
    void beginScene2D (const Matrix4f& cameraProduct);
    void endScene2D ();
    void flushScene2D (bool early);

  public:
    void submitQuad2D (const Matrix4f& transform, const RenderSpecification2D& spec = {});
    void submitQuad2D (const Vector3f& position, const Vector2f& size, const F32 rotation,
      const RenderSpecification2D& spec = {});

  private:
    void submitQuadVertex2D (const QuadVertex2D& vertex);
    Index slotTexture2D (const Shared<Texture>& texture);

  public:
    inline Count getVertexCount2D () const { return m_renderData2D.sceneVertexCount; }
    inline Count getIndexCount2D () const { return m_renderData2D.sceneIndexCount; }
    inline Count getBatchCount2D () const { return m_renderData2D.sceneBatchCount; }

  private:
    RenderData2D m_renderData2D;

  };

}

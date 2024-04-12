/** @file DG/Graphics/Renderer.cpp */

#include <DG/Math/Transforms.hpp>
#include <DG/Graphics/RenderCommand.hpp>
#include <DG/Graphics/Renderer.hpp>

namespace dg
{

  Renderer::Renderer ()
  {
    RenderCommand::initialize();
    RenderData2D& rd = m_renderData2D;
    
    // Blank White Texture
    U32 blankTextureData = 0xFFFFFFFF;
    rd.blankTexture = Texture::make();
    rd.blankTexture->upload(&blankTextureData, sizeof(U32));

    // Textures Container
    rd.textures.resize(TEXTURE_SLOT_COUNT, nullptr);
    rd.textures[0] = rd.blankTexture;

    // Index Buffer
    Collection<U32> indices(RenderData2D::INDICES_PER_BATCH + 30);
    for (Index i = 0, o = 0; i < indices.size(); i += 6, o += 4) {
      indices[i + 0] = o + 0;
      indices[i + 1] = o + 1;
      indices[i + 2] = o + 2;
      indices[i + 3] = o + 2;
      indices[i + 4] = o + 3;
      indices[i + 5] = o + 0;   
    }
    Shared<IndexBuffer> ibo = IndexBuffer::make(indices);

    // Quad Vertices
    rd.quadVertexArray = VertexArray::make();
    rd.quadVertices.resize(RenderData2D::VERTICES_PER_BATCH + 20);
    rd.quadVertexBuffer = VertexBuffer::allocateFrom<QuadVertex2D>(rd.quadVertices.size());
    rd.quadVertexBuffer->setLayout({
      { "in_Position",  VertexAttributeType::Float3 },
      { "in_TexCoords", VertexAttributeType::Float2 },
      { "in_Color",     VertexAttributeType::Float4 },
      { "in_TexIndex",  VertexAttributeType::Float  },
      { "in_EntityId",  VertexAttributeType::Float  }
    });
    rd.quadVertexArray->addVertexBuffer(rd.quadVertexBuffer);
    rd.quadVertexArray->setIndexBuffer(ibo);
    rd.quadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
    rd.quadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
    rd.quadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
    rd.quadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
    rd.quadTexCoords[0] = { 0.0f, 0.0f };
    rd.quadTexCoords[1] = { 1.0f, 0.0f };
    rd.quadTexCoords[2] = { 1.0f, 1.0f };
    rd.quadTexCoords[3] = { 0.0f, 1.0f };
    
  }

  Renderer::~Renderer ()
  {
    RenderCommand::shutdown();
    RenderData2D& rd = m_renderData2D;
    
    rd.quadVertexArray.reset();
    rd.quadVertexBuffer.reset();
    rd.blankTexture.reset();
    rd.quadShader.reset();
  }

  Unique<Renderer> Renderer::make ()
  {
    return std::make_unique<Renderer>();
  }

  void Renderer::useFrameBuffer2D (const Shared<FrameBuffer>& framebuffer)
  {
    if (m_renderData2D.sceneStarted == true) {
      flushScene2D(true);
    }

    if (m_renderData2D.framebuffer != nullptr) {
      m_renderData2D.framebuffer->unbind();
    }

    m_renderData2D.framebuffer = framebuffer;
    if (m_renderData2D.framebuffer != nullptr) {
      m_renderData2D.framebuffer->bind();
    }
  }

  void Renderer::useQuadShader2D (const Shared<Shader>& shader)
  {
    if (shader == nullptr || shader->isValid() == false) {
      DG_ENGINE_THROW(std::invalid_argument,
        "Attempt to use null or invalid shader for rendering quads!");
    }

    if (m_renderData2D.sceneStarted == true) {
      flushScene2D(true);
    }

    if (m_renderData2D.quadShader != nullptr) {
      m_renderData2D.quadShader->unbind();
    }

    m_renderData2D.quadShader = shader;
    for (Index i = 0; i < TEXTURE_SLOT_COUNT; ++i) {
      m_renderData2D.quadShader->setInteger("uni_TexSlots[" + std::to_string(i) + "]", i);
    }

    if (m_renderData2D.sceneStarted == true) {
      m_renderData2D.quadShader->setMatrix4f("uni_CameraProduct", m_renderData2D.cameraProduct);
    }
  }

  void Renderer::beginScene2D (const Matrix4f& projection, const Matrix4f& view)
  {
    beginScene2D(projection * view.getInverse());
  }

  void Renderer::beginScene2D (const Matrix4f& cameraProduct)
  {
    if (m_renderData2D.sceneStarted == true) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to begin 2D scene when one is already started!");
    }

    if (
      m_renderData2D.quadShader == nullptr
    ) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to begin 2D scene with insufficient shaders provided!");
    }

    m_renderData2D.cameraProduct = cameraProduct;
    m_renderData2D.quadShader->setMatrix4f("uni_CameraProduct", m_renderData2D.cameraProduct);
    m_renderData2D.quadVertexCount = 0;
    m_renderData2D.batchVertexCount = 0;
    m_renderData2D.sceneVertexCount = 0;
    m_renderData2D.quadIndexCount = 0;
    m_renderData2D.batchIndexCount = 0;
    m_renderData2D.sceneIndexCount = 0;
    m_renderData2D.batchTextureCount = 1;
    m_renderData2D.sceneBatchCount = 0;
    m_renderData2D.sceneStarted = true;
  }

  void Renderer::endScene2D ()
  {
    if (m_renderData2D.sceneStarted == false) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to end 2D scene when no such scene was started!");
    }

    flushScene2D(false);
    m_renderData2D.sceneStarted = false;
  }

  void Renderer::flushScene2D (bool early)
  {
    if (m_renderData2D.sceneStarted == false) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to flush 2D scene when no such scene was started!");
    }

    if (m_renderData2D.quadVertexCount > 0) {
      m_renderData2D.quadVertexBuffer->uploadFrom<QuadVertex2D>(
        m_renderData2D.quadVertices, m_renderData2D.quadVertexCount
      );
      
      for (Index i = 0; i < m_renderData2D.batchTextureCount; ++i) {
        m_renderData2D.textures[i]->bind(i);
      }

      m_renderData2D.quadShader->bind();
      RenderCommand::drawIndexed(m_renderData2D.quadVertexArray, m_renderData2D.quadIndexCount);
    }

    if (early == true) {
      m_renderData2D.quadVertexCount = 0;
      m_renderData2D.batchVertexCount = 0;
      m_renderData2D.quadIndexCount = 0;
      m_renderData2D.batchIndexCount = 0;
      m_renderData2D.batchTextureCount = 1;
    }

    m_renderData2D.sceneBatchCount++;
  }

  void Renderer::submitQuad2D (const Matrix4f& transform, const RenderSpecification2D& spec)
  {
    RenderData2D& rd = m_renderData2D;
    if (rd.sceneStarted == false) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to submit a 2D quad to a scene when no such scene is started!");
    }

    F32 texIndex = static_cast<F32>(slotTexture2D(spec.texture));
    F32 entityId = static_cast<F32>(spec.entityId);
    Vector3f positions[4] = {
      (transform * rd.quadVertexPositions[0]).getVector3(),
      (transform * rd.quadVertexPositions[1]).getVector3(),
      (transform * rd.quadVertexPositions[2]).getVector3(),
      (transform * rd.quadVertexPositions[3]).getVector3()
    };

    submitQuadVertex2D({ positions[0], rd.quadTexCoords[0], spec.color, texIndex, entityId });
    submitQuadVertex2D({ positions[1], rd.quadTexCoords[1], spec.color, texIndex, entityId });
    submitQuadVertex2D({ positions[2], rd.quadTexCoords[2], spec.color, texIndex, entityId });
    submitQuadVertex2D({ positions[3], rd.quadTexCoords[3], spec.color, texIndex, entityId });

    rd.quadIndexCount += 6;
    rd.batchIndexCount += 6;
    rd.sceneIndexCount += 6;

    if (
      rd.quadVertexCount    >= RenderData2D::VERTICES_PER_BATCH ||
      rd.quadIndexCount     >= RenderData2D::INDICES_PER_BATCH ||
      rd.batchTextureCount  >= TEXTURE_SLOT_COUNT
    ) {
      flushScene2D(true);
    }
  }

  void Renderer::submitQuad2D (const Vector3f& position, const Vector2f& size, const F32 rotation,
    const RenderSpecification2D& spec)
  {
    Matrix4f transform = translate(Matrix4f::IDENTITY, position);
    transform = rotate(transform, radians(rotation), { 0.0f, 0.0f, 1.0f });
    transform = scale(transform, { size.x, size.y, 1.0f });

    submitQuad2D(transform, spec);
  }

  void Renderer::submitQuadVertex2D (const QuadVertex2D& vertex)
  {
    m_renderData2D.quadVertices[m_renderData2D.quadVertexCount++] = vertex;
    m_renderData2D.batchVertexCount++;
    m_renderData2D.sceneVertexCount++;
  }

  Index Renderer::slotTexture2D (const Shared<Texture>& texture)
  {
    if (texture == nullptr) { return 0; }

    for (Index i = 1; i < m_renderData2D.batchTextureCount; ++i) {
      if (m_renderData2D.textures[i] == nullptr) {
        m_renderData2D.textures[i] = texture;
        return i;
      }

      if (m_renderData2D.textures[i].get() == texture.get()) {
        return i;
      }
    }

    m_renderData2D.textures[m_renderData2D.batchTextureCount] = texture;
    return m_renderData2D.batchTextureCount++;
  }

}

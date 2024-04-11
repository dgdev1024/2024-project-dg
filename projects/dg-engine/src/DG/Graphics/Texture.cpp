/** @file DG/Graphics/Texture.cpp */

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include <stb_image.h>

#include <DG/Graphics/Texture.hpp>

namespace dg
{

  Texture::Texture (const TextureSpecification& spec) :
    m_size { spec.size },
    m_colorChannelCount { spec.colorChannelCount },
    m_wrap { spec.wrap },
    m_magnify { spec.magnify },
    m_minify { spec.minify }
  {

  }

  bool Texture::loadFromFile (const Path& path)
  {
    if (path.empty()) {
      DG_ENGINE_ERROR("No image filename specified to load into the texture.");
      return false;
    }

    if (fs::exists(path) == false) {
      DG_ENGINE_ERROR("Image filename '{}' not found.", path);
      return false;
    }

    stbi_set_flip_vertically_on_load(true);
    stbi_uc* data = stbi_load(path.c_str(), &m_size.x, &m_size.y, &m_colorChannelCount, 0);
    if (data == nullptr) {
      DG_ENGINE_ERROR("Could not load image file '{}' - {}", path,
        stbi_failure_reason());
      return false;
    }

    m_valid = onImageDataLoaded(data);
    if (m_valid == false) {
      DG_ENGINE_ERROR("Could not load image file '{}' - Error parsing image data.", path);
    }

    stbi_image_free(data);
    return m_valid;
  }


}

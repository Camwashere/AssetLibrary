#pragma once
#include <cstdint>
#include <candy/asset/CompressionMode.hpp>
#include <filesystem>
namespace Candy::Asset
{
  enum class TextureFormat : uint32_t
  {
    Unknown = 0,
    R8,
    RG8,
    RGB8,
    RGBA8,
    R16F,
    RG16F,
    RGB16F,
    RGBA16F,
  };
  
  struct TextureInfo
  {
    uint64_t textureSize;
    TextureFormat format;
    CompressionMode compressionMode;
    uint32_t pixelSize[3];
    std::filesystem::path originalFile;
    uint32_t mipLevels;
  };
}
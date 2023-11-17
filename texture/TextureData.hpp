#pragma once
#include <cstdint>
#include "../asset/CompressionMode.hpp"
#include <filesystem>
namespace Asset
{
  enum class TextureFormat : uint32_t
  {
    Unknown = 0,
    R8,
    R16,
    R32,
    R8Int,
    R16Int,
    R32Int,
    RGB8,
    RGBA8,
    RGBA32F,
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
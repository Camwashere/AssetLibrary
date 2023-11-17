#pragma once
#include "TextureData.hpp"
#include "../asset/AssetFile.hpp"
namespace Asset
{
  class TexturePacker
  {
  public:
    static TextureInfo ReadTextureInfo(AssetFile& file);
    static void UnpackTexture(const TextureInfo& info, const char* sourceBuffer, size_t sourceSize, char* destinationBuffer);
    static AssetFile PackTexture(const TextureInfo& info, void* pixelData);
    
  };
}
#pragma once
#include "TextureData.hpp"
#include <candy/asset/AssetFile.hpp>
namespace Candy::Asset
{
  class TexturePacker
  {
  public:
    static TextureInfo ReadTextureInfo(AssetFile& file);
    static void UnpackTexture(const TextureInfo& info, const char* sourceBuffer, size_t sourceSize, char* destinationBuffer);
    static AssetFile PackTexture(const TextureInfo& info, void* pixelData);
    
  };
}
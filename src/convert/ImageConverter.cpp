#include "../../include/candy/asset/convert/ImageConverter.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <candy/asset/texture/TexturePacker.hpp>
#include <candy/asset/AssetLoader.hpp>
#include <iostream>
namespace Candy::Asset
{
  bool ImageConverter::Convert(const std::filesystem::path& inputPath, const std::filesystem::path& outputPath)
  {
    int texWidth, texHeight, texChannels;
    bool isHDR = (inputPath.extension() == ".hdr");
    void* pixels;
    size_t dataSize;
    TextureFormat format;
    if (isHDR)
    {
      pixels = stbi_loadf(inputPath.string().c_str(), &texWidth, &texHeight, &texChannels, 0);
      dataSize = sizeof(float);
      
      switch(texChannels)
      {
        case 1:
          format = TextureFormat::R16F;
          break;
        case 2:
          format = TextureFormat::RG16F;
          break;
        case 3:
          format = TextureFormat::RGB16F;
          break;
        case 4:
          format = TextureFormat::RGBA16F;
          break;
        default:
          format = TextureFormat::Unknown;
      }
    }
    else
    {
      pixels = stbi_load(inputPath.string().c_str(), &texWidth, &texHeight, &texChannels, 0);
      dataSize = sizeof(stbi_uc);
      switch(texChannels)
      {
        case 1:
          format = TextureFormat::R8;
          break;
        case 2:
          format = TextureFormat::RG8;
          break;
        case 3:
          format = TextureFormat::RGB8;
          break;
        case 4:
          format = TextureFormat::RGBA8;
          break;
        default:
          format = TextureFormat::Unknown;
      }
    }
    
    if (!pixels)
    {
      std::cerr << "Failed to load image: " << inputPath.string() << std::endl;
      return false;
    }
    if (format == TextureFormat::Unknown)
    {
      std::cerr << "Unsupported image format: " << inputPath.string() << std::endl;
      stbi_image_free(pixels);
      return false;
    }
    size_t texture_size = texWidth * texHeight * texChannels * dataSize;
    
    TextureInfo texInfo;
    texInfo.textureSize = texture_size;
    texInfo.pixelSize[0] = texWidth;
    texInfo.pixelSize[1] = texHeight;
    texInfo.format = format;
    texInfo.originalFile = inputPath.string();
    AssetFile newImage = (dataSize == sizeof(float))
                         ? TexturePacker::PackTexture(texInfo, (float*)pixels)
                         : TexturePacker::PackTexture(texInfo, (stbi_uc*)pixels);
    
    
    stbi_image_free(pixels);
    
    AssetLoader::SaveBinaryFile(outputPath.string().c_str(), newImage);
    
    return true;
  }
}
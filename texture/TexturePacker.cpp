#include "TexturePacker.hpp"
#include <nlohmann/json.hpp>
#include <lz4.h>
namespace Asset
{
  TextureInfo TexturePacker::ReadTextureInfo(AssetFile& file)
  {
    // Parse the JSON string in the file
    nlohmann::json texture_metadata = nlohmann::json::parse(file.json);
    
    // Initialize a new TextureInfo object
    TextureInfo info;
    
    // Load texture metadata from the JSON object
    info.format = static_cast<TextureFormat>(texture_metadata["format"].get<uint32_t>());
    info.pixelSize[0] = texture_metadata["width"];
    info.pixelSize[1] = texture_metadata["height"];
    info.pixelSize[2] = texture_metadata["depth"];
    info.textureSize = texture_metadata["buffer_size"];
    info.mipLevels = texture_metadata["mip_levels"];
    info.originalFile = std::filesystem::path(texture_metadata["original_file"].get<std::string>());
    info.compressionMode = static_cast<CompressionMode>(texture_metadata["compression"].get<uint8_t>());
    
    return info;
  }
  void TexturePacker::UnpackTexture(const TextureInfo& info, const char* sourceBuffer, size_t sourceSize, char* destinationBuffer)
  {
    if (info.compressionMode == CompressionMode::LZ4)
    {
      // The decompress function returns the number of bytes decompressed if successful, else negative.
      LZ4_decompress_safe(sourceBuffer, destinationBuffer, sourceSize, LZ4_compressBound(static_cast<int>(info.textureSize)));
    }
    else
    {
      memcpy(destination, sourceBuffer, sourceSize);
    }
    
    
  }
  AssetFile TexturePacker::PackTexture(const TextureInfo& info, void* pixelData)
  {
    nlohmann::json texture_metadata;
    texture_metadata["format"] = static_cast<uint32_t>(info.format);
    texture_metadata["width"] = info.pixelSize[0];
    texture_metadata["height"] = info.pixelSize[1];
    texture_metadata["depth"] = info.pixelSize[2];
    texture_metadata["buffer_size"] = info.textureSize;
    texture_metadata["mip_levels"] = info.mipLevels;
    texture_metadata["original_file"] = info.originalFile.string();
    
    
    //core file header
    AssetFile file;
    file.type = AssetType::Texture;
    file.version = 1;
    
    //compress buffer into blob
    int compressStaging = LZ4_compressBound(static_cast<int>(info.textureSize));
    
    file.binaryBlob.resize(compressStaging);
    
    int compressedSize = LZ4_compress_default((const char*)pixelData, file.binaryBlob.data(), static_cast<int>(info.textureSize), compressStaging);
    
    file.binaryBlob.resize(compressedSize);
    
    texture_metadata["compression"] = static_cast<uint8_t>(info.compressionMode);
    
    std::string strDump = texture_metadata.dump();
    file.json = strDump;
    
    
    return file;
  }
}
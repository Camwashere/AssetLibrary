#include <candy/asset/AssetLoader.hpp>
#include <fstream>
namespace Candy::Asset
{
  bool AssetLoader::SaveBinaryFile(const std::filesystem::path& path, const AssetFile& file)
  {
    std::ofstream outfile;
    outfile.open(path, std::ios::binary | std::ios::out);
    
    if (!outfile.is_open()) {
      // File could not be opened for writing.
      return false;
    }
    
    uint32_t assetType = static_cast<uint32_t>(file.type);
    outfile.write(reinterpret_cast<const char*>(&assetType), sizeof(uint32_t));
    
    uint32_t version = file.version;
    outfile.write(reinterpret_cast<const char*>(&version), sizeof(uint32_t));
    
    uint32_t length = file.json.size();
    outfile.write(reinterpret_cast<const char*>(&length), sizeof(uint32_t));
    
    uint32_t bloblength = file.binaryBlob.size();
    outfile.write(reinterpret_cast<const char*>(&bloblength), sizeof(uint32_t));
    
    outfile.write(file.json.data(), length);
    outfile.write(file.binaryBlob.data(), bloblength);
    
    outfile.close();
    
    return ! outfile.fail();
    
  }
  bool AssetLoader::LoadBinaryFile(const std::filesystem::path& path, AssetFile& outputFile)
  {
    std::ifstream infile;
    infile.open(path, std::ios::binary);
    
    if (!infile.is_open()) return false;
    
    //move file cursor to beginning
    infile.seekg(0);
    
    
    uint32_t assetType = static_cast<uint32_t>(AssetType::Unknown);
    infile.read(reinterpret_cast<char*>(&assetType), sizeof(uint32_t));
    outputFile.type = static_cast<AssetType>(assetType);
    if (outputFile.type == AssetType::Unknown)
    {
      infile.close();
      return false;
    }
    
    uint32_t jsonlen = 0;
    infile.read((char*)&jsonlen, sizeof(uint32_t));
    
    uint32_t bloblen = 0;
    infile.read((char*)&bloblen, sizeof(uint32_t));
    
    outputFile.json.resize(jsonlen);
    infile.read(outputFile.json.data(), jsonlen);
    
    outputFile.binaryBlob.resize(bloblen);
    infile.read(outputFile.binaryBlob.data(), bloblen);
    
    infile.close();
    
    // Check for errors at the end.
    return ! infile.fail();
  }
}
#pragma once
#include <filesystem>
#include <unordered_map>
#include "../asset/AssetType.hpp"
namespace Asset
{
  
  class AssetConverter
  {
  private:
    static std::unordered_map<std::string, std::string> externalToInternalExtensionMap;
    static std::unordered_map<std::string, AssetType> internalExtensionToAssetTypeMap;
    
    static bool NeedsUpdate(const std::filesystem::path& originalAssetFile, const std::filesystem::path& internalAssetFile);
    static void Update(const std::filesystem::path& originalAssetFile, const std::filesystem::path& internalAssetFile, AssetType assetType);
    
  public:
    static bool IsInternalAssetFile(const std::filesystem::path& filepath);
    static bool IsExternalAssetFile(const std::filesystem::path& filepath);
    static AssetType GetAssetType(const std::filesystem::path& filepath);
    static std::filesystem::path GetInternalAssetFilePath(const std::filesystem::path& filepath);
    
    
    static void Process(const std::filesystem::path& originalAssetFile);
  
  };
}
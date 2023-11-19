#include <candy/asset/convert/AssetConverter.hpp>
#include <assert.h>
#include <candy/asset/convert/ImageConverter.hpp>
namespace Candy::Asset
{
  std::unordered_map<std::string, std::string> AssetConverter::externalToInternalExtensionMap{
  {".png", ".texture"},
  {".jpg", ".texture"},
  {".jpeg", ".texture"},
  {".tga", ".texture"},
  {".bmp", ".texture"},
  {".hdr", ".texture"},
  {".pic", ".texture"},
  {".psd", ".texture"}
  };
  
  std::unordered_map<std::string, AssetType> AssetConverter::internalExtensionToAssetTypeMap
  {
    {".texture", AssetType::Texture},
    {".font", AssetType::Font},
    {".mesh", AssetType::Mesh},
    {".shader", AssetType::Shader},
    {".animation", AssetType::Animation},
    {".script", AssetType::Script},
    {".scene", AssetType::Scene},
  };
  
  bool AssetConverter::IsInternalAssetFile(const std::filesystem::path& filepath)
  {
    return internalExtensionToAssetTypeMap.find(filepath.extension().string())!=internalExtensionToAssetTypeMap.end();
  }
  bool AssetConverter::IsExternalAssetFile(const std::filesystem::path& filepath)
  {
    return externalToInternalExtensionMap.find(filepath.extension().string())!=externalToInternalExtensionMap.end();
  }
  AssetType AssetConverter::GetAssetType(const std::filesystem::path& filepath)
  {
    if (IsExternalAssetFile(filepath))
    {
      return internalExtensionToAssetTypeMap[externalToInternalExtensionMap[filepath.extension().string()]];
    }
    else if (IsInternalAssetFile(filepath))
    {
      return internalExtensionToAssetTypeMap[filepath.extension().string()];
    }
    else
    {
      return AssetType::Unknown;
    }
  }
  std::filesystem::path AssetConverter::GetInternalAssetFilePath(const std::filesystem::path& filepath)
  {
    if (IsExternalAssetFile(filepath))
    {
      std::filesystem::path newPath = filepath;
      return newPath.replace_extension(externalToInternalExtensionMap[filepath.extension().string()]);
    }
    else if (IsInternalAssetFile(filepath))
    {
      return filepath;
    }
    else
    {
      return {};
    }
  }
  void AssetConverter::Process(const std::filesystem::path& originalAssetFile)
  {
    if (IsExternalAssetFile(originalAssetFile))
    {
      AssetType assetType = GetAssetType(originalAssetFile);
      std::filesystem::path internalAssetFile = GetInternalAssetFilePath(originalAssetFile);
      assert(assetType == GetAssetType(internalAssetFile));
      if (NeedsUpdate(originalAssetFile, internalAssetFile))
      {
        Update(originalAssetFile, internalAssetFile, assetType);
      }
    }
  
  
  
  }
  
  void AssetConverter::Update(const std::filesystem::path& originalAssetFile, const std::filesystem::path& internalAssetFile, AssetType assetType)
  {
    assert(GetAssetType(originalAssetFile) == assetType && GetAssetType(internalAssetFile) == assetType);
    switch (assetType)
    {
      case AssetType::Texture:
      {
        ImageConverter::Convert(originalAssetFile, internalAssetFile);
        break;
      }
      case AssetType::Shader:
      {
      
      }
      default:
        break;
    }
  
  }
  
  
  
  bool AssetConverter::NeedsUpdate(const std::filesystem::path& originalAssetFile, const std::filesystem::path& internalAssetFile)
  {
    
    assert(std::filesystem::exists(originalAssetFile));
    
    if (!std::filesystem::exists(internalAssetFile))
    {
      return true;
    }
    
    // Get the last modification time for both files
    auto originalTime = std::filesystem::last_write_time(originalAssetFile);
    auto internalTime = std::filesystem::last_write_time(internalAssetFile);
    
    // If originalAssetFile has been modified more recently than internalAssetFile
    if (originalTime > internalTime)
    {
      return true;
    }
    
    return false;
  }
}
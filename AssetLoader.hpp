#pragma once
#include "asset/AssetFile.hpp"
#include <filesystem>

namespace Asset
{
  class AssetLoader
  {
  public:
    static bool SaveBinaryFile(const std::filesystem::path& path, const AssetFile& file);
    static bool LoadBinaryFile(const std::filesystem::path& path, AssetFile& assetFile);
  };
}
#pragma once
#include "AssetType.hpp"
#include <vector>
#include <string>
namespace Asset
{
  struct AssetFile
  {
    AssetType type;
    int version;
    std::string json;
    std::vector<char> binaryBlob;
  };
  
  
}
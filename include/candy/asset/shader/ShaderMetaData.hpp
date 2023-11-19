#pragma once
#include <string>
#include "candy/asset/shader/profile/ShaderProfileData.hpp"
#include "candy/asset/shader/processing/ShaderCompilationSettings.hpp"
namespace Candy::Asset
{
  struct ShaderMetaData
  {
    ShaderProfileData profile;
    ShaderCompilationSettings compilationSettings;
    
  };
}
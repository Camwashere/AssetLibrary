#pragma once
#include "ShaderCompilationSettings.hpp"
#include <unordered_map>
#include <candy/asset/shader/ShaderData.hpp>
namespace Candy::Asset
{
  struct ShaderCompiler
  {
    ShaderCompilationSettings settings;
    
  public:
    [[nodiscard]] std::unordered_map<ShaderData::Stage, std::vector<uint32_t>> Compile(const std::string& shaderName, const std::unordered_map<ShaderData::Stage, std::string>& sources)const;
  
  };
}
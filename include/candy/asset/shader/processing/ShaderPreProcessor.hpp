#pragma once
#include <unordered_map>
#include <string>
#include <filesystem>
#include <candy/asset/shader/ShaderData.hpp>
namespace Candy::Asset
{
  class ShaderPreProcessor
  {
  private:
    std::unordered_map<ShaderData::Stage, std::string> sources{};
    
  public:
    explicit ShaderPreProcessor(const std::filesystem::path& sourceFilePath);
    explicit ShaderPreProcessor(const std::vector<std::filesystem::path>& sourcePaths);
  
  private:
    void InitializeSources(const std::string& sourceCode);
    
  public:
    std::vector<ShaderData::Stage> GetStages()const;
    const std::string& GetSource(ShaderData::Stage stage);
    const std::unordered_map<ShaderData::Stage, std::string>& GetSources();
  
  };
}
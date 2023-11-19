#include <candy/asset/shader/processing/ShaderPreProcessor.hpp>
#include <CandyPch.hpp>
namespace Candy::Asset
{
  
  std::string ReadFile(const std::filesystem::path& path)
  {
    CANDY_PROFILE_FUNCTION();
    std::string result;
    std::ifstream in(path, std::ios::in | std::ios::binary); // ifstream closes itself due to RAII
    if (in)
    {
      in.seekg(0, std::ios::end);
      auto size = in.tellg();
      if (size != -1)
      {
        result.resize(size);
        in.seekg(0, std::ios::beg);
        in.read(&result[0], size);
      }
      else
      {
        CANDY_CORE_ERROR("Could not read from file: '{}'", path.string());
        
      }
    }
    else
    {
      CANDY_CORE_ERROR("Could not open file '{}'", path.string());
    }
    
    return result;
  }
  
  
  
  std::string ConsolidateFiles(const std::vector<std::filesystem::path>& paths)
  {
    std::string result;
    for (const auto& path : paths)
    {
      result += '\n' + ReadFile(path);
    }
    return result;
  }
  
  
  
  ShaderPreProcessor::ShaderPreProcessor(const std::filesystem::path& sourceFilePath)
  {
    std::string sourceCode = ReadFile(sourceFilePath);
    InitializeSources(sourceCode);
  }
  ShaderPreProcessor::ShaderPreProcessor(const std::vector<std::filesystem::path>& sourcePaths)
  {
    std::string sourceCode = ConsolidateFiles(sourcePaths);
    InitializeSources(sourceCode);
  }
  
  
  
  void ShaderPreProcessor::InitializeSources(const std::string& source)
  {
    const char* typeToken = "#stage";
    size_t typeTokenLength = strlen(typeToken);
    size_t pos = source.find(typeToken, 0); //Start of shader type declaration line
    while (pos != std::string::npos)
    {
      size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
      CANDY_CORE_ASSERT(eol != std::string::npos, "Syntax error");
      
      
      size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
      std::string type = source.substr(begin, eol - begin);
      CANDY_CORE_ASSERT(ShaderData::StringToStage(type) != ShaderData::Stage::None, "Invalid shader type specified");
      
      
      size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
      CANDY_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
      pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line
      
      sources[ShaderData::StringToStage(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
    }
  }
  
  std::vector<ShaderData::Stage> ShaderPreProcessor::GetStages()const
  {
    std::vector<ShaderData::Stage> stages{};
    for(const auto& [stage, source] : sources)
    {
      stages.push_back(stage);
    }
    return stages;
  }
  const std::string& ShaderPreProcessor::GetSource(ShaderData::Stage stage)
  {
    return sources.at(stage);
  }
  const std::unordered_map<ShaderData::Stage, std::string>& ShaderPreProcessor::GetSources()
  {
    return sources;
  }
}
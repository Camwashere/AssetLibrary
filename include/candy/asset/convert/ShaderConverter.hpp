#pragma once
#include <filesystem>
namespace Candy::Asset
{
  class ShaderConverter
  {
  public:
    static bool Convert(const std::filesystem::path& inputSourceFile, const std::filesystem::path& outputFile);
  };
}
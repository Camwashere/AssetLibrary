#pragma once
#include <filesystem>
namespace Candy::Asset
{
  class ImageConverter
  {
  public:
    static bool Convert(const std::filesystem::path& inputPath, const std::filesystem::path& outputPath);
  };
}
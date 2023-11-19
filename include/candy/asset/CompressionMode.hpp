#pragma once
#include <cstdint>
namespace Candy::Asset
{
  enum class CompressionMode : uint8_t
  {
    None=0,
    LZ4,
  };
}
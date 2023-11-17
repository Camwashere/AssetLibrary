#pragma once
#include <cstdint>
namespace Asset
{
  enum class CompressionMode : uint8_t
  {
    None=0,
    LZ4,
  };
}
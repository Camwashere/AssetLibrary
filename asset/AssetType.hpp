#pragma once
#include <cstdint>
namespace Asset
{
  enum class AssetType : uint32_t
  {
    Unknown=0,
    Texture,
    Font,
    Mesh,
    Material,
    Shader,
    Animation,
    Script,
    Scene,
  };
}
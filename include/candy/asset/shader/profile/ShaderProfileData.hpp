#pragma once
#include "ShaderProfileTypes.hpp"
#include <optional>
#include <vector>
#include <array>
#include "candy/math/Color.hpp"
namespace Candy::Asset
{
  struct ShaderConfigurationData
  {
    std::optional<uint32_t> customRenderPassIndex;
    bool discardRasterizer=false;
    PolygonRenderMode renderMode=PolygonRenderMode::None;
    CullMode cullMode = CullMode::None;
  };
  
  struct ShaderProfileData
  {
    uint32_t renderPassIndex=0;
    PolygonRenderMode renderMode=PolygonRenderMode::Shaded;
    TopologyType topologyType=TopologyType::Triangle;
    bool primitiveRestart=false;
    bool discardRasterizer=false;
    ShaderType shaderType=ShaderType::Graphics;
    CullMode cullMode = CullMode::Back;
    DepthBiasSettings depthBias{};
    DepthBoundsSettings depthBounds{};
    Color blendConstants = {0, 0, 0, 0};
    std::vector<BlendAttachmentConfig> blendAttachments;
    DepthStencilSettings depthStencil{};
    std::vector<DynamicStateType> dynamicStates;
  };
}
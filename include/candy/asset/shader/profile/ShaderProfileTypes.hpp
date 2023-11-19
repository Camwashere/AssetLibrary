#pragma once
#include <cstdint>
#include "ShaderEnums.hpp"
#include <string>
#include "candy/math/Color.hpp"
namespace Candy::Asset
{
  
  
  struct DepthBiasSettings
  {
    bool enable=false;
    float clamp=0.0f;
    float constantFactor=0.0f;
    float slopeFactor=0.0f;
  };
  
  struct DepthBoundsSettings
  {
    bool enable=false;
    float min=0.0f;
    float max=1.0f;
  };
  
  struct StencilOpState
  {
    uint32_t compareMask;
    uint32_t reference;
    uint32_t writeMask;
    CompareOp compareOp;
    StencilOp failOp;
    StencilOp passOp;
    StencilOp depthFailOp;
  };
  
  struct DepthStencilSettings
  {
    bool depthBufferReading = true;
    bool depthBufferWriting = true;
    CompareOp depthCompareOp = CompareOp::Less;
    
    bool stencilTest=false;
    StencilOpState front{};
    StencilOpState back{};
  };
  
  struct BlendAttachmentConfig
  {
    ColorChannels enabledChannels = ColorChannels::NONE;
    bool enableBlending=false;
    BlendFactor srcColorBlendFactor = BlendFactor::One;
    BlendFactor dstColorBlendFactor = BlendFactor::Zero;
    BlendOp colorBlendOp = BlendOp::Add;
    BlendFactor srcAlphaBlendFactor = BlendFactor::SrcAlpha;
    BlendFactor dstAlphaBlendFactor = BlendFactor::OneMinusSrcAlpha;
    BlendOp alphaBlendOp = BlendOp::Add;
  };
  
  
}
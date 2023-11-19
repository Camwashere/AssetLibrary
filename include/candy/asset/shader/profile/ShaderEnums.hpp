#pragma once

namespace Candy::Asset
{
  enum class CompareOp
  {
    Never=0,
    Less,
    Equal,
    LessOrEqual,
    Greater,
    NotEqual,
    GreaterOrEqual,
    Always
  };
  
  enum class StencilOp
  {
    Keep=0,
    Zero,
    Replace,
    IncrementAndClamp,
    DecrementAndClamp,
    Invert,
    IncrementAndWrap,
    DecrementAndWrap
  };
  
  
  
  enum class BlendFactor
  {
    Zero=0,
    One,
    SrcColor,
    OneMinusSrcColor,
    DstColor,
    OneMinusDstColor,
    SrcAlpha,
    OneMinusSrcAlpha,
    DstAlpha,
    OneMinusDstAlpha,
    ConstantColor,
    OneMinusConstantColor,
    ConstantAlpha,
    OneMinusConstantAlpha,
    SrcAlphaSaturate,
    Src1Color,
    OneMinusSrc1Color,
    Src1Alpha,
    OneMinusSrc1Alpha
  };
  
  enum class BlendOp
  {
    Add=0,
    Subtract,
    ReverseSubtract,
    Min,
    Max
  };
  
  enum class ShaderType
  {
    None=0,
    Graphics,
    Compute,
    RayTracing,
  };
  enum class TopologyType
  {
    None=0,
    Triangle,
    Line,
    Point,
  };
  
  enum PolygonRenderMode
  {
    None=0,
    Shaded,
    Wireframe,
    Point,
  };
  
  enum class CullMode
  {
    None=0,
    Front,
    Back,
    Both,
  };
  
  enum class WindingOrder
  {
    None=0,
    Clockwise,
    CounterClockwise,
  };
  
  enum class DynamicStateType
  {
    Viewport,
    DepthTestStatic,
    DepthTestDynamic,
    DepthWrite,
    BlendConstants,
    CullMode,
  };
}
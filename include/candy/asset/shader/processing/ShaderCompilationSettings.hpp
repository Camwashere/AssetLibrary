#pragma once
#include "candy/base/Version.hpp"
namespace Candy::Asset
{
  struct ShaderCompilationSettings
  {
    bool autoMapping=false;
    bool preserveBindings=false;
    bool suppressWarnings=false;
    bool warningsAsErrors=false;
    bool invertY=true;
    bool generateDebugInfo=true;
    bool optimize=true;
    bool recompileOnLoad=true;
    int glslVersion=460;
    Version vulkanVersion = Version(1, 3);
  };
}
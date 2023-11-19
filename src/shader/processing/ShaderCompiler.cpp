#include <candy/asset/shader/processing/ShaderCompiler.hpp>
#include <CandyPch.hpp>
#include "shaderc/libshaderc/include/shaderc/shaderc.hpp"
namespace Candy::Asset
{
  
  static shaderc_shader_kind StageToShaderC(ShaderData::Stage stage)
  {
    CANDY_PROFILE_FUNCTION();
    switch (stage)
    {
      
      case ShaderData::Stage::Vertex:   return shaderc_glsl_vertex_shader;
      case ShaderData::Stage::Fragment: return shaderc_glsl_fragment_shader;
      case ShaderData::Stage::Compute: return shaderc_glsl_compute_shader;
      case ShaderData::Stage::Geometry: return shaderc_glsl_geometry_shader;
      case ShaderData::Stage::TessellationControl: return shaderc_glsl_tess_control_shader;
      case ShaderData::Stage::TessellationEvaluation: return shaderc_glsl_tess_evaluation_shader;
      default:
        CANDY_CORE_ASSERT(false, "Unknown shader stage!");
        return (shaderc_shader_kind)0;
    }
  }
  
  static shaderc::CompileOptions GetCompileOptions(const ShaderCompilationSettings& settings)
  {
    shaderc::CompileOptions options;
    options.SetOptimizationLevel(settings.optimize? shaderc_optimization_level_performance : shaderc_optimization_level_zero);
    if (settings.generateDebugInfo)
    {
      options.SetGenerateDebugInfo();
    }
    options.SetPreserveBindings(settings.preserveBindings);
    
    //options.SetForcedVersionProfile(settings.glslVersion, shaderc_profile_core);
    
    options.SetTargetSpirv(shaderc_spirv_version_1_3);
    if (settings.vulkanVersion.GetMajor() == 1)
    {
      switch(settings.vulkanVersion.GetMinor())
      {
        case 0:
          options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_0);
          break;
        case 1:
          options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_1);
          break;
        case 2:
          options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);
          break;
        case 3:
          options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_3);
          break;
        default:
          CANDY_CORE_WARN("Invalid vulkan version in shader compilation settings ({}). Defaulting to 1.0", settings.vulkanVersion);
          options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_0);
          break;
      }
    }
    else
    {
      CANDY_CORE_WARN("Invalid vulkan version in shader compilation settings ({}). Defaulting to 1.0", settings.vulkanVersion);
      options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_0);
    }
    
    
    options.SetAutoBindUniforms(settings.autoMapping);
    options.SetAutoMapLocations(settings.autoMapping);
    options.SetInvertY(settings.invertY);
    //CANDY_CORE_ASSERT(settings.invertY == true, "Settings invert y is still false");
    if (settings.suppressWarnings)
    {
      options.SetSuppressWarnings();
    }
    if (settings.warningsAsErrors)
    {
      options.SetWarningsAsErrors();
    }
    
    return options;
  }
  std::unordered_map<ShaderData::Stage, std::vector<uint32_t>> ShaderCompiler::Compile(const std::string& shaderName, const std::unordered_map<ShaderData::Stage, std::string>& sources)const
  {
    CANDY_PROFILE_FUNCTION();
    shaderc::Compiler compiler;
    shaderc::CompileOptions options = GetCompileOptions(settings);
    
    std::unordered_map<ShaderData::Stage, std::vector<uint32_t>> binaries{};
    for (const auto& [stage, source] : sources)
    {
      shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, StageToShaderC(stage), shaderName.c_str(), options);
      
      if (module.GetCompilationStatus() != shaderc_compilation_status_success)
      {
        CANDY_CORE_ERROR("Shader compilation error '{}' for shader: '{}'. Failed to compile", module.GetErrorMessage(), shaderName);
        return {};
      }
      else
      {
        binaries[stage] = { module.cbegin(), module.cend() };
      }
    
    }
    
    return binaries;
  }
}
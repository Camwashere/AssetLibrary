cmake_minimum_required(VERSION 3.26)
project(AssetLibrary)

set(CMAKE_CXX_STANDARD 23)

find_package(Vulkan REQUIRED)
add_subdirectory(lib/lz4)
add_subdirectory(lib/json)
add_subdirectory(lib/CandyCommon)
add_subdirectory(lib/shaderc)
add_subdirectory(lib/SPIRV-Cross)
set(STB_FILES lib/stb/stb_image.h)
set(ASSET_LIB_FILES include/candy/asset/AssetType.hpp
        include/candy/asset/AssetFile.hpp
        include/candy/asset/texture/TextureData.hpp
        include/candy/asset/CompressionMode.hpp
        include/candy/asset/texture/TexturePacker.hpp
        src/texture/TexturePacker.cpp
        include/candy/asset/AssetLoader.hpp
        src/AssetLoader.cpp
        include/candy/asset/convert/AssetConverter.hpp
        src/convert/AssetConverter.cpp
        include/candy/asset/convert/ImageConverter.hpp
        src/convert/ImageConverter.cpp
        include/candy/asset/convert/ShaderConverter.hpp
        src/convert/ShaderConverter.cpp
        include/candy/asset/shader/profile/ShaderProfileData.hpp
        include/candy/asset/shader/profile/ShaderProfileTypes.hpp
        include/candy/asset/shader/profile/ShaderEnums.hpp
        include/candy/asset/shader/processing/ShaderCompilationSettings.hpp
        include/candy/asset/shader/ShaderMetaData.hpp
        include/candy/asset/shader/processing/ShaderPostProcessor.hpp
        src/shader/processing/ShaderPostProcessor.cpp
        include/candy/asset/shader/processing/ShaderCompiler.hpp
        include/candy/asset/shader/ShaderData.hpp
        src/shader/ShaderData.cpp
        include/candy/asset/shader/processing/ShaderPreProcessor.hpp
        src/shader/processing/ShaderPreProcessor.cpp
        src/shader/processing/ShaderCompiler.cpp
)
add_executable(AssetLibrary main.cpp ${ASSET_LIB_FILES} ${STB_FILES})

target_include_directories(AssetLibrary PRIVATE lib/lz4/lib lib/json/include lib/stb lib)
target_include_directories(AssetLibrary PUBLIC include)
target_link_libraries(AssetLibrary PUBLIC CandyCommon Vulkan::Vulkan)
target_link_libraries(AssetLibrary PRIVATE lz4 nlohmann_json::nlohmann_json shaderc_shared spirv-cross-c)



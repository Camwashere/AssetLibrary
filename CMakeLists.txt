cmake_minimum_required(VERSION 3.26)
project(AssetLibrary)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(lib/lz4)
add_subdirectory(lib/json)

add_executable(AssetLibrary main.cpp
        asset/AssetType.hpp
        asset/AssetFile.hpp
        texture/TextureData.hpp
        asset/CompressionMode.hpp
        texture/TexturePacker.hpp
        texture/TexturePacker.cpp
        AssetLoader.hpp
        asset/AssetLoader.cpp
        convert/AssetConverter.hpp
        convert/AssetConverter.cpp)

target_include_directories(AssetLibrary PRIVATE lib/lz4/lib lib/json/include)
target_link_libraries(AssetLibrary PRIVATE lz4 nlohmann_json::nlohmann_json)



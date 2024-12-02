#pragma once
#include <Geode/Geode.hpp>

namespace ninja {
namespace shaders {

extern bool shaderLoadFailed;
inline const char* swipeShaderKey = "NINJA_SHADER_SWIPE";

void loadShader(const char* vertexPath, const char* fragmentPath, const char* key);
void loadAllShaders();

}
}

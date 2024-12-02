#include "shaders.hpp"

namespace ninja {
namespace shaders {

bool shaderLoadFailed = false;

void loadShader(const char* vertexPath, const char* fragmentPath, const char* key) {
    geode::log::info("Creating shader {}", key);

    auto fileUtils = cocos2d::CCFileUtils::sharedFileUtils();
    auto fullFragmentPath = fileUtils->fullPathForFilename(vertexPath, true);
    auto fullVertexPath = fileUtils->fullPathForFilename(fragmentPath, true);

    auto program = new cocos2d::CCGLProgram;
    if (!program->initWithVertexShaderFilename(fullVertexPath.c_str(), fullFragmentPath.c_str())) {
        geode::log::warn("CCGLProgram init failed!");
        ninja::shaders::shaderLoadFailed = true;
        return;
    }
    program->autorelease();

    program->addAttribute(kCCAttributeNamePosition, cocos2d::kCCVertexAttrib_Position);
    // program->addAttribute(kCCAttributeNameColor, cocos2d::kCCVertexAttrib_Color); // not needed because its not used
    program->addAttribute(kCCAttributeNameTexCoord, cocos2d::kCCVertexAttrib_TexCoords);
    
    program->link();
    program->updateUniforms();
    program->use(); // does this break stuff?

    cocos2d::CCShaderCache::sharedShaderCache()->addProgram(program, key);

    GLenum error = glGetError();
    if (error) {
        geode::log::error("OpenGL error {} (convert it to hex yourself)", error);
    }

    geode::log::info("Created shader!");
}

void loadAllShaders() {
    loadShader("swipeShader.frag"_spr, "ccShader_PositionTexture.vert"_spr, swipeShaderKey);
}

}
}


$on_mod(Loaded) {
    ninja::shaders::loadAllShaders();
}

#include "Log.h"

namespace Vega {

    void SetLogLevel() {
        spdlog::set_level(spdlog::level::level_enum(V_LOG_LEVEL));
    }

    void GLAPIENTRY MessageCallback(GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        const void* userParam
    ) {
        if (type == GL_DEBUG_TYPE_ERROR) {
            spdlog::error(std::format("[GL ERROR]: {}", message));
        }
    }

}


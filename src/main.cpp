#include <glad/glad.hpp>
#include <GLFW/glfw3.h>

#include "utility.hpp"
#include "gl/shader.hpp"
#include "scene.hpp"
#include "scenes/scene1.hpp"

void init_glad() {
    glfwSwapInterval(1);
    if (!gladLoadGLES2Loader((GLADloadproc) glfwGetProcAddress)) {
        terminate("ERROR: Initializing glad");
    } 

    if (!GLAD_GL_ES_VERSION_3_0) {
        terminate("ERROR: Opengl 3.0 not supported");
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);  
    Shader::compileAll();
}

int main() {
    init_glad();
    loadScene<Scene1>();
    return 0;
}



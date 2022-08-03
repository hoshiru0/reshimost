#include "scene.hpp"

#include <gui/window.hpp>
#include <object/camera.hpp>

#include <GLFW/glfw3.h>

double delta_time {};
double current_time {};
uint32_t fps {};

SceneBase* current_scene;

SceneBase::SceneBase() {
    current_scene = this;
}

void SceneBase::run() {    
    float next_second = 1;
    double time_last_frame {};
    while (!glfwWindowShouldClose(window.getGlfwWindowPtr())) {
        delta_time = glfwGetTime()-time_last_frame;
        current_time = glfwGetTime();
        time_last_frame = current_time;

        Shader::forEach([] (Shader* s) {
            s->use();
            s->uniform("u_time", (float) current_time);
        });

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        updateScene();

        /* Swap front and back buffers */
        glfwSwapBuffers(window.getGlfwWindowPtr());

        /* Poll for and process events */
        glfwPollEvents();

        if (double t = glfwGetTime(); t > next_second) {
            std::cout << "fps: " << fps << std::endl;
            next_second = t+1;
            fps = 0;
        }
        fps++;
    }
}

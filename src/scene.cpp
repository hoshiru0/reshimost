#include <iostream>

#include "scene.hpp"
#include "window.hpp"
#include "camera.hpp"

#include <GLFW/glfw3.h>

std::unique_ptr<Scene> current_scene;

void Scene::updateScene() {
    camera->update();
    update();
    for (auto it = entities.end()-1; it >= entities.begin(); it--) {
        it->get()->updateEntity();
    }
}

double delta_time;

void Scene::run() {

    uint32_t fps {};
    float next_second = 1;
    double time_last_frame {};
    while (!glfwWindowShouldClose(window.getGlfwWindowPtr())) {
        /* Render here */
        
        delta_time = glfwGetTime()-time_last_frame;
        time_last_frame = glfwGetTime();

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

#include <GLFW/glfw3.h>
#include <iostream>

#include "scene.hpp"
#include "window.hpp"


std::unique_ptr<Scene> current_scene;

void Scene::updateScene() {
    update();
    for (auto& e : entities) {
        e->update();
    }
}

void Scene::run() {
    double delta_time {};

    uint32_t fps {};
    float next_second = 1;
    double time_last_frame {};
    while (!glfwWindowShouldClose(window->getGlfwWindowPtr())) {
        /* Render here */
        
        delta_time = glfwGetTime()-time_last_frame;
        time_last_frame = glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        updateScene();

        /* Swap front and back buffers */
        glfwSwapBuffers(window->getGlfwWindowPtr());

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
#include <GLFW/glfw3.h>
#include <array>

#include <input.hpp>
#include <window.hpp>

Input input;

static std::array<uint8_t, 512> keys {};
static uint8_t mouse_left {}; 
static uint8_t mouse_right {};

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    keys[key] = action;
}
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        mouse_left = action;
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        mouse_right = action;
    }
}

Input::Input() {
    GLFWwindow* windowptr = window.getGlfwWindowPtr();
    glfwSetKeyCallback(windowptr, key_callback);
    glfwSetMouseButtonCallback(windowptr, mouse_button_callback);
}

bool Input::getKey(int key) {
    return keys[key];
}

bool Input::getKeyDown(int key) {
    auto& k = keys[key];
    bool pressed = k == 1;
    if (pressed) {
        k++;
    }

    return pressed;
}

bool Input::getMouseLeft() {
    return mouse_left;
}

bool Input::getMouseRight() {
    return mouse_right;
}
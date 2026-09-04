#pragma once
#include <GLFW/glfw3.h>

class Input
{
private:
    /* data */
public:
    Input(/* args */) = delete;
    ~Input();

    void static processInput(GLFWwindow* window){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
};
};

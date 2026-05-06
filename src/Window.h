#pragma once
#ifndef DELULUENGINE_WINDOW_H
#define DELULUENGINE_WINDOW_H
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    bool ShouldClose() const;
    void PollEvents() const;
    void SwapBuffers() const;

    int width() const {return m_width;};
    int height() const {return m_height;};

private:
    GLFWwindow* m_handle = nullptr;

    int m_width;
    int m_height;

    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
};


#endif //DELULUENGINE_WINDOW_H
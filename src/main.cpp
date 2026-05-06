#include <iostream>
#include "Window.h"

int main()
{
    try
    {
        Window window(1920, 1080, "DeluluEngine");

        while(!window.ShouldClose())
        {
            window.PollEvents();

            glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);


            window.SwapBuffers();
        }
    }
    catch (const std::exception& e)
        {
            std::cerr << "Fatal: " << e.what() << std::endl;
            return 1;
        }
    return 0;
}
#include <iostream>
#include "Window.h"

int main()
{
    int i = 0;

    try
    {
        Window window(1000, 300, 1920, 1080, "SomeVisualEngine");

        while(!window.ShouldClose())
        {
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        window.SwapBuffers();
        window.PollEvents();
            
            //input handling here
            //should be a singleton? Check structural patterns before deciding.
            //Should I handle input seperated or should "Window.h" handle window input specifically?

        }
    }
    catch (const std::exception& e)
        {
            std::cerr << "Fatal: " << e.what() << std::endl;
            return 1;
        }
    return 0;
}
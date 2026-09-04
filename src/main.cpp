#include <iostream>
#include "Window.h"
#include "Input.h"
#include "Matrix.h"

int main()
{
    int i = 0;
    


    try
    {
        Window window(1000, 1000, 1920, 1080, "SomeVisualEngine");

        float triangle_vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f,  -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f};
    
        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices),triangle_vertices, GL_STATIC_DRAW);
        
        //Vertex
        const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
            "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        int vert_success;
        char vert_infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vert_success);
        if(!vert_success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, vert_infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << vert_infoLog << std::endl;
        }

        //Fragment
        const char* fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\0";
        
        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        int frag_success;
        char frag_infoLog[512];
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &frag_success);
        if(!frag_success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, frag_infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << frag_infoLog << std::endl;
        }

        //ShaderProg
        unsigned int shaderProgram;
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        
        int prog_success;
        char prog_infoLog[512];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &prog_success);
        if(!prog_success)
        {
            glGetProgramInfoLog(shaderProgram, 512, NULL, prog_infoLog);
        }

        glUseProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0); 

        //DOUBLE CHECK AND REWRITE ON OWN
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);

        // ..:: Initialization code (done once (unless your object frequently changes)) :: ..
// 1. bind Vertex Array Object
        glBindVertexArray(VAO);
// 2. copy our vertices array in a buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
// 3. then set our vertex attributes pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);  

        while(!window.ShouldClose())
        {
            
            glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            //Input
            Input::processInput(window.ExceptionAllowGetHandle());
            
            //RenderCommands
            // ..:: Drawing code (in render loop) :: ..
            // 4. draw the object
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);


            //Swap
            window.SwapBuffers();
            window.PollEvents();
        }
    }
    catch (const std::exception& e)
        {
            std::cerr << "Fatal: " << e.what() << std::endl;
            return 1;
        }
    return 0;
}
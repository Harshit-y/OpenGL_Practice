#include <iostream>
#include <cmath>
#include <unistd.h>

// IMPORTANT: GLAD headers MUST be included before GLFW headers.
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"


// For dynamic resize of viewport
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Background Color
void display(GLFWwindow* window, double currentTime){
    float green = (sin(currentTime) / 2.0f) + 0.5f;
    float red = (cos(currentTime) / 2.0f) + 0.5f;
    float blue = (sin(currentTime) / 2.0f) + 0.5f;

    glClearColor(red, green, blue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

// Array storing 3D coordinates of the triangle’s vertices (x,y,z)
// Vertices coordinates
GLfloat vertices[] =
{
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
    0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
    0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
};

// Indices for vertices order
GLuint indices[] =
{
    0, 3, 5, // Lower left triangle
    3, 2, 4, // Upper triangle
    5, 4, 1 // Lower right triangle
};

int main() {

    // Prints Current Working Directory

    // char cwd[1024];
    // if (getcwd(cwd, sizeof(cwd)) != nullptr) {
    //     std::cout << "Working directory: " << cwd << std::endl;
    // }

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set OpenGL version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);  // allow resize
    // glfwWindowHint(GLFW_SAMPLES, 4);          // enable 4x MSAA

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Project", NULL /*fullscreen*/, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the created window’s OpenGL context the current context (so OpenGL calls affect this window)
    glfwMakeContextCurrent(window);

    // Load OpenGL functions with GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // VSync ON
    glfwSwapInterval(1);

    // For MSAA
    // glEnable(GL_MULTISAMPLE);

    // Set the viewport
    glViewport(0, 0, 800, 600);
    
    // Tells GLFW to call the function "framebuffer_size_callback" when ever widow resizes
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Step 1: Build and compile the shaders
    // std::string vertPath = std::string(SHADER_DIR) + "/default.vert";
    // std::string fragPath = std::string(SHADER_DIR) + "/default.frag";


    Shader shaderProgram("../shaders/default.vert", "../shaders/default.frag");
    
    // Step 2: Setup vertex data and configure vertex attributes
    // Shift to global

    // Generates Vertex Array Object and binds it
    VAO VAO1;
    VAO1.Bind();

    // Generates Vertex Array Object and links it to vertices
    VBO VBO1(vertices,sizeof(vertices));

    // Generates Element Buffer Object and links it to indices
    EBO EBO1(indices, sizeof(indices));

    //Links VBO to VAO
    VAO1.LinkVBO(VBO1,0);

    //Unbind all to prevent accidental modification
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    

    // Step 3: Render loop (draw frame repeatedly until window closes)

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        // // Clear the the color buffer with a color
        // glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
        // // Clear the frame buffer with a color
        // glClear(GL_COLOR_BUFFER_BIT);
        
        // 1. Clear screen

        display(window, glfwGetTime());
        
        // 2. Use shader
        shaderProgram.Activate();
        // 3. Bind VAO
        VAO1.Bind();

        // Wireframe Mode
        // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

        // 4. Draw elements
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        // Swap buffers and poll for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // Delete all the objects we created
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();

    // Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
    return 0;
}
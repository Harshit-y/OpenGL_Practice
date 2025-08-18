#include <iostream>
#include <cmath>

// IMPORTANT: GLAD headers MUST be included before GLFW headers.
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// For dynamic resize of viewport
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void display(GLFWwindow* window, double currentTime){
    float green = (sin(currentTime) / 2.0f) + 0.5f;
    float red = (cos(currentTime) / 2.0f) + 0.5f;
    float blue = (sin(currentTime) / 2.0f) + 0.5f;

    glClearColor(red, green, blue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set OpenGL version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Project", NULL /*fullscreen*/, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window as the current OpenGL Context
    glfwMakeContextCurrent(window);

    // Load OpenGL functions with GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // VSync ON
    glfwSwapInterval(1);

    // Set the viewport
    glViewport(0, 0, 800, 600);
    
    // Tells GLFW to call the function "framebuffer_size_callback" when ever widow resizes
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        // // Clear the the color buffer with a color
        // glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
        // // Clear the frame buffer with a color
        // glClear(GL_COLOR_BUFFER_BIT);

        display(window, glfwGetTime());

        // Swap buffers and poll for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
    return 0;
}
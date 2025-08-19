#include <iostream>
#include <cmath>

// IMPORTANT: GLAD headers MUST be included before GLFW headers.
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 460 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

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


    // Create Vertex Shader Object and get its refernce
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach Vertex Shader source to the Vertex Shader Object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // Compile the Vertex Shader code into machine code
    glCompileShader(vertexShader);

    // Same steps for Fragment Shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    glCompileShader(fragmentShader);

    // Create a Shader Program Object and get its reference
    GLuint shaderProgram = glCreateProgram();

    // Attach the shaders to the Shader Program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // Wrap-up/link all the shaders together into the Shader Program
    glLinkProgram(shaderProgram);

    // Now we can delete the Shader Objects as they are already loaded in the Shader Program in the GPU
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Cordinates of the vertices
    GLfloat vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
    };

    // Initializing reference to VAO and VBO
    GLuint VAO, VBO;

    // Generating VAO and VBO
    glGenVertexArrays(1, &VAO); // one element VAO
    glGenBuffers(1, &VBO); // one element in VBO

    // Make the VAO the current Vertex Array Object
    glBindVertexArray(VAO);
    
    // Bind the VBO specifing it's a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Vertice data into VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Attribute data for VAO for first index i.e VBO
    // Configure the Vertex Attribute so that OpenGL knows how to read the VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // Enable the Vertex Attribute so that OpenGL knows to use it
    glEnableVertexAttribArray(0);

    // Bind both the VAO and VBO so that we don't accidently modify them
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        // // Clear the the color buffer with a color
        // glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
        // // Clear the frame buffer with a color
        // glClear(GL_COLOR_BUFFER_BIT);
        
        display(window, glfwGetTime());
        
        
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap buffers and poll for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // Delete all the objects we created
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(shaderProgram);

    // Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
    return 0;
}
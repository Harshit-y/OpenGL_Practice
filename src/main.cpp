#include <iostream>
#include <cmath>
#include <unistd.h>

// IMPORTANT: GLAD headers MUST be included before GLFW headers.
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shaderClass.h>


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



    // Initializing reference to VAO, VBO and EBO
    GLuint VAO[1], VBO[1], EBO[1];

    // Generating VAO and VBO

    // Generate one Vertex Array Object (VAO), one Vertex Buffer Object (VBO) and one Element Buffer Object(EBO)
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);
    glGenBuffers(1, EBO);


    // Make the VAO the current Vertex Array Object
    glBindVertexArray(*VAO);
    
    // Bind the VBO specifing it's a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    
    // Copy vertex data from CPU memory into GPU memory (inside VBO)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);

    // Copy element data from CPU memory into GPU memory (inside VBO)
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Define how vertex attribute 0 (aPos) should interpret the data in the bound VBO: 3 floats per vertex, tightly packed
    // Configure the Vertex Attribute so that OpenGL knows how to read the VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

    // Enable the Vertex Attribute so that OpenGL knows to use it
    glEnableVertexAttribArray(0);

    // Unbind the VBO and VAO so we don’t accidentally modify them later
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Bind the EBO to 0 so that we don't accidentally modify it
	// MAKE SURE TO UNBIND IT AFTER UNBINDING THE VAO, as the EBO is linked in the VAO
	// This does not apply to the VBO because the VBO is already linked to the VAO during glVertexAttribPointer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

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
        glBindVertexArray(*VAO);

        // Wireframe Mode
        // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

        // 4. Draw elements
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        // Swap buffers and poll for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // Delete all the objects we created
    glDeleteBuffers(1, VBO);
    glDeleteBuffers(1, EBO);
    glDeleteVertexArrays(1, VAO);
    shaderProgram.Delete();

    // Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
    return 0;
}
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

float xPosition = 0.0f;
float yPosition = 0.0f;
float moveSpeed = 0.025f;

void processInput(GLFWwindow* window, int key) {
    if (key == GLFW_KEY_LEFT) {
        xPosition -= moveSpeed;
    }
    if (key == GLFW_KEY_RIGHT) {
        xPosition += moveSpeed;
    }
    if (key == GLFW_KEY_UP) {
        yPosition += moveSpeed;
    }
    if (key == GLFW_KEY_DOWN) {
        yPosition -= moveSpeed;
    }
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Specify version of GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "Simple Rectangle", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Define vertices for a rectangle
    float vertices[] = {
        -0.025f, -0.025f, 0.0f, // bottom left
         0.025f, -0.025f, 0.0f, // bottom right
         0.025f,  0.025f, 0.0f, // top right
        -0.025f,  0.025f, 0.0f  // top left
    };

    // Define indices for the rectangle
    unsigned int indices[] = {
        0, 1, 2, // first triangle
        2, 3, 0  // second triangle
    };

    // Create and bind vertex array object (VAO)
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create vertex buffer object (VBO) and index buffer object (EBO)
    unsigned int VBO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind VBO and copy vertex data into it
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind EBO and copy index data into it
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind VAO (it's always a good practice to unbind any VAOs/ VBOs to prevent unwanted changes)
    glBindVertexArray(0);

    // Set the key callback function
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (action == GLFW_PRESS) {
            processInput(window, key);
        }
        });

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {

        // Set clear color and clear the buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the rectangle with updated position
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // Close window
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

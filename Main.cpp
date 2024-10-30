#include <glfw3.h>
#include <glad/glad.h> 
#include "Shader.h"
#include "Camera.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

void framebuffer_size_callback(GLFWwindow* window, int witdh, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

unsigned int* loadTextureImage(unsigned char* data, unsigned int textNumber);

//Window dimensions
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//Delta time:
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//Last position of mouse cursor
float lastX = 400.0f, lastY = 300.0f;

//Check if it is the first movement of the mouse
bool firstMouse = true;

//Camera global variable
Camera cameraC;

int main()
{
    //Initialize glfw and sets the OpenGL version to use
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Creating a window object
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearningOpenGL", NULL, NULL);

    if (window == NULL) {
        std::cout << "FAILED TO CREATE GLFW WINDOW" << std::endl;
        glfwTerminate();
        return -1;
    }

    //Make it the component of the main thread.
    glfwMakeContextCurrent(window);

    //Initializing GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "FAILED TO INITIALIZE GLAD" << std::endl;
        return -1;
    }

    //Sets the window components
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    //Attach function to window object
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Attach function to mouse movement
    glfwSetCursorPosCallback(window, mouse_callback);

    //Attach 
    glfwSetScrollCallback(window, scroll_callback);

    //Set the mouse input mode
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Shader shaderProgram("vertexShader.glsl", "fragmentShader.glsl");

    cameraC = Camera();

    float verticesCube[] = {
        // Positions           Texture
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    //vertices for panels
    unsigned int verticesPanels[] = {
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
    };

    //Indices
    unsigned int indicesPanels[] = {
        0, 1, 3,
        1, 2, 3
    };
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  0.0f, -15.0f),
        glm::vec3(-1.5f, 0.0f, -2.5f),
        glm::vec3(-3.8f, 0.0f, -12.3f),
        glm::vec3(2.4f,  0.0f, -3.5f),
        glm::vec3(-1.7f, 0.0f, -7.5f),
        glm::vec3(1.3f,  0.0f, -2.5f),
        glm::vec3(1.5f,  0.0f, -2.5f),
        glm::vec3(1.5f,  0.0f, -1.5f),
        glm::vec3(-1.3f, 0.0f, -1.5f)
    };

    //Create 
    unsigned int EBOs[2];
    glGenBuffers(2, EBOs);

    //Buffer for OpenGL: Creates the buffer, attaches it to an array buffer then draw it.
    unsigned int VBOs[3];
    glGenBuffers(3, VBOs);

    //Creating VAOs
    unsigned int VAOs[3];
    glGenVertexArrays(3, VAOs);
}

unsigned int* loadTextureImage(unsigned char* data, unsigned int textNumber)
{

}

void framebuffer_size_callback(GLFWwindow* window, int witdh, int height)
{

}
void processInput(GLFWwindow* window)
{

}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

}
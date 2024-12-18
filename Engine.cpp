#include "Engine.h"

Engine::Engine()
{
    std::cout << "Starting Engine..." << std::endl;
    //Initialize glfw and sets the OpenGL version to use
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    //Creating a window object
    windowApp = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "WorldExplorer", NULL, NULL);

    if (windowApp == NULL) {
        std::cout << "FAILED TO CREATE GLFW WINDOW" << std::endl;
        glfwTerminate();
    }

    //Make it the component of the main thread.
    glfwMakeContextCurrent(windowApp);

    //Initializing GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "FAILED TO INITIALIZE GLAD" << std::endl;
    }

    //Attach function to window object
    glfwSetFramebufferSizeCallback(windowApp, framebuffer_size_callback);

    //Enabling z-buffer
    glEnable(GL_DEPTH_TEST);

    //Enable Hide and capture cursor
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    stbi_set_flip_vertically_on_load(true);

    mainCamera = Camera();
    userInterface = GUI();
}

Engine::~Engine()
{
    glfwDestroyWindow(windowApp);
    glfwTerminate();
}


void Engine::renderLoop()
{
    std::cout << "Starting the rendering..." << std::endl;
}

//Function to resize window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

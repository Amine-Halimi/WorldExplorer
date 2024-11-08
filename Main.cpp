/*
This is a 3D renderer I have written learning the guide of LearnOpenGL
*/

#include <glad/glad.h>
#include <glfw3.h>
#include "Shader.h"
#include "iostream"
#include "Camera.h"
#include "stb_image.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"


void framebuffer_size_callback(GLFWwindow* window, int witdh, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int loadTexture(char const* path);
//Window dimensions
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


bool opacityChanged = false;
float opacity = 0.2f;

//Delta time:
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//Last position of mouse cursor
float lastX = 400.0f, lastY = 300.0f;

//Check if it is the first movement of the mouse
bool firstMouse = true;

//Yaw and pitch
float yaw = -90.0f;
float pitch = 0.0f;

//Fov
float fov = 45.0f;

Camera camera;

glm::vec3 lightPos(1.5f, 1.0f, 2.0f);

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

    //Enabling z-buffer
    glEnable(GL_DEPTH_TEST);

    //Enable Hide and capture cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Shader lightingShader("vertexLightingShader.glsl", "fragmentLightingShader.glsl");
    camera = Camera();

    Shader lightCubeShader("vertexShader.glsl", "fragmentShader.glsl");
    /*
    float vertices[] = {
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

    
    //Indices
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    //Create
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    */


    float verticesLightCube[] = {
    //Positions              Normal             Textures
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    glm::vec3 pointLightPositions[] = {
       glm::vec3(0.7f,  0.2f,  2.0f),
       glm::vec3(2.3f, -3.3f, -4.0f),
       glm::vec3(-4.0f,  2.0f, -12.0f),
       glm::vec3(0.0f,  0.0f, -3.0f)
    };
    //Buffer for OpenGL: Creates the buffer, attaches it to an array buffer then draw it.
    unsigned int VBO;
    glGenBuffers(1, &VBO);


    //Creating a VAO
    unsigned int VAOs[1];
    glGenVertexArrays(1, VAOs);

    //Bind buffer and copy data to buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLightCube), verticesLightCube, GL_STATIC_DRAW);

    //vertex Positions
    glBindVertexArray(VAOs[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);

    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int containerTextureID, containerSpecularMapID, containerEmissionMapID;
    containerTextureID = loadTexture("textures\\container2.png");
    containerSpecularMapID = loadTexture("textures\\container2_specular.png");
    //containerEmissionMapID = loadTexture("textures\\matrix.jpg");

    lightingShader.use();
    lightingShader.setInt("material.diffuse", 0);
    lightingShader.setInt("material.specular", 1);
    //lightingShader.setInt("material.emission", 2);

    //Main application loop
    while (!glfwWindowShouldClose(window)) {
        float currentTime = static_cast<float>(glfwGetTime());
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        processInput(window);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /*
        ourShader.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures[1]);

        if (opacityChanged)
        {
            ourShader.setFloat("opacity", opacity);
            opacityChanged = false;
        }
        */
        glm::mat4 view = camera.GetViewMatrix();
        //GLM Perspective view matrix transformation
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(camera.zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        /*
        float changeInTime = glfwGetTime() * 20.0f;
        float angle = glm::radians(changeInTime);
        lightPos = glm::vec3(2.0f * cos(angle), 2.0f * sin(angle), 0.0f);
        */
        /*
        glm::vec3 lightColor;
        lightColor.x = sin(glfwGetTime() * 2.0f);
        lightColor.y = sin(glfwGetTime() * 0.7f);
        lightColor.z = sin(glfwGetTime() * 1.3f);
        */
        lightingShader.use();
        lightingShader.setMat4("view", view);
        lightingShader.setMat4("projection", projection);

        lightingShader.setVec3("viewPos", camera.Position);
        lightingShader.setFloat("material.shininess", 64.0f);

        glm::vec3 diffuseLight = glm::vec3(0.5f);
        glm::vec3 ambientLight = glm::vec3(0.2f);

        //Directional light
        lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        lightingShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        lightingShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

        //Pointlight lights
        for (int i = 0; i < 4; i++)
        {
            std::string name = "pointlights[" + std::to_string(i) + "].";
            lightingShader.setVec3(name + "position", pointLightPositions[i]);
            lightingShader.setVec3(name + "ambient", 0.05f, 0.05f, 0.05f);
            lightingShader.setVec3(name + "diffuse", 0.8f, 0.8f, 0.8f);
            lightingShader.setVec3(name + "specular", 1.0f, 1.0f, 1.0f);

            lightingShader.setFloat(name + "constant", 1.0f);
            lightingShader.setFloat(name + "linear", 0.09f);
            lightingShader.setFloat(name + "quadratic", 0.032f);
        }

        //Spotlight

        lightingShader.setVec3("spotlight.position", camera.Position);
        lightingShader.setVec3("spotlight.direction", camera.Front);
        lightingShader.setFloat("spotlight.cutOff", glm::cos(glm::radians(12.5f)));
        lightingShader.setFloat("spotlight.outerCutOff", glm::cos(glm::radians(17.5f)));
        lightingShader.setVec3("spotlight.ambient", ambientLight);
        lightingShader.setVec3("spotlight.diffuse", diffuseLight);
        lightingShader.setVec3("spotlight.specular", 1.0f, 1.0f, 1.0f); 
        lightingShader.setFloat("spotlight.constant", 1.0f);
        lightingShader.setFloat("spotlight.linear", 0.09f);
        lightingShader.setFloat("spotlight.quadratic", 0.032f);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, containerTextureID);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, containerSpecularMapID);
        /*
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, containerEmissionMapID);
        */
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            lightingShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glBindVertexArray(lightVAO);
        lightCubeShader.use();
        lightCubeShader.setMat4("view", view);
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setVec3("lightColor", glm::vec3(1.0f));
        for (int i = 0; i < 4; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f));
            lightCubeShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, VAOs);
    glDeleteVertexArrays(1, &lightVAO);

    glfwTerminate();
    return 0;
}
//Function that process input
void processInput(GLFWwindow* window)
{
    const float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        opacityChanged = true;
        opacity += 0.025f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        opacityChanged = true;
        opacity -= 0.025f;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.ProcessKeyBoard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.ProcessKeyBoard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.ProcessKeyBoard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.ProcessKeyBoard(RIGHT, deltaTime);
    }

}

//Function to resize window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//Camera control for the mouse
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    //Set the offset in x and y
    float xoffset = static_cast<float>(xpos) - lastX;
    float yoffset = static_cast<float>(ypos) - lastY;
    lastX = static_cast<float>(xpos);
    lastY = static_cast<float>(ypos);

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

unsigned int loadTexture(char const* path)
{

    //Creating a OpenGL texture object
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrChannels;

    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format;
        if (nrChannels == 1)
        {
            format = GL_RED;
        }
        else if (nrChannels == 3)
        {
            format = GL_RGB;
        }
        else if (nrChannels == 4)
        {
            format = GL_RGBA;
        }
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        //Options for the textures wrapping around the S and T axis
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        //Texture filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    return textureID;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

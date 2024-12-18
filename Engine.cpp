#include "Engine.h"



Engine::Engine()
{   
    std::cout << "Starting Engine..." << std::endl;

    status = setUpEngine();

    switch (status)
    {
    case 0: std::cout << "Everything working properly\n"; break;
    case -1: std::cout << "Shutting down engine\n"; break;
    default: std::cout << "Default case switch\n";
    };
}

Engine::~Engine()
{
    glfwDestroyWindow(windowApp);
    glfwTerminate();
}

int Engine::setUpEngine()
{
    //Initialize glfw and sets the OpenGL version to use
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    //Creating a window object
    windowApp = glfwCreateWindow(scr_width, scr_height, "WorldExplorer", NULL, NULL);

    if (windowApp == NULL) {
        std::cout << "FAILED TO CREATE GLFW WINDOW" << std::endl;
        glfwTerminate();
        return -1;
    }

    //Make it the component of the main thread.
    glfwMakeContextCurrent(windowApp);

    //Initializing GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "FAILED TO INITIALIZE GLAD" << std::endl;
        return -1;
    }

    //Attach function to window object
    glfwSetFramebufferSizeCallback(windowApp, framebuffer_size_callback);

    //Enabling z-buffer
    glEnable(GL_DEPTH_TEST);

    stbi_set_flip_vertically_on_load(true);

    mainCamera = Camera();
    //userInterface = GUI();

    lastX = scr_width / 2.0f;
    lastY = scr_height / 2.0f;

    return 0;
}
void Engine::renderLoop()
{
    if (status == 0)
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos; // Enable mouse controls

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(windowApp, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
        ImGui_ImplOpenGL3_Init("#version 330");

        Shader lightCubeShader("vertexShader.glsl", "fragmentShader.glsl");
        std::string path = "assets\\backpack.obj";

        std::cout << "Creating the shader..." << std::endl;
        Shader ourShader("vertexLightingShader.glsl", "fragmentLightingShader.glsl");
        std::cout << "Done creating the shader!" << std::endl;

        std::cout << "Loading the model..." << std::endl;
        Model modelBackpack(path.c_str());
        std::cout << "Done loading the model..." << std::endl;


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
        glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f,  0.2f,  2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3(0.0f,  0.0f, -3.0f)
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


        //Buffer for OpenGL: Creates the buffer, attaches it to an array buffer then draw it.
        unsigned int VBO;
        glGenBuffers(1, &VBO);


        unsigned int lightVAO;
        glGenVertexArrays(1, &lightVAO);
        //Bind buffer and copy data to buffer
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLightCube), verticesLightCube, GL_STATIC_DRAW);
        glBindVertexArray(lightVAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);


        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        std::cout << "Starting the rendering..." << std::endl;

        while (!glfwWindowShouldClose(windowApp)) {
            float currentTime = static_cast<float>(glfwGetTime());
            deltaTime = currentTime - lastFrame;
            lastFrame = currentTime;


            glfwPollEvents();


            glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if (!io.WantCaptureMouse)
            {
                processInput();
            }

            // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
            if (show_demo_window)
                ImGui::ShowDemoWindow(&show_demo_window);

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

                ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
                ImGui::Checkbox("Another Window", &show_another_window);

                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

                if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                ImGui::End();
            }

            // 3. Show another simple window.
            if (show_another_window)
            {
                ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                ImGui::Text("Hello from another window!");
                if (ImGui::Button("Close Me"))
                    show_another_window = false;
                ImGui::End();
            }

            //Rendering
            ourShader.use();
            glm::mat4 view = mainCamera.GetViewMatrix();
            //GLM Perspective view matrix transformation
            glm::mat4 projection = glm::mat4(1.0f);
            projection = glm::perspective(glm::radians(mainCamera.zoom), (float)scr_width / (float)scr_height, 0.1f, 100.0f);
            ourShader.setMat4("projection", projection);
            ourShader.setMat4("view", view);

            // render the loaded model
            glm::mat4 spaceModel = glm::mat4(1.0f);
            spaceModel = glm::translate(spaceModel, glm::vec3(0.0f, 0.0f, 0.0f));
            spaceModel = glm::scale(spaceModel, glm::vec3(1.0f, 1.0f, 1.0f));
            ourShader.setMat4("model", spaceModel);
            modelBackpack.Draw(ourShader);


            ourShader.setVec3("viewPos", mainCamera.Position);
            ourShader.setFloat("material.shininess", 64.0f);

            glm::vec3 diffuseLight = glm::vec3(0.5f);
            glm::vec3 ambientLight = glm::vec3(0.2f);

            //Directional light
            ourShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
            ourShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
            ourShader.setVec3("dirLight.diffuse", 0.1f, 0.1f, 0.1f);
            ourShader.setVec3("dirLight.specular", 0.1f, 0.1f, 0.1f);

            //Pointlight lights
            for (int i = 0; i < 4; i++)
            {
                std::string name = "pointlights[" + std::to_string(i) + "].";
                ourShader.setVec3(name + "position", pointLightPositions[i]);
                ourShader.setVec3(name + "ambient", 0.05f, 0.05f, 0.05f);
                ourShader.setVec3(name + "diffuse", diffuseLight);
                ourShader.setVec3(name + "specular", 1.0f, 1.0f, 1.0f);

                ourShader.setFloat(name + "constant", 1.0f);
                ourShader.setFloat(name + "linear", 0.09f);
                ourShader.setFloat(name + "quadratic", 0.032f);
            }

            //Spotlight

            ourShader.setVec3("spotlight.position", mainCamera.Position);
            ourShader.setVec3("spotlight.direction", mainCamera.Front);
            ourShader.setFloat("spotlight.cutOff", glm::cos(glm::radians(12.5f)));
            ourShader.setFloat("spotlight.outerCutOff", glm::cos(glm::radians(17.5f)));
            ourShader.setVec3("spotlight.ambient", ambientLight);
            ourShader.setVec3("spotlight.diffuse", diffuseLight);
            ourShader.setVec3("spotlight.specular", 1.0f, 1.0f, 1.0f);
            ourShader.setFloat("spotlight.constant", 1.0f);
            ourShader.setFloat("spotlight.linear", 0.09f);
            ourShader.setFloat("spotlight.quadratic", 0.032f);


            glBindVertexArray(lightVAO);
            lightCubeShader.use();
            lightCubeShader.setVec3("lightColor", 0.8f, 0.8f, 0.8f);
            lightCubeShader.setMat4("view", view);
            lightCubeShader.setMat4("projection", projection);
            lightCubeShader.setVec3("lightColor", 0.8f, 0.5f, 0.1f);
            for (int i = 0; i < 4; i++)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, pointLightPositions[i]);
                model = glm::scale(model, glm::vec3(0.2f));
                lightCubeShader.setMat4("model", model);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(windowApp);
        }
    }

    else
    {
        std::cout << "CANNOT RENDER ENGINE. STATUS OF THE ENGINE IS NEGATIVE" << std::endl;
    }
}
void Engine::processInput()
{
    const float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(windowApp, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(windowApp, true);
    }

    if (glfwGetKey(windowApp, GLFW_KEY_W) == GLFW_PRESS)
    {
        mainCamera.ProcessKeyBoard(FORWARD, deltaTime);
    }
    if (glfwGetKey(windowApp, GLFW_KEY_S) == GLFW_PRESS)
    {
        mainCamera.ProcessKeyBoard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(windowApp, GLFW_KEY_A) == GLFW_PRESS)
    {
        mainCamera.ProcessKeyBoard(LEFT, deltaTime);
    }
    if (glfwGetKey(windowApp, GLFW_KEY_D) == GLFW_PRESS)
    {
        mainCamera.ProcessKeyBoard(RIGHT, deltaTime);
    }

    if (glfwGetMouseButton(windowApp, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glfwSetInputMode(windowApp, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        double mouseX;
        double mouseY;

        glfwGetCursorPos(windowApp, &mouseX, &mouseY);

        mouseMovement(mouseX, mouseY);
    }

    if (glfwGetMouseButton(windowApp, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        glfwSetInputMode(windowApp, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void Engine::mouseMovement(double xpos, double ypos)
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

    mainCamera.ProcessMouseMovement(xoffset, yoffset);
}

void Engine::scrollWheel(double xoffset, double yoffset)
{
    mainCamera.ProcessMouseScroll(static_cast<float>(yoffset));
}

//Function to resize window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

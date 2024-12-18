#ifndef ENGINE_H
#define ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "iostream"
#include "Camera.h"
#include "stb/stb_image.h"
#include "Model.h"
#include "Scene.h"
#include "GUI.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 1200;
class Engine
{

public:
	Engine();
	~Engine();

	void renderLoop();

private:
	Camera mainCamera;
	GLFWwindow* windowApp;
	GUI userInterface;
	std::vector<Scene*> listOfScenes;

	float deltaTime { 0.0f };
	float lastFrame { 0.0f };

	void processInput();

	
};
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif

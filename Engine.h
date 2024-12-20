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


class Engine
{

public:
	Engine();
	~Engine();

	void renderLoop();

private:
	//Last position of mouse cursor
	float lastX;
	float lastY;

	int status{ 0 };

	//Check if it is the first movement of the mouse
	bool firstMouse{ true };
	unsigned int scr_width{ 1600 };
	unsigned int scr_height{ 1200 };

	Camera mainCamera;
	GLFWwindow* windowApp;
	GUI userInterfaceGraphic;
	std::vector<Scene*> listOfScenes;

	float deltaTime { 0.0f };
	float lastFrame { 0.0f };

	int setUpEngine();


	void processInput();

	void mouseMovement(double xpos, double ypos);

	void scrollWheel(double xoffset, double yoffset);
};
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif

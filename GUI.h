#ifndef GUI_H
#define GUI_H

#include "GLFW/glfw3.h"
#include "iostream"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

struct userInterfaceWindowFunction
{
	virtual void renderWindow(bool showWindow, int objectId, ImGuiIO& io)
	{

	}
	~userInterfaceWindowFunction()
	{

	}
};

struct userInterfaceWindow
{
	bool showWindow;
	int objectId;
	
	userInterfaceWindowFunction* function;
	userInterfaceWindow* innerUserInterfaceWindows;

	void renderWindow(ImGuiIO& io)
	{
		std::cout << "Inside userInterfaceWindow" << std::endl;
		function->renderWindow(showWindow, objectId, io);
	}

	userInterfaceWindow()
	{
	}

	~userInterfaceWindow()
	{

	}

}; 

struct renderObjectComponentWindowFunction : userInterfaceWindowFunction
{
	void renderWindow(bool showWindow, int objectId, ImGuiIO& io)
	{

	}
};

struct sceneSelectorWindowFunction : userInterfaceWindowFunction
{
	void renderWindow(bool showWindow, int objectId, ImGuiIO& io)
	{

	}
};

struct demoWindowFunction : userInterfaceWindowFunction
{
	void renderWindow(bool showWindow, int objectId, ImGuiIO& io)
	{
		std::cout << "Inside demoWindowFunction" << std::endl;
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		if (showWindow)
		{
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
		}
	}
};


class GUI
{
public:
	GUI();
	GUI(GLFWwindow* windowApp);
	~GUI();
	
	void displayWindow(ImGuiIO& io);
	void createNewFrame();
	void renderGUI();

private:
	
	userInterfaceWindow mainWindow;
	
};

#endif

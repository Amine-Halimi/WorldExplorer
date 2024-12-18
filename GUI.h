#ifndef GUI_H
#define GUI_H

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

struct userInterfaceWindowFunction
{
	virtual void renderWindow(bool showWindow, int objectId)
	{

	}
};

struct userInterfaceWindow
{
	bool showWindow;
	int objectId;
	userInterfaceWindowFunction function;
	userInterfaceWindow* innerUserInterfaceWindows;

	void renderWindow()
	{
		function.renderWindow(showWindow, objectId);
	}
}; 
class GUI
{
public:
	GUI();
	~GUI();
private:
	void renderMainWindow();
	
};
#endif

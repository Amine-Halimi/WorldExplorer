#ifndef GUI_H
#define GUI_H

#include "imgui/imgui.h"

struct userInterfaceWindowFunction
{
	void renderWindow(bool showWindow)
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
		function.renderWindow(showWindow);
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

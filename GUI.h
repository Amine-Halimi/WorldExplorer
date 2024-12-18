#ifndef GUI_H
#define GUI_H

#include "imgui/imgui.h"

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

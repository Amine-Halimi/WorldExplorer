#include "GUI.h"
#include "iostream"
GUI::GUI()
{

    std::cout << "Creating GUI object" << std::endl;
    mainWindow.objectId = 1;
    mainWindow.showWindow = true;
    mainWindow.function = new demoWindowFunction();

}
/*
Implementation for the GUI constructor. Sets up Imgui.
windowApp: GLFWwindow*: Pointer of the GLFWwindow initialized in the Engine.cpp renderloop function 
*/

GUI::GUI(GLFWwindow* windowApp)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(windowApp, true);         
    ImGui_ImplOpenGL3_Init("#version 330");

    mainWindow.objectId = 1;
    mainWindow.showWindow = true;
    mainWindow.function = new demoWindowFunction();
}
// Destructor for GUI
GUI::~GUI()
{

}
/*
Shutdown calls the shutdown functions for Im::Gui
*/
void GUI::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

/*
Calls the Im:Gui new frame functions
*/
void GUI::createNewFrame()
{
    //std::cout << "Creating new frame" << std::endl;
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

/*
Calls the renderWindow function
*/
void GUI::displayWindow(ImGuiIO& io)
{
    //std::cout << "Calling mainWindow renderWindow function." << std::endl;
    mainWindow.renderWindow(io);
}
/*
Calls the Im:Gui render function
*/
void GUI::renderGUI()
{
    //std::cout << "Im:Gui:: Render()" << std::endl;
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
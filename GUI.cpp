#include "GUI.h"
#include "iostream"
GUI::GUI()
{

    std::cout << "Creating GUI object" << std::endl;
    mainWindow.objectId = 1;
    mainWindow.showWindow = true;
    mainWindow.function = new demoWindowFunction();

}

GUI::GUI(GLFWwindow* windowApp)
{

    mainWindow.objectId = 1;
    mainWindow.showWindow = true;
    mainWindow.function = new demoWindowFunction();

}

GUI::~GUI()
{

}

void GUI::createNewFrame()
{
    std::cout << "Creating new frame" << std::endl;
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GUI::displayWindow(ImGuiIO& io)
{
    std::cout << "Calling mainWindow renderWindow function." << std::endl;
    mainWindow.renderWindow(io);
}

void GUI::renderGUI()
{
    std::cout << "Im:Gui:: Render()" << std::endl;
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
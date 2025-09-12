#include "Application.h"

struct GLFWwindow;

int main()
{
    GLFWwindow* window = Application::Initialize();
    Application::Run(window);
    Application::Exit(window);
}

#include "ui_backend.hpp"
#include "ui.hpp"

#define GL_SILENCE_DEPRECATION


bool open = true;
bool drag = false;
bool lmb_down = false;
double last_mouse_clicked_x = 0.0f;
double last_mouse_clicked_y = 0.0f;
const char* glsl_version = "#version 150";

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            glfwGetCursorPos(window, &last_mouse_clicked_x, &last_mouse_clicked_y);
            lmb_down = true;
        }
        if (action == GLFW_RELEASE)
        {
            lmb_down = false;
            drag = false;
        }
    }
}

RECT GetDesktopResolution()
{
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    return desktop;
}

void window_move_attach(GLFWwindow* window)
{
    if (lmb_down && !drag && ImGui::IsItemHovered())
        drag = true;

    if (drag)
    {
        int win_x, win_y;
        double mouse_x, mouse_y;
        glfwGetCursorPos(window, &mouse_x, &mouse_y);
        glfwGetWindowPos(window, &win_x, &win_y);
        glfwSetWindowPos(window, mouse_x + win_x - last_mouse_clicked_x, mouse_y + win_y - last_mouse_clicked_y);
    }
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int RenderUi()
{
    RECT DesktopRes = GetDesktopResolution();

    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(GuiSettings::WindowWidth, GuiSettings::WindowHeight, GuiSettings::AppName, nullptr, nullptr);
    if (window == nullptr)
        return 1;

    glfwSetWindowPos(window, (DesktopRes.right / 2) - (GuiSettings::WindowWidth / 2), DesktopRes.bottom / 2 - GuiSettings::WindowHeight);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.IniFilename = NULL;
    io.LogFilename = NULL;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    while (open)
    {
        if (glfwWindowShouldClose(window))
        {
            open = false;
        }

        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin(GuiSettings::AppName, &open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
        ImGui::SetWindowSize({ GuiSettings::WindowWidth, GuiSettings::WindowHeight });
        ImGui::SetWindowPos({ 0, 0 });
        window_move_attach(window);

        ui();

        ImGui::End();

        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.0f * 0.0f, 0.0f * 0.0f, 0.0f * 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

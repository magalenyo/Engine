#include "ModuleEditor.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <string>

ModuleEditor::ModuleEditor()
{
}

ModuleEditor::~ModuleEditor()
{
}

bool ModuleEditor::Init()
{
    const char* glsl_version = "#version 130";

    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
    ImGui_ImplOpenGL3_Init(glsl_version);
    isReady = true;

    return true;
}

bool ModuleEditor::CleanUp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return true;
}

update_status ModuleEditor::Update()
{
    static bool show_console = true;

    if (show_console) {
        DrawConsole(&show_console, "hola");
    }

    //ImGui::ShowDemoWindow();
    return UPDATE_CONTINUE;
}


update_status ModuleEditor::PreUpdate()
{
    // THESE SHOULD BE CALLED BEFORE ANY DRAWING
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(App->window->window);
    ImGui::NewFrame();
    return UPDATE_CONTINUE;
}

void ModuleEditor::DrawConsole(bool* p_open, std::string logText)
{
    ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Console", p_open))
    {
        ImGui::End();
        return;
    }

    ImGui::Text(logText.c_str());

    ImGui::End();



}

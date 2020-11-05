#include "ModuleEditor.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

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
    ImGui::ShowDemoWindow();
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

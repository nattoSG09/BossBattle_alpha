#include "ImGuiManager.h"

// include headerFile...
#include "../Windows/Window.h"
#include "../DirectX/Direct3D.h"

bool ImGuiManager::Initialize(Window* _window, Direct3D* _d3d)
{
	if (IMGUI_CHECKVERSION() == false) return false;

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();

	if (ImGui_ImplWin32_Init(_window->WindowHandle()) == false) return false;
	if (ImGui_ImplDX11_Init(_d3d->Device(), _d3d->Context()) == false)return false;
}

void ImGuiManager::BeginFrame()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiManager::EndFrame()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::ShutDown()
{
	ImGui_ImplDX11_Shutdown();
	ImGui::DestroyContext();
}

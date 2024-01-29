#pragma once

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

class Window;
class Direct3D;

namespace ImGuiManager
{
	bool Initialize(Window* _window, Direct3D* _d3d);
	void BeginFrame();
	void EndFrame();
	void ShutDown();
};
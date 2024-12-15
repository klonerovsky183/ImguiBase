#pragma once

#include "ui_backend.hpp"

#include <string>
#include <cstring>
#include <imgui_internal.h>

namespace GuiSettings
{
	extern float WindowWidth;
	extern float WindowHeight;
	extern wchar_t AppName[255];
	extern char AppNameImGui[255];

	extern std::string CurrentTheme;
	extern std::string CurrentPage;

	extern ImVec4 AccentColor;
}

namespace Pages {
	void Default();
}

namespace Themes {
	void Default();
}

void ui();

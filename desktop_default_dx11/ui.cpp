#include "ui.hpp"

namespace GuiSettings
{
	extern float WindowWidth = 500.0f;
	extern float WindowHeight = 100.0f;
	extern wchar_t AppName[255] = L"Example window";
	extern char AppNameImGui[255] = "Takumo Loader";

	extern std::string CurrentTheme = "Default";
	extern std::string CurrentPage = "Default";

	extern ImVec4 AccentColor = { 0.0f, 0.0f, 0.0f, 0.0f };
}

void ui()
{
	if (GuiSettings::CurrentTheme == "Default") Themes::Default();

	if (GuiSettings::CurrentPage == "Default") Pages::Default();
}

namespace Pages {
	void Default()
	{
		ImGui::Text("Hello, world!");
	}
}

namespace Themes {
	void Default()
	{
		ImGuiStyle* style = &ImGui::GetStyle();
	}
}

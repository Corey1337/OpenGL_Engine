#include "menu.h"

void Menu::setting_tab()
{
	static char title[255] = "OpenGl Engine";
	ImGui::InputText("Window title", title, sizeof(title));

	const char *res_listbox_items[] = {"1920x1080", "1680x1050", "1440x900", "1200x800", "1280x720", "854x480"};
	std::vector<sf::Vector2u> res_listbox_items_ = {{1920, 1080}, {1680, 1050}, {1440, 900}, {1200, 800}, {1280, 720}, {854, 480}};
	static int res_listbox_item_current = 0;
	ImGui::Combo("Resolution", &res_listbox_item_current, res_listbox_items, IM_ARRAYSIZE(res_listbox_items));

	const char *theme_items[] = {"Dark theme", "Light theme", "Classic theme"};
	static int theme_items_current = 0;
	ImGui::Combo("Theme", &theme_items_current, theme_items, IM_ARRAYSIZE(theme_items));

	static bool is_fullscreen = false;
	ImGui::Checkbox("Fullscreen (not working)", &is_fullscreen);

	if (ImGui::Button("Change Font"))
	{
		ImGuiFileDialog::Instance()->OpenModal("ChangeFont", "Choose File", "Fonts files (*.ttf){.ttf}", ".\\.\\res\\fonts");
	}

	ImGui::SameLine();
	path_name temp_path = {"", ""};
	temp_path = OpenFile("ChangeFont(not working)", temp_path);
	ImGui::BulletText(temp_path.name.c_str());

	static float col[4];
	ImGui::LabelText("", "SkyBox color");
	ImGui::ColorPicker4("", col);

	if (ImGui::Button("Apply", ImVec2(125, 25)))
	{
		sf::ContextSettings settings;
		settings.depthBits = 24;
		settings.stencilBits = 8;
		settings.majorVersion = 4;
		settings.minorVersion = 3;

		if (theme_items_current == 0)
			ImGui::StyleColorsDark();
		if (theme_items_current == 1)
			ImGui::StyleColorsLight();
		if (theme_items_current == 2)
			ImGui::StyleColorsClassic();

			
		gl_->set_sky_color(col);

		// if (temp_path.name != "")
		// {
		// 	auto font = ImGui::GetIO().Fonts->AddFontFromFileTTF(temp_path.path.c_str(), 14);
		// 	ImGui::PushFont(font);
		// }

		if (is_fullscreen)
		{
			// win_->create(sf::VideoMode::getFullscreenModes()[0], "First Window", sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen, settings);
		}
		else
		{
			// win_->create(sf::VideoMode(win_->getSize().x, win_->getSize().y, 32), "First Window", sf::Style::Titlebar | sf::Style::Close, settings);
		}
		win_->setSize(res_listbox_items_[res_listbox_item_current]);
		win_->setTitle(title);
	}
}

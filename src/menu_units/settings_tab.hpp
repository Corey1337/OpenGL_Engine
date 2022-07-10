#include "menu.h"

void Menu::setting_tab()
{
	static char title[255] = "OpenGl Engine";
	ImGui::InputText("Window title", title, sizeof(title));

	const char *res_listbox_items[] = {"1920x1080", "1680x1050", "1440x900", "1200x800", "1280x720", "854x480"};
	std::vector<sf::Vector2u> res_listbox_items_ = {{1920, 1080}, {1680, 1050}, {1440, 900}, {1200, 800}, {1280, 720}, {854, 480}};
	static int res_listbox_item_current = 0;
	ImGui::Combo("Resolution", &res_listbox_item_current, res_listbox_items, IM_ARRAYSIZE(res_listbox_items));

	static bool is_fullscreen = false;
	ImGui::Checkbox("Fullscreen", &is_fullscreen);

	if (ImGui::Button("Apply", ImVec2(125, 25)))
	{
		sf::ContextSettings settings;
		settings.depthBits = 24;
		settings.stencilBits = 8;
		settings.majorVersion = 4;
		settings.minorVersion = 3;
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

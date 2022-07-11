#include "menu.h"

#include "menu_units/light_tab.hpp"
#include "menu_units/object_tab.hpp"
#include "menu_units/open_file.hpp"
#include "menu_units/settings_tab.hpp"
#include "menu_units/camera_tab.hpp"

Menu::Menu(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Scene> scene, std::shared_ptr<GL> gl)
{
	win_ = window;
	scene_ = scene;
	gl_ = gl;
	(void *)ImGui::SFML::Init(*win_);
	ImGui::StyleColorsDark();
	deltaClock = std::make_shared<sf::Clock>();
	// ImGui::GetIO().IniFilename = "";
}

void Menu::render()
{
	ImGui::SFML::Update(*win_, deltaClock->restart());
	ImGui::Begin("Window title", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
	{
		static int tabb = 0;
		ImGui::SameLine();
		if (ImGui::Button("Objects", ImVec2(150, 25)))
		{
			tabb = 0;
		}
		ImGui::SameLine();
		if (ImGui::Button("Light", ImVec2(150, 25)))
		{
			tabb = 1;
		}
		ImGui::SameLine();
		if (ImGui::Button("Camera", ImVec2(150, 25)))
		{
			tabb = 2;
		}
		ImGui::SameLine();
		if (ImGui::Button("Settings", ImVec2(150, 25)))
		{
			tabb = 3;
		}
		
		if (tabb == 0)
		{
			objects_tab(scene_->get_objects());
		}
		if (tabb == 1)
		{
			light_tab(scene_->get_light());
		}
		if (tabb == 2)
		{
			camera_tab(scene_->get_camera());
		}
		if (tabb == 3)
		{
			setting_tab();
		}
	}
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	ImGui::SFML::Render(*win_);
}

void Menu::ToggleButton(const char *str_id, bool *v)
{
	ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList *draw_list = ImGui::GetWindowDrawList();

	float height = ImGui::GetFrameHeight();
	float width = height * 1.55f;
	float radius = height * 0.50f;

	ImGui::InvisibleButton(str_id, ImVec2(width, height));
	if (ImGui::IsItemClicked())
		*v = !*v;

	float t = *v ? 1.0f : 0.0f;

	ImGuiContext &g = *GImGui;
	float ANIM_SPEED = 0.08f;
	if (g.LastActiveId == g.CurrentWindow->GetID(str_id)) // && g.LastActiveIdTimer < ANIM_SPEED)
	{
		float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
		t = *v ? (t_anim) : (1.0f - t_anim);
	}

	ImU32 col_bg;
	if (ImGui::IsItemHovered())
		col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.78f, 0.78f, 0.78f, 1.0f), ImVec4(0.64f, 0.83f, 0.34f, 1.0f), t));
	else
		col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.85f, 0.85f, 0.85f, 1.0f), ImVec4(0.56f, 0.83f, 0.26f, 1.0f), t));

	draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
	draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));
}
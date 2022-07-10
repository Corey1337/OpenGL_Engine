#include "menu.h"

Menu::Menu(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Scene> scene)
{
	win_ = window;
	scene_ = scene;
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
		if (ImGui::Button("Settings", ImVec2(150, 25)))
		{
			tabb = 2;
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
			setting_tab();
		}
	}
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	ImGui::SFML::Render(*win_);
}

void Menu::objects_tab(std::shared_ptr<std::vector<Object *>> objects)
{
	static char selectedItem[255];
	static int selected_ind = -1;
	bool selected[objects->size()];

	static float scaleV[3];
	static float spinV[3];
	static float deg;
	static float transV[3];

	if (selected_ind != -1)
	{
		selected[selected_ind] = true;
		strcpy(selectedItem, (*objects)[selected_ind]->get_name().c_str());
	}

	if (ImGui::BeginCombo("ObjectList", selectedItem))
	{

		for (int i = 0; i < objects->size(); i++)
		{
			if (ImGui::Selectable((*objects)[i]->get_name().c_str(), &selected[i]))
			{
				selected_ind = i;

				strcpy(selectedItem, (*objects)[selected_ind]->get_name().c_str());

				{
					auto temp = (*objects)[selected_ind]->get_scale();
					scaleV[0] = temp.x;
					scaleV[1] = temp.y;
					scaleV[2] = temp.z;
				}

				{
					auto temp = (*objects)[selected_ind]->get_rotation();
					spinV[0] = temp.spin_vec.x;
					spinV[1] = temp.spin_vec.y;
					spinV[2] = temp.spin_vec.z;
					deg = temp.spin_deg;
				}

				{
					auto temp = (*objects)[selected_ind]->get_position();
					transV[0] = temp.x;
					transV[1] = temp.y;
					transV[2] = temp.z;
				}
			}
		}
		ImGui::EndCombo();
	}
	ImGui::SameLine();
	if (ImGui::Button("Add", ImVec2(125, 25)))
	{
		ImGui::OpenPopup("Create object");
	}

	bool open = true;
	if (ImGui::BeginPopupModal("Create object", &open))
	{
		static std::string obj_name, obj_model_path, obj_texture_path, obj_normal_path = "";

		static bool model_type;
		static char obj_name_[255];
		if (ImGui::InputText("Object name", obj_name_, sizeof(obj_name_)))
			obj_name = obj_name_;

		ToggleButton("Toggle", &model_type);
		ImGui::SameLine();
		ImGui::BulletText("model/primitive");
		static std::string model_name;
		if (!model_type)
		{

			if (ImGui::Button("Choose Model"))
			{
				ImGuiFileDialog::Instance()->OpenModal("ChooseModel", "Choose File", "Model files (*.fbx *.obj){.fbx,.obj}", ".\\res\\");
			}

			if (model_name != "")
			{
				ImGui::SameLine();
				ImGui::BulletText(model_name.c_str());
				ImGui::SameLine();
				if (ImGui::Button("X"))
				{
					model_name = "";
					obj_model_path = "";
				}
			}
			if (ImGuiFileDialog::Instance()->Display("ChooseModel"))
			{
				if (ImGuiFileDialog::Instance()->IsOk())
				{
					obj_model_path = ImGuiFileDialog::Instance()->GetFilePathName();
					model_name = ImGuiFileDialog::Instance()->GetCurrentFileName();
				}
				ImGuiFileDialog::Instance()->Close();
			}
		}
		if (model_type)
		{
			std::vector<std::string> primitives = {"a", "b", "c"};
			static std::string primprev = "";
			static bool prim[3];
			if (ImGui::BeginCombo("PrimitiveList", primprev.c_str()))
			{
				for (int i = 0; i < primitives.size(); i++)
				{
					ImGui::Selectable(primitives[i].c_str(), &prim);
					if (prim[i])
						primprev = primitives[i];
				}
				ImGui::EndCombo();
			}
		}

		if (ImGui::Button("Choose Texture"))
		{
			ImGuiFileDialog::Instance()->OpenModal("ChooseTexture", "Choose File", "Image files (*.png *.gif *.jpg *.jpeg){.png,.gif,.jpg,.jpeg}", ".\\res\\");
		}
		static std::string texture_name;
		if (texture_name != "")
		{
			ImGui::SameLine();
			ImGui::BulletText(texture_name.c_str());
			ImGui::SameLine();
			if (ImGui::Button("X"))
			{
				texture_name = "";
				obj_texture_path = "";
			}
		}
		if (ImGuiFileDialog::Instance()->Display("ChooseTexture"))
		{
			if (ImGuiFileDialog::Instance()->IsOk())
			{
				obj_texture_path = ImGuiFileDialog::Instance()->GetFilePathName();
				texture_name = ImGuiFileDialog::Instance()->GetCurrentFileName();
			}
			ImGuiFileDialog::Instance()->Close();
		}

		if (ImGui::Button("Choose Normal Texture"))
		{
			ImGuiFileDialog::Instance()->OpenModal("ChooseNormal", "Choose File", "Image files (*.png *.gif *.jpg *.jpeg){.png,.gif,.jpg,.jpeg}", ".\\res\\");
		}
		static std::string normal_name;
		if (normal_name != "")
		{
			ImGui::SameLine();
			ImGui::BulletText(normal_name.c_str());
			ImGui::SameLine();
			if (ImGui::Button("X"))
			{
				normal_name = "";
				obj_normal_path = "";
			}
		}
		if (ImGuiFileDialog::Instance()->Display("ChooseNormal"))
		{
			if (ImGuiFileDialog::Instance()->IsOk())
			{
				obj_normal_path = ImGuiFileDialog::Instance()->GetFilePathName();
				normal_name = ImGuiFileDialog::Instance()->GetCurrentFileName();
			}
			ImGuiFileDialog::Instance()->Close();
		}

		if (ImGui::Button("Create") && obj_name != "") // model_name != ""
		{
			objects->push_back(new Object(obj_name, obj_model_path, obj_texture_path, obj_texture_path));
			obj_name = "";
			strcpy(obj_name_, "");
			obj_model_path = "";
			obj_texture_path = "";
			obj_normal_path = "";
			// model_name = "";
			texture_name = "";
			normal_name = "";
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Close"))
		{
			obj_name = "";
			strcpy(obj_name_, "");
			obj_model_path = "";
			obj_texture_path = "";
			obj_normal_path = "";
			// model_name = "";
			texture_name = "";
			normal_name = "";
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}

	if (selected_ind != -1)
	{
		if (ImGui::InputText("Change name", &selectedItem[0], sizeof(selectedItem)))
		{
			(*objects)[selected_ind]->set_name(selectedItem);
		}

		ImGui::LabelText("", "Scale obj");
		{
			if (ImGui::SliderFloat("Scale prop", &scaleV[0], -10.0f, 10.0f))
			{
				scaleV[1] = scaleV[0];
				scaleV[2] = scaleV[0];
				(*objects)[selected_ind]->set_scale(Vector3(scaleV[0], scaleV[1], scaleV[2]));
			}
			if (ImGui::SliderFloat3("Scale", scaleV, -10.0f, 10.0f))
			{
				(*objects)[selected_ind]->set_scale(Vector3(scaleV[0], scaleV[1], scaleV[2]));
			}
		}
		ImGui::LabelText("", "Spin obj");
		{
			if (ImGui::SliderFloat3("Spin vector", spinV, -10.0f, 10.0f) || ImGui::SliderFloat("Degree", &deg, -360.0f, 360.0f))
			{
				(*objects)[selected_ind]->set_rotation(Vector3(spinV[0], spinV[1], spinV[2]), deg);
			}
		}
		ImGui::LabelText("", "Translate obj");
		{
			if (ImGui::SliderFloat3("Translate vector", transV, -10.0f, 10.0f))
			{
				(*objects)[selected_ind]->set_position(Vector3(transV[0], transV[1], transV[2]));
			}
		}
		if (ImGui::Button("Delete obj"))
		{
			objects->erase(objects->begin() + selected_ind);
			selected_ind = -1;
			strcpy(selectedItem, "");
		}
	}
}

void Menu::light_tab(std::shared_ptr<Light> light)
{
	static float lightPosV[3] = {0.0f, 0.0f, 0.0f};
	static float materialShine = scene_->get_light()->get_shine();
	if (ImGui::SliderFloat("Shininess", &materialShine, 0.0f, 32.0f))
		scene_->get_light()->set_shine(materialShine);
	if (ImGui::SliderFloat3("LightPos", lightPosV, -10.0f, 10.0f))
	{
		scene_->get_light()->set_pos(Vector3(lightPosV[0], lightPosV[1], lightPosV[2]));
	}
}

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
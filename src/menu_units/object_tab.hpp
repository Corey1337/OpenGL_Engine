#include "menu.h"

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
		static std::string obj_name;
		static path_name model;
		static path_name texture;
		static path_name normal;

		static char obj_name_[255];
		if (ImGui::InputText("Object name", obj_name_, sizeof(obj_name_)))
			obj_name = obj_name_;

		static bool is_primitive;
		ToggleButton("Toggle", &is_primitive);
		ImGui::SameLine();
		ImGui::BulletText("model/primitive");
		if (!is_primitive)
		{

			if (ImGui::Button("Choose Model"))
			{
				ImGuiFileDialog::Instance()->OpenModal("ChooseModel", "Choose File", "Model files (*.fbx *.obj){.fbx,.obj}", ".\\res\\");
			}
			if (model.name != "")
			{
				ImGui::SameLine();
				ImGui::BulletText(model.name.c_str());
				ImGui::SameLine();
				if (ImGui::Button("X"))
				{
					model.name = "";
					model.path = "";
				}
			}
			model = OpenFile("ChooseModel", model);
		}
		if (is_primitive)
		{
			static int curItem = 0;
			const char *primitives[3] = {"Cube", "Pyramid", "Sphere"};
			ImGui::Combo("Primitives", &curItem, primitives, 3, -1);
			if (curItem == 0)
			{
				model.name = "Cube";
			}
			if (curItem == 1)
			{
				model.name = "Pyramid";
			}
			if (curItem == 2)
			{
				model.name = "Sphere";
			}
		}

		if (ImGui::Button("Choose Texture"))
		{
			ImGuiFileDialog::Instance()->OpenModal("ChooseTexture", "Choose File", "Image files (*.png *.gif *.jpg *.jpeg){.png,.gif,.jpg,.jpeg}", ".\\res\\");
		}
		if (texture.name != "")
		{
			ImGui::SameLine();
			ImGui::BulletText(texture.name.c_str());
			ImGui::SameLine();
			if (ImGui::Button("X"))
			{
				texture.name = "";
				texture.path = "";
			}
		}
		texture = OpenFile("ChooseTexture", texture);

		if (ImGui::Button("Choose Normal Texture"))
		{
			ImGuiFileDialog::Instance()->OpenModal("ChooseNormal", "Choose File", "Image files (*.png *.gif *.jpg *.jpeg){.png,.gif,.jpg,.jpeg}", ".\\res\\");
		}

		if (normal.name != "")
		{
			ImGui::SameLine();
			ImGui::BulletText(normal.name.c_str());
			ImGui::SameLine();
			if (ImGui::Button("X"))
			{
				normal.name = "";
				normal.path = "";
			}
		}
		normal = OpenFile("ChooseNormal", normal);

		if (ImGui::Button("Create") && obj_name != "" && ((model.name != "" && !is_primitive) || is_primitive))
		{
			if (is_primitive)
			{
				if (model.name == "Cube")
					objects->push_back(new Cube(obj_name, texture.path, normal.path));
				if (model.name == "Pyramid")
					objects->push_back(new Pyramid(obj_name, texture.path, normal.path));
				if (model.name == "Sphere")
					objects->push_back(new Sphere(obj_name, texture.path, normal.path));
			}
			else
				objects->push_back(new Object(obj_name, model.path, texture.path, normal.path));

			is_primitive = false;
			model = {"", ""};
			texture = {"", ""};
			normal = {"", ""};
			obj_name = "";
			strcpy(obj_name_, "");
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Close"))
		{

			model = {"", ""};
			texture = {"", ""};
			normal = {"", ""};
			obj_name = "";
			strcpy(obj_name_, "");
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

		if (ImGui::Button("Change Texture"))
		{
			ImGuiFileDialog::Instance()->OpenModal("ChangeTexture", "Choose File", "Image files (*.png *.gif *.jpg *.jpeg){.png,.gif,.jpg,.jpeg}", ".\\res\\");
		}
		{
			path_name temp_path = {"", ""};
			temp_path = OpenFile("ChangeTexture", temp_path);
			if (temp_path.name != "")
				(*objects)[selected_ind]->set_texture(temp_path.path);
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

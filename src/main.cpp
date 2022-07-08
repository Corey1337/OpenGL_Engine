#include <iostream>
#include <utility>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-sfml.h"

#include "math/math.hpp"
#include "render/loader.h"
#include "math/glm_test.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ImGuiFileDialog/ImGuiFileDialog.h"

int main()
{

	sf::ContextSettings settings;
	settings.depthBits = 24;  // количество битов буффера глубины
	settings.stencilBits = 8; //количество битов буфера трафарета
	settings.majorVersion = 4;
	settings.minorVersion = 3;
	// settings.attributeFlags = sf::ContextSettings::Core;

	sf::RenderWindow window;
	window.create(sf::VideoMode(1920, 1080, 32), "OpenGl Engine", sf::Style::Titlebar | sf::Style::Close, settings);
	// window.setVerticalSyncEnabled(true);
	window.setActive();
	window.setFramerateLimit(60);

	glEnable(GL_DEPTH_TEST);
	// glDepthMask(GL_TRUE);
	// glDepthFunc(GL_LEQUAL);
	// glDepthRange(1.0f, 0.0f);

	(void *)ImGui::SFML::Init(window);
	// ImGui::GetIO().IniFilename = "";

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{ // включить glew
		std::cout << "Error:: glew not init =(" << std::endl;
		return -1;
	}

	auto shaderProgram = ShaderLoader::getInstance().load(".\\res\\shaders\\shader");

	std::vector<Vertex> vertices = {
		// координаты       				 // текстурные координаты
		Vertex{Vector3(-0.5f, -0.5f, -0.5f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)},
		Vertex{Vector3(0.5f, -0.5f, -0.5f), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)},
		Vertex{Vector3(0.5f, 0.5f, -0.5f), Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f)},
		Vertex{Vector3(0.5f, 0.5f, -0.5f), Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f)},
		Vertex{Vector3(-0.5f, 0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f)},
		Vertex{Vector3(-0.5f, -0.5f, -0.5f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)},

		Vertex{Vector3(-0.5f, -0.5f, 0.5f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)},
		Vertex{Vector3(0.5f, -0.5f, 0.5f), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)},
		Vertex{Vector3(0.5f, 0.5f, 0.5f), Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f)},
		Vertex{Vector3(0.5f, 0.5f, 0.5f), Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f)},
		Vertex{Vector3(-0.5f, 0.5f, 0.5f), Vector2(0.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f)},
		Vertex{Vector3(-0.5f, -0.5f, 0.5f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)},

		Vertex{Vector3(-0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f)},
		Vertex{Vector3(-0.5f, 0.5f, -0.5f), Vector2(1.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f)},
		Vertex{Vector3(-0.5f, -0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f)},
		Vertex{Vector3(-0.5f, -0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f)},
		Vertex{Vector3(-0.5f, -0.5f, 0.5f), Vector2(0.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f)},
		Vertex{Vector3(-0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f)},

		Vertex{Vector3(0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f)},
		Vertex{Vector3(0.5f, 0.5f, -0.5f), Vector2(1.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f)},
		Vertex{Vector3(0.5f, -0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f)},
		Vertex{Vector3(0.5f, -0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f)},
		Vertex{Vector3(0.5f, -0.5f, 0.5f), Vector2(0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f)},
		Vertex{Vector3(0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f)},

		Vertex{Vector3(-0.5f, -0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)},
		Vertex{Vector3(0.5f, -0.5f, -0.5f), Vector2(1.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)},
		Vertex{Vector3(0.5f, -0.5f, 0.5f), Vector2(1.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)},
		Vertex{Vector3(0.5f, -0.5f, 0.5f), Vector2(1.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)},
		Vertex{Vector3(-0.5f, -0.5f, 0.5f), Vector2(0.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)},
		Vertex{Vector3(-0.5f, -0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)},

		Vertex{Vector3(-0.5f, 0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)},
		Vertex{Vector3(0.5f, 0.5f, -0.5f), Vector2(1.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)},
		Vertex{Vector3(0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)},
		Vertex{Vector3(0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)},
		Vertex{Vector3(-0.5f, 0.5f, 0.5f), Vector2(0.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)},
		Vertex{Vector3(-0.5f, 0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)},
	};

	std::vector<Object> objects;
	Object obj1;
	obj1.set_name("pistol");
	obj1.set_model(".\\res\\models\\pistol_colt\\colt low polyfbx.fbx");
	obj1.set_texture(".\\res\\models\\pistol_colt\\colt_low_polyfbx_m1911_BaseColor.png");
	obj1.set_texture_norm(".\\res\\models\\pistol_colt\\colt_low_polyfbx_m1911_Normal.png");
	objects.push_back(obj1);

	Object obj2;
	obj2.set_name("axe");
	obj2.set_model(".\\res\\models\\axe\\axe_hp.fbx");
	obj2.set_texture(".\\res\\models\\axe\\AXE_vertexcolor.png");
	obj2.set_texture_norm(".\\res\\models\\axe\\AXE_normal.png");
	objects.push_back(obj2);

	// VertexArray VAO;
	// VAO.bind();

	// VertexBuffer VBO;
	// VBO.bind(vertices);

	// glGenBuffers(1, &EBO);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// VBO.bindAttribute(0, 3, sizeof(Vertex), offsetof(Vertex, pos));
	// VBO.bindAttribute(1, 2, sizeof(Vertex), offsetof(Vertex, uv));
	// VBO.bindAttribute(2, 3, sizeof(Vertex), offsetof(Vertex, norm));

	// VAO.unbind();
	// VBO.unbind();

	auto cameraPos = Vector3(3.0f, 3.0f, 3.0f);

	auto lightPos = Vector3(0.0f, 0.0f, 5.0f);
	auto lightAmb = Vector3(0.2f, 0.2f, 0.2f);
	auto lightDiff = Vector3(0.5f, 0.5f, 0.5f);
	auto lightSpec = Vector3(1.0f, 1.0f, 1.0f);

	auto materialSpec = Vector3(0.5f, 0.5f, 0.5f);
	auto materialShine = 32.0f;

	bool isGo = true;

	Vector3 translate_vec(0.0f);

	sf::Clock deltaClock;
	while (isGo)
	{
		sf::Event windowEvent;

		while (window.pollEvent(windowEvent))
		{
			ImGui::SFML::ProcessEvent(windowEvent);

			switch (windowEvent.type)
			{
			case sf::Event::Closed:
				isGo = false;
				break;
			case sf::Event::Resized:
				glViewport(0, 0, windowEvent.size.width, windowEvent.size.height);
			default:
				break;
			}
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);				//отчистка экрана
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //отчистка экрана

		glEnable(GL_DEPTH_TEST);

		// texture->bind(0);
		// textureNorm->bind(1);

		shaderProgram->bind();

		// VAO.bind();

		Mat4 view = CreateViewMatrix(cameraPos, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
		Mat4 proj = perspective(radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		shaderProgram->setUniformVec3("light.ambient", lightAmb);
		shaderProgram->setUniformVec3("light.diffuse", lightDiff);
		shaderProgram->setUniformVec3("light.specular", lightSpec);
		shaderProgram->setUniformVec3("light.position", lightPos);

		shaderProgram->setUniformInt("material.diffuse", 0);
		shaderProgram->setUniformInt("material.normalMap", 1);
		shaderProgram->setUniformVec3("material.specular", materialSpec);
		shaderProgram->setUniformFloat("material.shininess", materialShine);

		shaderProgram->setUniformVec3("viewPos", cameraPos);

		shaderProgram->setUniformMat4("view", view);
		shaderProgram->setUniformMat4("projection", proj);

		for (auto &obj_ : objects)
		{
			obj_.bind();
			Mat4 translation = translationMat(obj_.get_position());
			Mat4 rotation = rotateMat(obj_.get_rotation().spin_vec, radians(obj_.get_rotation().spin_deg));
			Mat4 scale = scaleMat(obj_.get_scale());
			Mat4 model = CraeteModelMatrix(translation, rotation, scale);
			shaderProgram->setUniformMat4("model", model);
			obj_.draw();
			obj_.unbind();
		}

		shaderProgram->unbind();

		ImGui::SFML::Update(window, deltaClock.restart());
		ImGui::Begin("Window title");

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
				static char selectedItem[255];
				static int selected_ind = -1;
				bool selected[objects.size()];

				static float scaleV[3];
				static float spinV[3];
				static float deg;
				static float transV[3];

				if (selected_ind != -1)
				{
					selected[selected_ind] = true;
					strcpy(selectedItem, objects[selected_ind].get_name().c_str());
				}

				if (ImGui::BeginCombo("ObjectList", selectedItem))
				{

					for (int i = 0; i < objects.size(); i++)
					{
						if (ImGui::Selectable(objects[i].get_name().c_str(), &selected[i]))
						{
							selected_ind = i;

							strcpy(selectedItem, objects[selected_ind].get_name().c_str());

							{
								auto temp = objects[selected_ind].get_scale();
								scaleV[0] = temp.x;
								scaleV[1] = temp.y;
								scaleV[2] = temp.z;
							}

							{
								auto temp = objects[selected_ind].get_rotation();
								spinV[0] = temp.spin_vec.x;
								spinV[1] = temp.spin_vec.y;
								spinV[2] = temp.spin_vec.z;
								deg = temp.spin_deg;
							}

							{
								auto temp = objects[selected_ind].get_position();
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
					std::string obj_name;
					std::string obj_model_path;
					std::string obj_texture_path;
					std::string obj_normal_path;

					if (ImGui::Button("Choose Modes"))
					{
						ImGuiFileDialog::Instance()->OpenModal("ChooseModel", "Choose File", "Model files (*.fbx *.obj){.fbx,.obj}", ".\\res\\");
					}
					if (ImGuiFileDialog::Instance()->Display("ChooseModel"))
					{
						if (ImGuiFileDialog::Instance()->IsOk())
						{
							std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
							std::string fileName = ImGuiFileDialog::Instance()->GetCurrentFileName();
							std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
						}
						ImGuiFileDialog::Instance()->Close();
					}

					if (ImGui::Button("Choose Texture"))
					{
						ImGuiFileDialog::Instance()->OpenModal("ChooseTexture", "Choose File", "Image files (*.png *.gif *.jpg *.jpeg){.png,.gif,.jpg,.jpeg}", ".\\res\\");
					}
					if (ImGuiFileDialog::Instance()->Display("ChooseTexture"))
					{
						if (ImGuiFileDialog::Instance()->IsOk())
						{
							std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
							std::string fileName = ImGuiFileDialog::Instance()->GetCurrentFileName();
							std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
						}
						ImGuiFileDialog::Instance()->Close();
					}

					if (ImGui::Button("Choose Normal Texture"))
					{
						ImGuiFileDialog::Instance()->OpenModal("ChooseNormal", "Choose File", "Image files (*.png *.gif *.jpg *.jpeg){.png,.gif,.jpg,.jpeg}", ".\\res\\");
					}
					if (ImGuiFileDialog::Instance()->Display("ChooseNormal"))
					{
						if (ImGuiFileDialog::Instance()->IsOk())
						{
							std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
							std::string fileName = ImGuiFileDialog::Instance()->GetCurrentFileName();
							std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
						}
						ImGuiFileDialog::Instance()->Close();
					}

					if (ImGui::Button("Create"))
					{
					}
					ImGui::SameLine();
					if (ImGui::Button("Close"))
					{
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}

				if (selected_ind != -1)
				{
					if (ImGui::InputText("Change name", &selectedItem[0], sizeof(selectedItem)))
					{
						objects[selected_ind].set_name(selectedItem);
					}

					ImGui::LabelText("", "Scale obj");
					{
						if (ImGui::SliderFloat("Scale prop", &scaleV[0], -10.0f, 10.0f))
						{
							scaleV[1] = scaleV[0];
							scaleV[2] = scaleV[0];
							objects[selected_ind].set_scale(Vector3(scaleV[0], scaleV[1], scaleV[2]));
						}
						if (ImGui::SliderFloat3("Scale", scaleV, -10.0f, 10.0f))
						{
							objects[selected_ind].set_scale(Vector3(scaleV[0], scaleV[1], scaleV[2]));
						}
					}
					ImGui::LabelText("", "Spin obj");
					{
						if (ImGui::SliderFloat3("Spin vector", spinV, -10.0f, 10.0f) || ImGui::SliderFloat("Degree", &deg, -360.0f, 360.0f))
						{
							objects[selected_ind].set_rotation(Vector3(spinV[0], spinV[1], spinV[2]), deg);
						}
					}
					ImGui::LabelText("", "Translate obj");
					{
						if (ImGui::SliderFloat3("Translate vector", transV, -10.0f, 10.0f))
						{
							objects[selected_ind].set_position(Vector3(transV[0], transV[1], transV[2]));
						}
					}
				}
			}

			if (tabb == 1)
			{
				static float lightPosV[3] = {0.0f, 0.0f, 0.0f};
				ImGui::SliderFloat("Shininess", &materialShine, 0.0f, 32.0f);
				if (ImGui::SliderFloat3("LightPos", lightPosV, -10.0f, 10.0f))
				{
					lightPos[0] = lightPosV[0];
					lightPos[1] = lightPosV[1];
					lightPos[2] = lightPosV[2];
				}
			}
			if (tabb == 2)
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
					if (is_fullscreen)
					{
						window.create(sf::VideoMode::getFullscreenModes()[0], "First Window", sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen, settings);
					}
					else
					{
						window.create(sf::VideoMode(window.getSize().x, window.getSize().y, 32), "First Window", sf::Style::Titlebar | sf::Style::Close, settings);
					}
					window.setSize(res_listbox_items_[res_listbox_item_current]);
					window.setTitle(title);
				}
			}
		}
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();

		ImGui::SFML::Render(window);

		window.display();
	}
	window.close();

	ImGui::SFML::Shutdown();
	return 0;
}

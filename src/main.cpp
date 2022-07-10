#include <iostream>
#include <utility>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui-sfml.h"

#include "math/math.hpp"
#include "math/glm_test.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ImGuiFileDialog/ImGuiFileDialog.h"

#include "app.h"

int main()
{
	auto app = std::make_unique<App>("OpenGL Engine");

	app->loop();

	// ImGui::SFML::Shutdown();
	return 0;
}

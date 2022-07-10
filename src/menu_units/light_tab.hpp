#include "menu.h"

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

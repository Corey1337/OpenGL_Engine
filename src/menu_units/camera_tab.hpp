#include "menu.h"

void Menu::camera_tab(std::shared_ptr<Camera> camera)
{
    auto temp = camera->get_position();
    static float posV[3];
    posV[0] = temp[0];
    posV[1] = temp[1];
    posV[2] = temp[2];

    temp = camera->get_direction();
    static float dirV[3];
    dirV[0] = temp[0];
    dirV[1] = temp[1];
    dirV[2] = temp[2];

    ImGui::LabelText("", "Camera position");
    if (ImGui::SliderFloat3("Position", posV, -10.0f, 10.0f))
    {
        camera->set_position(Vector3(posV[0], posV[1], posV[2]));
    }
    ImGui::LabelText("", "Camera direction");
    if (ImGui::SliderFloat3("Direction", dirV, -10.0f, 10.0f))
    {
        camera->set_direction(Vector3(dirV[0], dirV[1], dirV[2]));
    }
}
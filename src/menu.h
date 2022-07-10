#include <string>
#include <memory>

#include "imgui.h"
#include "imgui-sfml.h"
#include "imgui_internal.h"
#include "ImGuiFileDialog/ImGuiFileDialog.h"

#include "scene.h"

#include <SFML/Graphics.hpp>

class Menu
{
public:
    Menu(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Scene> scene);

    void render();

    ~Menu(){ ImGui::SFML::Shutdown(); }

private:
    static Menu *sInstance;

    void ToggleButton(const char *str_id, bool *v);

    void objects_tab(std::shared_ptr<std::vector<Object *>> objects);
    void light_tab(std::shared_ptr<Light> light);
    void setting_tab();

    std::shared_ptr<sf::Clock> deltaClock;
    std::shared_ptr<sf::RenderWindow> win_;
    std::shared_ptr<Scene> scene_;
};
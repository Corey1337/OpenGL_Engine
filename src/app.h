#include <string>
#include <SFML/Graphics.hpp>

#include "menu.h"
#include "GL.h"
#include "scene.h"

class App
{
public:
    App(const std::string &app_name);

    static App &Instanse() { return *sInstanse; }

    void loop();

    void event();

    std::shared_ptr<Scene>* get_scene();

private:
    static App *sInstanse;

    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<Menu> menu;
    std::shared_ptr<GL> gl;
    std::shared_ptr<Scene> scene;
};
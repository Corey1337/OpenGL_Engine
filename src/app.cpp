#include "app.h"

App::App(const std::string &app_name)
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 4;
    settings.minorVersion = 3;
    // settings.attributeFlags = sf::ContextSettings::Core;

    window = std::make_shared<sf::RenderWindow>();

    window->create(sf::VideoMode(1920, 1080, 32), app_name, sf::Style::Titlebar | sf::Style::Close, settings);
    // window.setVerticalSyncEnabled(true);
    window->setActive();
    window->setFramerateLimit(60);
    gl = std::make_shared<GL>();
    scene = std::make_shared<Scene>();
    menu = std::make_shared<Menu>(window, scene);
}

void App::loop()
{
    while (window->isOpen())
    {
        event();

        gl->render();

        scene->render();

        menu->render();

        window->display();
    }
    
    menu->~Menu();
    window->close();
}

void App::event()
{
    sf::Event windowEvent;

    while (window->pollEvent(windowEvent))
    {
        ImGui::SFML::ProcessEvent(windowEvent);

        switch (windowEvent.type)
        {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::Resized:
            glViewport(0, 0, windowEvent.size.width, windowEvent.size.height);
        default:
            break;
        }
    }
}

std::shared_ptr<Scene>* App::get_scene()
{
    return &scene;
}

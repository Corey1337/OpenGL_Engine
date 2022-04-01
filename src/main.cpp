#include <iostream>
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include "utils/shaderLoader.h"
#include "glm/vec2.hpp"
#include "math/vec2.hpp"

using namespace std;

int main() {

	sf::ContextSettings settings;
	settings.depthBits = 24; // количество битов буффера глубины
	settings.stencilBits = 8; //количество битов буфера трафарета
	settings.majorVersion = 4;
	settings.minorVersion = 3;
	settings.attributeFlags = sf::ContextSettings::Core;

	sf::Window window(sf::VideoMode(800, 600, 32), "First Window",
		sf::Style::Titlebar | sf::Style::Close);

	glewExperimental = GL_TRUE; // включить все современные функции ogl

	if (GLEW_OK != glewInit()) { // включить glew
		cout << "Error:: glew not init =(" << endl;
		return -1;
	}

	bool isGo = true;

    auto shaderProgram = LoadShaders(".\\res\\shaders\\shader.vs", ".\\res\\shaders\\shader.fs");

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 0.1f, //лн
        -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f, //лв
        0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 1.0f, //пн
        0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 1.0f //пв
    };

    unsigned int indices[] = { //вершины квадрата соединяем
        0, 1, 2, //первый треуг
        1, 2, 3 //второй треуг
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO); //сгенерили id для массивов вершин (1 шт)
    glBindVertexArray(VAO); // связали массив с opengl

    glGenBuffers(1, &VBO); //буфер данных размером 1
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //связали буфер с opengl
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //прокинули массив в opengl

    glGenBuffers(1, &EBO); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0); // прописали параметры для объекта
    glEnableVertexAttribArray(0); //layout y позиции 0

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float))); // прописали параметры для объекта
    glEnableVertexAttribArray(1); //цвет

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); //снять бинд с массивов


	while (isGo) {
		sf::Event windowEvent;

		while (window.pollEvent(windowEvent)) { // обработка ивентов
			switch (windowEvent.type)
			{
			case sf::Event::Closed:
				isGo = false;
				break;
			default:
				break;
			}
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //отчистка экрана
		glClear(GL_COLOR_BUFFER_BIT); //отчистка экрана

        glUseProgram(shaderProgram); //прокидываем шейдерную прогу
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//...

		window.display();
	}


	window.close();
	return 0;
}
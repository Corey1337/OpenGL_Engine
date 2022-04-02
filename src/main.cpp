#include <iostream>
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include "utils/shaderLoader.h"
#include "glm/vec2.hpp"
#include "math/math.hpp"
#include "glm/mat3x3.hpp"
#include "stb/stb_image.h"

using namespace std;

int main() {

	
	// Mat4 a({
	// 	{2, 3, 4, 1},
	// 	{4, 5, 6, 1},
	// 	{4, 5, 7, 1},
	// 	{4, 5, 7, 3},
	// });

	// auto c = inverse(a);

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

    auto shaderProgram = LoadShaders(".\\res\\shaders\\shader.vs", ".\\res\\shaders\\shader.fs");

    // float vertices[] = {
    //     -0.5f, -0.5f, 0.0f,  0.0, 0.0, //лн
    //     -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, //лв
    //     0.5f, 0.5f, 0.0f,  1.0f, 1.0f,//пв
    //     0.5f, -0.5f, 0.0f,  1.0f, 0.0f//пн квадрат
    // };

    // unsigned int indices[] = { //вершины квадрата соединяем
    //     0, 1, 3, //первый треуг
    //     1, 2, 3 //второй треуг
    // };

	float vertices [] = {
		// координаты        // текстурные координаты
	   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO); //сгенерили id для массивов вершин (1 шт)
    glBindVertexArray(VAO); // связали массив с opengl

    glGenBuffers(1, &VBO); //буфер данных размером 1
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //связали буфер с opengl
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //прокинули массив в opengl

    //glGenBuffers(1, &EBO); 
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0); // прописали параметры для объекта
    glEnableVertexAttribArray(0); //layout y позиции 0

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3 * sizeof(float))); // прописали параметры для объекта
    glEnableVertexAttribArray(1); //цвет

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); //снять бинд с массивов

	stbi_set_flip_vertically_on_load(true);
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(".\\res\\img\\aska.jpg", &width, &height, &nrChannels, 0);
	if(data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else{
		cout << "Cant load img" << endl;
	}

	stbi_image_free(data);

	bool isGo = true;

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

		glBindTexture(GL_TEXTURE_2D, texture);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//...
		window.display();
	}


	window.close();
	return 0;
}
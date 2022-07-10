#include "GL.h"

GL::GL()
{
    glEnable(GL_DEPTH_TEST);
    // glDepthMask(GL_TRUE);
    // glDepthFunc(GL_LEQUAL);
    // glDepthRange(1.0f, 0.0f);

    glewExperimental = GL_TRUE;

    if (GLEW_OK != glewInit())
    { // включить glew
        std::cout << "Error:: glew not init =(" << std::endl;
        // return -1;
    }

    float temp[4] = {0.2f, 0.3f, 0.3f, 1.0f};
    set_sky_color(temp);
}

void GL::render()
{
    glClearColor(SkyColor[0], SkyColor[1], SkyColor[2], SkyColor[3]);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
}

void GL::set_sky_color(float color[4])
{
    SkyColor[0] = color[0];
    SkyColor[1] = color[1];
    SkyColor[2] = color[2];
    SkyColor[3] = color[3];
}
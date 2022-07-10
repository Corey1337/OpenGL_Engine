#include <GL/glew.h>
#include <iostream>

class GL
{
public:
    GL();
    void render();
    void set_sky_color(float color[4]);
private:
    float SkyColor[4];
};
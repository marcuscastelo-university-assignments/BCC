#include <iostream>
#include <GL/glut.h>

void drawWindow() {

}

int main(int argc, char const *argv[])
{
    glutCreateWindow("Teste");
    glutDisplayFunc(drawWindow);
    glutMainLoop();
    return 0;
}

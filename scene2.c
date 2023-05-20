#include <GL/glut.h>
#include <math.h>
#include <windows.h>

GLfloat angulo = 0.00;
void display();

void lighting()
{
    float position[4] = {-1, 4, -1, 1.0f};
    float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    //float dim_white[4] = {0.2f, 0.2f, 0.2f, 1.0f};
    float black[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float global_ambient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    //glLightfv(GL_LIGHT0, GL_AMBIENT, dim_white);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

void idle(void)
{
    angulo += 0.05;
    display();
}

void desenharBules()
{
    glMatrixMode(GL_MODELVIEW);
    //ILUMINACAO
    float kd[4] = {0.5f, 0.6f, 0.0f, 1.0f};
    float ks[4] = {0.9f, 0.9f, 0.9f, 1.0f};
    float ns = 120.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
    glMaterialf(GL_FRONT, GL_SHININESS, ns);

    //VIEWPORTS
    glViewport(0, 300, 450, 300);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(25, 1.5, 0.1, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 2.0f,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    glRotatef(angulo, 0, 1, 0);
    glutSolidTeapot(0.2f);

    glViewport(0, 0, 450, 300);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(5, 1.5, 0.1, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 10.0f, 0.1f,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    glRotatef(angulo, 0, 1, 0);
    glutSolidTeapot(0.2f);

    glViewport(450, 300, 450, 300);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, 1.5, 0.1, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.6f, 0.0f, 0.0f,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    glRotatef(angulo, 0, 1, 0);
    glutSolidTeapot(0.2f);

    glViewport(450, 0, 450, 300);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40, 1.5, 0.1, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.6f, 0.5f, 1.0f,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    glRotatef(angulo, 0, 1, 0);
    glutSolidTeapot(0.2f);

    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    desenharBules();

    glFlush();
}

int init()
{
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
    glClearColor(0.5, 0.5, 0.5, 0.5);
    glEnable(GL_DEPTH_TEST);
    lighting();
    return 0;
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(900, 600);
    glutCreateWindow("Scene 2");
    glEnable(GL_DEPTH_TEST);

    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}

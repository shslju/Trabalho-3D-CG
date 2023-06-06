#include <GL/glut.h>
#include <math.h>
#include <windows.h>

GLfloat angulo = 0.00;
void display();

void lighting()
{
    // Vetores com valores dos elementos usados no glLight*
    float position[4] = {-1, 4, -1, 1.0f};
    float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float dim_white[4] = {0.2f, 0.2f, 0.2f, 1.0f};

    // Iluminação ambiente global independente de todas as outras fontes
    float global_ambient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, dim_white);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    // Permite o funcionamento
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

// Funcao de callback da rotacao
void idle(void)
{
    angulo += 0.05;
    display();
}

void desenharBules()
{
    glMatrixMode(GL_MODELVIEW);
    // Iluminacao da cena
    float kd[4] = {0.5f, 0.6f, 0.0f, 1.0f};
    float ks[4] = {0.9f, 0.9f, 0.9f, 1.0f};
    float ns = 120.0f;

    // Definindo propriedades da superfície
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
    glMaterialf(GL_FRONT, GL_SHININESS, ns);

    // VIEWPORTS
    glViewport(0, 300, 450, 300); // Superior esquerda
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(25, 1.5, 0.1, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 2.0f, // Pos da camera
              0.0, 0.0, 0.0,    // Onde a camera aponta
              0.0, 1.0, 0.0);   // Vetor view-up
    glRotatef(angulo, 0, 1, 0);
    glutSolidTeapot(0.2f);

    glViewport(0, 0, 450, 300); // Inferior esquerda
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

    glViewport(450, 300, 450, 300); // Superior direita
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

    glViewport(450, 0, 450, 300); // Inferior direita
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
    glClearColor(0.5, 0.5, 0.5, 0.5);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
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
    glutIdleFunc(idle); //Funcao da rotacao
    glutMainLoop();
    return 0;
}

#include <windows.h>
#include <stdio.h>
#include <gl/glut.h>
int ambient_lighting_enabled = 1;
int lighting0_enabled = 0;
float t_y = -1;
GLfloat angle = 30;
void lighting()
{
    float position[4] = {2.0f, 2.0f, 2.0f, 0.0f};
    float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    float global_ambient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    if (ambient_lighting_enabled)
    {
        // remoção de superfícies ocultas
        // glEnable(GL_CULL_FACE);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

void init()
{
    glClearColor(0.60f, 0.60f, 0.60f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    lighting();
}

void changeVision()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angle, 1, 0.1, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2, 2, 2, 0, 0, 0, 0, 1, 0);
}

void GerenciaTeclado(unsigned char key, int x, int y)
{
    printf("d");
    switch (key)
    {
    case 'd':
        // x_ok++;
        break;
    case 'a':
        // x_ok--;
        break;
    case 'w':
        // zoom
        if (angle >= 10)
        {
            angle -= 5;
        }
        break;
    case 's':
        // tirar zoom hihi
        if (angle <= 130)
        {
            angle += 5;
        }
        break;
    case 'k':
        ambient_lighting_enabled = 1;
    case 'j':
        ambient_lighting_enabled = 0;
    default:
        break;
    }
    // printf("%f %f\n", x_ok, t_y);
    changeVision();
    glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    float w_kd[4] = {1.0f, 0.0f, 0.0f, 1.0f};
    float w_ks[4] = {0.2f, 0.2f, 0.2f, 1.0f};
    float w_ns = 1.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, w_kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, w_ks);
    glMaterialf(GL_FRONT, GL_SHININESS, w_ns);
    glBegin(GL_QUADS);
    // chao
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1, 0, -1);
    glVertex3f(1, 0, -1);
    glVertex3f(1, 0, 1);
    glVertex3f(-1, 0, 1);
    // parede rsrs
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-1, 0, -1);
    glVertex3f(1, 0, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);
    // parede rsrs
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, 0, 1);
    glVertex3f(-1, 0, -1);
    glVertex3f(-1, 1, -1);
    glEnd();
    // TEAPOT LIGHT COEFFICIENTS
    float kd[4] = {0.0f, 0.65f, 0.80f, 1.0f};
    float ks[4] = {0.9f, 0.9f, 0.9f, 1.0f};
    float ns = 120.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
    glMaterialf(GL_FRONT, GL_SHININESS, ns);
    glMatrixMode(GL_MODELVIEW);
    // TEAPOT TRANSLATION
    GLfloat translation_teapot[3] = {-0.25f, 0.15f, 0.40f};
    glPushMatrix();
    glTranslatef(translation_teapot[0], translation_teapot[1], translation_teapot[2]);
    glRotatef(25, 0, 1, 0);
    glutSolidTeapot(0.2f);
    glPopMatrix();
    // SPHERE LIGHT COEFFICIENTS
    float kd_s[4] = {1.0f, 0.7f, 0.0f, 1.0f};
    float ks_s[4] = {0.1f, 0.1f, 0.1f, 1.0f};
    float ns_s = 10.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd_s);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks_s);
    glMaterialf(GL_FRONT, GL_SHININESS, ns_s);
    glMatrixMode(GL_MODELVIEW);
    // SPHERE TRANSLATION
    GLfloat translation_sphere[3] = {-0.25f, 0.15f, -0.25f};
    glPushMatrix();
    glTranslatef(translation_sphere[0], translation_sphere[1], translation_sphere[2]);
    glutSolidSphere(0.15, 40, 40);
    glPopMatrix();
    // TORUS LIGHT COEFFICIENTS
    float kd_t[4] = {0.55f, 1.0f, 0.0f, 1.0f};
    float ks_t[4] = {0.9f, 0.9f, 0.9f, 1.0f};
    float ns_t = 120.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd_t);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks_t);
    glMaterialf(GL_FRONT, GL_SHININESS, ns_t);
    glMatrixMode(GL_MODELVIEW);
    // TORUS TRANSLATION
    GLfloat translation_torus[3] = {0.40f, 0.15f, 0.40f};
    glPushMatrix();
    glTranslatef(translation_torus[0], translation_torus[1], translation_torus[2]);
    glRotatef(90, 1, 0, 0);
    glutSolidTorus(0.06f, 0.2f, 30, 30);
    glPopMatrix();
    glFlush();
}
int main(int argc, char **argv)
{
    printf("aa");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 0);
    glutInitWindowSize(500, 500);

    glutCreateWindow("trabalho cg rsrsrs");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(GerenciaTeclado);
    glutMainLoop();
}

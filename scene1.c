#include <windows.h>
#include <stdio.h>
#include <gl/glut.h>
int face_culling = 0;
GLfloat x_ok = 1.5f, y_ok = 1.0f, z_ok = 2.0f;
GLfloat angle = 30;

void lighting()
{
    // Declaração da fonte de luz da cena
    float position[4] = {-1, 4, -1, 1.0f};
    float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float black[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float global_ambient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void init()
{
    glClearColor(0.50f, 0.50f, 0.50f, 1.0f);
    // Ocultação de faces ocultas
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    lighting();
}

void gerenciaVisao()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angle, 1, 0.1, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x_ok, y_ok, z_ok, 0, 0, 0, 0, 1, 0);
}

void GerenciaTeclado(unsigned char key, int x, int y)
{
    float additive = 0.5f;
    switch (key)
    {
    case 'd':
        x_ok = x_ok + additive;
        break;
    case 'a':
        x_ok = x_ok - additive;
        break;
    case 's':
        y_ok = y_ok - additive;
        break;
    case 'w':
        y_ok = y_ok + additive;
        break;
    case 'q':
        z_ok = z_ok + additive;
        break;
    case 'e':
        z_ok = z_ok - additive;
        break;
    case 'f':
        if (face_culling)
        {
            face_culling = 0;
        }
        else
        {
            face_culling = 1;
        }
        break;
    case '=':
        // zoom
        if (angle >= 10)
        {
            angle -= 5;
        }
        break;
    case '-':
        // tirar zoom hihi
        if (angle <= 130)
        {
            angle += 5;
        }
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
    gerenciaVisao();
    lighting();
    glutPostRedisplay();
}

void display()
{
    gerenciaVisao();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    lighting();
    // Essa parte é explicada mais a frente
    glFrontFace(GL_CCW);
    // Coeficientes de luz das paredes / chão
    float w_kd[4] = {1.0f, 0.0f, 0.0f, 1.0f};
    float w_ks[4] = {1.0f, 0.01f, 0.01f, 1.0f};
    float w_ns = 1.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, w_kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, w_ks);
    glMaterialf(GL_FRONT, GL_SHININESS, w_ns);
    // PRIMEIRA PAREDE
    GLfloat translation_cube[3] = {-5.65f, 0.15f, 0.0f};
    glPushMatrix();
    glScalef(0.1f, 1.5f, 5.65f);
    glTranslatef(translation_cube[0], translation_cube[1], translation_cube[2]);
    glutSolidCube(0.2f);
    glPopMatrix();
    // SEGUNDA PAREDE
    GLfloat translation_cube2[3] = {0.00f, 0.15f, -5.65f};
    glPushMatrix();
    glScalef(5.65f, 1.5f, 0.1f);
    glTranslatef(translation_cube2[0], translation_cube2[1], translation_cube2[2]);
    glutSolidCube(0.2f);
    glPopMatrix();
    // CHAO
    GLfloat translation_cube3[3] = {0.00f, 0.60f, 0.0f};
    glPushMatrix();
    glScalef(5.65f, 0.1f, 5.65f);
    glTranslatef(translation_cube3[0], translation_cube3[1], translation_cube3[2]);
    glutSolidCube(0.2f);
    glPopMatrix();
    // Parte da frente do bule foi indexada em sentido horário
    // então face o culling não funciona normalmente, porque o algoritmo assume
    // que os vértices são indexados em sentido anti-horário.
    glFrontFace(GL_CW);
    // Coeficientes de luz do bule
    float kd[4] = {0.0f, 0.65f, 0.80f, 1.0f};
    float ks[4] = {0.9f, 0.9f, 0.9f, 1.0f};
    float ns = 120.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
    glMaterialf(GL_FRONT, GL_SHININESS, ns);
    glMatrixMode(GL_MODELVIEW);
    // Translação do bule
    GLfloat translation_teapot[3] = {-0.25f, 0.22f, 0.30f};
    glPushMatrix();
    glTranslatef(translation_teapot[0], translation_teapot[1], translation_teapot[2]);
    // glRotatef(50, 0, 1, 0);
    glutSolidTeapot(0.2f);
    glPopMatrix();

    glFrontFace(GL_CCW);
    // Coeficientes de luz da esfera
    float ka_s[4] = {1.0f, 0.6f, 0.0f, 1.0f};
    float kd_s[4] = {1.0f, 0.6f, 0.0f, 1.0f};
    float ks_s[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float ns_s = 10.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT, ka_s);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, kd_s);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks_s);
    glMaterialf(GL_FRONT, GL_SHININESS, ns_s);
    glMatrixMode(GL_MODELVIEW);
    // Translação da esfera
    GLfloat translation_sphere[3] = {-0.25f, 0.20f, -0.25f};
    glPushMatrix();
    glTranslatef(translation_sphere[0], translation_sphere[1], translation_sphere[2]);
    glutSolidSphere(0.15, 40, 40);
    glPopMatrix();

    // Coeficientes de luz do donut
    float kd_t[4] = {0.55f, 1.0f, 0.0f, 1.0f};
    float ks_t[4] = {0.55f, 0.9f, 0.9f, 1.0f};
    float ns_t = 120.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd_t);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks_t);
    glMaterialf(GL_FRONT, GL_SHININESS, ns_t);
    glMatrixMode(GL_MODELVIEW);
    // Translação e rotação do donut
    GLfloat translation_torus[3] = {0.40f, 0.20f, 0.10f};
    glPushMatrix();
    glTranslatef(translation_torus[0], translation_torus[1], translation_torus[2]);
    glRotatef(90, 1, 0, 0);
    glutSolidTorus(0.06f, 0.2f, 30, 30);
    glPopMatrix();
    // Desenha tudo
    glFlush();
}
int main(int argc, char **argv)
{
    printf("aa");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(200, 0);
    glutInitWindowSize(500, 500);

    glutCreateWindow("trabalho cg rsrsrs");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(GerenciaTeclado);
    glutMainLoop();
}

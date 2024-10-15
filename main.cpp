#include <GL/freeglut_std.h>
#include <GL/glut.h>

GLfloat camX = 20.0f, camY = 20.0f, camZ = 20.0f; // Posición inicial de la cámara

GLUquadricObj *p = gluNewQuadric();
float angTronco = 0;
float angBrazo11 = 0;
float angBrazo12 = 0;
float angBrazo13 = 0;
float angBrazo14 = 0;
float angEsf1 = 0;
float angEsf2 = 0;
float angEsf3 = 0;


void inicializar()
{
    glClearColor(0.7,0.7,0.7,0.0);
    glEnable(GL_DEPTH_TEST);
    gluQuadricDrawStyle(p,GLU_LINE);
}

void graficarEjes()
{
    glColor3f(0,0,0);
    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(50,0,0);

        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,50,0);

        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,50);
    glEnd();
}

void graficar()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ, 0, 0, 0, 0, 1, 0);  // Uso de las variables de cámara

    graficarEjes();

    // Tronco
    glPushMatrix();//1
        glColor3f(1,1,0.5);
        glRotatef(angTronco,0,1,0);
        glTranslatef(0,0,0);
        glScalef(2,1,3);
        glutSolidCube(4);

        // Brazo 1.1
        glPushMatrix();//1
            glColor3f(0.5,0.3,0.5);
            glTranslatef(0,0.9,1);
            glRotatef(angBrazo11,1,0,0);
            glRotatef(-75,1,0,0);
            gluCylinder(p, 0.5, 0.5, 10, 16, 16);

            glPushMatrix();//2 esfera
                glTranslatef(0,0,10);
                glRotatef(angEsf1, 0,0,1);
                glutWireSphere(0.5,16,16);

                glPushMatrix();//3
                // BRazo 1.2
                    glColor3f(0,1,0);
                    glTranslatef(0,0,0);
                    glRotatef(angBrazo12,1,0,0);
                    glRotatef(45,1,0,0);
                    gluCylinder(p, 0.5, 0.5, 5, 16, 16);

                    glPushMatrix();//4 esfera
                        glTranslatef(0,0,5);
                        glRotatef(angEsf2, 0, 0, 1);
                        glutWireSphere(0.5,16,16);

                        glPushMatrix();//5
                        //BRazo1.3
                            glColor3f(0,0,1);
                            glTranslatef(0,0,0);
                            glRotatef(90,1,0,0);
                            glRotatef(angBrazo13, 1, 0, 0);
                            gluCylinder(p, 0.5, 0.5, 4, 16, 16);

                            glPushMatrix();//6
                                glTranslatef(0,0,4);
                                glRotatef(angEsf3, 0, 0, 1);
                                glutWireSphere(0.5,16,16);
                                glPushMatrix();//brazo 1.4
                                    glTranslatef(0,0,0);
                                    glRotatef(90,1,0,0);
                                    glScalef(0.5,0.5,0.5);
                                    glRotatef(angBrazo14, 1, 0, 0);
                                    gluCylinder(p, 0.5, 0.5, 4, 16, 16);
                                glPopMatrix();
                            glPopMatrix();//acaba el 6

                        glPopMatrix();//acaba el 5
                    glPopMatrix();//acaba el 4
                glPopMatrix();//acaba el 3
            glPopMatrix();//acaba el 2

        glPopMatrix();//acaba el 1

        // Brazo 2.1
        glPushMatrix();
        glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
}

void redimensionar(int w, int h)
{
    glViewport(0,0,w,h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,(float)w/(float)h,1,100);
}

// Función para mover la cámara con las teclas z, x, c, v, w, q
void moverCamara(unsigned char key, int x, int y)
{
    switch (key) {
        case 'z':  //camara
            camZ -= 1.0f;
            break;
        case 'x':
            camZ += 1.0f;
            break;
        case 'c':
            camY += 1.0f;
            break;
        case 'v':
            camY -= 1.0f;
            break;
        case 'w':
            camX -= 1.0f;
            break;
        case 'q':   //camara
            camX += 1.0f;
            break;
        case 'a':
            angTronco -= 5;
        break;
        case 's':
            angTronco += 5;
        break;
        case 'e':
            angEsf1 -= 5;
        break;
        case 'r':
            angEsf1 += 5;
        break;
        case 'd':
            angBrazo11 += 2.5;
        break;
        case 'f':
            angBrazo11 -= 2.5;
        break;
        case 'g':
            angBrazo12 +=2.5;
        break;
        case 'h':
            angBrazo12 -=2.5;
        break;
        case 't':
            angEsf2 -= 5;
        break;
        case 'y':
            angEsf2 +=5;
        break;
        case 'j':
            angBrazo13 -= 2.5;
        break;
        case 'k':
            angBrazo13 += 2.5;
        break;
        case 'u':
            angEsf3 -= 5;
        break;
        case 'i':
            angEsf3 += 5;
        break;
        case 'n':
            angBrazo14 -= 2.5;
        break;
        case 'm':
            angBrazo14 += 2.5;
        break;

        default:
            break;
    }
    glutPostRedisplay();  // Actualiza la pantalla
}




void rotarBrazo12(int i)
{
    //angBrazo12 = angBrazo12 + 1;
    glutPostRedisplay();
    glutTimerFunc(200, rotarBrazo12, 3);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600,400);
    glutInitWindowPosition(100,200);
    glutCreateWindow("JLPERALTA");
    inicializar();

    glutDisplayFunc(graficar);
    glutReshapeFunc(redimensionar);

    glutKeyboardFunc(moverCamara);  // Asocia la función de teclado

    //glutTimerFunc(500, rotarTronco, 1);
    /*glutTimerFunc(600, rotarBrazo11, 2);
    glutTimerFunc(200, rotarBrazo12, 3);*/

    glutMainLoop();

    return 0;
}


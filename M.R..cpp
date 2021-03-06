﻿
#include <GL/glut.h>
#include <windows.h> 
#include <math.h>
//#ifndef WIN32
//#endif
#include <stdlib.h>
#include <stdio.h>


float distance = 30.0;
float katX = 0.00, katY = 0.00;
bool l1 = false, l2 = false;
#define PI_CONST 3.14159265358979323846
float angles(float alfa) {
    return alfa * (PI_CONST / 180);
}

void cam_position() {
    float camX = distance * sin(angles(katX)) * cos(angles(katY));
    float camY = distance * sin((angles(katY)));
    float camZ = distance * cos((angles(katX))) * cos((angles(katY)));
    float upX = distance * sin(angles(katX)) * cos(angles(katY + 90));
    float upY = distance * sin(angles(katY + 90));
    float upZ = distance * cos((angles(katX))) * cos(angles(katY + 90));
    gluLookAt(camX, camY, camZ, 0.0, 0.0, 0.0, upX, upY, upZ);
}

void leg()
{
    // nogi tak jak podstawa mają kolor niebieski
    GLfloat normal_vertex[24 * 3] =
    {
     0.0,0.0,0.0,  2.0,0.0,0.0, 2.0,2.0,0.0, 0.0,2.0,0.0,
     0.0,0.0,0.0,  2.0,0.0,0.0, 2.0,0.0,-2.0, 0.0,0.0,-2.0,
     0.0,0.0,-2.0, 2.0,0.0,-2.0, 2.0,2.0,-2.0, 0.0,2.0,-2.0,
     0.0,2.0,0.0,  2.0,2.0,0.0, 2.0,2.0,-2.0, 0.0,2.0,-2.0,
     2.0,0.0,0.0, 2.0,0.0,-2.0, 2.0,2.0,-2.0, 2.0,2.0,0.0,
     0.0,0.0,0.0, 0.0,0.0,-2.0, 0.0,2.0,-2.0, 0.0,2.0,0.0
    };

    GLfloat color[24 * 3] =
    {

    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0
    };

    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, normal_vertex);
    glColorPointer(3, GL_FLOAT, 0, color);


    glDrawArrays(GL_QUADS, 0, 24);
    //poniżej inny sposób rysowania jakby był problem z powyższą linijką kodu
    //static unsigned short wall[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23 };
    //glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, wall);

    glEnd();
}

void cuboid(GLfloat x, GLfloat y, GLfloat z, GLfloat dx, GLfloat dy, GLfloat dz)
{
    glBegin(GL_QUADS);

    //gora - żółty
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(x, y + dy, z);
    glVertex3f(x + dx, y + dy, z);
    glVertex3f(x + dx, y + dy, z + dz);
    glVertex3f(x, y + dy, z + dz);

    //dol - żółty
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(x, y, z);
    glVertex3f(x + dx, y, z);
    glVertex3f(x + dx, y, z + dz);
    glVertex3f(x, y, z + dz);

    //prawa - żółty
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(x + dx, y, z);
    glVertex3f(x + dx, y, z + dz);
    glVertex3f(x + dx, y + dy, z + dz);
    glVertex3f(x + dx, y + dy, z);

    //lewa - żółty
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(x, y, z);
    glVertex3f(x, y, z + dz);
    glVertex3f(x, y + dy, z + dz);
    glVertex3f(x, y + dy, z);

    //przod - zielony
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(x, y, z);
    glVertex3f(x + dx, y, z);
    glVertex3f(x + dx, y + dy, z);
    glVertex3f(x, y + dy, z);

    //tyl - czerwony
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(x, y, z + dz);
    glVertex3f(x + dx, y, z + dz);
    glVertex3f(x + dx, y + dy, z + dz);
    glVertex3f(x, y + dy, z + dz);

    glEnd();
}


void base(GLfloat x, GLfloat y, GLfloat z, GLfloat dx, GLfloat dy, GLfloat dz)
{
    glBegin(GL_QUADS);
    //poniżej został użyty wszędzie kolor niebieski
    //gora
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(x, y + dy, z);
    glVertex3f(x + dx, y + dy, z);
    glVertex3f(x + dx, y + dy, z + dz);
    glVertex3f(x, y + dy, z + dz);

    //dol
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(x, y, z);
    glVertex3f(x + dx, y, z);
    glVertex3f(x + dx, y, z + dz);
    glVertex3f(x, y, z + dz);

    //prawa
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(x + dx, y, z);
    glVertex3f(x + dx, y, z + dz);
    glVertex3f(x + dx, y + dy, z + dz);
    glVertex3f(x + dx, y + dy, z);

    //lewa
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(x, y, z);
    glVertex3f(x, y, z + dz);
    glVertex3f(x, y + dy, z + dz);
    glVertex3f(x, y + dy, z);

    //przod
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(x, y, z);
    glVertex3f(x + dx, y, z);
    glVertex3f(x + dx, y + dy, z);
    glVertex3f(x, y + dy, z);

    //tyl
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(x, y, z + dz);
    glVertex3f(x + dx, y, z + dz);
    glVertex3f(x + dx, y + dy, z + dz);
    glVertex3f(x, y + dy, z + dz);

    glEnd();
}

void slant(GLfloat x, GLfloat y, GLfloat z, GLfloat ddx, GLfloat dkx, GLfloat dy, GLfloat dz)
{
    glBegin(GL_QUADS);

    //gora - żółty
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(x, y + dy, z);
    glVertex3f(x + dkx, y + dy, z);
    glVertex3f(x + dkx, y + dy, z + dz);
    glVertex3f(x, y + dy, z + dz);

    //dol - żółty
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(x + ddx, y, z);
    glVertex3f(x + ddx + dkx, y, z);
    glVertex3f(x + ddx + dkx, y, z + dz);
    glVertex3f(x + ddx, y, z + dz);

    //prawa - żółty
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(x + ddx + dkx, y, z);
    glVertex3f(x + dkx, y + dy, z);
    glVertex3f(x + dkx, y + dy, z + dz);
    glVertex3f(x + ddx + dkx, y, z + dz);

    //lewa - żółty
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(x + ddx, y, z);
    glVertex3f(x, y + dy, z);
    glVertex3f(x, y + dy, z + dz);
    glVertex3f(x + ddx, y, z + dz);

    //przod - zielony
    glColor3f(0.0, 1.0, 0.0);    
    glVertex3f(x + ddx, y, z);
    glVertex3f(x, y + dy, z);
    glVertex3f(x + dkx, y + dy, z);
    glVertex3f(x + ddx + dkx, y, z);

    //tyl - czerwony
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(x + ddx, y, z + dz);
    glVertex3f(x, y + dy, z + dz);
    glVertex3f(x + dkx, y + dy, z + dz);
    glVertex3f(x + ddx + dkx, y, z + dz);

    glEnd();
}

void display()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    gluPerspective(60.0, 1.0, 0.1, 50.0); 
    cam_position();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //pierwsza litera
    
    cuboid(-12.0, 16.0, 2.0, -4.0, -16.0, -4.0);
    cuboid(-6.0, 0.0, 2.0, 4.0, 16.0, -4.0);
     slant(-15.0, 10.0, 2.0, 4.0, 4.0, 6.0, -4.0);
     slant(-7.0, 10.0, 2.0, -4.0, 4.0, 6.0, -4.0);
    
                
    //druga litera
    cuboid(2.0, 0.0, 2.0, 4.0, 16.0, -4.0);
    cuboid(16.0, 12.0, 2.0, -14.0, 4.0, -4.0);
    cuboid(16.0, 12.0, 2.0, -4.0, -4.0, -4.0);
    cuboid(16.0, 8.0, 2.0, -10.0, -4.0, -4.0);
     slant(16.0, 6.0, 2.0, -6.0, -4.0, -6.0, -4.0);

    
    //kula 
    glColor3f(0.0, 1.0, 0.0); 
    GLdouble radius = 2.0;
    GLint slices, stacks;
    slices = stacks = 40;
    glTranslatef(0.0, 2.0, 0.0);
    glutSolidSphere(radius, slices, stacks);

    //podstawa i nogi
    base(-20.0, -6.0, -10.0, 40.0, 4.0, 20.0);
    

    glTranslatef(-20.0, -8.0, 10.0);  
    leg();

    glTranslatef(38.0, 0.0, -18.0);
    leg();

    glTranslatef(0.0, 0.0, 18.0);
    leg();
     
    glTranslatef(-38.0, 0.0, -18.0);
    leg();


    glFlush();
}


void Redisplay(int width, int height)
{
    glViewport(0, 0, width, height);
    display();
}


void klaw1(int key, int x, int y) {
    if (key == GLUT_KEY_UP) katY = (float)((360 + (int)katY + 5) % 360);
    else if (key == GLUT_KEY_DOWN) katY = (float)((360 + (int)katY - 5) % 360);
    else if (key == GLUT_KEY_LEFT) katX = (float)((360 + (int)katX + 5) % 360);
    else if (key == GLUT_KEY_RIGHT) katX = (float)((360 + (int)katX - 5) % 360);
    display();
}
void klaw0(unsigned char key, int x, int y) {
    if (key == '+') distance -= 0.5;
    else if (key == '-') distance += 0.5;

    display();
}

//generowanie okienka
void main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(600,480);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Michał Rodak s439471");
    glutDisplayFunc(display);

    glutReshapeFunc(Redisplay); 
    glutKeyboardFunc(klaw0);
    glutSpecialFunc(klaw1);

    glutMainLoop();
}
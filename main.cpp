#include <string.h>
#include "SOIL.h"

#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include <stdlib.h>
#include <iostream>

#include <math.h>


using namespace std;

int days=0, years=0, Bdays=1; //variables days and years for earth and Bdays for planet B
GLfloat rotatespeed = 0.1;
GLfloat year = 0.0; //degrees
GLfloat day = 0.0;
GLfloat moonrotate = 0.0;
GLfloat moonself = 0.0;
GLfloat moonrotaterate = 2 * rotatespeed;
GLfloat moonselfrotate = 5.0 * rotatespeed;
GLfloat dayrate = 5.0 * rotatespeed;
GLfloat yearrate =  dayrate * rotatespeed;

#define PI 3.14159
GLfloat matrixX[16];
GLfloat matrixY[16];
GLfloat matrixZ[16];
GLfloat x, y, z, w;
//static GLint RotateY=0; /* model rotation Y index*/
//static GLint RotateX=0; /* model rotation X index*/
//static GLint RotateZ=0; /* model rotation X index*/

bool WireFrame= false;

GLuint tex[4]; // Texture pointer
//static void glGenTextures(1,&tex);// Possible to have 1D, 2D and even 3D textures
GLdouble TranslateX,TranslateY,Zoom,RotateX,RotateY,RotateZ;


GLdouble rotate_x=0;
GLdouble rotate_y=0;
GLdouble scale=1;


const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };


/* GLUT callback Handlers */


void CreateFromAxisAngle(GLfloat X, GLfloat Y, GLfloat Z, GLfloat degree)
{
 /* First we want to convert the degrees to radians since the angle is assumed to be in radians*/
GLfloat angle = (GLfloat)((degree / 180.0f) * PI);
 /* Here we calculate the sin( theta / 2) once for optimization */
GLfloat result = (GLfloat)sin( angle / 2.0f );
 /* Calcualte the w value by cos( theta / 2 ) */
w = (GLfloat)cos( angle / 2.0f );
 /* Calculate the x, y and z of the quaternion */
x = (GLfloat)(X * result);
y = (GLfloat)(Y * result);
z = (GLfloat)(Z * result);
}




static void resize(int width, int height)
{
     double Ratio;

   if(width<=height)
            glViewport(0,(GLsizei) (height-width)/2,(GLsizei) width,(GLsizei) width);
    else
          glViewport((GLsizei) (width-height)/2 ,0 ,(GLsizei) height,(GLsizei) height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
gluPerspective (50.0f,1,0.1f, 100.0f);
 }

void textureLoad(char * fileName, GLuint &handle)
{
    int width, height;
    unsigned char *image;

    glBindTexture(GL_TEXTURE_2D, handle);
    image = SOIL_load_image(fileName, &width, &height,0,SOIL_LOAD_RGB);

    if(!image)cout<<" Image file not found "<<endl;
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,image);
    SOIL_free_image_data(image);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);

}









static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,5,10,0.0,0.0,0.0,0.0,1.0,0.0);

    if(WireFrame)
glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Draw Our Mesh In Wireframe Mesh
else
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //Toggle WIRE FRAME

    glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( rotate_y, 0.0, 1.0, 0.0 );
    glScalef ( scale, scale, scale );

    // your code here
                                //creating sun
    glPushMatrix();
    glColor3f(0.9, 0.6, 0.1);
    glutSolidSphere( 1.5, 40, 40);
    glRotatef(years, 0.0, 1.0, 0.0);
    years = (years + 1) % 360;

        glPushMatrix();                 //creating earth
        glTranslatef(2.0, 0.5, 0.0);
        glRotatef(days, 0.0, 1.0, 0.0);
        days = (days + 1) % 360;
        glColor3f (0, 0.5, 2.0);
        glutSolidSphere(0.5, 30, 30);


        glPushMatrix();
            glRotatef(moonrotate,0.0,1.0,0.0);

            glTranslatef(2.0,0.0,0.0);
            glRotatef(-moonrotate,0.0,1.0,0.0);
            glRotatef(moonself,0.0,1.0,0.0);

            glColor3f(0.3,0.3,0.5);
            glutSolidSphere(0.1,8,8);
        glPopMatrix();
        glPopMatrix();
        glPushMatrix();                 //creating planet2
        glTranslatef(3.0, 1.0, 3.0);
        glRotatef(Bdays, 0.0, 1.0, 0.0);
        Bdays = (Bdays + 1) % 360;
        glColor3f (1.0, 1.4, 1);
        glutSolidSphere(0.8, 20, 20);
        glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
    }
}



static void Specialkeys(int key, int x, int y)
{
    switch(key)
    {
     case GLUT_KEY_END:
        scale+= (float) 0.5f;   // to Zoom in by 0.5
        break;
    case GLUT_KEY_HOME:
        scale-= (float) 0.5f;  // to Zoom Out  by 0.5
        break;
    case GLUT_KEY_UP:
        RotateX-=5;            // to run animation in backward loop
        break;
    case GLUT_KEY_DOWN:
        RotateX+=5;            // to run animation in forward loop
        break;
    case GLUT_KEY_LEFT:
        RotateY-=5;            // to run animation in backward loop
        break;
    case GLUT_KEY_RIGHT:
        RotateY+=5;            // to run animation in forward loop
        break;
   }
glutPostRedisplay();
}


static void idle(void)
{
     day += dayrate;
    year += yearrate;
    moonself += moonselfrotate;
    moonrotate += moonrotaterate;

    glutPostRedisplay();
}

static void init(void)
{
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);


    glGenTextures(7,tex);
    glEnable(GL_TEXTURE_2D);
    textureLoad("images/sun.jpg",tex[0]);// reading the images
    textureLoad("images/earthh.jpg",tex[1]);
    textureLoad("images/moon.jpg",tex[2]);
    textureLoad("images/earth.jpg",tex[3]);


}


/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitWindowSize(1200,1200);
    glutInitWindowPosition(50,50);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("SOLAR SYSTEM");
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(Specialkeys);

    glutIdleFunc(idle);
    glutMainLoop();

    return EXIT_SUCCESS;
}

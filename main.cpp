#ifdef __APPLE__
#include <iostream>
#include<stdlib.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include<OpenGL/glu.h>
#else
#include <iostream>
#include<stdlib.h>
#include<GL/glut.h>
#endif

using namespace std;

const float abcd[4][2][2] = {{{0,0},{0,0.16}},{{0.85,0.04},{-0.04,0.85}},{{0.2,-0.26},{0.23,0.22}},{{-0.15,0.28},{0.26,0.24}}};
const float ef[4][2][1] = {{{0},{0}},{{0},{1.6}},{{0},{1.6}},{{0},{0.44}}};

/* Helper method to perform matrix multiplication and addition
 * abcd[i]*{x,y}+ef[i]
 */
void generateFern(float &x, float &y){

    float tempX = x, tempY = y;
    //Generate random number based on probability
    int probability = rand()%100;
    int pIndex;
    static int countPoints = 0;

    if (probability < 85) pIndex = 0;
    else if (probability == 85) pIndex = 1;
    else if (probability > 85 && probability < 93) pIndex = 2;
    else pIndex = 3;

    //Perform abcd[pIndex]*{x,y} + ef[pIndex]

    tempX = abcd[pIndex][0][0]*x + abcd[pIndex][0][1]*y + ef[pIndex][0][0];
    tempY = abcd[pIndex][1][0]*x + abcd[pIndex][1][1]*y + ef[pIndex][1][0];
    x = tempX;
    y = tempY;

    glPointSize(2);
    glColor3f(0,1,0);
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();
    glFlush();
    cout<<countPoints++<<endl;
}


void myinit()
{
/* set up viewing */
/* 500 x 500 window with origin lower left */

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(-10, 10, 0, 20);
      glMatrixMode(GL_MODELVIEW);
}

void display( void )
{
    int j, k;
    glClearColor(1.0, 1.0, 1.0, 1.0); /* white background */
    glClear(GL_COLOR_BUFFER_BIT);  /*clear the window */


/* compute and plots 5000 new points */

    float x = 0, y = 0;

    for(k=0; k<5000; k++)
    {
        //cout<<'('<<x<<','<<y<<')'<<endl;
        float num = rand()%100/100;
        float num2 = rand()%3;
        if(num2==0) glColor3f(num,0,0);
        else if(num2==1) glColor3f(0,num,0);
        else glColor3f(0,0,num);
        generateFern(x,y);
     }
 }

int main(int argc, char** argv)
{

/* Standard GLUT initialization */

    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500); /* 500 x 500 pixel window */
    glutInitWindowPosition(25,25); /* place window top left on display */
    glutCreateWindow("Barnsley Fern"); /* window title */
    glutDisplayFunc(display); /* display callback invoked when window opened */

    myinit(); /* set attributes */

    glutMainLoop(); /* enter event loop */
}

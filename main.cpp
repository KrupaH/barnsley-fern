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

//1
float barnsley_abcd[4][2][2] = {{{0,0},{0,0.16}},{{0.85,0.04},{-0.04,0.85}},{{0.2,-0.26},{0.23,0.22}},{{-0.15,0.28},{0.26,0.24}}};
float barnsley_ef[4][2][1] = {{{0},{0.16}},{{0},{1.6}},{{0},{1.6}},{{0},{0.44}}};
float barnsley_p[4] = {1,85,7,7};

//2
float barnsley_mod_abcd[4][2][2] = {{{0,0},{0,0.2}},{{0.845,0.035},{-0.035,0.82}},{{0.20,-0.31},{0.255,0.245}},{{-0.15,0.24},{0.25,0.20}}};
float barnsley_mod_ef[4][2][1] = {{{0},{-0.12}},{{0},{1.6}},{{0},{0.29}},{{0},{0.68}}};
float barnsley_mod_p[4] = {1,85,7,7};

//3
float cyclo_abcd[4][2][2] = {{{0,0},{0,0.25}},{{0.95,0.005},{-0.005,0.93}},{{0.035,-0.20},{0.16,0.04}},{{-0.04,0.2},{0.16,0.04}}};
float cyclo_ef[4][2][1] = {{{0},{-0.4}},{{-0.002},{0.5}},{{-0.09},{0.02}},{{0.083},{0.12}}};
float cyclo_p[4] = {2,84,7,7};

//4
float culcita_abcd[4][2][2] = {{{0,0},{0,0.16}},{{0.85,0.02},{-0.02,0.83}},{{0.09,-0.28},{0.30,0.11}},{{-0.09,0.28},{0.30,0.09}}};
float culcita_ef[4][2][1] = {{{0},{-0.14}},{{0},{1}},{{0},{0.6}},{{0},{0.7}}};
float culcita_p[4] = {2,84,7,7};

float abcd[4][2][2];
float ef[4][2][1];
float p[4];

int flag=0;
float c;
static float menu;
static float submenu;
char name_var[25]={"Barnsley Fern"};
bool isFirstDisplay = true;

void assignFern(float abcd[4][2][2], float ef[4][2][1], float p[4]){
    for(int i=0 ; i<4 ; i++){
        for(int j=0 ; j<2 ; j++){
            for(int k=0 ; k<2 ; k++){
                ::abcd[i][j][k] = abcd[i][j][k];
            }
            ::ef[i][j][0] = ef[i][j][0];
        }
        ::p[i] = p[i];
    }
}

void changeFern(const int changeLeaf){
    switch(changeLeaf){
        case 1: assignFern(barnsley_abcd, barnsley_ef, barnsley_p);
                strcpy(name_var,"Barnsley Fern");
                glutPostRedisplay();
                break;
        case 2: assignFern(barnsley_mod_abcd, barnsley_mod_ef, barnsley_mod_p);
                strcpy(name_var,"Modified Barnsley Fern");
                glutPostRedisplay();
                break;
        case 3: assignFern(cyclo_abcd, cyclo_ef, cyclo_p);
                strcpy(name_var,"Cyclosorus Fern");
                glutPostRedisplay();
                break;
        case 4: assignFern(culcita_abcd, culcita_ef, culcita_p);
                strcpy(name_var,"Culcita Fern");
                glutPostRedisplay();
                break;
        case 5: exit(0);

    }
}

/* Helper method to perform matrix multiplication and addition
 * abcd[i]*{x,y}+ef[i]
 */
void generateFern(float &x, float &y){

    float tempX = x, tempY = y;
    //Generate random number based on probability
    int probability = rand()%100;
    int pIndex;
    static int countPoints = 0;

    if (probability < p[0]) pIndex = 0;
    else if (probability >= p[0] && probability < (p[0]+p[1])) pIndex = 1;
    else if (probability >= (p[0]+p[1]) && probability < (p[0]+p[1]+p[2])) pIndex = 2;
    else pIndex = 3;

    //Perform abcd[pIndex]*{x,y} + ef[pIndex]

    tempX = abcd[pIndex][0][0]*x + abcd[pIndex][0][1]*y + ef[pIndex][0][0];
    tempY = abcd[pIndex][1][0]*x + abcd[pIndex][1][1]*y + ef[pIndex][1][0];
    x = tempX;
    y = tempY;
}


void myinit()
{
/* set up viewing */
/* 500 x 500 window with origin lower left */

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(-10, 10, 0, 10);
      glMatrixMode(GL_MODELVIEW);
}

void display_name()
{
	if(flag==1){
  	glRasterPos2f(-9,9);

  	for(int i=0; name_var[i]!='\0';i++)
  	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, name_var[i]);
  	}
}
}
void reshapeFunc(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w, 2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
	else
		glOrtho(-2.0 * (GLfloat) w / (GLfloat) h, 2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
		flag=1;
}

void colorChange(int color)
{
  	c = color;
    glutPostRedisplay();
}


void display( void )

{
    int j, k;
    glClearColor(1.0, 1.0, 1.0, 1.0); /* white background */
    glClear(GL_COLOR_BUFFER_BIT);  /*clear the window */

    if(c==6) glColor3f(1,0,0);
    else if(c==7) glColor3f(0,1,0);
    else if(c==8) glColor3f(0,0,1);
    else glColor3f(0,1,0);

    display_name();
    cout<<"Flag: "<<flag<<" c="<<c<<endl;
    //initialization of abcd, ef, and p if first display
    if(isFirstDisplay){
        changeFern(1);
        isFirstDisplay = false;
    }

/* compute and plots 5000 new points */

    float x = 0, y = 0;

    if(flag==1){
        for(k=0; k<5000; k++)
        {
            generateFern(x,y);
            glBegin(GL_POINTS);
            glVertex2f(x,y);
            glEnd();
            glFlush();
  		  }
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
    glutMouseFunc(mouse);
    glutDisplayFunc(display); /* display callback invoked when window opened */



    submenu=glutCreateMenu(colorChange);

    glutAddMenuEntry("Red",6);
    glutAddMenuEntry("Green",7);
    glutAddMenuEntry("Blue",8);

    glutCreateMenu(changeFern); //Main menu
    glutAddSubMenu("Color",submenu);
    glutAddMenuEntry("Barnsley",1);
    glutAddMenuEntry("Barnsley_Mod",2);
    glutAddMenuEntry("Cyclo",3);
    glutAddMenuEntry("Culcita",4);
    glutAddMenuEntry("Quit",5);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
    myinit(); /* set attributes */
    glutMainLoop(); /* enter event loop */
}

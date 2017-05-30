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
int w,a,s,d,x;

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
    if (h == 0)
            h = 1;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ((float)w)/((float)h), 1, 200);

    glLoadIdentity();
    gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0,0.0,0.0, 0.0, 0.0);
}

void mouse(int button, int state, int x, int y)
{
  	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
  		  flag=1;
  	else
  		  flag=0;
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'w': w=1; break; //Up
        case 'a': a=1; break; //Left
        case 'd': d=1; break; //Right
        case 's': s=1; break; //Down
        case 'x': exit(0);
    }
}


void display( void )
{
    int j, k;
    glClearColor(1.0, 1.0, 1.0, 1.0); /* white background */
    glClear(GL_COLOR_BUFFER_BIT);  /*clear the window */
    display_name();
    //initialization of abcd, ef, and p if first display
    if(isFirstDisplay){
        changeFern(1);
		isFirstDisplay = false;
    }



/* compute and plots 5000 new points */

    float x = 0, y = 0;

    for(k=0; k<30000; k++)
    {
        //cout<<'('<<x<<','<<y<<')'<<endl;

        float num = rand()%100/100;
        float num2 = rand()%3;

        if(num2==0)
          glColor3f(num,0,0);
        else if(num2==1)
          glColor3f(0,num,0);
        else
          glColor3f(0,0,num);

    		if(flag==1)
    			 generateFern(x,y);
  		  if (w==1)
            glTranslatef(10,10,0); //Up
  		  if(s==1)
            glTranslatef(-10,-10,0); //Down
    		if(a==1)
            glRotatef(60,1,0,0); //Left
    		if(d==1)
            glRotatef(-60,1,0,0); //Right

        glColor3f(0,1,0.3);
        glBegin(GL_POINTS);
        glVertex2f(x,y);
        glEnd();
        glFlush();
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
  	glutKeyboardFunc(keyboard);
    glutDisplayFunc(display); /* display callback invoked when window opened */

    glutCreateMenu(changeFern);
    glutAddMenuEntry("Barnsley",1);
    glutAddMenuEntry("Barnsley_Mod",2);
    glutAddMenuEntry("Cyclo",3);
    glutAddMenuEntry("Culcita",4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    myinit(); /* set attributes */

    glutMainLoop(); /* enter event loop */
}

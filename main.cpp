#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <GL/glut.h>
#include<iostream>

#define pi (2*acos(0.0))
using namespace std;

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;

double map_angle;
double Block_size=40;
double Block_distance=38,size_cube=38;
int slices_spehere=15, stacks_spehere=10;
int segments_cylinder=24;
double temp=10;
double move_pos=2;
double ar=-40,org=-30,rm=0;//translate position
double sredious = 10.0;//,base=15.0,height=20.0;
double x1=0,rr=0,rl=0,ru=0,rd=0,ry=20;
//static int cnum = 0; /// to check circle number to specify planes.

struct point
{
	double x,y,z;
};

point l,u,r,pos,t;




double degreetoredian(double d)
{
    return (d)*(double)(pi/180);
}


void drawAxes()
{
	if(drawaxes==1)
	{
	    glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);{
			for(int i=-150;i<150;i+=8){
                glVertex3f( 150,i,0);
                glVertex3f(-150,i,0);
			}

			for(int i=-150;i<150;i+=8){
                glVertex3f(i,-150,0);
                glVertex3f(i, 150,0);
			}
		}glEnd();
	}
}

void drawwheel(double radius,int segments)
{
    int i;
    struct point points[100];
    glColor3f(1.0,0.0,1.0);
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points


   ///circle
        glColor3f(1.0,1.0,1.0);
        for(i=0;i<segments;i++) ///circle 1
        {
            glBegin(GL_LINES);
            {
                glVertex3f(points[i].x,6,points[i].y);
                glVertex3f(points[i+1].x,6,points[i+1].y);
            }
            glEnd();
        }

        for(i=0;i<segments;i++) ///circle 2
        {
            glBegin(GL_LINES);
            {
                glVertex3f(points[i].x,-6,points[i].y);
                glVertex3f(points[i+1].x,-6,points[i+1].y);
            }
            glEnd();

        }

        for(int j=0;j<segments;j +=1)///circle coloring
        {
            if(j%2==0){
                glColor3f(5*.1,5*0.1,5*0.1);
            }
            else{
                glColor3f(1.0,1.01,0.05);
            }
            glBegin(GL_POLYGON_BIT);
            {
                glVertex3f(points[j].x,6,points[j].y);
                glVertex3f(points[j].x,-6,points[j].y);
                glVertex3f(points[j+1].x,6,points[j+1].y);
                glVertex3f(points[j+1].x,-6,points[j+1].y);
            }

            glEnd();
        }

        glBegin(GL_POLYGON);///plate 1
        {
                glColor3f(5*.1,5*0.1,5*0.1);
                glVertex3f(20,4,0);
                glVertex3f(-20,4,0);
                glVertex3f(-20,-4,0);
                glVertex3f(20,-4,0);
        }
        glEnd();
        glBegin(GL_POLYGON);///plate 2
        {
               glColor3f(1.0,1.01,0.05);
                glVertex3f(0,4,20);
                glVertex3f(0,4,-20);
                glVertex3f(0,-4,-20);
                glVertex3f(0,-4,20);
        }
        glEnd();

}

void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	//gluLookAt(0,0,200,	0,0,0,	0,1,0);
	gluLookAt(pos.x, pos.y, pos.z,     pos.x + l.x,pos.y + l.y, pos.z + l.z,     u.x, u.y, u.z);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects
    glPushMatrix();{
        glRotatef(rr,0,0,1);
        glRotatef(-rl,0,0,1);
        glRotatef(ru,-0.5,0.5,0);
        glRotatef(-rd,-0.5,0.5,0);

        glPushMatrix();{
            drawAxes();
        }glPopMatrix();

        glPushMatrix();{
             glTranslated(t.x, t.y,20);
             glRotatef(rm, 0, 0, 1);
             glRotatef(90, 0, 0, 1);

             glPushMatrix();{
                glRotatef(4*x1,0,1,0); //wheel rotating
                drawwheel(20,34);
            }glPopMatrix();

        }glPopMatrix();
    }glPopMatrix();

//	drawGrid();

    ///move from shoulder


   // drawSS();



    //drawCone(20,50,24);

	//drawSphere(30,24,20);




	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}







void animate(){
	angle+=0.05;
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}
void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	cameraHeight=0.0;
	cameraAngle=0.0;
	angle=0;

	u.x=10;
    u.y=10;
    u.z=1;


    r.x=-2/sqrt(2);
    r.y=2/sqrt(2);
    r.z=0;

    l.x=-1/sqrt(2) ;
    l.y=-1/sqrt(2) ;
    l.z=0;

    pos.x=150;
    pos.y=150;
    pos.z=70;


	map_angle=-100;

	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}
void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:	//down arrow key
		    rd +=.5;
			cameraHeight -= 3.0;
//			pos.x-=l.x*move_pos;
//			pos.y-=l.y*move_pos;
			pos.z-=l.z*move_pos;

			break;
		case GLUT_KEY_UP:		// up arrow key
		    ru +=.5;
			cameraHeight += 3.0;
//			pos.x+=l.x*move_pos;
//			pos.y+=l.y*move_pos;
			//pos.z+=l.z*move_pos;
			break;

		case GLUT_KEY_RIGHT:
		    rr +=.5;
			cameraAngle += 3.0;
//			pos.x+=r.x*move_pos;
//			pos.y+=r.y*move_pos;
//			pos.z+=r.z*move_pos;
			//pos.z=0;
			break;
		case GLUT_KEY_LEFT:
		    rl +=.5;
			cameraAngle -= 0.03;
//			pos.x-=r.x*move_pos;
//			pos.y-=r.y*move_pos;
//			//pos.z-=r.z*move_pos;

			break;

		case GLUT_KEY_PAGE_UP:
		    pos.x+=u.x*move_pos;
			pos.y+=u.y*move_pos;
			//pos.z+=u.z*move_pos;
			break;
		case GLUT_KEY_PAGE_DOWN:
            pos.x-=u.x*move_pos;
			pos.y-=u.y*move_pos;
			//pos.z-=u.z*move_pos;
			break;

		case GLUT_KEY_HOME:
		    if(Block_size>0)
            {
                Block_size-=5;
                temp+=5;
            }
			break;
		default:
			break;
	}
}


void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 's':
           if(x1<300){
                x1+=.5;
                t.y += cos(degreetoredian(rm));
                t.x -= sin(degreetoredian(rm));
            }
            break;
        case 'w':
           if(x1>-300){
                x1 -=.5;
                t.y -= cos(degreetoredian(rm));
                t.x += sin(degreetoredian(rm));
           }
            break;
        case 'a':
            rm+=.5;
            break;
        case 'd':
            rm-=.5;
            break;
        case 'e':
            exit(0);
            break;
        default :
            break;

    }

    glutPostRedisplay();
}


int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(1280, 980);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program \"Robotic Hand\"");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

//	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutKeyboardFunc(key);
	//glutMouseFunc(mouseListener);


	glutMainLoop();		//The main loop of OpenGL

	return 0;
}

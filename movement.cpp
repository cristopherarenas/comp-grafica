#include <GL/glut.h>
#include <unistd.h>
#include "sphere.h"

float * pos;
TSphere * sphere;

void initgl(){
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0,0.0,0.0,0.0);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0,1.0,1.0,100.0);
	
	sphere = new TSphere(5,1);
	
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(3,3,14,0,0,0,0,1,0);
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
	glutWireCube(10);
	glPushMatrix();
	glColor3f(0.0,0.0,1.0);
	pos = sphere -> getPosv();
	glTranslatef(pos[0],pos[1],pos[2]);
	glutSolidSphere(1,10,10);
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void idle(void){
	sphere->test();
	usleep(33);
	glutPostRedisplay();
}

int main(int argc, char ** argv){
	glutInit(&argc,argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(20,20);
	glutInitWindowSize(500,500);
	glutCreateWindow(argv[0]);
	
	initgl();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
	
	return 0;
}

#include <GL/glut.h>

void display1(void){
	//Color de fondo negro
	glClearColor(0.0,0.0,0.0,0.0);
	
	//limpiar pantalla
	glClear(GL_COLOR_BUFFER_BIT);

	//modo proyeccion
	glMatrixMode(GL_PROJECTION);
	
	//se carga la matriz identidad
	glLoadIdentity();
	
	//proyeccion ortografica dentro del cubo
	glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
	
	//modo de modelado
	glMatrixMode(GL_MODELVIEW);
	
	//se dibuja un triangulo
	glBegin(GL_TRIANGLES);
	//color rojo
	glColor3f(1.0,0.0,0.0);
	//posicion de vertice 1
	glVertex3f(0.0,0.8,0.0);
	//color verde
	glColor3f(0.0,1.0,0.0);
	//posicion de vertice 2
	glVertex3f(-0.6,-0.2,0.0);
	//color azul
	glColor3f(0.0,0.0,1.0);
	//posicion de vertice 3
	glVertex3f(0.6,-0.2,0.0);
	//Fin dibujo
	glEnd();
	
	//se fuerza el dibujo
	glFlush();
	
	//pausa de 10 segundos
	sleep(10);
	
	//fin del programa
	exit(0);
	
}

void display(void){
	//Color de fondo negro
	glClearColor(0.0,0.0,0.0,0.0);
	
	//limpiar pantalla
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//modo proyeccion
	glMatrixMode(GL_PROJECTION);
	
	//se carga la matriz identidad
	glLoadIdentity();
	
	//proyeccion perspectiva 
	//angulo de visualizacion de 60 grados
	//razon ancho/alto es 1
	//distancia minima es z=1.0
	//distancia maxima es z=100.0
	gluPerspective(60.0,1.0,1.0,100.0);
	
	//modo de modelado
	glMatrixMode(GL_MODELVIEW);
	
	glTranslatef(0.0,0.0,-2.0);
	
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	
	
	glBegin(GL_QUADS);
	glColor3f(0.0,1.0,1.0);
	glVertex3f(-0.5,0.5,-0.5);
	glVertex3f(-0.5,-0.5,0.5);
	glVertex3f(0.5,-0.5,0.5);
	glVertex3f(0.5,0.5,-0.5);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3f(1.0,0.0,0.0);
	glVertex3f(0.0,0.5,0.0);
	glVertex3f(-0.7,-0.5,0.0);
	glVertex3f(0.7,-0.5,0.0);
	glEnd();
	
	//se fuerza el dibujo
	glFlush();
	
	//pausa de 10 segundos
	sleep(10);
	
	//fin del programa
	exit(0);
	
}


int main(int argc, char ** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(20,20);
	glutInitWindowSize(500,500);
	glutCreateWindow(argv[0]);
	
	glutDisplayFunc(display);
	glutMainLoop();
	
	return 0;
}

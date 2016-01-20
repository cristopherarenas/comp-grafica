#include <GL/glut.h>
#include <iostream>
#include <SOIL/SOIL.h>
#include <vector>
#include <time.h>
#include <string>
#include <sstream>

using namespace std;

typedef struct {
   GLfloat verticeXYZ[3];
   GLfloat colorRGB[3];
} Vertice;

typedef struct {
   float x,y;
   int izda, dcha;
} EstadoRaton;

int tiempo = 0;

bool* keyStates = new bool[256]; // Create an array of boolean values of length 256 (0-255) 

bool movingUp = false; // Whether or not we are moving up or down  

bool animacion = false;

Vertice cuadrado[4] = {
   {{-3,4,0},{1,0,0}},
   {{-3,2,0},{1,0,0}},
   {{-1,2,0},{1,0,0}},
   {{-1,4,0},{1,0,0}}
};
Vertice cuadrado_b[4] = {
   {{-9,4,0},{0,1,0}},
   {{-9,2,0},{0,1,0}},
   {{-7,2,0},{0,1,0}},
   {{-7,4,0},{0,1,0}}
};
Vertice cuadrado_c[4] = {
   {{-6,4,0},{0,0,1}},
   {{-6,2,0},{0,0,1}},
   {{-4,2,0},{0,0,1}},
   {{-4,4,0},{0,0,1}}
};


Vertice selector = {{0,0,0},{1,1,1}};
EstadoRaton raton;
int ventana[2], vertice_sel;
GLfloat formato_global;

 
void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

string convertInt(int number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

GLuint loadTexture(const char * filename)                                    
{
	GLuint tex_2d = SOIL_load_OGL_texture
		(
			filename,
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
		 
    return tex_2d;                                     
}


void IniciarGLUT() {
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(600,600);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Proyecto Computación Gráfica");
}

void keyPressed (unsigned char key, int x, int y) {  
	keyStates[key] = true; // Set the state of the current key to pressed  
}  
  
void keyUp (unsigned char key, int x, int y) {  
	keyStates[key] = false; // Set the state of the current key to not pressed  
	
	switch ( key ) {
	case 'r':
		glutFullScreen();
		break;
	case 's':
		glutReshapeWindow(800, 600);
		glutPositionWindow(100,100);
		break;
	case 27:	// Escape key
		exit(1);
	case 'z':
		animacion = true;
		break;
	case 'x':
		animacion = false;
		break;
	}
} 

vector<GLuint> texturas;
vector<GLuint> cielo;

void cargar_texturas()
{
	int j;

	for(j=1;j<41;j++)
	{
		string filename = "textures/Diapositiva"+convertInt(j)+".PNG";
		
		texturas.push_back(loadTexture(filename.c_str())); 
	}
	for(j=41;j<45;j++)
	{
		string filename = "textures/Diapositiva"+convertInt(j)+".PNG";
		
		cielo.push_back(loadTexture(filename.c_str())); 
	}
	
	for(j=43;j>41;j--)
	{
		string filename = "textures/Diapositiva"+convertInt(j)+".PNG";
		
		cielo.push_back(loadTexture(filename.c_str())); 
	}
	
}

void animar()
{
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();                                      // Reset The View  
    glEnable(GL_TEXTURE_2D);
    //glTranslatef(0.0f, 0.0f, -6.0f);
	//cout << tiempo << endl;
	tiempo++;
    glColor3f(1.0f,1.0f,1.0f);
	//loadBMP_custom("textura3.bmp");
	
	
	
	//texturas.push_back(loadTexture("orange.bmp")); 
	//texturas.push_back(loadTexture("blue.bmp")); 
	
	// Typical Texture Generation Using Data From The Bitmap
    glBindTexture(GL_TEXTURE_2D, texturas[(tiempo+6)%40]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	
	int i;
	
	glBegin(GL_QUADS);
	for (i=0; i<4; i++) {	
		if(i==0)
			glTexCoord2f(1.0,1.0);
		else if(i==1)
			glTexCoord2f(1.0,0.0);
		else if(i==2)
			glTexCoord2f(0.0,0.0);
		else if(i==3)
			glTexCoord2f(0.0,1.0);
			
		glVertex3fv(cuadrado_b[i].verticeXYZ);
	}
	glEnd();
	
	// Typical Texture Generation Using Data From The Bitmap
    glBindTexture(GL_TEXTURE_2D, cielo[tiempo%6]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	glBegin(GL_QUADS);
	for (i=0; i<4; i++) {
		if(i==0)
			glTexCoord2f(1.0,1.0);
		else if(i==1)
			glTexCoord2f(1.0,0.0);
		else if(i==2)
			glTexCoord2f(0.0,0.0);
		else if(i==3)
			glTexCoord2f(0.0,1.0);
		
		glVertex3fv(cuadrado[i].verticeXYZ);
	}
	glEnd();
	
	// Typical Texture Generation Using Data From The Bitmap
    glBindTexture(GL_TEXTURE_2D, texturas[tiempo%40]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	glBegin(GL_QUADS);
	for (i=0; i<4; i++) {
		if(i==0)
			glTexCoord2f(1.0,1.0);
		else if(i==1)
			glTexCoord2f(1.0,0.0);
		else if(i==2)
			glTexCoord2f(0.0,0.0);
		else if(i==3)
			glTexCoord2f(0.0,1.0);
		
		glVertex3fv(cuadrado_c[i].verticeXYZ);
	}
	glEnd();
	
	glPointSize(7);
	glBegin(GL_POINTS);
	glColor3fv(selector.colorRGB);
	glVertex3fv(selector.verticeXYZ);
	glEnd();
}

void defecto() {
  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
 
  int i;
 
  glBegin(GL_QUADS);
      for (i=0; i<4; i++) {
         glColor3fv(cuadrado_b[i].colorRGB);
         glVertex3fv(cuadrado_b[i].verticeXYZ);
      }
  glEnd();
 
  glBegin(GL_QUADS);
        for (i=0; i<4; i++) {
         glColor3fv(cuadrado[i].colorRGB);
         glVertex3fv(cuadrado[i].verticeXYZ);
      }
  glEnd();
	
  glBegin(GL_QUADS);
        for (i=0; i<4; i++) {
         glColor3fv(cuadrado_c[i].colorRGB);
         glVertex3fv(cuadrado_c[i].verticeXYZ);
      }
  glEnd();
  
  glPointSize(7);
  glBegin(GL_POINTS);
      glColor3fv(selector.colorRGB);
      glVertex3fv(selector.verticeXYZ);
  glEnd();
  
  
}

void Render()
{
	if(animacion)
	{
		animar();
		sleep(300000);
	}
	else
	{
		defecto();
	}
	glutSwapBuffers();
}

void ReProyectar(int w, int h) {
  GLfloat formato;

  ventana[0] = w;
  ventana[1] = h;
 
  if(h == 0) h = 1;
     
    glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  formato = (GLfloat)w / (GLfloat)h;
  formato_global = formato;
    if (w <= h) glOrtho (-10.0f, 10.0f, -10.0f / formato, 10.0f / formato, -1.0f, 1.0f);
    else glOrtho (-10.0f * formato, 10.0f * formato, -10.0f, 10.0f, -1.0f, 1.0f);
}

float ObtenerPosPlanoX(float x, int ancho_ventana, int alto_ventana, float pos_x_min, float pos_x_max, float format) {
   float pos_x_relativa = ((float)x/ancho_ventana); //La posición relativa de 0 a 1 en X
   float pos_plano;
   
   if (ancho_ventana<=alto_ventana) pos_plano = (pos_x_min+((pos_x_max-pos_x_min)*pos_x_relativa));
   else pos_plano = ((pos_x_min * format)+(((pos_x_max-pos_x_min) * format)*pos_x_relativa));
   
   return pos_plano;
}

float ObtenerPosPlanoY(float y, int ancho_ventana, int alto_ventana, float pos_y_min, float pos_y_max, float format) {
   float pos_y_relativa = ((float)y/alto_ventana); //La posición relativa de 0 a 1 en Y
   float pos_plano;
   
   if (ancho_ventana<=alto_ventana) pos_plano = -((pos_y_min / format)+(((pos_y_max-pos_y_min) / format)*pos_y_relativa));
   else pos_plano = -(pos_y_min+((pos_y_max-pos_y_min)*pos_y_relativa));
   
   return pos_plano;
}

void ControlRaton(int button, int state, int x, int y) {
   if (button==GLUT_LEFT_BUTTON) {
      if (state==GLUT_DOWN){
		   raton.izda = 1;
	  }
      else raton.izda = 0;
   }
   else if (button==GLUT_RIGHT_BUTTON) {
      if (state==GLUT_DOWN) {
            raton.dcha = 1;
         
         raton.x = ObtenerPosPlanoX(x,ventana[0],ventana[1],-10,10,formato_global);
         raton.y = ObtenerPosPlanoY(y,ventana[0],ventana[1],-10,10,formato_global);
   
         int i;
         for (i=0; i<4; i++) {
            if (raton.x > cuadrado_b[i].verticeXYZ[0] - 0.5f &&
               raton.x < cuadrado_b[i].verticeXYZ[0] + 0.5f &&
               raton.y > cuadrado_b[i].verticeXYZ[1] - 0.5f &&
               raton.y < cuadrado_b[i].verticeXYZ[1] + 0.5f ) {
               vertice_sel = i;
            }
         }
         for (i=0; i<4; i++) {
            if (raton.x > cuadrado[i].verticeXYZ[0] - 0.5f &&
               raton.x < cuadrado[i].verticeXYZ[0] + 0.5f &&
               raton.y > cuadrado[i].verticeXYZ[1] - 0.5f &&
               raton.y < cuadrado[i].verticeXYZ[1] + 0.5f ) {
               vertice_sel = 4 + i;
            }
         }
         for (i=0; i<4; i++) {
            if (raton.x > cuadrado_c[i].verticeXYZ[0] - 0.5f &&
               raton.x < cuadrado_c[i].verticeXYZ[0] + 0.5f &&
               raton.y > cuadrado_c[i].verticeXYZ[1] - 0.5f &&
               raton.y < cuadrado_c[i].verticeXYZ[1] + 0.5f ) {
               vertice_sel = 8 + i;
            }
         }
        }
      else raton.dcha = 0;
   }
}

void MovimRaton(int x, int y) {
   raton.x = ObtenerPosPlanoX(x,ventana[0],ventana[1],-10,10,formato_global);
   raton.y = ObtenerPosPlanoY(y,ventana[0],ventana[1],-10,10,formato_global);
}



void MoverVertice(int value) {
switch (vertice_sel) {
	case 0: case 1: case 2: case 3:
		selector.verticeXYZ[0] = cuadrado_b[vertice_sel].verticeXYZ[0];
		selector.verticeXYZ[1] = cuadrado_b[vertice_sel].verticeXYZ[1];
		break;
	case 4: case 5: case 6: case 7:
		selector.verticeXYZ[0] = cuadrado[vertice_sel-4].verticeXYZ[0];
		selector.verticeXYZ[1] = cuadrado[vertice_sel-4].verticeXYZ[1];
		break;
	case 8: case 9: case 10: case 11:
		selector.verticeXYZ[0] = cuadrado_c[vertice_sel-8].verticeXYZ[0];
		selector.verticeXYZ[1] = cuadrado_c[vertice_sel-8].verticeXYZ[1];
		break;
}
   
   if (raton.izda) {
      if (vertice_sel<=3) {
         cuadrado_b[vertice_sel].verticeXYZ[0] = selector.verticeXYZ[0] = raton.x;
         cuadrado_b[vertice_sel].verticeXYZ[1] = selector.verticeXYZ[1] = raton.y;
      }
      else if(vertice_sel>3 && vertice_sel<=7){
         cuadrado[vertice_sel-4].verticeXYZ[0] = selector.verticeXYZ[0] = raton.x;
         cuadrado[vertice_sel-4].verticeXYZ[1] = selector.verticeXYZ[1] = raton.y;
      }
      else
      {
         cuadrado_c[vertice_sel-8].verticeXYZ[0] = selector.verticeXYZ[0] = raton.x;
         cuadrado_c[vertice_sel-8].verticeXYZ[1] = selector.verticeXYZ[1] = raton.y;
	  }
   }
   
   glutTimerFunc(33,MoverVertice,1);
   glutPostRedisplay();
}



int main(int argc, char **argv) {
	glutInit(&argc,argv); //Solo necesario en Linux
	IniciarGLUT();

	cargar_texturas();
	
	glutReshapeFunc(ReProyectar);
	glutDisplayFunc(Render);
	glutIdleFunc(Render);
	glutMouseFunc(ControlRaton);
	glutTimerFunc(33,MoverVertice,1);
	glutMotionFunc(MovimRaton);
	glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses  
	glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key up events  
	

	glutMainLoop();

	return 0;
}

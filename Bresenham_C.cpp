#include <stdio.h>
#include "main.h"

//Dibuja las simetrías de cada punto en OpenGL

int window_w ;
int window_h ;
int centrox, centroy, radio;

void ochopuntos(int Xc, int Yc, int x, int y) {
	int i, j;
	float aux1, aux2;
	int sim[8][2] = { {x,y},{x,-y},{-x,y},{-x,-y},{y,x},{y,-x},{-y,x},{-y,-x} };//Arreglo de puntos de simetría
	//imprimir simetrías (Se dibujan los puntos simetricos deplazados
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 2; j++) {
			if (j == 0) {
				aux1 = sim[i][j]+ Xc;
			}
			else {
				aux2 = sim[i][j]+Yc;
			}
		}
		glPointSize(1);//Tamaño de punto a dibujar
		glBegin(GL_POINTS);
		glColor3f(1.0f, 1.0f, 1.0f);//Color blanco
		glVertex3f(aux1+Xc, aux2+Yc, -1.0f);
		glEnd();
	}
}

void Bresenham_c(int Xc, int Yc, int r) {
	int i, j, pk, xk, yk, a, b;
	float aux1, aux2;
	ochopuntos(Xc, Yc, 0, r);
	pk = 1 - r;
	//Hacemos que el punto de partida sea (xk,yk)=(0,r)
	xk = 0;
	yk = r;
	//El ciclo while siguiente calculará cada punto del primer octante, y a su vez las 8 simetrías de cada uno
	while (yk > xk) {
		if (pk < 0) {
			pk = pk + 2 * xk + 3;
			xk++;
			ochopuntos(Xc,Yc,xk, yk);//Sustituir por el dibujo del punto en OpenGL				
		}
		else {
			pk = pk + 2 * (xk - yk) + 5;
			xk++;
			yk--;
			ochopuntos(Xc, Yc,xk, yk);//Sustituir por el dibujo del punto en OpenGL
		}
	}
}

void InitGL(GLvoid)     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo
	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limpiamos pantalla y Depth Buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Bresenham_c(centrox,centroy,radio);



	glutSwapBuffers();
	// Swap The Buffers
}

void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	glOrtho(-window_w, window_w, -window_h, window_h, 0.1, 20);
}


int main(int argc, char** argv)   // Main Function
{
	glutInit(&argc, argv); // Inicializamos OpenGL
	//glutInitDisplayMode (GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Sencillo )
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	glutCreateWindow("Circunferencia"); // Nombre de la Ventana
	printf("Ingresa las coordenadas del centro\n\n");
	printf("X: ");
	scanf_s("%d",&centrox);
	printf("Y: ");
	scanf_s("%d",&centroy);
	printf("Ingresa el valor del radio: ");
	scanf_s("%d",&radio);
	window_w = radio*1.5;
	window_h = window_w;
	glutInitWindowSize(window_w, window_h);	// Tamaño de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut función de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut función en caso de cambio de tamano
	//glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
	//glutSpecialFunc     ( arrow_keys );	//Otras
	glutMainLoop();          // 

	return 0;
}

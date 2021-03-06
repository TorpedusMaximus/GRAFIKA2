#define _USE_MATH_DEFINES
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

using namespace std;
typedef float point3[3];
int model = 1; //startuje z chmura punktów
int n = 20;
point3** points;//siatka 
static GLfloat theta[] = { 0.0, 0.0, 0.0 };
point3** color; //kolory

void drawPoints() {
	glBegin(GL_POINTS);
	for (int i = 0; i <= n; i++) {
		for (int ii = 0; ii <= n; ii++) {
			glVertex3f(points[i][ii][0], points[i][ii][1], points[i][ii][2]);
		}
	}
	glEnd();
}

void drawLines() {

	for (int i = 0; i < n; i++) {
		for (int ii = 0; ii < n; ii++) {
			glBegin(GL_LINE_LOOP);//naniesienie trójkąta siatki 
			glVertex3f(points[i][ii][0], points[i][ii][1], points[i][ii][2]);
			glVertex3f(points[i + 1][ii][0], points[i + 1][ii][1], points[i + 1][ii][2]);
			glVertex3f(points[i + 1][ii + 1][0], points[i + 1][ii + 1][1], points[i + 1][ii + 1][2]);
			glEnd();
		}
	}
}

void drawTriangles() {
	for (int i = 0; i < n; i++) {
		for (int ii = 0; ii < n; ii++) {
			glBegin(GL_TRIANGLES);
			glColor3f(color[i][ii][0], color[i][ii][1], color[i][ii][2]);
			glVertex3f(points[i][ii][0], points[i][ii][1], points[i][ii][2]);
			glColor3f(color[i+1][ii][0], color[i+1][ii][1], color[i+1][ii][2]);
			glVertex3f(points[i + 1][ii][0], points[i + 1][ii][1], points[i + 1][ii][2]);
			glColor3f(color[i+1][ii+1][0], color[i+1][ii+1][1], color[i+1][ii+1][2]);
			glVertex3f(points[i + 1][ii + 1][0], points[i + 1][ii + 1][1], points[i + 1][ii + 1][2]);
			glEnd();


			glBegin(GL_TRIANGLES);
			glColor3f(color[i][ii][0], color[i][ii][1], color[i][ii][2]);
			glVertex3f(points[i][ii][0], points[i][ii][1], points[i][ii][2]);
			glColor3f(color[i][ii+1][0], color[i][ii+1][1], color[i][ii+1][2]);
			glVertex3f(points[i][ii + 1][0], points[i][ii + 1][1], points[i][ii + 1][2]);
			glColor3f(color[i + 1][ii + 1][0], color[i + 1][ii + 1][1], color[i + 1][ii + 1][2]);
			glVertex3f(points[i + 1][ii + 1][0], points[i + 1][ii + 1][1], points[i + 1][ii + 1][2]);
			glEnd();
		}
	}
}

void jajko() {
	float u = 0, v = 0;
	float udiff = 1.0 / n, vdiff = 1.0 / n; //n - liczba punktów na powierzchni jajka
	glTranslated(0, -(160 * pow(0.5, 4) - 320 * pow(0.5, 3) + 160 * pow(0.5, 2)) / 2, 0);//obniżenie środka figury do centrum układu współrzędnych
	
	for (int i = 0; i <= n; i++) {
		v = 0;//obliczenie potęg w celu przyspieszenia obliczeń
		float u2 = pow(u, 2);
		float u3 = pow(u, 3);
		float u4 = pow(u, 4);
		float u5 = pow(u, 5);

		for (int ii = 0; ii <= n; ii++) {//obliczenie współrzędnych punktów
			points[i][ii][0] = (-90 * u5 + 225 * u4 - 270 * u3 + 180 * u2 - 45 * u) * cos(M_PI * v);
			points[i][ii][1] = 160 * u4 - 320 * u3 + 160 * u2;
			points[i][ii][2] = (-90 * u5 + 225 * u4 - 270 * u3 + 180 * u2 - 45 * u) * sin(M_PI * v);
			v =v+ vdiff;
		}
		u = u+ udiff;
	}

	switch (model) {//rysowanie jajka w określony sposób
	case 1:
		drawPoints();
		break;
	case 2:
		drawLines();
		break;
	case 3:
		drawTriangles();
		break;
	}
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	jajko();
	glFlush();
	glutSwapBuffers();
}

void MyInit(void)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


}

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{

	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio  określającej proporcję
	// wymiarów okna 
	if (vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0
		vertical = 1;
	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkościokna okna widoku (viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)  
	glMatrixMode(GL_PROJECTION);
	// Przełączenie macierzy bieżącej na macierz projekcji 
	glLoadIdentity();
	// Czyszcznie macierzy bieżącej            
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie współczynnika  proporcji okna
	// Gdy okno nie jest kwadratem wymagane jest określenie tak zwanej
	// przestrzeni ograniczającej pozwalającej zachować właściwe
	// proporcje rysowanego obiektu.
	// Do okreslenia przestrzeni ograniczjącej służy funkcja
	// glOrtho(...)            
	if (horizontal <= vertical)

		glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);
	else

		glOrtho(-7.5 * AspectRatio, 7.5 * AspectRatio, -7.5, 7.5, 10.0, -10.0);
	glMatrixMode(GL_MODELVIEW);
	// Przełączenie macierzy bieżącej na macierz widoku modelu                                   

	glLoadIdentity();
	// Czyszcenie macierzy bieżącej
}

void keys(unsigned char key, int x, int y)
{
	if (key == 'p') model = 1;
	if (key == 'w') model = 2;
	if (key == 's') model = 3;

	RenderScene(); // przerysowanie obrazu sceny
}

void spinEgg()
{

	theta[0] -= 0.5;
	if (theta[0] > 360.0) theta[0] -= 360.0;

	theta[1] -= 0.5;
	if (theta[1] > 360.0) theta[1] -= 360.0;

	theta[2] -= 0.5;
	if (theta[2] > 360.0) theta[2] -= 360.0;

	glutPostRedisplay(); //odświeżenie zawartości aktualnego okna
}

void main(void)
{
	srand(time(NULL));
	color = new point3 * [n + 1];
	for (int i = 0; i <= n; i++) {
		color[i] = new point3[n + 1];
	}
	for (int i = 0; i <= n; i++) {
		for (int ii = 0; ii <= n; ii++) {
			color[i][ii][0] = (rand() % 101) * 0.01;
			color[i][ii][1] = (rand() % 101) * 0.01;
			color[i][ii][2] = (rand() % 101) * 0.01;
		}
	}

	points = new  point3 * [n + 1];
	for (int i = 0; i <= n; i++) {
		points[i] = new point3[n + 1]; // naniesienie punktów na płaszczyznę
	}

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(300, 300);
	glutCreateWindow("Jajko");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	MyInit();
	glEnable(GL_DEPTH_TEST);
	glutKeyboardFunc(keys);
	glutIdleFunc(spinEgg);
	glutMainLoop();
}


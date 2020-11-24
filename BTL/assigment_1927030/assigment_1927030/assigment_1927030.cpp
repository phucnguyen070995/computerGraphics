#include <windows.h>

#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"
#include "tchar.h"


using namespace std;

int		screenWidth = 1200;
int		screenHeight = 600;

Mesh	tetrahedron;
Mesh	cube;
Mesh	cylinder;
Mesh	shape1;
Mesh	shape2;
Mesh	shape3;
Mesh	shape4;
Mesh	shape5;

float	angle = 0, angleX = 0, angleY = 0, angleZ = 0;
int		rotateX = 0;
int		rotateY = 0;
int		rotateZ = 0;

int		nChoice = 1;

void drawAxis()
{
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(4, 0, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 4, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 4);
	glEnd();
}
void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(4.5, 4, 2, 0, 0, 0, 0, 1, 0);

	glRotatef(angle, rotateX, rotateY, rotateZ);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, screenWidth / 2, screenHeight);

	drawAxis();

	glColor3f(0, 0, 0);
	if (nChoice == 1)
		tetrahedron.DrawWireframe();
	else if (nChoice == 2)
		cube.DrawWireframe();
	else if (nChoice == 3)
		cylinder.DrawWireframe();
	else if (nChoice == 4)
		shape1.DrawWireframe();
	else if (nChoice == 5)
		shape2.DrawWireframe();
	else if (nChoice == 6)
		shape3.DrawWireframe();
	else if (nChoice == 7)
		shape4.DrawWireframe();
	else if (nChoice == 8)
		shape5.DrawWireframe();

	glViewport(screenWidth / 2, 0, screenWidth / 2, screenHeight);

	drawAxis();
	if (nChoice == 1)
		tetrahedron.DrawColor();
	else if (nChoice == 2)
		cube.DrawColor();
	else if (nChoice == 3)
		cylinder.DrawColor();
	else if (nChoice == 4)
		shape1.DrawColor();
	else if (nChoice == 5)
		shape2.DrawColor();
	else if (nChoice == 6)
		shape3.DrawColor();
	else if (nChoice == 7)
		shape4.DrawColor();
	else if (nChoice == 8)
		shape5.DrawColor();

	glFlush();
	glutSwapBuffers();
}

void mySpecialFunc(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		angleX += 5;
		angle = angleX;
		rotateX = 1; rotateY = 0; rotateZ = 0;
	}
	else if (key == GLUT_KEY_RIGHT) {
		angleX -= 5;
		angle = angleX;
		rotateX = 1; rotateY = 0; rotateZ = 0;
	}
	else if (key == GLUT_KEY_UP) {
		angleZ += 5;
		angle = angleZ;
		rotateX = 0; rotateY = 0; rotateZ = 1;
	}
	else if (key == GLUT_KEY_DOWN) {
		angleZ -= 5;
		angle = angleZ;
		rotateX = 0; rotateY = 0; rotateZ = 1;
	}

	glutPostRedisplay();
}

void myInit()
{
	float	fHalfSize = 4;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
}

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "1. Tetrahedron" << endl;
	cout << "2. Cube" << endl;
	cout << "3. Cylinder" << endl;
	cout << "4. Shape 1" << endl;
	cout << "5. Shape 2" << endl;
	cout << "6. Shape 3" << endl;
	cout << "7. Shape 4" << endl;
	cout << "8. Shape 5" << endl;
	cout << "Input the choice: " << endl;
	cin >> nChoice;

	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Lab 2"); // open the screen window

	tetrahedron.CreateTetrahedron();
	cube.CreateCube(1);
	cylinder.CreateCylinder(20, 4, 1);
	shape1.CreateShape1(1, 3, 1.5, 0.5);
	shape2.CreateShape2(1.5/4.0, 1 / 4.0, 1 / 4.0, 2 / 4.0, 4 / 4.0, 8 / 4.0, 0.5);
	shape3.CreateShape3(0.5, 4, 2, 0.7, 1, 0.5, 0.5);
	shape4.CreateShape4(3, 0.5, 4, 1.5, 0.75, 0.5);
	shape5.CreateShape5(1, 5, 0.5);
	myInit();
	glutDisplayFunc(myDisplay);
	glutSpecialFunc(mySpecialFunc);

	glutMainLoop();
	return 0;
}

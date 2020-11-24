// Bai3.cpp : Defines the entry point for the console application.
//

#include <windows.h>

#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"
#include "tchar.h"

using namespace std;

int		angle = 0;
int		screenWidth = 600;
int		screenHeight = 300;

Mesh	tetrahedron;
Mesh	cube;

int		nChoice = 1;

void mySpecialFunc(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		angle += 5;
	}
	else if (key == GLUT_KEY_RIGHT) {
		angle -= 5;
	}
	glutPostRedisplay();
}

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

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, screenWidth / 2, screenHeight);
	glRotatef(angle, 0, 1, 0);
	drawAxis();

	glColor3f(0, 0, 0);
	if (nChoice == 1)
		tetrahedron.DrawWireframe();
	else if (nChoice == 2)
		cube.DrawWireframe();

	glViewport(screenWidth / 2, 0, screenWidth / 2, screenHeight);

	drawAxis();
	if (nChoice == 1)
		tetrahedron.DrawColor();
	else if (nChoice == 2)
		cube.DrawColor();

	glFlush();
	glutSwapBuffers();
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
	cout << "Input the choice: " << endl;
	cin >> nChoice;

	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Lab 2"); // open the screen window

	tetrahedron.CreateTetrahedron();
	cube.CreateCube(1);

	myInit();
	glutDisplayFunc(myDisplay);
	glutSpecialFunc(mySpecialFunc);

	glutMainLoop();
	return 0;
}


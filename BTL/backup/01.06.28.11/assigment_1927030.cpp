#include <windows.h>

#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"
#include "tchar.h"
#define PI			3.1415926

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
Mesh	base;
Mesh	bulong1;
Mesh	bulong2;
Mesh	bulong3;
Mesh	bulong4;

float shape1_R = 0.8, shape1_Height = 8.3, shape1_Width = 1.3, Depth = 0.75;
float shape2_R1 = 0.45, shape2_R2 = 0.6, shape2_X1 = 0.45, shape2_X2 = 0.75, shape2_H1 = 1.65, shape2_H2 = 8.1;
float shape3_R = 0.5, shape3_W1 = 0.9, shape3_W2 = 0.5, shape3_H1 = 5.3, shape3_H2 = 3.5, shape3_H3 = 0.8;
float shape4_W1 = 2.6, shape4_W2 = 0.1, shape4_H1 = 2.6, shape4_H2 = 1.25, shape4_R = 0.5;
float shape5_R = 0.6, shape5_Height = 1.7;
float base_Width = 20, base_Height = 6, base_Depth = 1;

float	handleAngle = 15;
float	endAngle;
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

void circle_circle_intersection(double x0, double y0, double r0, double x1, double y1, double r1, double& xi, double& yi, double& xi_prime, double& yi_prime) {
	double a, dx, dy, d, h, rx, ry;
	double x2, y2;
	dx = x1 - x0;
	dy = y1 - y0;
	d = hypot(dx, dy);
	if (d > (r0 + r1)) return;
	if (d < fabs(r0 - r1)) return;
	a = ((r0 * r0) - (r1 * r1) + (d * d)) / (2.0 * d);
	x2 = x0 + (dx * a / d);
	y2 = y0 + (dy * a / d);
	h = sqrt((r0 * r0) - (a * a));
	rx = -dy * (h / d);
	ry = dx * (h / d);
	xi = x2 + rx;
	xi_prime = x2 - rx;
	yi = y2 + ry;
	yi_prime = y2 - ry;
}

void myDisplay()
{
	//Tim giao diem 2 dtr
	double x1 = -2.1, y1 = 1.4, r1 = 3.5;
	double x2 = 3.1 - 2 * cos(handleAngle / 180 * PI);
	double y2 = 3.85 - 2 * sin(handleAngle / 180 * PI);
	double r2 = 1.7;
	double x3, y3, x3_prime, y3_prime;
	circle_circle_intersection(x1, y1, r1, x2, y2, r2, x3, y3, x3_prime, y3_prime);
	if (y3_prime < y3) {
		x3 = x3_prime;
		y3 = y3_prime;
	}
	endAngle = atan((y3 - 1.4) / 3.5) / PI * 180;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(4.5, 4, 2, 0, 0, 0, 0, 1, 0);

	/*glRotatef(angle, rotateX, rotateY, rotateZ);*/

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, screenWidth / 2, screenHeight);

	glPushMatrix();
	glRotatef(angle, rotateX, rotateY, rotateZ);
	drawAxis();
	glPopMatrix();

	glColor3f(0, 0, 0);
	if (nChoice == 1) {
		glRotatef(angle, rotateX, rotateY, rotateZ);
		tetrahedron.DrawWireframe();
	}
		
	else if (nChoice == 2) {
		glRotatef(angle, rotateX, rotateY, rotateZ);
		cube.DrawWireframe();
	}
		
	else if (nChoice == 3) {
		glRotatef(angle, rotateX, rotateY, rotateZ);
		cylinder.DrawWireframe();
	}
		
	else if (nChoice == 4) {
		glRotatef(angle, rotateX, rotateY, rotateZ);
		shape1.DrawWireframe();
	}
		
	else if (nChoice == 5) {
		glRotatef(angle, rotateX, rotateY, rotateZ);
		shape2.DrawWireframe();
	}
		
	else if (nChoice == 6) {
		glRotatef(angle, rotateX, rotateY, rotateZ);
		shape3.DrawWireframe();
	}
		
	else if (nChoice == 7) {
		glRotatef(angle, rotateX, rotateY, rotateZ);
		shape4.DrawWireframe();
	}
		
	else if (nChoice == 8) {
		glRotatef(angle, rotateX, rotateY, rotateZ);
		shape5.DrawWireframe();
	}
		
	else if (nChoice == 9) {
		glPushMatrix();
		glRotatef(angle, rotateX, rotateY, rotateZ);
		glTranslatef(-shape1_R * (2.1 / 0.8), (1.4 / 0.8) * shape1_R, 0);
		glRotatef(endAngle, 0, 0, 1);
		glTranslatef(shape1_R * (4 / 0.8), -(0.5 / 0.8) * shape1_R, -Depth);
		glRotatef(90, 1, 0, 0);
		shape1.SetColor(1);
		shape1.DrawWireframe();
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, rotateX, rotateY, rotateZ);
		glTranslatef((3.1 / 2.6) * shape4_W1, (3.85 / 2.6) * shape4_W1, 0);
		glRotatef(handleAngle, 0, 0, 1);
		glTranslatef(8.2, 0, -Depth);
		glRotatef(180, 0, 0, 1);
		glRotatef(90, 1, 0, 0);
		shape2.SetColor(2);
		shape2.DrawWireframe();
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, rotateX, rotateY, rotateZ);
		glTranslatef(-shape3_H1 * (1 + 1.2 / 5.3), 0, 0);
		glRotatef(90, 1, 0, 0);
		glRotatef(180, 0, 1, 0);
		shape3.SetColor(3);
		shape3.DrawWireframe();
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, rotateX, rotateY, rotateZ);
		glTranslatef(shape4_W1 * (5.6 / 2.6), 0, 0);
		glRotatef(-90, 0, 1, 0);
		glRotatef(-90, 0, 0, 1);
		shape4.SetColor(4);
		shape4.DrawWireframe();
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, rotateX, rotateY, rotateZ);
		glTranslatef(x3, y3, 0);
		float tmp_angle = atan((y3 - y2) / (x3 - x2)) / PI * 180;
		if (tmp_angle < 0) tmp_angle = 180 + tmp_angle;
		glRotatef(tmp_angle, 0, 0, 1);
		glRotatef(90, 1, 0, 0);
		shape5.SetColor(5);
		shape5.DrawWireframe();
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, rotateX, rotateY, rotateZ);
		glTranslatef(-base_Width / 2.0, -base_Depth, -base_Height / 2.0);
		base.SetColor(10);
		base.DrawWireframe();
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, rotateX, rotateY, rotateZ);
		bulong1.SetColor(12);
		glTranslatef(-2.1, 1.4, Depth);
		glRotatef(-90, 1, 0, 0);
		bulong1.DrawWireframe();
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, rotateX, rotateY, rotateZ);
		bulong1.SetColor(12);
		glTranslatef(x3, y3, Depth);
		glRotatef(-90, 1, 0, 0);
		bulong1.DrawWireframe();
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, rotateX, rotateY, rotateZ);
		bulong1.SetColor(12);
		glTranslatef(x2, y2, Depth);
		glRotatef(-90, 1, 0, 0);
		bulong1.DrawWireframe();
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, rotateX, rotateY, rotateZ);
		bulong1.SetColor(12);
		glTranslatef(3.1, 3.85, Depth);
		glRotatef(-90, 1, 0, 0);
		bulong1.DrawWireframe();
		glPopMatrix();
	}

	glViewport(screenWidth / 2, 0, screenWidth / 2, screenHeight);

	glPushMatrix();
	glRotatef(angle, rotateX, rotateY, rotateZ);
	drawAxis();
	glPopMatrix();

	if (nChoice == 1) {
		glRotatef(angle, rotateX, rotateY, rotateZ);
		tetrahedron.SetColor(1);
		tetrahedron.DrawColor();
	}

	else if (nChoice == 2) {
		glRotatef(angle, rotateX, rotateY, rotateZ);
		cube.SetColor(1);
		cube.DrawColor();
	}

	else if (nChoice == 3) {
		glRotatef(angle, rotateX, rotateY, rotateZ);
		cylinder.SetColor(1);
		cylinder.DrawColor();
	}

	else if (nChoice == 4) {
		glRotatef(angle, rotateX, rotateY, rotateZ);
		shape1.SetColor(1);
		shape1.DrawColor();
	}

	else if (nChoice == 5) {
		glRotatef(angle, rotateX, rotateY, rotateZ);
		shape2.SetColor(2);
		shape2.DrawColor();
	}

	else if (nChoice == 6) {
		glRotatef(angle, rotateX, rotateY, rotateZ);
		shape3.SetColor(3);
		shape3.DrawColor();
	}

	else if (nChoice == 7) {
		glRotatef(angle, rotateX, rotateY, rotateZ);
		shape4.SetColor(4);
		shape4.DrawColor();
	}

	else if (nChoice == 8) {
		glRotatef(angle, rotateX, rotateY, rotateZ);
		shape5.SetColor(5);
		shape5.DrawColor();
	}
	else if (nChoice == 9) {
		glPushMatrix();
		glRotatef(angle, rotateX, rotateY, rotateZ);
		glTranslatef(-shape1_R * (2.1 / 0.8), (1.4 / 0.8) * shape1_R, 0);
		glRotatef(endAngle, 0, 0, 1);
		glTranslatef(shape1_R * (4 / 0.8), -(0.5 / 0.8) * shape1_R, -Depth);
		glRotatef(90, 1, 0, 0);
		shape1.SetColor(1);
		shape1.DrawColor();
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, rotateX, rotateY, rotateZ);
		glTranslatef((3.1 / 2.6) * shape4_W1, (3.85 / 2.6) * shape4_W1, 0);
		glRotatef(handleAngle, 0, 0, 1);
		glTranslatef(8.2, 0, -Depth);
		glRotatef(180, 0, 0, 1);
		glRotatef(90, 1, 0, 0);
		shape2.SetColor(2);
		shape2.DrawColor();
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, rotateX, rotateY, rotateZ);
		glTranslatef(-shape3_H1 * (1 + 1.2 / 5.3), 0, 0);
		glRotatef(90, 1, 0, 0);
		glRotatef(180, 0, 1, 0);
		shape3.SetColor(7);
		shape3.DrawColor();
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, rotateX, rotateY, rotateZ);
		glTranslatef(shape4_W1* (5.6 / 2.6), 0, 0);
		glRotatef(-90, 0, 1, 0);
		glRotatef(-90, 0, 0, 1);
		shape4.SetColor(4);
		shape4.DrawColor();
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, rotateX, rotateY, rotateZ);
		glTranslatef(x3, y3, 0);
		float tmp_angle = atan((y3 - y2) / (x3 - x2)) / PI * 180;
		if (tmp_angle < 0) tmp_angle = 180 + tmp_angle;
		glRotatef(tmp_angle, 0, 0, 1);
		glRotatef(90, 1, 0, 0);
		shape5.SetColor(9);
		shape5.DrawColor();
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, rotateX, rotateY, rotateZ);
		glTranslatef(-base_Width / 2.0, -base_Depth, -base_Height / 2.0);
		base.SetColor(8);
		base.DrawColor();
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, rotateX, rotateY, rotateZ);
		bulong1.SetColor(12);
		glTranslatef(-2.1, 1.4, Depth);
		glRotatef(-90, 1, 0, 0);
		bulong1.DrawColor();
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, rotateX, rotateY, rotateZ);
		bulong1.SetColor(12);
		glTranslatef(x3, y3, Depth);
		glRotatef(-90, 1, 0, 0);
		bulong1.DrawColor();
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, rotateX, rotateY, rotateZ);
		bulong1.SetColor(12);
		glTranslatef(x2, y2, Depth);
		glRotatef(-90, 1, 0, 0);
		bulong1.DrawColor();
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, rotateX, rotateY, rotateZ);
		bulong1.SetColor(12);
		glTranslatef(3.1, 3.85, Depth);
		glRotatef(-90, 1, 0, 0);
		bulong1.DrawColor();
		glPopMatrix();
	}

	glFlush();
	glutSwapBuffers();
}

void myKeyboard(unsigned char key, int x, int y) {
	if (key == '1') {
		if (handleAngle + 3 < 50) handleAngle = handleAngle + 3;
	}
	else if (key == '2') {
		if (handleAngle - 3 > -1) handleAngle = handleAngle - 3;
	}
	glutPostRedisplay();
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
		angleY += 5;
		angle = angleY;
		rotateX = 0; rotateY = 1; rotateZ = 0;
	}
	else if (key == GLUT_KEY_DOWN) {
		angleY -= 5;
		angle = angleY;
		rotateX = 0; rotateY = 1; rotateZ = 0;
	}
	else if (key == GLUT_KEY_PAGE_UP) {
		angleZ += 5;
		angle = angleZ;
		rotateX = 0; rotateY = 0; rotateZ = 1;
	}
	else if (key == GLUT_KEY_PAGE_DOWN) {
		angleZ -= 5;
		angle = angleZ;
		rotateX = 0; rotateY = 0; rotateZ = 1;
	}
	glutPostRedisplay();
}

void myInit()
{
	float	fHalfSize = 12;

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
	cout << "9. Show all" << endl;
	cout << "Input the choice: " << endl;
	cin >> nChoice;

	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("assignment 1927030"); // open the screen window

	tetrahedron.CreateTetrahedron();
	cube.CreateCube(1);
	cylinder.CreateCylinder(20, 4, 1);
	shape1.CreateShape1(shape1_R, shape1_Height, shape1_Width, Depth);
	shape2.CreateShape2(shape2_R1, shape2_R2, shape2_X1, shape2_X2, shape2_H1, shape2_H2, Depth);
	shape3.CreateShape3(shape3_R, shape3_W1, shape3_W2, shape3_H1, shape3_H2, shape3_H3, Depth);
	shape4.CreateShape4(shape4_W1, shape4_W2, shape4_H1, shape4_H2, shape4_R, Depth);
	shape5.CreateShape5(shape5_R, shape5_Height, Depth);
	base.CreateBase(base_Width, base_Height, base_Depth);
	bulong1.CreateCylinder(20, Depth * 2, shape3_R / 2.0);
	bulong2.CreateCylinder(20, Depth * 2, shape3_R / 2.0);
	bulong3.CreateCylinder(20, Depth * 2, shape3_R / 2.0);
	bulong4.CreateCylinder(20, Depth * 2, shape3_R / 2.0);
	myInit();
	glutDisplayFunc(myDisplay);
	glutSpecialFunc(mySpecialFunc);
	glutKeyboardFunc(myKeyboard);

	glutMainLoop();
	return 0;
}

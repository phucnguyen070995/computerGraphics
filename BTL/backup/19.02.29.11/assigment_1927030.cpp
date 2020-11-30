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

Mesh	cylinder;
Mesh	shape1;
Mesh	shape2;
Mesh	shape3;
Mesh	shape4;
Mesh	shape5;
Mesh	base;
Mesh	bulong1;

float shape1_R = 0.8, shape1_Height = 8.3, shape1_Width = 1.3, Depth = 0.75;
float shape2_R1 = 0.45, shape2_R2 = 0.6, shape2_X1 = 0.45, shape2_X2 = 0.75, shape2_H1 = 1.65, shape2_H2 = 8.1;
float shape3_R = 0.5, shape3_W1 = 0.9, shape3_W2 = 0.5, shape3_H1 = 5.3, shape3_H2 = 3.5, shape3_H3 = 0.8;
float shape4_W1 = 2.6, shape4_W2 = 0.1, shape4_H1 = 2.6, shape4_H2 = 1.25, shape4_R = 0.5;
float shape5_R = 0.6, shape5_Height = 1.7;
float base_Width = 15, base_Height = 4, base_Depth = 1;

float	handleAngle = 40;
float	endAngle;
float	angle = 0, angleX = 0, angleY = 0, angleZ = 0;
int		rotateX = 0;
int		rotateY = 0;
int		rotateZ = 0;
int		flag = 0;
int		view_flag = 0;
int		light = 0;

float		camera_angle = 135;
float		camera_height = 7.6;
float		camera_dis = 16.6;

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

void setupLight() {
	GLfloat	lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat	lightSpecular[] = { 0.9,0.9,0.9, 1.0f };
	GLfloat	lightAmbient[] = { 0.07,0.07,0.07, 1.0f };
	GLfloat light_position1[] = { 100.0f, 100.0f, 100.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat light_position2[] = { -100.0f, 100.0f, -100.0f, 0.0f };
	glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);
	glEnable(GL_LIGHT1);
	if (light == 0) {
		glEnable(GL_LIGHT1);
	}
	else glDisable(GL_LIGHT1);
}

void setupMaterial(float ambient[], float diffuse[], float specular[], float shiness)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}


void myInit()
{
	float	fHalfSize = 9;


	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (view_flag == 0) {
		gluPerspective(60, 2, 1, 1000);
	}
	else glOrtho(-fHalfSize * screenWidth / screenHeight, fHalfSize * screenWidth / screenHeight, -fHalfSize * 3 / 4, fHalfSize * 5 / 4, 0.1, 100);
}

void DrawCell(float x, float y, float width, float alpha) {
	glDisable(GL_LIGHTING);
	glColor4f(0.8, 0.8, 1.0, alpha);
	glBegin(GL_POLYGON);
	glVertex3f(x, 0, y + width);
	glVertex3f(x + width / 3.0, 0, y + width);
	glVertex3f(x + width / 2.0, 0, y + width / 2.0);
	glVertex3f(x, 0, y + width * 2 / 3.0);
	glEnd();
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);
	glColor4f(0.6, 0.6, 0.6, 1);
	glBegin(GL_POLYGON);
	glVertex3f(x, 0, y + width * 2 / 3.0);
	glVertex3f(x + width / 2.0, 0, y + width / 2.0);
	glVertex3f(x + width * 0.4, 0, y + width * 0.2);
	glVertex3f(x, 0, y + width / 3.0);
	glEnd();
	glEnable(GL_LIGHTING);
	
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHTING);
	glColor4f(0.8, 0.8, 1.0, alpha);
	glBegin(GL_POLYGON);
	glVertex3f(x, 0, y + width / 3.0);
	glVertex3f(x + width * 0.4, 0, y + width * 0.2);
	glVertex3f(x + width / 3.0, 0, y);
	glVertex3f(x, 0, y);
	glEnd();
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);
	glColor4f(0.6, 0.6, 0.6, 1);
	glBegin(GL_POLYGON);
	glVertex3f(x + width / 3.0, 0, y);
	glVertex3f(x + width * 0.4, 0, y + width * 0.2);
	glVertex3f(x + width * 0.7, 0, y + width * 0.1);
	glVertex3f(x + width * 2 / 3.0, 0, y);
	glEnd();
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);
	glColor4f(0.8, 0.8, 1.0, alpha);
	glBegin(GL_POLYGON);
	glVertex3f(x + width * 2 / 3.0, 0, y);
	glVertex3f(x + width * 0.7, 0, y + width * 0.1);
	glVertex3f(x + width , 0, y);
	glEnd();
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);
	glColor4f(0.8, 0.8, 1.0, alpha);
	glBegin(GL_POLYGON);
	glVertex3f(x + width, 0, y);
	glVertex3f(x + width * 0.9, 0, y + width * 0.3);
	glVertex3f(x + width, 0, y + width / 3.0);
	glEnd();
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);
	glColor4f(0.6, 0.6, 0.6, 1);
	glBegin(GL_POLYGON);
	glVertex3f(x + width, 0, y);
	glVertex3f(x + width * 0.7, 0, y + width * 0.1);
	glVertex3f(x + width * 0.75, 0, y + width * 0.25);
	glVertex3f(x + width * 0.9, 0, y + width * 0.3);
	glEnd();
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);
	glColor4f(0.6, 0.6, 0.6, 1);
	glBegin(GL_POLYGON);
	glVertex3f(x + width, 0, y + width / 3.0);
	glVertex3f(x + width * 0.9, 0, y + width * 0.3);
	glVertex3f(x + width * 0.8, 0, y + width * 0.6);
	glVertex3f(x + width, 0, y + width * 2 / 3.0);
	glEnd();
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);
	glColor4f(0.8, 0.8, 1.0, alpha);
	glBegin(GL_POLYGON);
	glVertex3f(x + width, 0, y + width * 2 / 3.0);
	glVertex3f(x + width, 0, y + width);
	glVertex3f(x + width * 2 / 3.0, 0, y + width);
	glVertex3f(x + width * 0.8, 0, y + width * 0.6);
	glEnd();
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);
	glColor4f(0.6, 0.6, 0.6, 1);
	glBegin(GL_POLYGON);
	glVertex3f(x + width * 2 / 3.0, 0, y + width);
	glVertex3f(x + width / 3.0, 0, y + width);
	glVertex3f(x + width / 2.0, 0, y + width / 2.0);
	glVertex3f(x + width * 0.8, 0, y + width * 0.6);
	glEnd();
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);
	glColor4f(0.8, 0.8, 1.0, alpha);
	glBegin(GL_POLYGON);
	glVertex3f(x + width * 0.75, 0, y + width * 0.25);
	glVertex3f(x + width * 0.9, 0, y + width * 0.3);
	glVertex3f(x + width * 0.8, 0, y + width * 0.6);
	glVertex3f(x + width / 2.0, 0, y + width / 2.0);
	glEnd();
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);
	glColor4f(0.8, 0.8, 1.0, alpha);
	glBegin(GL_POLYGON);
	glVertex3f(x + width / 2.0, 0, y + width / 2.0);
	glVertex3f(x + width * 0.75, 0, y + width * 0.25);
	glVertex3f(x + width * 0.7, 0, y + width * 0.1);
	glVertex3f(x + width * 0.4, 0, y + width * 0.2);
	glEnd();
	glEnable(GL_LIGHTING);
}

void DrawGroup4(float x, float y, float width, float alpha) {

	DrawCell(x, y, width, 0.6);

	glPushMatrix();
	glTranslatef(x , 0, y + 2 * width);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-x, 0, -y);
	DrawCell(x, y, width, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, 0, y + 2 * width);
	glRotatef(180, 0, 1, 0);
	glTranslatef(-x, 0, -y);
	DrawCell(x, y, width, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, 0, y);
	glRotatef(-90, 0, 1, 0);
	glTranslatef(-x, 0, -y);
	DrawCell(x, y, width, 0.6);
	glPopMatrix();
}


void myDisplay()
{
	myInit();
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
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	//glEnable(GL_COLOR_MATERIAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (view_flag == 0) {
		gluLookAt(camera_dis * cos(camera_angle / 180 * PI), camera_height, camera_dis * sin(camera_angle / 180 * PI), 0, 2, 0, 0, 1, 0);
	}
	else gluLookAt(0, 0, 15, 0, 0, 0, 0, 1, 0);
	/*cout << camera_dis << " " << camera_height << endl;*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setupLight();
	if (flag == 0) glEnable(GL_LIGHTING);
	else glDisable(GL_LIGHTING);

	glViewport(0, 0, screenWidth, screenHeight);

	if (1) {
		glPushMatrix();
		glTranslatef(-shape1_R * (2.1 / 0.8), (1.4 / 0.8) * shape1_R, 0);
		glRotatef(endAngle, 0, 0, 1);
		glTranslatef(shape1_R * (4 / 0.8), -(0.5 / 0.8) * shape1_R, -Depth);
		glRotatef(90, 1, 0, 0);

		//Set up Material---------------------------------
		GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0f };
		GLfloat diffuse[] = { 0.2, 0.2, 0.7765, 1.0f };
		GLfloat specular[] = { 0.7,0.7,0.7, 1.0f };
		GLfloat shiness = 120.8;
		setupMaterial(ambient, diffuse, specular, shiness);
		//-------------------------------------------

		shape1.Draw(flag);
		glPopMatrix();

		glPushMatrix();
		glTranslatef((3.1 / 2.6) * shape4_W1, (3.85 / 2.6) * shape4_W1, 0);
		glRotatef(handleAngle, 0, 0, 1);
		glTranslatef(8.2, 0, -Depth);
		glRotatef(180, 0, 0, 1);
		glRotatef(90, 1, 0, 0);

		//Set up Material---------------------------------
		GLfloat ambient1[] = { 0.2, 0.7765, 0.2, 1.0f };
		GLfloat diffuse1[] = { 0.2, 0.7765, 0.2, 1.0f };
		GLfloat specular1[] = { 0.7,0.7,0.7, 1.0f };
		GLfloat shiness1 = 120;
		setupMaterial(ambient1, diffuse1, specular1, shiness1);
		//-------------------------------------------

		shape2.Draw(flag);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-shape3_H1 * (1 + 1.2 / 5.3), 0, 0);
		glRotatef(90, 1, 0, 0);
		glRotatef(180, 0, 1, 0);

		//Set up Material---------------------------------
		GLfloat ambient2[] = { 0.7765, 0.4902, 0.3451, 1.0f };
		GLfloat diffuse2[] = { 0.7765, 0.4902, 0.3451, 1.0f };
		GLfloat specular2[] = { 0.7,0.7,0.7, 1.0f };
		GLfloat shiness2 = 120.8;
		setupMaterial(ambient2, diffuse2, specular2, shiness2);
		//-------------------------------------------

		shape3.Draw(flag);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(shape4_W1 * (5.6 / 2.6), 0, 0);
		glRotatef(-90, 0, 1, 0);
		glRotatef(-90, 0, 0, 1);

		shape4.Draw(flag);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(x3, y3, 0);
		float tmp_angle = atan((y3 - y2) / (x3 - x2)) / PI * 180;
		if (tmp_angle < 0) tmp_angle = 180 + tmp_angle;
		glRotatef(tmp_angle, 0, 0, 1);
		glRotatef(90, 1, 0, 0);

		//Set up Material---------------------------------
		GLfloat ambient3[] = { 0.7765, 0.2, 0.3451, 1.0f };
		GLfloat diffuse3[] = { 0.7765, 0.2, 0.3451, 1.0f };
		GLfloat specular3[] = { 0.7,0.7,0.7, 1.0f };
		GLfloat shiness3 = 120.8;
		setupMaterial(ambient3, diffuse3, specular3, shiness3);
		//-------------------------------------------

		shape5.Draw(flag);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-base_Width / 2.0, -base_Depth, -base_Height / 2.0);

		//Set up Material---------------------------------
		GLfloat ambient4[] = { 0.7765, 0.2, 0.2, 1.0f };
		GLfloat diffuse4[] = { 0.7765, 0.2, 0.2, 1.0f };
		GLfloat specular4[] = { 0.7,0.7,0.7, 1.0f };
		GLfloat shiness4 = 100.8;
		setupMaterial(ambient4, diffuse4, specular4, shiness4);
		//-------------------------------------------

		base.Draw(flag);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-2.2, 1.4, Depth);
		glRotatef(-90, 1, 0, 0);

		//Set up Material---------------------------------
		GLfloat ambient5[] = { 0.2, 0.2, 0.2, 1.0f };
		GLfloat diffuse5[] = { 0.2, 0.2, 0.2, 1.0f };
		GLfloat specular5[] = { 0.7,0.7,0.7, 1.0f };
		GLfloat shiness5 = 100.8;
		setupMaterial(ambient5, diffuse5, specular5, shiness5);
		//-------------------------------------------

		bulong1.Draw(flag);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(x3, y3, Depth);
		glRotatef(-90, 1, 0, 0);
		bulong1.Draw(flag);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(x2, y2, Depth);
		glRotatef(-90, 1, 0, 0);
		bulong1.Draw(flag);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(3.1, 3.85, Depth);
		glRotatef(-90, 1, 0, 0);
		bulong1.Draw(flag);
		glPopMatrix();

	}

	glPushMatrix();
	glTranslatef(0, -2 * base_Depth, 0);
	glScalef(1, -1, 1);
	if (1) {
		glPushMatrix();
		glTranslatef(-shape1_R * (2.1 / 0.8), (1.4 / 0.8) * shape1_R, 0);
		glRotatef(endAngle, 0, 0, 1);

		glTranslatef(shape1_R * (4 / 0.8), -(0.5 / 0.8) * shape1_R, -Depth);
		glRotatef(90, 1, 0, 0);

		//Set up Material---------------------------------
		GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0f };
		GLfloat diffuse[] = { 0.2, 0.2, 0.7765, 1.0f };
		GLfloat specular[] = { 0.7,0.7,0.7, 1.0f };
		GLfloat shiness = 120.8;
		setupMaterial(ambient, diffuse, specular, shiness);
		//-------------------------------------------

		shape1.Draw(flag);
		glPopMatrix();

		glPushMatrix();
		glTranslatef((3.1 / 2.6) * shape4_W1, (3.85 / 2.6) * shape4_W1, 0);
		glRotatef(handleAngle, 0, 0, 1);

		glTranslatef(8.2, 0, -Depth);
		glRotatef(180, 0, 0, 1);
		glRotatef(90, 1, 0, 0);

		//Set up Material---------------------------------
		GLfloat ambient1[] = { 0.2, 0.7765, 0.2, 1.0f };
		GLfloat diffuse1[] = { 0.2, 0.7765, 0.2, 1.0f };
		GLfloat specular1[] = { 0.7,0.7,0.7, 1.0f };
		GLfloat shiness1 = 120;
		setupMaterial(ambient1, diffuse1, specular1, shiness1);
		//-------------------------------------------

		shape2.Draw(flag);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-shape3_H1 * (1 + 1.2 / 5.3), 0, 0);
		glRotatef(90, 1, 0, 0);
		glRotatef(180, 0, 1, 0);

		//Set up Material---------------------------------
		GLfloat ambient2[] = { 0.7765, 0.4902, 0.3451, 1.0f };
		GLfloat diffuse2[] = { 0.7765, 0.4902, 0.3451, 1.0f };
		GLfloat specular2[] = { 0.7,0.7,0.7, 1.0f };
		GLfloat shiness2 = 120.8;
		setupMaterial(ambient2, diffuse2, specular2, shiness2);
		//-------------------------------------------

		shape3.Draw(flag);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(shape4_W1 * (5.6 / 2.6), 0, 0);
		glRotatef(-90, 0, 1, 0);
		glRotatef(-90, 0, 0, 1);

		shape4.Draw(flag);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(x3, y3, 0);
		float tmp_angle = atan((y3 - y2) / (x3 - x2)) / PI * 180;
		if (tmp_angle < 0) tmp_angle = 180 + tmp_angle;
		glRotatef(tmp_angle, 0, 0, 1);
		glRotatef(90, 1, 0, 0);

		//Set up Material---------------------------------
		GLfloat ambient3[] = { 0.7765, 0.2, 0.3451, 1.0f };
		GLfloat diffuse3[] = { 0.7765, 0.2, 0.3451, 1.0f };
		GLfloat specular3[] = { 0.7,0.7,0.7, 1.0f };
		GLfloat shiness3 = 120.8;
		setupMaterial(ambient3, diffuse3, specular3, shiness3);
		//-------------------------------------------

		shape5.Draw(flag);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-base_Width / 2.0, -base_Depth, -base_Height / 2.0);

		//Set up Material---------------------------------
		GLfloat ambient4[] = { 0.7765, 0.2, 0.2, 1.0f };
		GLfloat diffuse4[] = { 0.7765, 0.2, 0.2, 1.0f };
		GLfloat specular4[] = { 0.7,0.7,0.7, 1.0f };
		GLfloat shiness4 = 100.8;
		setupMaterial(ambient4, diffuse4, specular4, shiness4);
		//-------------------------------------------

		base.Draw(flag);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-2.2, 1.4, Depth);
		glRotatef(-90, 1, 0, 0);

		//Set up Material---------------------------------
		GLfloat ambient5[] = { 0.2, 0.2, 0.2, 1.0f };
		GLfloat diffuse5[] = { 0.2, 0.2, 0.2, 1.0f };
		GLfloat specular5[] = { 0.7,0.7,0.7, 1.0f };
		GLfloat shiness5 = 100.8;
		setupMaterial(ambient5, diffuse5, specular5, shiness5);
		//-------------------------------------------

		bulong1.Draw(flag);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(x3, y3, Depth);
		glRotatef(-90, 1, 0, 0);
		bulong1.Draw(flag);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(x2, y2, Depth);
		glRotatef(-90, 1, 0, 0);
		bulong1.Draw(flag);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(3.1, 3.85, Depth);
		glRotatef(-90, 1, 0, 0);
		bulong1.Draw(flag);
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -base_Depth ,0);
	glRotatef(30, 0, 1, 0);
	glDisable(GL_STENCIL_TEST);
	// Blend the floor onto the screen
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (int i = -100; i < 100; i=i+10) {
		for (int j = -100; j < 100; j = j + 10) {
			DrawGroup4(i, j, 5, 0.6);
		}
	}
	
	glDisable(GL_BLEND);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}


void myKeyboard(unsigned char key, int x, int y) {
	if (key == '1') {
		if (handleAngle + 1 < 49) handleAngle = handleAngle + 1;
	}
	else if (key == '2') {
		if (handleAngle - 1 > 1) handleAngle = handleAngle - 1;
	}
	else if (key == '+') {
		camera_dis += 0.2;
	}
	else if (key == '-') {
		camera_dis -= 0.2;
	}
	else if (key == 'W' || key == 'w') {
		flag = (flag + 1) % 2;
	}
	else if (key == 'V' || key == 'v') {
		view_flag = (view_flag + 1) % 2;
	}
	else if (key == 'D' || key == 'd') {
		light = (light + 1) % 2;
	}
	glutPostRedisplay();
}

void mySpecialFunc(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		camera_angle -= 1;
	}
	else if (key == GLUT_KEY_RIGHT) {
		camera_angle += 1;
	}
	else if (key == GLUT_KEY_UP) {
		camera_height += 0.2;
	}
	else if (key == GLUT_KEY_DOWN) {
		camera_height -= 0.2;
	}
	glutPostRedisplay();
}

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "1, 2: Xoay can dao" << endl;
	cout << "W, w: Chuyen doi qua lai giua che do khung day va to mau" << endl;
	cout << "V, v: Chuyen doi qua lai giua hai che do nhin khac nhau" << endl;
	cout << "D, d: Bat, tat nguon sang thu hai" << endl;
	cout << "+	 : Tang khoang cach camera" << endl;
	cout << "-	 : Giam khoang cach camera" << endl;
	cout << "up arrow  : Tang chieu cao camera" << endl;
	cout << "down arrow: Giam chieu cao camera" << endl;
	cout << "<-	: Quay camera theo chieu kim dong ho" << endl;
	cout << ">-	: Quay camera nguoc chieu kim dong ho" << endl;


	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("assignment-1927030"); // open the screen window

	shape1.CreateShape1(shape1_R, shape1_Height, shape1_Width, Depth);
	shape2.CreateShape2(shape2_R1, shape2_R2, shape2_X1, shape2_X2, shape2_H1, shape2_H2, Depth);
	shape3.CreateShape3(shape3_R, shape3_W1, shape3_W2, shape3_H1, shape3_H2, shape3_H3, Depth);
	shape4.CreateShape4(shape4_W1, shape4_W2, shape4_H1, shape4_H2, shape4_R, Depth);
	shape5.CreateShape5(shape5_R, shape5_Height, Depth);
	base.CreateBase(base_Width, base_Height, base_Depth);
	bulong1.CreateCylinder(20, Depth * 2, shape3_R / 2.0);

	myInit();
	glutDisplayFunc(myDisplay);
	glutSpecialFunc(mySpecialFunc);
	glutKeyboardFunc(myKeyboard);

	glutMainLoop();
	return 0;
}

#include <glut.h>
#include <math.h>

#define PI  3.1415926

float RSaokim = 2.5;
float RTraidat = RSaokim * 149600 / 108200;

void drawCircle(float x0, float y0, float R, int n = 40) {
	float x, y;
	float angleinc = 2 * PI / n; // angle increment each step
	float angle;
	glBegin(GL_LINE_LOOP);
	angle = 0;
	x = R * cos(angle);
	y = R * sin(angle);
	glVertex2f(x, y);
	for (int i = 1; i < n; i++) {
		angle += angleinc;
		x = R * cos(angle);
		y = R * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();
}

void myInit() {
	glClearColor(1, 1, 1, 1);
	glColor3f(0.0, 0.0, 0.0);



	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4.5, 4.5, -4.5, 4.5, -1.0, 1.0);
}

void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	drawCircle(0, 0, RTraidat, 100);
	drawCircle(0, 0, RSaokim, 100);

	float angleTraidatInc = 4;
	float factor = 365.25636 / 224.7008;
	float  angleSaokimInc = factor * angleTraidatInc;
	float xTraidat, yTraidat, xSaokim, ySaokim;
	float angleTraidat = 90, angleSaokim = 90;
	glBegin(GL_LINES);
	for (int i = 0; i <= (360.0 / angleTraidatInc) * 8; i++) {
		angleTraidat -= angleTraidatInc;
		angleSaokim -= angleSaokimInc;
		xTraidat = RTraidat * cos(angleTraidat * PI / 180);
		yTraidat = RTraidat * sin(angleTraidat * PI / 180);
		xSaokim = RSaokim * cos(angleSaokim * PI / 180);
		ySaokim = RSaokim * sin(angleSaokim * PI / 180);

		glVertex2f(xTraidat, yTraidat);
		glVertex2f(xSaokim, ySaokim);
	}
	glEnd();

	glFlush();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Example");

	myInit();

	glutDisplayFunc(mydisplay);
	glutMainLoop();
}
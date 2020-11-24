#include <glut.h>
#include <math.h>

#define PI 3.1415926
float R = 2;

struct Point2D {
	float x, y;
};

Point2D pointArr[10];

void drawPoint(Point2D p) {
	glBegin(GL_POINTS);
	glVertex2f(p.x, p.y);
	glEnd();
}

Point2D lineIntersection(Point2D p1, Point2D p2, Point2D p3, Point2D p4) {
	Point2D t;
	float A1, B1, A2, B2;

	A1 = (p2.y - p1.y) / (p2.x - p1.x);
	B1 = p1.y - A1 * p1.x;
	A2 = (p4.y - p3.y) / (p4.x - p3.x);
	B2 = p3.y - A2 * p3.x;
	t.x = (B2 - B1) / (A1 - A2);
	t.y = A1 * t.x + B1;
	return t;
}

void calculatePoints() {
	for (int i = 0; i < 5; i++) {
		pointArr[i].x = R * cos(PI / 2 + i * 2 * PI / 5);
		pointArr[i].y = R * sin(PI / 2 + i * 2 * PI / 5);
	}
	pointArr[5] = lineIntersection(pointArr[0], pointArr[2], pointArr[1], pointArr[4]);
	pointArr[6] = lineIntersection(pointArr[0], pointArr[2], pointArr[1], pointArr[3]);
	pointArr[7] = lineIntersection(pointArr[1], pointArr[3], pointArr[2], pointArr[4]);
	pointArr[8] = lineIntersection(pointArr[2], pointArr[4], pointArr[0], pointArr[3]);
	pointArr[9] = lineIntersection(pointArr[0], pointArr[3], pointArr[1], pointArr[4]);
}

void myInit() {
	calculatePoints();
	glClearColor(1, 0, 0, 1);
	glColor3f(1.0, 1.0, 0.0);



	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-4.5, 4.5, -3.0, 3.0);
}

void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(5);

	/*for (int i = 0; i < 10; i++) {
		drawPoint(pointArr[i]);
	}*/

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
	glVertex2f(pointArr[0].x, pointArr[0].y);
	glVertex2f(pointArr[5].x, pointArr[5].y);
	glVertex2f(pointArr[1].x, pointArr[1].y);
	glVertex2f(pointArr[6].x, pointArr[6].y);
	glVertex2f(pointArr[2].x, pointArr[2].y);
	glVertex2f(pointArr[7].x, pointArr[7].y);
	glVertex2f(pointArr[3].x, pointArr[3].y);
	glVertex2f(pointArr[8].x, pointArr[8].y);
	glVertex2f(pointArr[4].x, pointArr[4].y);
	glVertex2f(pointArr[9].x, pointArr[9].y);
	glVertex2f(pointArr[0].x, pointArr[0].y);
	glEnd();

	glFlush();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(600, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("National Flag");

	myInit();

	glutDisplayFunc(mydisplay);
	glutMainLoop();
}
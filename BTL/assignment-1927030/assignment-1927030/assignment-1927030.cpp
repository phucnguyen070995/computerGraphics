//#include "stdafx.h"
#include <windows.h>
#include <math.h>
#include <gl.h>
#include <glut.h>
#include "tchar.h"
#include <iostream>
#define PI			3.1415926
#define	COLORNUM		14

using namespace std;

class Point3
{
public:
	float x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	void set(Point3& p)
	{
		x = p.x; y = p.y; z = p.z;
	}
	Point3() { x = y = z = 0; }
	Point3(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}

};
class Color3
{
public:
	float r, g, b;
	void set(float red, float green, float blue)
	{
		r = red; g = green; b = blue;
	}
	void set(Color3& c)
	{
		r = c.r; g = c.g; b = c.b;
	}
	Color3() { r = g = b = 0; }
	Color3(float red, float green, float blue)
	{
		r = red; g = green; b = blue;
	}

};
class Point2
{
public:
	Point2() { x = y = 0.0f; } // constructor 1
	Point2(float xx, float yy) { x = xx; y = yy; } // constructor 2
	void set(float xx, float yy) { x = xx; y = yy; }
	float getX() { return x; }
	float getY() { return y; }
	void draw() {
		glBegin(GL_POINTS);
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();
	}
private:
	float 	x, y;
};
class IntRect
{
public:
	IntRect() { l = 0; r = 100; b = 0; t = 100; } // constructor
	IntRect(int left, int right, int bottom, int top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void set(int left, int right, int bottom, int top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void draw() {
		glRecti(l, b, r, t);
		glFlush();
	} // draw this rectangle using OpenGL
	int  getWidth() { return (r - l); }
	int  getHeight() { return (t - b); }
private:
	int	l, r, b, t;
};


class RealRect
{
public:
	RealRect() { l = 0; r = 100; b = 0; t = 100; } // constructor
	RealRect(float left, float right, float bottom, float top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void set(float left, float right, float bottom, float top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	float  getWidth() { return (r - l); }
	float  getHeight() { return (t - b); }
	void draw() {
		glRectf(l, b, r, t);
		glFlush();
	};// draw this rectangle using OpenGL
private:
	float	l, r, b, t;
};

class Vector3
{
public:
	float	x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	void set(Vector3& v)
	{
		x = v.x; y = v.y; z = v.z;
	}
	void flip()
	{
		x = -x; y = -y; z = -z;
	}
	void normalize();
	Vector3() { x = y = z = 0; }
	Vector3(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	Vector3(Vector3& v)
	{
		x = v.x; y = v.y; z = v.z;
	}
	Vector3 cross(Vector3 b);
	float dot(Vector3 b);
};

//=================================

class VertexID
{
public:
	int		vertIndex;
	int		colorIndex;
};

class Face
{
public:
	int		nVerts;
	VertexID* vert;
	Vector3		facenorm;

	Face()
	{
		nVerts = 0;
		vert = NULL;
	}
	~Face()
	{
		if (vert != NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

class Mesh
{
public:
	int		numVerts;
	Point3* pt;

	int		numFaces;
	Face* face;
public:
	Mesh()
	{
		numVerts = 0;
		pt = NULL;
		numFaces = 0;
		face = NULL;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}
		if (face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void DrawWireframe();
	void DrawColor();

	void CreateCylinder(int nSegment, float fHeight, float fRadius);
	void CreateShape1(float R, float Height, float Width, float Depth);
	void CreateShape2(float R1, float R2, float X1, float X2, float H1, float H2, float Depth);
	void CreateShape3(float R, float X1, float X2, float X3, float Z1, float Z2, float Y);
	void CreateShape4(float W1, float W2, float H1, float H2, float R, float Depth);
	void CreateShape5(float R, float Height, float Depth);
	void CreateBase(float Width, float Height, float Depth);
	void SetColor(int colorIdx);
	void Draw(int flag);
	void CalFacesNorm();
};

//=================================

Vector3 Vector3::cross(Vector3 b)
{
	Vector3 c(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	return c;
}
float Vector3::dot(Vector3 b)
{
	return x * b.x + y * b.y + z * b.z;
}
void Vector3::normalize()
{
	float temp = sqrt(x * x + y * y + z * z);
	x = x / temp;
	y = y / temp;
	z = z / temp;
}

//=================================

float	ColorArr[COLORNUM][3] = { {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, { 0.0,  0.0, 1.0},
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0},
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.5,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
									{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0} };

void Mesh::CreateCylinder(int numPoints, float fHeight, float fRadius)
{
	numVerts = numPoints * 2;
	pt = new Point3[numVerts];

	int		i;
	int		idx = 0;
	float	fAngle = 2 * PI / numPoints;

	for (i = 0; i < numPoints; i++)
	{
		pt[idx].x = fRadius * cos(fAngle * i);
		pt[idx].z = fRadius * sin(fAngle * i);
		pt[idx].y = -fHeight * 0.1;
		idx++;
	}

	// Nhân đôi số điểm (đổi depth của những điểm cũ ==> điểm mới)
	for (i = 0; i < numPoints; i++) {
		pt[idx].x = pt[i].x;
		pt[idx].z = pt[i].z;
		pt[idx].y = fHeight + fHeight * 0.1;
		idx++;
	}

	// Tạo các lưới đa giác (faces)
	numFaces = numPoints + 2;
	face = new Face[numFaces];

	idx = 0;

	// mặt dưới hình trụ
	face[idx].nVerts = numPoints;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = 0; i < numPoints; i++) {
		face[idx].vert[i].vertIndex = i;
	}
	idx++;

	int offset_idx = numPoints;

	// mặt trên hình trụ
	face[idx].nVerts = numPoints;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = numPoints - 1; i >= 0; i--) {
		face[idx].vert[numPoints - 1 - i].vertIndex = i + offset_idx;
	}
	idx++;

	// xung quanh
	for (int i = 0; i < numPoints - 1; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i;
		face[idx].vert[1].vertIndex = i + offset_idx;
		face[idx].vert[2].vertIndex = i + 1 + offset_idx;
		face[idx].vert[3].vertIndex = i + 1;
		idx++;
	}

	// mảnh cuối
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = numPoints - 1;
	face[idx].vert[1].vertIndex = numPoints - 1 + offset_idx;
	face[idx].vert[2].vertIndex = offset_idx;
	face[idx].vert[3].vertIndex = 0;
	idx++;
	CalFacesNorm();
}

void Mesh::CreateShape1(float R, float Height, float Width, float Depth) {
	float goc1 = atan(Width / (Height - R));
	float goc2 = acos(R / sqrt(Width * Width + (Height - R) * (Height - R)));
	float alpha = PI - goc1 - goc2;

	int numPoints = 10;

	this->numVerts = ((numPoints + 1) + 2) * 2;
	this->pt = new Point3[numVerts];

	int idx = 0;
	float angleInc = alpha / numPoints;

	// Tạo (numPoints + 1) điểm trên hình cung
	for (int i = 0; i <= numPoints; i++) {
		pt[idx].x = -Height + R * (1 - cos(angleInc * i));
		pt[idx].z = -R * sin(angleInc * i);
		pt[idx].y = 0;
		idx++;
	}

	// Điểm tiếp theo theo counter clockwise
	pt[idx].x = 0;
	pt[idx].z = -Width;
	pt[idx].y = 0;
	idx++;

	pt[idx].x = 0;
	pt[idx].z = 0;
	pt[idx].y = 0;
	idx++;

	// Nhân đôi số điểm (đổi depth của những điểm cũ ==> điểm mới)
	for (int i = 0; i < (numPoints + 1) + 2; i++) {
		pt[idx].x = pt[i].x;
		pt[idx].z = pt[i].z;
		pt[idx].y = Depth;
		idx++;
	}

	// Tạo các lưới đa giác (faces)
	numFaces = numPoints + 5;
	face = new Face[numFaces];

	idx = 0;

	// mặt dưới cung tròn
	face[idx].nVerts = numPoints + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = 0; i < numPoints + 3; i++) {
		face[idx].vert[i].vertIndex = i;
	}
	idx++;

	int offset_idx = numPoints + 3;

	// mặt trên hình trụ
	face[idx].nVerts = numPoints + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = numPoints + 2; i >= 0; i--) {
		face[idx].vert[numPoints + 2 - i].vertIndex = i + offset_idx;
	}
	idx++;

	// xung quanh
	for (int i = 0; i < numPoints + 2; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i;
		face[idx].vert[1].vertIndex = i + offset_idx;
		face[idx].vert[2].vertIndex = i + 1 + offset_idx;
		face[idx].vert[3].vertIndex = i + 1;
		idx++;
	}

	// mảnh cuối
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = numPoints + 2;
	face[idx].vert[1].vertIndex = numPoints + 2 + offset_idx;
	face[idx].vert[2].vertIndex = offset_idx;
	face[idx].vert[3].vertIndex = 0;
	idx++;
	CalFacesNorm();
}

void Mesh::CreateShape2(float R1, float R2, float X1, float X2, float H1, float H2, float Depth) {
	// Góc vòng cung bên trái
	float goc11 = atan(X1 / H1);
	float goc12 = acos(R1 / sqrt(X1 * X1 + H1 * H1));
	float alpha1 = PI - goc11 - goc12;

	// Góc vòng cung bên phải
	float goc21 = atan(X2 / H2);
	float goc22 = acos(R2 / sqrt(X2 * X2 + H2 * H2));
	float alpha2 = PI - goc21 - goc22;

	int numPoints = 5;
	this->numVerts = ((numPoints * 2 + 1) * 2 + 5) * 2;
	this->pt = new Point3[numVerts];

	int idx = 0;
	float angleInc = alpha1 / numPoints;

	// Tạo (numPoints + 1) điểm trên hình cung bên trái
	for (int i = 0; i <= numPoints; i++) {
		pt[idx].x = R1 - R1 * cos(angleInc * i);
		pt[idx].z = -R1 * sin(angleInc * i);
		pt[idx].y = 0;
		idx++;
	}

	// Các điểm rời rạc tiếp theo
	pt[idx].x = R1 + H1;
	pt[idx].z = -X1;
	pt[idx].y = 0;
	idx++;

	pt[idx].x = R1 + H1;
	pt[idx].z = 0;
	pt[idx].y = 0;
	idx++;

	pt[idx].x = R1 + H1;
	pt[idx].z = -X2;
	pt[idx].y = 0;
	idx++;

	angleInc = alpha2 / numPoints;

	// Tạo (numPoints + 1) điểm trên hình cung bên phải
	for (int i = 0; i <= numPoints; i++) {
		pt[idx].x = R1 + H1 + H2 + R2 * cos(alpha2 - angleInc * i);
		pt[idx].z = -R2 * sin(alpha2 - angleInc * i);
		pt[idx].y = 0;
		idx++;
	}
	// Nhân đôi số điểm theo trục đối xứng Ox
	for (int i = (numPoints + 1) * 2 + 1; i > 0; i--) {
		if (i == numPoints + 2) {
			continue;
		}
		pt[idx].x = pt[i].x;
		pt[idx].z = -1 * pt[i].z;
		pt[idx].y = 0;
		idx++;
	}
	// Nhân đôi thoe chiều cao
	for (int i = 0; i < ((numPoints * 2 + 1) * 2 + 5); i++) {
		pt[idx].x = pt[i].x;
		pt[idx].z = pt[i].z;
		pt[idx].y = Depth;
		idx++;
	}

	// Tạo các lưới đa giác (faces)
	numFaces = numPoints * 4 + 6 + 3 * 2;
	face = new Face[numFaces];

	idx = 0;

	//// góc phần 3 thứ 1 dưới
	face[idx].nVerts = numPoints + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = 0; i < numPoints + 3; i++) {
		face[idx].vert[i].vertIndex = i;
	}
	idx++;

	//// góc phần 3 thứ 2 dưới
	face[idx].nVerts = numPoints * 2 + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = 0; i < numPoints * 2 + 3; i++) {
		face[idx].vert[i].vertIndex = numPoints + 3 + i;
	}
	idx++;

	//// góc phần 3 thứ 3 dưới
	face[idx].nVerts = numPoints + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = numPoints + 2;
	for (int i = 1; i < numPoints + 2; i++) {
		face[idx].vert[i].vertIndex = 3 * numPoints + 5 + i;
	}
	face[idx].vert[numPoints + 2].vertIndex = 0;
	idx++;

	int offset_idx = (numPoints * 2 + 1) * 2 + 5;

	//// góc phần 3 thứ 1 trên
	face[idx].nVerts = numPoints + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = numPoints + 2; i >= 0; i--) {
		face[idx].vert[numPoints + 2 - i].vertIndex = i + offset_idx;
	}
	idx++;

	//// góc phần 3 thứ 2 trên
	face[idx].nVerts = numPoints * 2 + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = numPoints * 2 + 2; i >= 0; i--) {
		face[idx].vert[numPoints * 2 + 2 - i].vertIndex = numPoints + 3 + i + offset_idx;
	}
	idx++;

	//// góc phần 3 thứ 3 trên
	face[idx].nVerts = numPoints + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = offset_idx;
	for (int i = numPoints + 1; i >= 0; i--) {
		face[idx].vert[numPoints + 2 - i].vertIndex = 3 * numPoints + 5 + i + offset_idx;
	}
	face[idx].vert[numPoints + 2].vertIndex = numPoints + 2 + offset_idx;
	idx++;

	// xung quanh góc phần 3 thứ 1
	for (int i = 0; i < numPoints; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i;
		face[idx].vert[1].vertIndex = i + offset_idx;
		face[idx].vert[2].vertIndex = i + 1 + offset_idx;
		face[idx].vert[3].vertIndex = i + 1;
		idx++;
	}

	// Các mặt đa giác xung quanh
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = numPoints;
	face[idx].vert[1].vertIndex = numPoints + offset_idx;
	face[idx].vert[2].vertIndex = numPoints + 1 + offset_idx;
	face[idx].vert[3].vertIndex = numPoints + 1;
	idx++;

	// Các mặt đa giác xung quanh
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = numPoints + 1;
	face[idx].vert[1].vertIndex = numPoints + 1 + offset_idx;
	face[idx].vert[2].vertIndex = numPoints + 3 + offset_idx;
	face[idx].vert[3].vertIndex = numPoints + 3;
	idx++;

	// Các mặt đa giác xung quanh
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = numPoints + 3;
	face[idx].vert[1].vertIndex = numPoints + 3 + offset_idx;
	face[idx].vert[2].vertIndex = numPoints + 4 + offset_idx;
	face[idx].vert[3].vertIndex = numPoints + 4;
	idx++;

	// xung quanh góc phần 3 thứ 2
	for (int i = 0; i < numPoints * 2; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numPoints + 4 + i;
		face[idx].vert[1].vertIndex = numPoints + 4 + i + offset_idx;
		face[idx].vert[2].vertIndex = numPoints + 5 + i + offset_idx;
		face[idx].vert[3].vertIndex = numPoints + 5 + i;
		idx++;
	}

	// Các mặt đa giác xung quanh
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 3 * numPoints + 4;
	face[idx].vert[1].vertIndex = 3 * numPoints + 4 + offset_idx;
	face[idx].vert[2].vertIndex = 3 * numPoints + 5 + offset_idx;
	face[idx].vert[3].vertIndex = 3 * numPoints + 5;
	idx++;

	// Các mặt đa giác xung quanh
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 3 * numPoints + 5;
	face[idx].vert[1].vertIndex = 3 * numPoints + 5 + offset_idx;
	face[idx].vert[2].vertIndex = 3 * numPoints + 6 + offset_idx;
	face[idx].vert[3].vertIndex = 3 * numPoints + 6;
	idx++;

	// Các mặt đa giác xung quanh
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 3 * numPoints + 6;
	face[idx].vert[1].vertIndex = 3 * numPoints + 6 + offset_idx;
	face[idx].vert[2].vertIndex = 3 * numPoints + 7 + offset_idx;
	face[idx].vert[3].vertIndex = 3 * numPoints + 7;
	idx++;

	// xung quanh góc phần 3 thứ 3
	for (int i = 0; i < numPoints - 1; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 3 * numPoints + 7 + i;
		face[idx].vert[1].vertIndex = 3 * numPoints + 7 + i + offset_idx;
		face[idx].vert[2].vertIndex = 3 * numPoints + 8 + i + offset_idx;
		face[idx].vert[3].vertIndex = 3 * numPoints + 8 + i;
		idx++;
	}

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 4 * numPoints + 6;
	face[idx].vert[1].vertIndex = 4 * numPoints + 6 + offset_idx;
	face[idx].vert[2].vertIndex = offset_idx;
	face[idx].vert[3].vertIndex = 0;
	idx++;
	CalFacesNorm();
}

void Mesh::CreateShape3(float R, float W1, float W2, float H1, float H2, float H3, float Depth) {
	// Góc vòng cung dưới
	float goc11 = atan(H3 / W2);
	float goc12 = acos(R / sqrt(H3 * H3 + W2 * W2));
	float alpha1 = goc11 + goc12;

	// Góc vòng cung trên
	float goc21 = atan((W1 + W2) / (H1 - H2 - H3));
	float goc22 = acos(R / sqrt((W1 + W2) * (W1 + W2) + (H1 - H2 - H3) * (H1 - H2 - H3)));
	float alpha2 = goc21 + goc22;

	int numPoints = 15;
	this->numVerts = (numPoints + 5) * 2;
	this->pt = new Point3[numVerts];

	int idx = 0;
	float angleInc = (2 * PI - alpha1 - alpha2) / numPoints;

	// Điểm đầu tiên
	pt[idx].x = -H2;
	pt[idx].z = W1;
	pt[idx].y = 0;
	idx++;

	// Tạo (numPoints + 1) điểm trên hình cung bên trái
	for (int i = 0; i <= numPoints; i++) {
		pt[idx].x = -H2 - H3 + R * sin(alpha1 + angleInc * i);
		pt[idx].z = W1 + W2 - R * cos(alpha1 + angleInc * i);
		pt[idx].y = 0;
		idx++;
	}

	// Các điểm rời rạc tiếp theo
	pt[idx].x = -H1;
	pt[idx].z = 0;
	pt[idx].y = 0;
	idx++;

	pt[idx].x = 0;
	pt[idx].z = 0;
	pt[idx].y = 0;
	idx++;

	pt[idx].x = 0;
	pt[idx].z = W1;
	pt[idx].y = 0;
	idx++;

	// Nhân đôi thoe chiều cao
	for (int i = 0; i < numPoints + 5; i++) {
		pt[idx].x = pt[i].x;
		pt[idx].z = pt[i].z;
		pt[idx].y = Depth;
		idx++;
	}

	// Tạo các lưới đa giác (faces)
	numFaces = numPoints + 9;
	face = new Face[numFaces];

	idx = 0;

	// góc phần 2 thứ 1 dưới
	face[idx].nVerts = numPoints + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = 0; i < numPoints + 3; i++) {
		face[idx].vert[i].vertIndex = i;
	}
	idx++;

	// góc phần 2 thứ 2 dưới
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 0;
	face[idx].vert[1].vertIndex = numPoints + 2;
	face[idx].vert[2].vertIndex = numPoints + 3;
	face[idx].vert[3].vertIndex = numPoints + 4;
	idx++;

	int offset_idx = numPoints + 5;

	// góc phần 2 thứ 1 trên
	face[idx].nVerts = numPoints + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = numPoints + 2 + offset_idx;
	for (int i = numPoints + 1; i >= 0; i--) {
		face[idx].vert[numPoints + 2 - i].vertIndex = offset_idx + i;
	}
	idx++;

	// góc phần 2 thứ 2 trên
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = numPoints + offset_idx + 4;
	face[idx].vert[1].vertIndex = numPoints + offset_idx + 3;
	face[idx].vert[2].vertIndex = numPoints + offset_idx + 2;
	face[idx].vert[3].vertIndex = offset_idx;
	idx++;

	// xung quanh
	for (int i = 0; i < numPoints + 4; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i;
		face[idx].vert[1].vertIndex = i + offset_idx;
		face[idx].vert[2].vertIndex = i + 1 + offset_idx;
		face[idx].vert[3].vertIndex = i + 1;
		idx++;
	}

	// mảnh cuối
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = numPoints + 4;
	face[idx].vert[1].vertIndex = numPoints + 4 + offset_idx;
	face[idx].vert[2].vertIndex = offset_idx;
	face[idx].vert[3].vertIndex = 0;
	idx++;
	CalFacesNorm();
}

void Mesh::CreateShape4(float W1, float W2, float H1, float H2, float R, float Depth) {
	// Góc vòng cung bên trái
	float goc11 = atan(W2 / H2);
	float goc12 = acos(R / sqrt(W2 * W2 + H2 * H2));
	float alpha1 = goc11 + goc12;

	// Góc vòng cung bên phải
	float goc21 = atan((W1 - W2) / (H1 + H2));
	float goc22 = acos(R / sqrt((W1 - W2) * (W1 - W2) + (H1 + H2) * (H1 + H2)));
	float alpha2 = goc21 + goc22;

	int numPoints = 15;
	this->numVerts = (numPoints + 1 + 3) * 2;
	this->pt = new Point3[numVerts];
	int idx = 0;
	float angleInc = (2 * PI - alpha1 - alpha2) / numPoints;

	// Tạo (numPoints + 1) điểm trên hình cung bên trái
	for (int i = 0; i <= numPoints; i++) {
		pt[idx].x = -H1 - H2 + R * cos(alpha1 + angleInc * i);
		pt[idx].z = W1 - W2 + R * sin(alpha1 + angleInc * i);
		pt[idx].y = 0;
		idx++;
	}

	// Các điểm rời rạc tiếp theo
	pt[idx].x = 0;
	pt[idx].z = 0;
	pt[idx].y = 0;
	idx++;

	pt[idx].x = 0;
	pt[idx].z = W1;
	pt[idx].y = 0;
	idx++;

	pt[idx].x = -H1;
	pt[idx].z = W1;
	pt[idx].y = 0;
	idx++;

	// Nhân đôi thoe chiều cao
	for (int i = 0; i < numPoints + 1 + 3; i++) {
		pt[idx].x = pt[i].x;
		pt[idx].z = pt[i].z;
		pt[idx].y = Depth;
		idx++;
	}

	// Tạo các lưới đa giác (faces)
	numFaces = numPoints + 8;
	face = new Face[numFaces];

	idx = 0;

	// góc phần 2 thứ 1 dưới
	face[idx].nVerts = numPoints + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = 0; i < numPoints + 2; i++) {
		face[idx].vert[i].vertIndex = i;
	}
	face[idx].vert[numPoints + 2].vertIndex = numPoints + 3;
	idx++;

	// góc phần 2 thứ 2 dưới
	face[idx].nVerts = 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = numPoints + 1;
	face[idx].vert[1].vertIndex = numPoints + 2;
	face[idx].vert[2].vertIndex = numPoints + 3;
	idx++;

	int offset_idx = numPoints + 1 + 3;

	// góc phần 2 thứ 1 trên
	face[idx].nVerts = numPoints + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = numPoints + 3 + offset_idx;
	for (int i = numPoints + 1; i >= 0; i--) {
		face[idx].vert[numPoints + 2 - i].vertIndex = offset_idx + i;
	}
	idx++;

	// góc phần 2 thứ 2 trên
	face[idx].nVerts = 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = numPoints + offset_idx + 3;
	face[idx].vert[1].vertIndex = numPoints + offset_idx + 2;
	face[idx].vert[2].vertIndex = numPoints + offset_idx + 1;
	idx++;

	// xung quanh
	for (int i = 0; i < numPoints + 3; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i;
		face[idx].vert[1].vertIndex = i + offset_idx;
		face[idx].vert[2].vertIndex = i + 1 + offset_idx;
		face[idx].vert[3].vertIndex = i + 1;
		idx++;
	}

	// mảnh cuối
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = numPoints + 3;
	face[idx].vert[1].vertIndex = numPoints + 3 + offset_idx;
	face[idx].vert[2].vertIndex = offset_idx;
	face[idx].vert[3].vertIndex = 0;
	idx++;
	CalFacesNorm();
}

void Mesh::CreateShape5(float R, float Height, float Depth) {
	int numPoints = 15;
	this->numVerts = (numPoints + 1) * 4;
	this->pt = new Point3[numVerts];

	int idx = 0;
	float angleInc = PI / numPoints;

	// Tạo (numPoints + 1) điểm trên hình cung bên trái
	for (int i = 0; i <= numPoints; i++) {
		pt[idx].x = -R * sin(angleInc * i);
		pt[idx].z = R * cos(angleInc * i);
		pt[idx].y = 0;
		idx++;
	}

	// Tạo (numPoints + 1) điểm trên hình cung bên phải
	for (int i = 0; i <= numPoints; i++) {
		pt[idx].x = Height + R * sin(angleInc * i);
		pt[idx].z = -R * cos(angleInc * i);
		pt[idx].y = 0;
		idx++;
	}

	// Khúc này nhân đôi số điểm (đổi depth của những điểm cũ ==> điểm mới)
	for (int i = 0; i < (numPoints + 1) * 2; i++) {
		pt[idx].x = pt[i].x;
		pt[idx].z = pt[i].z;
		pt[idx].y = Depth;
		idx++;
	}

	// Tạo các lưới đa giác (faces)
	numFaces = numPoints * 2 + 4;
	face = new Face[numFaces];

	idx = 0;

	// mặt đáy
	face[idx].nVerts = (numPoints + 1) * 2;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = 0; i < (numPoints + 1) * 2; i++) {
		face[idx].vert[i].vertIndex = i;
	}
	idx++;

	int offset_idx = (numPoints + 1) * 2;

	// mặt trên
	face[idx].nVerts = (numPoints + 1) * 2;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = 0; i < (numPoints + 1) * 2; i++) {
		face[idx].vert[i].vertIndex = offset_idx * 2 - 1 - i;
	}
	idx++;


	// xung quanh
	for (int i = 0; i < numPoints * 2 + 1; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i;
		face[idx].vert[1].vertIndex = i + offset_idx;
		face[idx].vert[2].vertIndex = i + 1 + offset_idx;
		face[idx].vert[3].vertIndex = i + 1;
		idx++;
	}

	// mảnh cuối
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 2 * numPoints + 1;
	face[idx].vert[1].vertIndex = 2 * numPoints + 1 + offset_idx;
	face[idx].vert[2].vertIndex = offset_idx;
	face[idx].vert[3].vertIndex = 0;
	idx++;
	CalFacesNorm();
}

void Mesh::CreateBase(float Width, float Height, float Depth) {
	this->numVerts = 8;
	this->pt = new Point3[numVerts];
	int idx = 0;

	pt[idx].x = 0;
	pt[idx].z = 0;
	pt[idx].y = 0;
	idx++;

	pt[idx].x = Width;
	pt[idx].z = 0;
	pt[idx].y = 0;
	idx++;

	pt[idx].x = Width;
	pt[idx].z = Height;
	pt[idx].y = 0;
	idx++;

	pt[idx].x = 0;
	pt[idx].z = Height;
	pt[idx].y = 0;
	idx++;

	// Khúc này nhân đôi số điểm (đổi depth của những điểm cũ ==> điểm mới)
	for (int i = 0; i < 4; i++) {
		pt[idx].x = pt[i].x;
		pt[idx].z = pt[i].z;
		pt[idx].y = Depth;
		idx++;
	}

	// Tạo các lưới đa giác (faces)
	numFaces = 6;
	face = new Face[numFaces];

	idx = 0;
	// mặt đáy
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = 0; i < 4; i++) {
		face[idx].vert[i].vertIndex = i;
	}
	idx++;

	int offset_idx = 4;

	// mặt trên
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = 3; i >= 0; i--) {
		face[idx].vert[3 - i].vertIndex = i + offset_idx;
	}
	idx++;

	// xung quanh
	for (int i = 0; i < 3; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i;
		face[idx].vert[1].vertIndex = i + offset_idx;
		face[idx].vert[2].vertIndex = i + 1 + offset_idx;
		face[idx].vert[3].vertIndex = i + 1;
		idx++;
	}

	// mảnh cuối
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 3;
	face[idx].vert[1].vertIndex = 3 + offset_idx;
	face[idx].vert[2].vertIndex = offset_idx;
	face[idx].vert[3].vertIndex = 0;
	idx++;
	CalFacesNorm();
}

void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;
			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColor()
{
	/*glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCullFace(GL_BACK);*/
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			//int		ic = face[f].vert[v].colorIndex;

			glNormal3f(face[f].facenorm.x, face[f].facenorm.y, face[f].facenorm.z);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::SetColor(int colorIdx) {
	for (int f = 0; f < numFaces; f++)
	{
		for (int v = 0; v < face[f].nVerts; v++)
		{
			face[f].vert[v].colorIndex = colorIdx;
		}
	}
}

void Mesh::Draw(int flag) {
	if (flag == 0) this->DrawColor();
	else {
		this->SetColor(12);
		this->DrawWireframe();
	}
}

void Mesh::CalFacesNorm() {
	float mx, my, mz;
	int idx, next;
	for (int f = 0; f < numFaces; f++) {
		mx = 0;
		my = 0;
		mz = 0;
		for (int v = 0; v < face[f].nVerts; v++) {
			idx = v;
			next = (idx + 1) % face[f].nVerts;
			int p1 = face[f].vert[idx].vertIndex;
			int p2 = face[f].vert[next].vertIndex;

			mx = mx + (pt[p1].y - pt[p2].y) * (pt[p1].z + pt[p2].z);
			my = my + (pt[p1].z - pt[p2].z) * (pt[p1].x + pt[p2].x);
			mz = mz + (pt[p1].x - pt[p2].x) * (pt[p1].y + pt[p2].y);
		}
		face[f].facenorm.set(mx, my, mz);
		face[f].facenorm.normalize();
	}
};

//=============================================

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

float	shape2angle = 40;
float	shape1angle;
int		flag = 0;
int		view_flag = 0;
int		light = 0;

float		camera_angle = 115;
float		camera_height = 13.4;
float		camera_dis = 13.4;

void c_c_intersection(double x0, double y0, double r0, double x1, double y1, double r1, double& xi, double& yi, double& xi_prime, double& yi_prime) {
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
	glVertex3f(x + width, 0, y);
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
	glTranslatef(x, 0, y + 2 * width);
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
	double x2 = 3.1 - 2 * cos(shape2angle / 180 * PI);
	double y2 = 3.85 - 2 * sin(shape2angle / 180 * PI);
	double r2 = 1.7;
	double x3, y3, x3_prime, y3_prime;
	c_c_intersection(x1, y1, r1, x2, y2, r2, x3, y3, x3_prime, y3_prime);
	if (y3_prime < y3) {
		x3 = x3_prime;
		y3 = y3_prime;
	}
	/*cout << camera_angle << " " << camera_height << " " << camera_dis << endl;*/
	shape1angle = atan((y3 - 1.4) / 3.5) / PI * 180;

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
		glRotatef(shape1angle, 0, 0, 1);
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
		glRotatef(shape2angle, 0, 0, 1);
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
		glRotatef(shape1angle, 0, 0, 1);

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
		glRotatef(shape2angle, 0, 0, 1);

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
	glTranslatef(0, -base_Depth, 0);
	glRotatef(30, 0, 1, 0);
	glDisable(GL_STENCIL_TEST);
	// Blend the floor onto the screen
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (int i = -100; i < 100; i = i + 10) {
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
		if (shape2angle + 1 < 49) shape2angle = shape2angle + 1;
	}
	else if (key == '2') {
		if (shape2angle - 1 > 1) shape2angle = shape2angle - 1;
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
	glutCreateWindow("Nguyen Hoang Phuc - 1927030"); // open the screen window

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


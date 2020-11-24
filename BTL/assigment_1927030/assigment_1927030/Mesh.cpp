﻿#include "Mesh.h"
#include <math.h>
#include <windows.h>
#include <iostream>
#define PI			3.1415926
#define	COLORNUM		14


float	ColorArr[COLORNUM][3] = { {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, { 0.0,  0.0, 1.0},
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0},
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.5,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
									{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0} };

void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius)
{
	numVerts = nSegment * 2 + 2;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle = 2 * PI / nSegment;
	float	x, y, z;

	pt[0].set(0, fHeight / 2, 0);
	for (i = 0; i < nSegment; i++)
	{
		x = fRadius * cos(fAngle * i);
		z = fRadius * sin(fAngle * i);
		y = fHeight / 2;
		pt[i + 1].set(x, y, z);

		y = -fHeight / 2;
		pt[i + 1 + nSegment].set(x, y, z);
	}
	pt[numVerts - 1].set(0, -fHeight / 2, 0);

	numFaces = nSegment * 3;
	face = new Face[numFaces];

	idx = 0;
	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = i + 1;
		idx++;
	}

	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 1;
		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numVerts - 1;
		if (i < nSegment - 1)
			face[idx].vert[2].vertIndex = i + 2 + nSegment;
		else
			face[idx].vert[2].vertIndex = 1 + nSegment;
		face[idx].vert[1].vertIndex = i + 1 + nSegment;
		idx++;
	}

}

void Mesh::CreateCube(float	fSize)
{
	int i;

	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set(fSize, fSize, fSize);
	pt[2].set(fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set(fSize, -fSize, fSize);
	pt[6].set(fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);


	numFaces = 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for (i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for (i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;

}

void Mesh::CreateTetrahedron()
{
	int i;
	numVerts = 4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(1, 0, 0);
	pt[2].set(0, 1, 0);
	pt[3].set(0, 0, 1);

	numFaces = 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;


	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;


	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;


	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;
}

void Mesh::CreateCuboid(float	fSizeX, float fSizeY, float	fSizeZ) {
	int i;

	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-fSizeX, fSizeY, fSizeZ);
	pt[1].set(fSizeX, fSizeY, fSizeZ);
	pt[2].set(fSizeX, fSizeY, -fSizeZ);
	pt[3].set(-fSizeX, fSizeY, -fSizeZ);
	pt[4].set(-fSizeX, -fSizeY, fSizeZ);
	pt[5].set(fSizeX, -fSizeY, fSizeZ);
	pt[6].set(fSizeX, -fSizeY, -fSizeZ);
	pt[7].set(-fSizeX, -fSizeY, -fSizeZ);


	numFaces = 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for (i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for (i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;
}

void Mesh::CreateShape1(float R, float Height, float Width, float Depth) {
	float goc1 = atan(Width / Height);
	float goc2 = acos(R / sqrt(Width * Width + Height * Height));
	float alpha = PI - goc1 - goc2;

	int nSegments = 10;

	this->numVerts = ((nSegments + 1) + 3) * 2;
	this->pt = new Point3[numVerts];

	int idx = 0;
	float angleInc = alpha / nSegments;

	// Tạo (nSegments + 1) điểm trên hình cung
	for (int i = 0; i <= nSegments; i++) {
		pt[idx].x = -Height - R * cos(angleInc * i);
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

	// Tâm của cung tròn (idx = segment +3)
	pt[idx].x = -Height;
	pt[idx].z = 0;
	pt[idx].y = 0;
	idx++;

	// Khúc này nhân đôi số điểm (đổi depth của những điểm cũ ==> điểm mới)
	for (int i = 0; i < (nSegments + 1) + 3; i++) {
		pt[idx].x = pt[i].x;
		pt[idx].z = pt[i].z;
		pt[idx].y = Depth;
		idx++;
	}


	// Tạo các lưới đa giác (faces)
	numFaces = nSegments * 3 + 5;
	face = new Face[numFaces];

	idx = 0;

	// mặt dưới hình trụ
	for (int i = 0; i < nSegments; i++) {
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = nSegments + 3;
		face[idx].vert[1].vertIndex = i;
		face[idx].vert[2].vertIndex = i + 1;
		idx++;
	}
	int nOffset = nSegments + 1 + 3;

	// mặt trên hình trụ
	for (int i = 0; i < nSegments; i++) {
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = nSegments + 3 + nOffset;
		face[idx].vert[1].vertIndex = i + nOffset;
		face[idx].vert[2].vertIndex = i + 1 + nOffset;
		idx++;
	}

	// xung quanh hình trụ
	for (int i = 0; i < nSegments; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i;
		face[idx].vert[1].vertIndex = i + nOffset;
		face[idx].vert[2].vertIndex = i + 1 + nOffset;
		face[idx].vert[3].vertIndex = i + 1;
		idx++;
	}
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments;
	face[idx].vert[1].vertIndex = nSegments + 1;
	face[idx].vert[2].vertIndex = nSegments + 2;
	face[idx].vert[3].vertIndex = nSegments + 3;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments + 3 + nOffset;
	face[idx].vert[1].vertIndex = nSegments + 2 + nOffset;
	face[idx].vert[2].vertIndex = nSegments + 1 + nOffset;
	face[idx].vert[3].vertIndex = nSegments + 0 + nOffset;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments + 0;
	face[idx].vert[1].vertIndex = nSegments + 0 + nOffset;
	face[idx].vert[2].vertIndex = nSegments + 1 + nOffset;
	face[idx].vert[3].vertIndex = nSegments + 1;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments + 2;
	face[idx].vert[1].vertIndex = nSegments + 1;
	face[idx].vert[2].vertIndex = nSegments + 1 + nOffset;
	face[idx].vert[3].vertIndex = nSegments + 2 + nOffset;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 0;
	face[idx].vert[1].vertIndex = nOffset;
	face[idx].vert[2].vertIndex = nSegments + 2 + nOffset;
	face[idx].vert[3].vertIndex = nSegments + 2;
	idx++;
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

	int nSegments = 5;
	this->numVerts = ((nSegments * 2 + 1) * 2 + 5) * 2;
	this->pt = new Point3[numVerts];

	int idx = 0;
	float angleInc = alpha1 / nSegments;

	// Tạo (nSegments + 1) điểm trên hình cung bên trái
	for (int i = 0; i <= nSegments; i++) {
		pt[idx].x = R1 - R1 * cos(angleInc * i);
		pt[idx].z = - R1 * sin(angleInc * i);
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

	angleInc = alpha2 / nSegments;

	// Tạo (nSegments + 1) điểm trên hình cung bên phải
	for (int i = 0; i <= nSegments; i++) {
		pt[idx].x = R1 + H1 + H2 + R2 * cos(alpha2 - angleInc * i);
		pt[idx].z = -R2 * sin(alpha2 - angleInc * i);
		pt[idx].y = 0;
		idx++;
	}
	// Nhân đôi số điểm theo trục đối xứng Ox
	for (int i = (nSegments + 1) * 2 + 1; i > 0; i--) {
		if (i == nSegments + 2) {
			continue;
		}
		pt[idx].x = pt[i].x;
		pt[idx].z = -1 * pt[i].z;
		pt[idx].y = 0;
		idx++;
	}
	// Nhân đôi thoe chiều cao
	for (int i = 0; i < ((nSegments * 2 + 1) * 2 + 5); i++) {
		pt[idx].x = pt[i].x;
		pt[idx].z = pt[i].z;
		pt[idx].y = Depth;
		idx++;
	}

	// Tạo các lưới đa giác (faces)
	numFaces = nSegments * 4 + 6 + 3 * 2;
	face = new Face[numFaces];

	idx = 0;

	//// góc phần 3 thứ 1 dưới
	face[idx].nVerts = nSegments + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = 0; i < nSegments + 3; i++) {
		face[idx].vert[i].vertIndex = i;
	}
	idx++;

	//// góc phần 3 thứ 2 dưới
	face[idx].nVerts = nSegments * 2 + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = 0; i < nSegments * 2 + 3; i++) {
		face[idx].vert[i].vertIndex = nSegments + 3 + i;
	}
	idx++;

	//// góc phần 3 thứ 3 dưới
	face[idx].nVerts = nSegments + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments + 2;
	for (int i = 1; i < nSegments + 2; i++) {
		face[idx].vert[i].vertIndex = 3 * nSegments + 5 + i;
	}
	face[idx].vert[nSegments + 2].vertIndex = 0;
	idx++;

	int nOffset = (nSegments * 2 + 1) * 2 + 5;

	//// góc phần 3 thứ 1 trên
	face[idx].nVerts = nSegments + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = nSegments + 2; i >= 0; i--) {
		face[idx].vert[nSegments + 2 - i].vertIndex = i + nOffset;
	}
	idx++;

	//// góc phần 3 thứ 2 trên
	face[idx].nVerts = nSegments * 2 + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = nSegments * 2 + 2; i >= 0; i--) {
		face[idx].vert[nSegments * 2 + 2 - i].vertIndex = nSegments + 3 + i + nOffset;
	}
	idx++;

	//// góc phần 3 thứ 3 trên
	face[idx].nVerts = nSegments + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nOffset;
	for (int i = nSegments + 1; i >= 0; i--) {
		face[idx].vert[nSegments + 2 - i].vertIndex = 3 * nSegments + 5 + i + nOffset;
	}
	face[idx].vert[nSegments + 2].vertIndex = nSegments + 2 + nOffset;
	idx++;

	// xung quanh góc phần 3 thứ 1
	for (int i = 0; i < nSegments; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i;
		face[idx].vert[1].vertIndex = i + nOffset;
		face[idx].vert[2].vertIndex = i + 1 + nOffset;
		face[idx].vert[3].vertIndex = i + 1;
		idx++;
	}

	// Các mặt đa giác xung quanh
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments;
	face[idx].vert[1].vertIndex = nSegments + nOffset;
	face[idx].vert[2].vertIndex = nSegments + 1 + nOffset;
	face[idx].vert[3].vertIndex = nSegments + 1;
	idx++;

	// Các mặt đa giác xung quanh
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments + 1;
	face[idx].vert[1].vertIndex = nSegments + 1 + nOffset;
	face[idx].vert[2].vertIndex = nSegments + 3 + nOffset;
	face[idx].vert[3].vertIndex = nSegments + 3;
	idx++;

	// Các mặt đa giác xung quanh
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments + 3;
	face[idx].vert[1].vertIndex = nSegments + 3 + nOffset;
	face[idx].vert[2].vertIndex = nSegments + 4 + nOffset;
	face[idx].vert[3].vertIndex = nSegments + 4;
	idx++;

	// xung quanh góc phần 3 thứ 2
	for (int i = 0; i < nSegments * 2; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = nSegments + 4 + i;
		face[idx].vert[1].vertIndex = nSegments + 4 + i + nOffset;
		face[idx].vert[2].vertIndex = nSegments + 5 + i + nOffset;
		face[idx].vert[3].vertIndex = nSegments + 5 + i;
		idx++;
	}

	// Các mặt đa giác xung quanh
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 3 * nSegments + 4;
	face[idx].vert[1].vertIndex = 3 * nSegments + 4 + nOffset;
	face[idx].vert[2].vertIndex = 3 * nSegments + 5 + nOffset;
	face[idx].vert[3].vertIndex = 3 * nSegments + 5;
	idx++;

	// Các mặt đa giác xung quanh
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 3 * nSegments + 5;
	face[idx].vert[1].vertIndex = 3 * nSegments + 5 + nOffset;
	face[idx].vert[2].vertIndex = 3 * nSegments + 6 + nOffset;
	face[idx].vert[3].vertIndex = 3 * nSegments + 6;
	idx++;

	// Các mặt đa giác xung quanh
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 3 * nSegments + 6;
	face[idx].vert[1].vertIndex = 3 * nSegments + 6 + nOffset;
	face[idx].vert[2].vertIndex = 3 * nSegments + 7 + nOffset;
	face[idx].vert[3].vertIndex = 3 * nSegments + 7;
	idx++;

	// xung quanh góc phần 3 thứ 3
	for (int i = 0; i < nSegments - 1; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 3 * nSegments + 7 + i;
		face[idx].vert[1].vertIndex = 3 * nSegments + 7 + i + nOffset;
		face[idx].vert[2].vertIndex = 3 * nSegments + 8 + i + nOffset;
		face[idx].vert[3].vertIndex = 3 * nSegments + 8 + i;
		idx++;
	}

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 4 * nSegments + 6;
	face[idx].vert[1].vertIndex = 4 * nSegments + 6 + nOffset;
	face[idx].vert[2].vertIndex = nOffset;
	face[idx].vert[3].vertIndex = 0;
	idx++;
}

void Mesh::CreateShape3(float R, float X1, float X2, float X3, float Z1, float Z2, float Y) {
	// Danh sách điểm trên vòng cung bên trái
	float goc11 = atan(X3 / Z2);
	float goc12 = acos(R / sqrt(X3 * X3 + Z2 * Z2));
	float alpha1 = PI - goc11 - goc12;

	int nSegments = 9;

	this->numVerts = ((nSegments + 1) + 5 + (nSegments + 1)) * 2;
	this->pt = new Point3[numVerts];

	int idx = 0;
	float angleInc = alpha1 / nSegments;

	// Tạo (nSegments + 1) điểm trên hình cung bên trái
	for (int i = 0; i <= nSegments; i++) {
		pt[idx].x = -X2 - X3 + R * sin(angleInc * i);
		pt[idx].z = -Z1 - Z2 - R * cos(angleInc * i);
		pt[idx].y = 0;
		idx++;
	}

	// Điểm tiếp theo theo counter clockwise
	// Index = nSegments + 1
	pt[idx].x = - X2;
	pt[idx].z = - Z1;
	pt[idx].y = 0;
	idx++;	

	// nSegments + 2
	pt[idx].x = 0;
	pt[idx].z = - Z1;
	pt[idx].y = 0;
	idx++;	

	// nSegments + 3
	pt[idx].x = 0;
	pt[idx].z = 0;
	pt[idx].y = 0;
	idx++;	

	// nSegments + 4
	pt[idx].x = - X1;
	pt[idx].z = 0;
	pt[idx].y = 0;
	idx++;	

	// nSegments + 5 (tâm đường tròn)
	pt[idx].x = -X2 - X3;
	pt[idx].z = -Z1 - Z2;
	pt[idx].y = 0;
	idx++;

	// Danh sách điểm trên vòng cung bên phải
	float rightWidth = X1 - (X2 + X3);
	float rightHeight = Z1 + Z2;
	float goc21 = atan(rightWidth / rightHeight);
	float goc22 = acos(R / sqrt(rightWidth * rightWidth + rightHeight * rightHeight));
	float alpha2 = PI - goc21 - goc22;

	angleInc = alpha2 / nSegments;

	// Tạo (nSegments + 1) điểm trên hình cung
	for (int i = 0; i <= nSegments; i++) {
		pt[idx].x = -X2 - X3 - R * sin(angleInc * i);
		pt[idx].z = -Z1 - Z2 - R * cos(angleInc * i);
		pt[idx].y = 0;
		idx++;
	}

	// Khúc này nhân đôi số điểm (đổi depth của những điểm cũ ==> điểm mới)
	for (int i = 0; i < (nSegments + 1) * 2 + 5; i++) {
		pt[idx].x = pt[i].x;
		pt[idx].z = pt[i].z;
		pt[idx].y = Y;
		idx++;
	}

	// Tạo các lưới đa giác (faces)
	numFaces = nSegments * 3 * 2 + 13;
	face = new Face[numFaces];

	idx = 0;

	// mặt dưới hình trụ
	for (int i = 0; i < nSegments; i++) {
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = nSegments + 5;
		face[idx].vert[1].vertIndex = i;
		face[idx].vert[2].vertIndex = i + 1;
		idx++;
	}
	int nOffset = (nSegments + 1) + 5 + (nSegments + 1);

	// mặt trên hình trụ
	for (int i = 0; i < nSegments; i++) {
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = nSegments + 5 + nOffset;
		face[idx].vert[1].vertIndex = i + nOffset;
		face[idx].vert[2].vertIndex = i + 1 + nOffset;
		idx++;
	}

	// xung quanh hình trụ
	for (int i = 0; i < nSegments; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i;
		face[idx].vert[1].vertIndex = i + nOffset;
		face[idx].vert[2].vertIndex = i + 1 + nOffset;
		face[idx].vert[3].vertIndex = i + 1;
		idx++;
	}

	// Các mặt đa giác phía dưới
	face[idx].nVerts = 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments;
	face[idx].vert[1].vertIndex = nSegments + 5;
	face[idx].vert[2].vertIndex = nSegments + 1;
	idx++;

	face[idx].nVerts = 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments + 1;
	face[idx].vert[1].vertIndex = nSegments + 5;
	face[idx].vert[2].vertIndex = nSegments + 4;
	idx++;

	face[idx].nVerts = 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments + 4;
	face[idx].vert[1].vertIndex = nSegments + 5;
	face[idx].vert[2].vertIndex = nSegments + 6 + nSegments;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments + 1;
	face[idx].vert[1].vertIndex = nSegments + 4;
	face[idx].vert[2].vertIndex = nSegments + 3;
	face[idx].vert[3].vertIndex = nSegments + 2;
	idx++;

	// Các mặt đa giác phía trên
	face[idx].nVerts = 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments + nOffset;
	face[idx].vert[1].vertIndex = nSegments + 5 + nOffset;
	face[idx].vert[2].vertIndex = nSegments + 1 + nOffset;
	idx++;

	face[idx].nVerts = 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments + 1 + nOffset;
	face[idx].vert[1].vertIndex = nSegments + 5 + nOffset;
	face[idx].vert[2].vertIndex = nSegments + 4 + nOffset;
	idx++;

	face[idx].nVerts = 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments + 4 + nOffset;
	face[idx].vert[1].vertIndex = nSegments + 5 + nOffset;
	face[idx].vert[2].vertIndex = nSegments + 6 + nSegments + nOffset;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments + 1 + nOffset;
	face[idx].vert[1].vertIndex = nSegments + 4 + nOffset;
	face[idx].vert[2].vertIndex = nSegments + 3 + nOffset;
	face[idx].vert[3].vertIndex = nSegments + 2 + nOffset;
	idx++;

	// Các mặt đa giác xung quanh
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments;
	face[idx].vert[1].vertIndex = nSegments + nOffset;
	face[idx].vert[2].vertIndex = nSegments + 1 + nOffset;
	face[idx].vert[3].vertIndex = nSegments + 1;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments + 1;
	face[idx].vert[1].vertIndex = nSegments + 1 + nOffset;
	face[idx].vert[2].vertIndex = nSegments + 2 + nOffset;
	face[idx].vert[3].vertIndex = nSegments + 2;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments + 2;
	face[idx].vert[1].vertIndex = nSegments + 2 + nOffset;
	face[idx].vert[2].vertIndex = nSegments + 3 + nOffset;
	face[idx].vert[3].vertIndex = nSegments + 3;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments + 3;
	face[idx].vert[1].vertIndex = nSegments + 3 + nOffset;
	face[idx].vert[2].vertIndex = nSegments + 4 + nOffset;
	face[idx].vert[3].vertIndex = nSegments + 4;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments + 4;
	face[idx].vert[1].vertIndex = nSegments + 4 + nOffset;
	face[idx].vert[2].vertIndex = nSegments + 6 + nSegments + nOffset;
	face[idx].vert[3].vertIndex = nSegments + 6 + nSegments;
	idx++;

	// mặt dưới hình trụ bên phải
	for (int i = 0; i < nSegments; i++) {
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = nSegments + 5;
		face[idx].vert[1].vertIndex = i + (nSegments + 1) + 5;
		face[idx].vert[2].vertIndex = i + 1+ (nSegments + 1) + 5;
		idx++;
	}
	//int nOffset = (nSegments + 1) + 5 + (nSegments + 1);

	//// mặt trên hình trụ bên phải
	for (int i = 0; i < nSegments; i++) {
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = nSegments + 5 + nOffset;
		face[idx].vert[1].vertIndex = i + (nSegments + 1) + 5 + nOffset;
		face[idx].vert[2].vertIndex = i + 1 + (nSegments + 1) + 5 + nOffset;
		idx++;
	}

	//// xung quanh hình trụ bên phải
	for (int i = 0; i < nSegments; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i + (nSegments + 1) + 5;
		face[idx].vert[1].vertIndex = i + nOffset + (nSegments + 1) + 5;
		face[idx].vert[2].vertIndex = i + 1 + nOffset + (nSegments + 1) + 5;
		face[idx].vert[3].vertIndex = i + 1 + (nSegments + 1) + 5;
		idx++;
	}
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

	int nSegments = 15;
	this->numVerts = (nSegments + 1 + 3) * 2;
	this->pt = new Point3[numVerts];

	int idx = 0;
	float angleInc = (2 * PI - alpha1 - alpha2) / nSegments;

	// Tạo (nSegments + 1) điểm trên hình cung bên trái
	for (int i = 0; i <= nSegments; i++) {
		pt[idx].x = - H1 - H2 + R * cos(alpha1 + angleInc * i);
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

	pt[idx].x = - H1;
	pt[idx].z = W1;
	pt[idx].y = 0;
	idx++;

	// Nhân đôi thoe chiều cao
	for (int i = 0; i < nSegments + 1 + 3; i++) {
		pt[idx].x = pt[i].x;
		pt[idx].z = pt[i].z;
		pt[idx].y = Depth;
		idx++;
	}

	// Tạo các lưới đa giác (faces)
	numFaces = nSegments + 8;
	face = new Face[numFaces];

	idx = 0;

	// góc phần 2 thứ 1 dưới
	face[idx].nVerts = nSegments + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = 0; i < nSegments + 2; i++) {
		face[idx].vert[i].vertIndex = i;
	}
	face[idx].vert[nSegments + 2].vertIndex = nSegments + 3;
	idx++;

	// góc phần 2 thứ 2 dưới
	face[idx].nVerts = 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments + 1;
	face[idx].vert[1].vertIndex = nSegments + 2;
	face[idx].vert[2].vertIndex = nSegments + 3;
	idx++;
	
	int nOffset = nSegments + 1 + 3;

	// góc phần 2 thứ 1 trên
	face[idx].nVerts = nSegments + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments + 3 + nOffset;
	for (int i = nSegments + 1; i >= 0; i--) {
		face[idx].vert[nSegments + 2 - i].vertIndex = nOffset + i;
	}
	idx++;

	// góc phần 2 thứ 2 trên
	face[idx].nVerts = 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments + nOffset + 3;
	face[idx].vert[1].vertIndex = nSegments + nOffset + 2;
	face[idx].vert[2].vertIndex = nSegments + nOffset + 1;
	idx++;

	// xung quanh
	for (int i = 0; i < nSegments + 3; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i;
		face[idx].vert[1].vertIndex = i + nOffset;
		face[idx].vert[2].vertIndex = i + 1 + nOffset;
		face[idx].vert[3].vertIndex = i + 1;
		idx++;
	}

	// mảnh cuối
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments + 3;
	face[idx].vert[1].vertIndex = nSegments + 3 + nOffset;
	face[idx].vert[2].vertIndex = nOffset;
	face[idx].vert[3].vertIndex = 0;
	idx++;
}

void Mesh::CreateShape5(float R, float Height, float Depth) {
	int nSegments = 30;
	this->numVerts = (nSegments + 1) * 4;
	this->pt = new Point3[numVerts];

	int idx = 0;
	float angleInc = PI / nSegments;

	// Tạo (nSegments + 1) điểm trên hình cung bên trái
	for (int i = 0; i <= nSegments; i++) {
		pt[idx].x = - R * sin(angleInc * i);
		pt[idx].z = R * cos(angleInc * i);
		pt[idx].y = 0;
		idx++;
	}

	// Tạo (nSegments + 1) điểm trên hình cung bên phải
	for (int i = 0; i <= nSegments; i++) {
		pt[idx].x = Height + R * sin(angleInc * i);
		pt[idx].z = - R * cos(angleInc * i);
		pt[idx].y = 0;
		idx++;
	}

	// Khúc này nhân đôi số điểm (đổi depth của những điểm cũ ==> điểm mới)
	for (int i = 0; i < (nSegments + 1) * 2; i++) {
		pt[idx].x = pt[i].x;
		pt[idx].z = pt[i].z;
		pt[idx].y = Depth;
		idx++;
	}

	// Tạo các lưới đa giác (faces)
	numFaces = nSegments * 2 + 4;
	face = new Face[numFaces];

	idx = 0;

	// mặt đáy
	face[idx].nVerts = (nSegments + 1) * 2;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = 0; i < (nSegments + 1) * 2; i++) {
		face[idx].vert[i].vertIndex = i;
	}
	idx++;

	int nOffset = (nSegments + 1) * 2;

	// mặt trên
	face[idx].nVerts = (nSegments + 1) * 2;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = 0; i < (nSegments + 1) * 2; i++) {
		face[idx].vert[i].vertIndex = nOffset * 2 - 1 - i;
	}
	idx++;
	

	// xung quanh cung tròn bên trái
	for (int i = 0; i < nSegments; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i;
		face[idx].vert[1].vertIndex = i + nOffset;
		face[idx].vert[2].vertIndex = i + 1 + nOffset;
		face[idx].vert[3].vertIndex = i + 1;
		idx++;
	}

	// xung quanh cung tròn bên phải
	for (int i = 0; i < nSegments; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = nSegments + i;
		face[idx].vert[1].vertIndex = nSegments + i + nOffset;
		face[idx].vert[2].vertIndex = nSegments + i + 1 + nOffset;
		face[idx].vert[3].vertIndex = nSegments + i + 1;
		idx++;
	}

	// Các mặt đa giác xung quanh
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments;
	face[idx].vert[1].vertIndex = nSegments + nOffset;
	face[idx].vert[2].vertIndex = nSegments + 1 + nOffset;
	face[idx].vert[3].vertIndex = nSegments + 1;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 0;
	face[idx].vert[1].vertIndex = (nSegments + 1) * 2 - 1;
	face[idx].vert[2].vertIndex = (nSegments + 1) * 2 - 1 + nOffset;
	face[idx].vert[3].vertIndex = nOffset;
	idx++;
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

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColor()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;

			ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawPoint() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	glPointSize(3);
	glColor3f(1, 0, 0);
	for (int f = 0; f < numVerts; f++) {
		glBegin(GL_POINTS);
		glVertex3f(pt[f].x, pt[f].y, pt[f].z);
		glEnd();
	}
}


#include "Mesh.h"
#include <math.h>
#define PI			3.1415926
#define	COLORNUM		14


float	ColorArr[COLORNUM][3] = { {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, { 0.0,  0.0, 1.0},
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0},
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.5,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
									{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0} };

void Mesh::CreateCylinder(int nSegments, float fHeight, float fRadius)
{
	numVerts = nSegments * 2;
	pt = new Point3[numVerts];

	int		i;
	int		idx = 0;
	float	fAngle = 2 * PI / nSegments;

	for (i = 0; i < nSegments; i++)
	{
		pt[idx].x = fRadius * cos(fAngle * i);
		pt[idx].z = fRadius * sin(fAngle * i);
		pt[idx].y = -fHeight * 0.1;
		idx++;
	}

	// Nhân đôi số điểm (đổi depth của những điểm cũ ==> điểm mới)
	for (i = 0; i < nSegments; i++) {
		pt[idx].x = pt[i].x;
		pt[idx].z = pt[i].z;
		pt[idx].y = fHeight + fHeight * 0.1;
		idx++;
	}

	// Tạo các lưới đa giác (faces)
	numFaces = nSegments + 2;
	face = new Face[numFaces];

	idx = 0;

	// mặt dưới hình trụ
	face[idx].nVerts = nSegments;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = 0; i < nSegments; i++) {
		face[idx].vert[i].vertIndex = i;
	}
	idx++;

	int nOffset = nSegments;

	// mặt trên hình trụ
	face[idx].nVerts = nSegments;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = nSegments - 1; i >= 0; i--) {
		face[idx].vert[nSegments - 1 - i].vertIndex = i + nOffset;
	}
	idx++;

	// xung quanh
	for (int i = 0; i < nSegments - 1; i++) {
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
	face[idx].vert[0].vertIndex = nSegments - 1;
	face[idx].vert[1].vertIndex = nSegments - 1 + nOffset;
	face[idx].vert[2].vertIndex = nOffset;
	face[idx].vert[3].vertIndex = 0;
	idx++;
	CalculateFacesNorm();
}

void Mesh::CreateShape1(float R, float Height, float Width, float Depth) {
	float goc1 = atan(Width / (Height - R));
	float goc2 = acos(R / sqrt(Width * Width + (Height - R) * (Height - R)));
	float alpha = PI - goc1 - goc2;

	int nSegments = 10;

	this->numVerts = ((nSegments + 1) + 2) * 2;
	this->pt = new Point3[numVerts];

	int idx = 0;
	float angleInc = alpha / nSegments;

	// Tạo (nSegments + 1) điểm trên hình cung
	for (int i = 0; i <= nSegments; i++) {
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
	for (int i = 0; i < (nSegments + 1) + 2; i++) {
		pt[idx].x = pt[i].x;
		pt[idx].z = pt[i].z;
		pt[idx].y = Depth;
		idx++;
	}

	// Tạo các lưới đa giác (faces)
	numFaces = nSegments + 5;
	face = new Face[numFaces];

	idx = 0;

	// mặt dưới cung tròn
	face[idx].nVerts = nSegments + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = 0; i < nSegments + 3; i++) {
		face[idx].vert[i].vertIndex = i;
	}
	idx++;

	int nOffset = nSegments + 3;

	// mặt trên hình trụ
	face[idx].nVerts = nSegments + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = nSegments + 2; i >= 0; i--) {
		face[idx].vert[nSegments + 2 - i].vertIndex = i + nOffset;
	}
	idx++;

	// xung quanh
	for (int i = 0; i < nSegments + 2; i++) {
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
	face[idx].vert[0].vertIndex = nSegments + 2;
	face[idx].vert[1].vertIndex = nSegments + 2 + nOffset;
	face[idx].vert[2].vertIndex = nOffset;
	face[idx].vert[3].vertIndex = 0;
	idx++;
	CalculateFacesNorm();
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
	CalculateFacesNorm();
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

	int nSegments = 15;
	this->numVerts = (nSegments + 5) * 2;
	this->pt = new Point3[numVerts];

	int idx = 0;
	float angleInc = (2 * PI - alpha1 - alpha2) / nSegments;

	// Điểm đầu tiên
	pt[idx].x = -H2;
	pt[idx].z = W1;
	pt[idx].y = 0;
	idx++;

	// Tạo (nSegments + 1) điểm trên hình cung bên trái
	for (int i = 0; i <= nSegments; i++) {
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
	for (int i = 0; i < nSegments + 5; i++) {
		pt[idx].x = pt[i].x;
		pt[idx].z = pt[i].z;
		pt[idx].y = Depth;
		idx++;
	}

	// Tạo các lưới đa giác (faces)
	numFaces = nSegments + 9;
	face = new Face[numFaces];

	idx = 0;

	// góc phần 2 thứ 1 dưới
	face[idx].nVerts = nSegments + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = 0; i < nSegments + 3; i++) {
		face[idx].vert[i].vertIndex = i;
	}
	idx++;

	// góc phần 2 thứ 2 dưới
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 0;
	face[idx].vert[1].vertIndex = nSegments + 2;
	face[idx].vert[2].vertIndex = nSegments + 3;
	face[idx].vert[3].vertIndex = nSegments + 4;
	idx++;

	int nOffset = nSegments + 5;

	// góc phần 2 thứ 1 trên
	face[idx].nVerts = nSegments + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments + 2 + nOffset;
	for (int i = nSegments + 1; i >= 0; i--) {
		face[idx].vert[nSegments + 2 - i].vertIndex = nOffset + i;
	}
	idx++;

	// góc phần 2 thứ 2 trên
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments + nOffset + 4;
	face[idx].vert[1].vertIndex = nSegments + nOffset + 3;
	face[idx].vert[2].vertIndex = nSegments + nOffset + 2;
	face[idx].vert[3].vertIndex = nOffset;
	idx++;

	// xung quanh
	for (int i = 0; i < nSegments + 4; i++) {
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
	face[idx].vert[0].vertIndex = nSegments + 4;
	face[idx].vert[1].vertIndex = nSegments + 4 + nOffset;
	face[idx].vert[2].vertIndex = nOffset;
	face[idx].vert[3].vertIndex = 0;
	idx++;
	CalculateFacesNorm();
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
	CalculateFacesNorm();
}

void Mesh::CreateShape5(float R, float Height, float Depth) {
	int nSegments = 15;
	this->numVerts = (nSegments + 1) * 4;
	this->pt = new Point3[numVerts];

	int idx = 0;
	float angleInc = PI / nSegments;

	// Tạo (nSegments + 1) điểm trên hình cung bên trái
	for (int i = 0; i <= nSegments; i++) {
		pt[idx].x = -R * sin(angleInc * i);
		pt[idx].z = R * cos(angleInc * i);
		pt[idx].y = 0;
		idx++;
	}

	// Tạo (nSegments + 1) điểm trên hình cung bên phải
	for (int i = 0; i <= nSegments; i++) {
		pt[idx].x = Height + R * sin(angleInc * i);
		pt[idx].z = -R * cos(angleInc * i);
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


	// xung quanh
	for (int i = 0; i < nSegments * 2 + 1; i++) {
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
	face[idx].vert[0].vertIndex = 2 * nSegments + 1;
	face[idx].vert[1].vertIndex = 2 * nSegments + 1 + nOffset;
	face[idx].vert[2].vertIndex = nOffset;
	face[idx].vert[3].vertIndex = 0;
	idx++;
	CalculateFacesNorm();
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

	int nOffset = 4;

	// mặt trên
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i = 3; i >= 0; i--) {
		face[idx].vert[3 - i].vertIndex = i + nOffset;
	}
	idx++;

	// xung quanh
	for (int i = 0; i < 3; i++) {
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
	face[idx].vert[0].vertIndex = 3;
	face[idx].vert[1].vertIndex = 3 + nOffset;
	face[idx].vert[2].vertIndex = nOffset;
	face[idx].vert[3].vertIndex = 0;
	idx++;
	CalculateFacesNorm();
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

void Mesh::CalculateFacesNorm() {
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
#if !defined (_MESH_CLASS)
#define _MESH_CLASS

#include "supportClass.h"


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
	void DrawPoint();

	void CreateCylinder(int nSegment, float fHeight, float fRadius);
	void CreateShape1(float R, float Height, float Width, float Depth);
	void CreateShape2(float R1, float R2, float X1, float X2, float H1, float H2, float Depth);
	void CreateShape3(float R, float X1, float X2, float X3, float Z1, float Z2, float Y);
	void CreateShape4(float W1, float W2, float H1, float H2, float R, float Depth);
	void CreateShape5(float R, float Height, float Depth);
	void CreateBase(float Width, float Height, float Depth);
	void SetColor(int colorIdx);
	void Draw(int flag);
	void CalculateFacesNorm();
};

#endif
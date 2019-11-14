#pragma once
#include "noise.h"
#include "ppm.h"
#include <iostream>
#include <algorithm>
#include <cmath>

class Mesh {
public:
	Mesh(unsigned newlength, unsigned newwidth);
	Mesh(Mesh world, Mesh color);

	unsigned getLength() { return length; }
	unsigned getWidth() { return width; }
	unsigned getVerticesSize() { return verticesSize; }
	unsigned getIndicesSize() { return indicesSize; }
	float* getvertices() { return vertices; }
	unsigned* getindices() { return indices; }

	unsigned getVAO() { return VAO; }
	unsigned getVBO() { return VBO; }
	unsigned getEBO() { return EBO; }

	float getHeight(unsigned x, unsigned y);
	void setHeight(unsigned x, unsigned y, float z);

	void initializeAtZero();
	void translateMesh(int dx, int dy);

	void bindData();
	void bindColor();
	void drawMesh();

	void noisemap(int seed);

	Mesh createStraightRiver(int startx, int starty);
	Mesh createCurvyRiver(int startx, int starty);
	void straightInterpolation(int x0, int x1, int y0, int y1);
	void riverInterpolation(int x0, int x1, int y0, int y1);

	Mesh createColorMesh();

	void deleteMeshBuffers();

private:
	unsigned length;
	unsigned width;
	unsigned verticesSize;
	unsigned indicesSize;
	float* vertices;
	unsigned* indices;

	unsigned VAO, VBO, EBO;
};

float bilinearInterpolation(float bottomLeft, float topLeft, float bottomRight, float topRight, float xMin, float xMax, float yMin, float yMax, float xToCalc, float yToCalc);
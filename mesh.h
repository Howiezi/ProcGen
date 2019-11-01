#pragma once
#include "noise.h"
#include "ppm.h"
#include <iostream>
#include <algorithm>
#include <cmath>

class Mesh {
public:
	Mesh(unsigned length, unsigned width);

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
	void bindData();
	void drawMesh();

private:
	unsigned length;
	unsigned width;
	unsigned verticesSize;
	unsigned indicesSize;
	float* vertices;
	unsigned* indices;

	unsigned VAO, VBO, EBO;
};
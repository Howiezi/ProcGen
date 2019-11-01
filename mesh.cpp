#include "mesh.h"
#include "GLFunctions.h"

Mesh::Mesh(unsigned length, unsigned width) {
	this->length = length;
	this->width = width;
	this->verticesSize = length * width * 3;
	this->indicesSize = (length - 1) * (width - 1) * 6;
	this->vertices = new float[verticesSize];
	this->indices = new unsigned[indicesSize];

	this->VAO = GLgenVAO();
	this->VBO = GLgenVBO();
	this->EBO = GLgenEBO();
}

float Mesh::getHeight(unsigned x, unsigned y) {
	return vertices[x * 3 + y * width*3 + 2];
}

void Mesh::setHeight(unsigned x, unsigned y, float height) {
	vertices[x * 3 + y * width * 3 + 2] = height;
}

void Mesh::initializeAtZero() {
	std::cout << width << std::endl;
	for (unsigned i = 0; i < verticesSize / 3; i++) {
		vertices[i * 3] = 0.0f + i % width;
		vertices[1 + i * 3] = 0.0f + i / width;
		vertices[2 + i * 3] = 0.0f;
	}
	
	for (unsigned i = 0; i < indicesSize/6; i++) {
		indices[i * 6] = i / (width - 1) + i;
		indices[1 + i * 6] = i / (width - 1) + i + 1;
		indices[2 + i * 6] = i / (width - 1) + i + width;
		indices[3 + i * 6] = i / (width - 1) + i + 1;
		indices[4 + i * 6] = i / (width - 1) + i + width;
		indices[5 + i * 6] = i / (width - 1) + i + width + 1;
	}
}

void Mesh::translateMesh(int dx, int dy) {
	for (unsigned i = 0; i < verticesSize / 3; i++) {
		//std::cout << vertices[i * 3] << " " << vertices[1 + i * 3] << std::endl;
		vertices[i * 3] += (float)dx;
		vertices[1 + i * 3] += (float)dy;
		//std::cout << vertices[i * 3] << " " << vertices[1 + i * 3] << std::endl;
	}
}

void Mesh::bindData() {
	GLbindVAO(VAO);
	GLbindVBO(VBO);
	GLbufferVBO(vertices, verticesSize);
	GLbindEBO(EBO);
	GLbufferEBO(indices, indicesSize);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	GLunbindVBO();
	GLunbindVAO();
}

void Mesh::drawMesh() {
	GLbindVAO(VAO);
	GLdrawEBOTriangles(indicesSize);
	GLunbindVAO();
}

void Mesh::noisemap(int seed) {
	ppm image(length, width);

	PerlinNoise pn(seed);

	unsigned int kk = 0;

	for (unsigned i = 0; i < length; i++) {
		for (unsigned j = 0; j < width; j++) {
			double x = (double)j / ((double)width);
			double y = (double)i / ((double)length);

			double n = pn.noise(25 * x, 25 * y, 0.8);

			image.r[kk] = floor(255 * n);
			image.g[kk] = floor(255 * n);
			image.b[kk] = floor(255 * n);
			kk++;

			float zn = (float)n * 10;

			setHeight(j, i, zn);
		}
	}

	image.write("noisemap.ppm");
}

Mesh Mesh::createRiver(int x, int y) {
	float currentHeight = getHeight(x, y);
	int riverLength = rand() % 80 + 40;
	int riverWidth = rand() % 5 + 2;
	float dh = currentHeight / riverLength;
	Mesh river(riverLength, riverWidth+2);
	river.initializeAtZero();
	river.translateMesh(x-1, y);
	std::cout << riverLength << std::endl;
	std::cout << riverWidth << std::endl;
	for (int itery = 0; itery < riverLength; itery++) {
		for (int iterx = 0; iterx < riverWidth; iterx++) {
			setHeight(x+iterx, y, currentHeight);
			river.setHeight(iterx, itery, currentHeight + 0.4f);
			river.setHeight(iterx+1, itery, currentHeight + 0.4f);
			river.setHeight(iterx+2, itery, currentHeight + 0.4f);
		}
		setHeight(x+riverWidth, y, currentHeight + 0.5f);
		setHeight(x-1, y, currentHeight + 0.5f);
		currentHeight -= dh;
		y += 1;
	}
	return river;
}

void Mesh::deleteMeshBuffers() {
	GLdeleteVAO(VAO);
	GLdeleteVBO(VBO);
	GLdeleteEBO(EBO);
}
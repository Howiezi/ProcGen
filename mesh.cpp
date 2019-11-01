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
	return vertices[x * 3 + y * width + 2];
}

void Mesh::setHeight(unsigned x, unsigned y, float height) {
	vertices[x * 3 + y * width + 2] = height;
}

void Mesh::initializeAtZero() {
	std::cout << width << std::endl;
	for (unsigned i = 0; i < verticesSize / 12; i++) {
		vertices[i * 12] = -0.5f + i % width;
		vertices[1 + i * 12] = -0.5f + i / width;
		vertices[2 + i * 12] = 0.0f;

		vertices[3 + i * 12] = 0.5f + i % width;
		vertices[4 + i * 12] = -0.5f + i / width;
		vertices[5 + i * 12] = 0.0f;

		vertices[6 + i * 12] = 0.5f + i % width;
		vertices[7 + i * 12] = 0.5f + i / width;
		vertices[8 + i * 12] = 0.0f;

		vertices[9 + i * 12] = -0.5f + i % width;
		vertices[10 + i * 12] = 0.5f + i / width;
		vertices[11 + i * 12] = 0.0f;
	}
	
	for (unsigned i = 0; i < indicesSize/6; i++) {
		indices[i * 6] = i * 3;
		indices[1 + i * 6] = i * 3 + 3;
		indices[2 + i * 6] = i * 3 + 3 * width;
		indices[3 + i * 6] = i * 3 + 3;
		indices[4 + i * 6] = i * 3 + 3 * width;
		indices[5 + i * 6] = i * 3 + 3 * width + 3;
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
	//GLunbindVBO();
	//GLunbindVAO();
}

void Mesh::drawMesh() {
	GLbindVAO(VAO);
	GLdrawEBOTriangles(indicesSize);
	GLunbindVAO();
}
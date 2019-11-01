#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

unsigned GLgenVAO() {
	unsigned vao;
	glGenVertexArrays(1, &vao);
	return vao;
}

void GLbindVAO(unsigned vao) {
	glBindVertexArray(vao);
}

void GLunbindVAO() {
	glBindVertexArray(0);
}

void GLdeleteVAO(unsigned vao) {
	glDeleteVertexArrays(1, &vao);
}

unsigned GLgenVBO() {
	unsigned vbo;
	glGenBuffers(1, &vbo);
	return vbo;
}

void GLbindVBO(unsigned vbo) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void GLunbindVBO() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLdeleteVBO(unsigned vbo) {
	glDeleteBuffers(1, &vbo);
}

void GLbufferVBO(float* vertices, unsigned verticesSize) {
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*verticesSize, vertices, GL_STATIC_DRAW);
}

unsigned GLgenEBO() {
	unsigned ebo;
	glGenBuffers(1, &ebo);
	return ebo;
}

void GLbindEBO(GLuint ebo) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void GLunbindEBO() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLdeleteEBO(unsigned ebo) {
	glDeleteBuffers(1, &ebo);
}

void GLbufferEBO(unsigned *indices, unsigned indicesSize) {
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned)*indicesSize, indices, GL_STATIC_DRAW);
}

void GLdrawEBOTriangles(unsigned indicesSize) {
	//std::cout << indicesSize << std::endl;
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
}
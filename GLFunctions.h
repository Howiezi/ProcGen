#pragma once

#include "glad/glad.h"

void GLgenVAO(GLuint vao) {
	glGenVertexArrays(1, &vao);
}

void GLbindVAO(GLuint vao) {
	glBindVertexArray(vao);
}

void GLunbindVAO() {
	glBindVertexArray(0);
}

void GLgenBuffer(GLuint buffer) {
	glGenBuffers(1, &buffer);
}

void GLbindVBO(GLuint vbo) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void GLunbindVBO() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLbufferVBO(float* vertices) {
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void GLbindEBO(GLuint ebo) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void GLunbindEBO() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLbufferEBO(unsigned *indices) {
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void GLdrawEBOTriangles(unsigned indicesSize) {
	std::cout << indicesSize << std::endl;
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
}

void GLgenMeshVertexBuffers(GLuint vao, GLuint vbo, GLuint ebo) {
	GLgenVAO(vao);
	GLgenBuffer(vbo);
	GLgenBuffer(ebo);
}

class GLobject {
public:
	GLobject() {}

	GLuint getVAO() { return vao; }
	GLuint getVBO() { return vbo; }
	GLuint getEBO() { return ebo; }
private:
	GLuint vao, vbo, ebo;
};
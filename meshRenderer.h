#pragma once
#include "GLFunctions.h"
#include "mesh.h"

void drawMesh(Mesh mesh, GLuint vao, GLuint vbo, GLuint ebo) {
	GLgenMeshVertexBuffers(vao, vbo, ebo);
	GLbindVAO(vao);
	GLbindVBO(vbo);
	GLbufferVBO(mesh.getvertices());
	GLbindEBO(ebo);
	GLbufferEBO(mesh.getindices());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	GLdrawEBOTriangles(mesh.getIndicesSize());
}
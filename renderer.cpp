#include "renderer.h"

Renderer::Renderer(int id) {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	vid = id;

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}
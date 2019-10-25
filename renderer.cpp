#include "renderer.h"

Renderer::Renderer() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

Renderer::Renderer(float *data, int size,int id) {
	glGenVertexArrays(id, &VAO);
	glGenBuffers(id, &VBO);
	vid = id;

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

}
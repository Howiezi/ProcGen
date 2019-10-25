#pragma once
#include "glad/glad.h"

class Renderer {
public:
	Renderer();

	Renderer(float *data, int size);

	unsigned int getVBO() { return this->VBO; }

	unsigned int getVAO() { return this->VAO; }

private:
	unsigned int VBO, VAO;

};
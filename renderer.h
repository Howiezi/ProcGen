#pragma once
#include "glad/glad.h"

class Renderer {
public:
	Renderer(int id);

	unsigned int getVBO() { return this->VBO; }

	unsigned int getVAO() { return this->VAO; }

	int getId() { return this->vid; }

private:
	unsigned int VBO, VAO;
	int vid;

};
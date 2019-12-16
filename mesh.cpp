#include "mesh.h"
#include "GLFunctions.h"

Mesh::Mesh(unsigned newlength, unsigned newwidth) {
	this->length = newlength;
	this->width = newwidth;
	this->verticesSize = newlength * newwidth * 3;
	this->indicesSize = (newlength - 1) * (newwidth - 1) * 6;
	this->vertices = new float[verticesSize];
	this->indices = new unsigned[indicesSize];

	this->VAO = GLgenVAO();
	this->VBO = GLgenVBO();
	this->EBO = GLgenEBO();
}

Mesh::Mesh(Mesh world, Mesh color) {
	length = world.getLength() + color.getLength();
	width = world.getWidth();
	verticesSize = length * width * 3;
	indicesSize = (world.getLength() - 1) * (world.getWidth() - 1) * 6;
	vertices = new float[verticesSize];
	indices = new unsigned[indicesSize];
	for (int i = 0; i < world.getVerticesSize() + color.getVerticesSize(); i++) {
		if (i < world.getVerticesSize()) {
			vertices[i] = world.getvertices()[i];
		}
		else {
			vertices[i] = color.getvertices()[i - world.getVerticesSize()];
		}
	}
	indices = world.getindices();

	VAO = GLgenVAO();
	VBO = GLgenVBO();
	EBO = GLgenEBO();
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
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(verticesSize/2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	GLunbindVBO();
	GLunbindVAO();
}

void Mesh::bindColor() {
	GLbindVAO(VAO);
	GLbindVBO(VBO);
	GLbufferVBO(vertices, verticesSize);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
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

void Mesh::createMountain(int x, int y) {
	int mountainHeight = rand() % 2 + 8;
	setHeight(x, y,mountainHeight);
	float polHeight;
	float farHeight;
	float nearHeight = mountainHeight;
	for (int pol = 1; pol < 5; pol++) {
		float farHeight = getHeight(x + 5, y);
		float polHeight;
		if (nearHeight > farHeight) {
			polHeight = (nearHeight - farHeight) * (1.0f - pol / 5.0f);
			polHeight = fade(polHeight / nearHeight);
			polHeight = polHeight * nearHeight;
			polHeight += farHeight;
		}
		else {
			polHeight = (farHeight - nearHeight) * (pol / 5.0f);
			polHeight = fade(polHeight / farHeight);
			polHeight = polHeight * farHeight;
			polHeight += nearHeight;

		}
		//std::cout << nearHeight << " " << farHeight << " " << pol << " " << polHeight << std::endl;
		setHeight(x + pol, y, polHeight);
		farHeight = getHeight(x - pol, y);
		if (nearHeight > farHeight) {
			polHeight = (nearHeight - farHeight) * (1.0f - pol / 5.0f);
			polHeight = fade(polHeight / nearHeight);
			polHeight = polHeight * nearHeight;
			polHeight += farHeight;
		}
		else {
			polHeight = (farHeight - nearHeight) * (pol / 5.0f);
			polHeight = fade(polHeight / farHeight);
			polHeight = polHeight * farHeight;
			polHeight += nearHeight;
		}
		//std::cout << polHeight << std::endl;
		setHeight(x - pol, y, polHeight);
	}
	//straightInterpolation(x, x + 10, y, y + 10);
	//straightInterpolation(x - 10, x, y, y + 10);
	//straightInterpolation(x - 10, x, y - 10, y);
	//straightInterpolation(x, x + 10, y - 10, y);
	//for (int dx = -5; dx < 6; dx++) {
	//	for (int dy = -5; dx < 6; dy++) {
	//
	//	}
	//}
}

Mesh Mesh::createStraightRiver(int x, int y) {
	float currentHeight = getHeight(x, y);
	int riverLength = rand() % 80 + 40;
	int riverWidth = rand() % 3 + 1;
	float dh = currentHeight / riverLength;
	Mesh river(riverLength, riverWidth+2);
	river.initializeAtZero();
	river.translateMesh(x-1, y);
	std::cout << riverLength << std::endl;
	std::cout << riverWidth << std::endl;
	int polLength = 5;
	float nearHeight;
	float farHeight;
	float polHeight;
	for (int itery = 0; itery < riverLength; itery++) {
		for (int iterx = 0; iterx < riverWidth; iterx++) {
			setHeight(x+iterx, y, currentHeight);
			river.setHeight(iterx, itery, currentHeight + 0.4f);
			river.setHeight(iterx+1, itery, currentHeight + 0.4f);
			river.setHeight(iterx+2, itery, currentHeight + 0.4f);
			//float sss = fade((currentHeight + 0.4f) / 10);
		}
		setHeight(x+riverWidth, y, currentHeight + 0.5f);
		setHeight(x-1, y, currentHeight + 0.5f);
		nearHeight = currentHeight;
		for (int pol = 1; pol < polLength; pol++) {
			farHeight = getHeight(x + riverWidth + polLength, y);
			polHeight = fadeInterpolation(nearHeight, farHeight, pol);
			//std::cout << nearHeight << " " << farHeight << " " << pol << " " << polHeight<< std::endl;
			setHeight(x + riverWidth + pol, y, polHeight+1);
			farHeight = getHeight(x - 1 - polLength, y);
			polHeight = fadeInterpolation(nearHeight, farHeight, pol);
			//polHeight += (rand() % 5 - 5) / 20.0f;
			//std::cout << polHeight << std::endl;
			setHeight(x - 1 - pol, y, polHeight+1);
		}
		currentHeight -= dh;
		y += 1;
	}
	//straightInterpolation(x - 5, x - 1, y - riverLength, y);
	//straightInterpolation(x + riverWidth, x + riverWidth + 4, y - riverLength, y);
	return river;
}

enum RiverDirections {
	NORTH = 0,
	NORTHEAST = 1,
	EAST = 2,
	SOUTHEAST = 3
};

Mesh Mesh::createCurvyRiver(int x, int y) {
	float currentHeight = getHeight(x, y);
	int dh;
	int compassDirection = rand() % 4;
	int riverLength = rand() % 80 + 20;
	Mesh river(riverLength,5);
	if (currentHeight < 3.0f) {
		dh = (rand() % 10 + 7 - currentHeight) / riverLength;
	}
	else {
		dh = (-1)*currentHeight / riverLength;
	}
	int cx = x;
	int cy = y;
	for (int i = 0; i < riverLength; ++i) {
		setHeight(cx, cy, currentHeight);
		currentHeight += dh;

	}
	int riverWidth = rand() % 5 + 2;
	return river;
}

void Mesh::straightInterpolation(int x0, int x1, int y0, int y1) {
	int ylength = y1 - y0;
	int xlength = x1 - x0;
	std::cout << x0 << x1 << y0 << y1 << std::endl;

	for (int i = 0; i < ylength; i+=3) {
		for (int x = 0; x < 4; ++x) {
			for (int y = 0; y < 4; ++y) {
					//std::cout << i << std::endl;
				float z = bilinearInterpolation(getHeight(x0, y0 + i), getHeight(x0, y0 + 4 + i), getHeight(x1, y0 + i), getHeight(x1, y0 + 4 + i), x0, x1, y0, y1, x0 + x, y0 + i + y);
	
				setHeight(x0 + x, y0 + i + y, z);
			}
		}
	}
}

void Mesh::riverInterpolation(int x0, int x1, int y0, int y1) {

}

Mesh Mesh::createColorMesh() {
	Mesh colorMesh(length, width);
	for (int i = 0; i < verticesSize; i+=3) {
		float z = vertices[i + 2] / 10.0f;
		if (z > 0.84f) {
			colorMesh.vertices[i] = 1.0f;
			colorMesh.vertices[i + 1] = 1.0f;
			colorMesh.vertices[i + 2] = 1.0f;
		}
		else if (z > 0.72f) {
			colorMesh.vertices[i] = -2.5f + 4.167f * z;
			colorMesh.vertices[i + 1] = -2.5f + 4.167f * z;
			colorMesh.vertices[i + 2] = -2.5f + 4.167f * z;
		}
		else if (z > 0.56f) {
			colorMesh.vertices[i] = 0.5f;
			colorMesh.vertices[i + 1] = 0.5f;
			colorMesh.vertices[i + 2] = 0.5f;
		}
		else if (z > 0.44f) {
			colorMesh.vertices[i] = -0.9f + 2.5f * z;
			colorMesh.vertices[i + 1] = 0.5f;
			colorMesh.vertices[i + 2] = -0.9f + 2.5f * z;
		}
		else if (z > 0.28f) {
			colorMesh.vertices[i] = 0.2f;
			colorMesh.vertices[i + 1] = 0.5f;
			colorMesh.vertices[i + 2] = 0.2f;
		}
		else if (z > 0.16f) {
			colorMesh.vertices[i] = 1.507f - 4.667f * z;
			colorMesh.vertices[i + 1] = 0.967f - 1.667f * z;
			colorMesh.vertices[i + 2] = 0.9f - 2.5f * z;
		}
		else {
			colorMesh.vertices[i] = 0.76f;
			colorMesh.vertices[i + 1] = 0.70f;
			colorMesh.vertices[i + 2] = 0.50f;
		}
	}
	return colorMesh;
}

void Mesh::deleteMeshBuffers() {
	GLdeleteVAO(VAO);
	GLdeleteVBO(VBO);
	GLdeleteEBO(EBO);
}

float bilinearInterpolation(float bottomLeft, float topLeft, float bottomRight, float topRight, float xMin, float xMax, float yMin, float yMax, float xToCalc, float yToCalc) {
	float width = xMax - xMin;
	float height = yMax - yMin;
	float xDistanceToMaxValue = xMax - xToCalc;
	float yDistanceToMaxValue = yMax - yToCalc;
	float xDistanceToMinValue = xToCalc - xMin;
	float yDistanceToMinValue = yToCalc - yMin;

	return 1.0f / (width * height) * (
		bottomLeft * xDistanceToMaxValue * yDistanceToMaxValue +
		bottomRight * xDistanceToMinValue * yDistanceToMaxValue +
		topLeft * xDistanceToMaxValue * yDistanceToMinValue +
		topRight * xDistanceToMinValue * yDistanceToMinValue
		);
}

float fade(float z) {
	//std::cout << z * z * z * (z * (z * 6 - 15) + 10) << std::endl;
	return z * z * z * (z * (z * 6 - 15) + 10);
}

float fadeInterpolation(float nearValue, float farValue, int polValue) {
	float polHeight;
	if (nearValue > farValue) {
		polHeight = (nearValue - farValue) * (1.0f - polValue / 5.0f);
		polHeight = fade(polHeight / nearValue);
		polHeight = polHeight * nearValue;
		polHeight += farValue;
	}
	else {
		polHeight = (farValue - nearValue) * (polValue / 5.0f);
		polHeight = fade(polHeight / farValue);
		polHeight = polHeight * farValue;
		polHeight += nearValue;
	}
	return polHeight;
}
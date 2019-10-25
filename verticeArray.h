#pragma once
#include "noise.h"
#include "ppm.h"
#include <iostream>
#include <algorithm>
#include <cmath>

enum VerticeType {
	LowPoly = 6, // Three coordinate values + Three color values
	Texture = 5  // Three coordinate values + Two texture values
};

void initializeVerticeArrayTextures(float* vertices, unsigned int worldLength, unsigned int worldWidth);
void initializeVerticesTexture(float* vertices, int length);

void initializeVerticeArrayLowPoly(float* vertices, unsigned int worldLength, unsigned int worldWidth);
void initializeVerticesLowPoly(float* vertices, int length);
void initializeVerticeArrayLowPolyReadImage(float* vertices, unsigned int worldLength, unsigned int worldWidth);

void setLowPolyColor(float* vertices, unsigned int worldLength, unsigned int worldWidth);

class VerticeArray {
public:
	VerticeArray(int height, int width, VerticeType type);

	float* getVertices() { return vertices; }
	
	int getWorldWidth() { return worldWidth; }

	int getWorldHeight() { return worldHeight; }

	int getVerticesSize() { return verticesSize; }

	int getVerticeType() { return arrayType; }

	void initializeVertices();

	void noiseMap(int seed);

	void lowPolyColor();

	void addHighFreq(int seed, float freq);

	void setWaterHeight(float waterHeight);

	void setWaterColor();

private:
	float* vertices;
	int worldWidth;
	int worldHeight;
	// Amount of vertices in one world point
	int arrayType = 6;
	int pointVerticeAmount = 6;
	int verticesSize;
};
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

	void translate(int dx, int dy);

	void noiseMap(int seed);

	void createMountains();

	float bilinearInterpolation(float bottomleft, float topLeft, float bottomRight, float topRight, float xMin, float xMax, float yMin, float yMax, float xToCalc, float yToCalc);

	void getHeightInterpol(int xMin, int yMin, int xMax, int yMax);

	void lowPolyColor();

	void addHighFreq(int seed, float freq);

	void setWaterHeight(float waterHeight);

	void setWaterColor();

	VerticeArray createLake(int x, int y, int radius, int height);

	VerticeArray createRiver(int sx, int sy, int ex, int ey, float height);
	
	VerticeArray createRiver(int startX, int startY);

	void setZatPoint(int x, int y, float zn);

	float getZat(int x, int y);

private:
	float* vertices;
	int worldWidth;
	int worldHeight;
	// Amount of vertices in one world point
	int arrayType = 6;
	int pointVerticeAmount = 6;
	int verticesSize;
};
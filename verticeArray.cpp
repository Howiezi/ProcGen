#include "verticeArray.h"

void initializeVerticeArrayTextures(float* vertices, unsigned int worldLength, unsigned int worldWidth) {
	// Noise
	// ------------------------

	// Create an empty PPM image
	ppm image(worldLength, worldWidth);

	// Create a PerlinNoise object with the reference permutation vector
	PerlinNoise pn(1337);

	unsigned int kk = 0;
	// Visit every pixel of the image and assign a color generated with Perlin noise
	for (unsigned int i = 0; i < worldLength; ++i) {     // y
		for (unsigned int j = 0; j < worldWidth; ++j) {  // x
			double x = (double)j / ((double)worldWidth);
			double y = (double)i / ((double)worldLength);

			// Typical Perlin noise
			double n = pn.noise(10 * x, 10 * y, 0.8);

			// Wood like structure
			//n = 20 * pn.noise(x, y, 0.8);
			//n = n - floor(n);

			// Map the values to the [0, 255] interval, for simplicity we use 
			// tones of grey
			image.r[kk] = floor(255 * n);
			image.g[kk] = floor(255 * n);
			image.b[kk] = floor(255 * n);
			kk++;

			float zn = (float)n *10;
			if (i == 0) {
				if (j < (worldWidth-1)) {
					vertices[30 * j + 22] = zn;
				}
				if (j > 0) {
					vertices[30 * (j - 1) + 12] = zn;
					vertices[30 * (j - 1) + 17] = zn;
				}
			}
			else if (i < (worldLength - 1)) {
				if (j < (worldWidth - 1)) {
					vertices[(worldWidth - 1) * 30 * (i - 1) + 30 * j + 2] = zn;
					vertices[(worldWidth - 1) * 30 * (i - 1) + 30 * j + 27] = zn;
					vertices[(worldWidth - 1) * 30 * i + 30 * j + 22] = zn;
				}
				if (j > 0) {
					vertices[(worldWidth - 1) * 30 * (i - 1) + 30 * (j - 1) + 7] = zn;
					vertices[(worldWidth - 1) * 30 * i + 30 * (j - 1) + 12] = zn;
					vertices[(worldWidth - 1) * 30 * i + 30 * (j - 1) + 17] = zn;
				}
			}
			if (i == (worldLength - 1)) {
				if (j < (worldWidth - 1)) {
					vertices[(worldWidth - 1) * 30 * (i - 1) + 30 * j + 2] = zn;
					vertices[(worldWidth - 1) * 30 * (i - 1) + 30 * j + 27] = zn;
				}
				if (j > 0) {
					vertices[(worldWidth - 1) * 30 * (i - 1) + 30 * (j - 1) + 7] = zn;
				}
			}
		}
	}

	for (unsigned int i = 0; i < (worldLength - 1); i++) {
		for (unsigned int j = 0; j < (worldWidth - 1); j++) {
			vertices[j * 30 + i * (worldWidth - 1) * 30] += j;
			vertices[j * 30 + i * (worldWidth - 1) * 30 + 5] += j;
			vertices[j * 30 + i * (worldWidth - 1) * 30 + 10] += j;
			vertices[j * 30 + i * (worldWidth - 1) * 30 + 15] += j;
			vertices[j * 30 + i * (worldWidth - 1) * 30 + 20] += j;
			vertices[j * 30 + i * (worldWidth - 1) * 30 + 25] += j;
		
			vertices[j * 30 + i * (worldWidth - 1) * 30 + 1] -= i;
			vertices[j * 30 + i * (worldWidth - 1) * 30 + 6] -= i;
			vertices[j * 30 + i * (worldWidth - 1) * 30 + 11] -= i;
			vertices[j * 30 + i * (worldWidth - 1) * 30 + 16] -= i;
			vertices[j * 30 + i * (worldWidth - 1) * 30 + 21] -= i;
			vertices[j * 30 + i * (worldWidth - 1) * 30 + 26] -= i;
		}
	}

	std::cout << "xs and ys are done" << std::endl;

	// Save the image in a binary PPM file
	image.write("figure_8_R.ppm");
}

void initializeVerticeArrayLowPoly(float* vertices, unsigned int worldLength, unsigned int worldWidth) {
	// Noise
	// ------------------------

	// Create an empty PPM image
	ppm image(worldLength, worldWidth);

	// Create a PerlinNoise object with the reference permutation vector
	PerlinNoise pn(1337);

	unsigned int kk = 0;
	// Visit every pixel of the image and assign a color generated with Perlin noise
	for (unsigned int i = 0; i < worldLength; ++i) {     // y
		for (unsigned int j = 0; j < worldWidth; ++j) {  // x
			double x = (double)j / ((double)worldWidth);
			double y = (double)i / ((double)worldLength);

			// Typical Perlin noise
			double n = pn.noise(10 * x, 10 * y, 0.8);

			// Wood like structure
			//n = 20 * pn.noise(x, y, 0.8);
			//n = n - floor(n);

			// Map the values to the [0, 255] interval, for simplicity we use 
			// tones of grey
			image.r[kk] = floor(255 * n);
			image.g[kk] = floor(255 * n);
			image.b[kk] = floor(255 * n);
			kk++;

			float zn = (float)n * 10;
			if (i == 0) {
				if (j < (worldWidth - 1)) {
					vertices[36 * j + 26] = zn;
				}
				if (j > 0) {
					vertices[36 * (j - 1) + 14] = zn;
					vertices[36 * (j - 1) + 20] = zn;
				}
			}
			else if (i < (worldLength - 1)) {
				if (j < (worldWidth - 1)) {
					vertices[(worldWidth - 1) * 36 * (i - 1) + 36 * j + 2] = zn;
					vertices[(worldWidth - 1) * 36 * (i - 1) + 36 * j + 32] = zn;
					vertices[(worldWidth - 1) * 36 * i + 36 * j + 26] = zn;
				}
				if (j > 0) {
					vertices[(worldWidth - 1) * 36 * (i - 1) + 36 * (j - 1) + 8] = zn;
					vertices[(worldWidth - 1) * 36 * i + 36 * (j - 1) + 14] = zn;
					vertices[(worldWidth - 1) * 36 * i + 36 * (j - 1) + 20] = zn;
				}
			}
			if (i == (worldLength - 1)) {
				if (j < (worldWidth - 1)) {
					vertices[(worldWidth - 1) * 36 * (i - 1) + 36 * j + 2] = zn;
					vertices[(worldWidth - 1) * 36 * (i - 1) + 36 * j + 32] = zn;
				}
				if (j > 0) {
					vertices[(worldWidth - 1) * 36 * (i - 1) + 36 * (j - 1) + 8] = zn;
				}
			}
		}
	}

	for (unsigned int i = 0; i < (worldLength - 1); i++) {
		for (unsigned int j = 0; j < (worldWidth - 1); j++) {
			vertices[j * 36 + i * (worldWidth - 1) * 36] += j;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 6] += j;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 12] += j;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 18] += j;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 24] += j;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 30] += j;
		
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 1] -= i;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 7] -= i;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 13] -= i;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 19] -= i;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 25] -= i;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 31] -= i;
		}
	}

	std::cout << "xs and ys are done" << std::endl;

	// Save the image in a binary PPM file
	image.write("figure_8_R.ppm");
}

void initializeVerticeArrayLowPolyReadImage(float* vertices, unsigned int worldLength, unsigned int worldWidth) {
	// Create an empty PPM image
	const std::string& name = "heightmap.ppm";
	ppm image(name);

	unsigned int kk = 0;
	// Visit every pixel of the image and assign a color generated with Perlin noise
	for (unsigned int i = 0; i < worldLength; ++i) {     // y
		for (unsigned int j = 0; j < worldWidth; ++j) {  // x
			double x = (double)j / ((double)worldWidth);
			double y = (double)i / ((double)worldLength);

			float zn = image.r[kk]/25.5f;

			if (i == 0) {
				if (j < (worldWidth - 1)) {
					vertices[36 * j + 26] = zn;
				}
				if (j > 0) {
					vertices[36 * (j - 1) + 14] = zn;
					vertices[36 * (j - 1) + 20] = zn;
				}
			}
			else if (i < (worldLength - 1)) {
				if (j < (worldWidth - 1)) {
					vertices[(worldWidth - 1) * 36 * (i - 1) + 36 * j + 2] = zn;
					vertices[(worldWidth - 1) * 36 * (i - 1) + 36 * j + 32] = zn;
					vertices[(worldWidth - 1) * 36 * i + 36 * j + 26] = zn;
				}
				if (j > 0) {
					vertices[(worldWidth - 1) * 36 * (i - 1) + 36 * (j - 1) + 8] = zn;
					vertices[(worldWidth - 1) * 36 * i + 36 * (j - 1) + 14] = zn;
					vertices[(worldWidth - 1) * 36 * i + 36 * (j - 1) + 20] = zn;
				}
			}
			if (i == (worldLength - 1)) {
				if (j < (worldWidth - 1)) {
					vertices[(worldWidth - 1) * 36 * (i - 1) + 36 * j + 2] = zn;
					vertices[(worldWidth - 1) * 36 * (i - 1) + 36 * j + 32] = zn;
				}
				if (j > 0) {
					vertices[(worldWidth - 1) * 36 * (i - 1) + 36 * (j - 1) + 8] = zn;
				}
			}
			kk++;
		}
	}

	for (unsigned int i = 0; i < (worldLength - 1); i++) {
		for (unsigned int j = 0; j < (worldWidth - 1); j++) {
			vertices[j * 36 + i * (worldWidth - 1) * 36] += j;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 6] += j;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 12] += j;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 18] += j;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 24] += j;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 30] += j;

			vertices[j * 36 + i * (worldWidth - 1) * 36 + 1] -= i;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 7] -= i;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 13] -= i;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 19] -= i;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 25] -= i;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 31] -= i;
		}
	}
}

void initializeVerticesTexture(float* vertices,int length) {
	for (int i = 0; i < length; i++) {
		switch (i % 30) {
		case 0: vertices[i] = -0.5f; break;
		case 1: vertices[i] = -0.5f; break;
		case 2: vertices[i] = 0.0f; break;
		case 3: vertices[i] = 0.0f; break;
		case 4: vertices[i] = 0.0f; break;

		case 5: vertices[i] = 0.5f; break;
		case 6: vertices[i] = -0.5f; break;
		case 7: vertices[i] = 0.0f; break;
		case 8: vertices[i] = 1.0f; break;
		case 9: vertices[i] = 0.0f; break;

		case 10: vertices[i] = 0.5f; break;
		case 11: vertices[i] = 0.5f; break;
		case 12: vertices[i] = 0.0f; break;
		case 13: vertices[i] = 1.0f; break;
		case 14: vertices[i] = 1.0f; break;

		case 15: vertices[i] = 0.5f; break;
		case 16: vertices[i] = 0.5f; break;
		case 17: vertices[i] = 0.0f; break;
		case 18: vertices[i] = 1.0f; break;
		case 19: vertices[i] = 1.0f; break;

		case 20: vertices[i] = -0.5f; break;
		case 21: vertices[i] = 0.5f; break;
		case 22: vertices[i] = 0.0f; break;
		case 23: vertices[i] = 0.0f; break;
		case 24: vertices[i] = 1.0f; break;

		case 25: vertices[i] = -0.5f; break;
		case 26: vertices[i] = -0.5f; break;
		case 27: vertices[i] = 0.0f; break;
		case 28: vertices[i] = 0.0f; break;
		case 29: vertices[i] = 0.0f; break;
		}
	}
}

void initializeVerticesLowPoly(float* vertices, int length) {
	for (int i = 0; i < length; i++) {
		switch (i % 36) {
		// Bottom left corner
		case 0: vertices[i] = -0.5f; break;
		case 1: vertices[i] = -0.5f; break;
		case 2: vertices[i] = 0.0f; break;
		// Bottom right
		case 6: vertices[i] = 0.5f; break;
		case 7: vertices[i] = -0.5f; break;
		case 8: vertices[i] = 0.0f; break;
		// Top right
		case 12: vertices[i] = 0.5f; break;
		case 13: vertices[i] = 0.5f; break;
		case 14: vertices[i] = 0.0f; break;
		// Top right
		case 18: vertices[i] = 0.5f; break;
		case 19: vertices[i] = 0.5f; break;
		case 20: vertices[i] = 0.0f; break;
		// Top left
		case 24: vertices[i] = -0.5f; break;
		case 25: vertices[i] = 0.5f; break;
		case 26: vertices[i] = 0.0f; break;
		// Bottom left
		case 30: vertices[i] = -0.5f; break;
		case 31: vertices[i] = -0.5f; break;
		case 32: vertices[i] = 0.0f; break;
		}
	}
}

void setLowPolyColor(float* vertices, unsigned int worldLength, unsigned int worldWidth) {
	for (int i = 0; i < worldLength * worldWidth*6; i++) {
		if (vertices[i * 6 + 2] / 10 > 0.75) {
			vertices[i * 6 + 3] = 1.0f;
			vertices[i * 6 + 4] = 1.0f;
			vertices[i * 6 + 5] = 1.0f;
		}
		else if (vertices[i * 6 + 2] / 10 > 0.50) {
			vertices[i * 6 + 3] = 0.5f;
			vertices[i * 6 + 4] = 0.5f;
			vertices[i * 6 + 5] = 0.5f;
		}
		else if (vertices[i * 6 + 2] / 10 > 0.25) {
			vertices[i * 6 + 3] = 0.2f;
			vertices[i * 6 + 4] = 0.5f;
			vertices[i * 6 + 5] = 0.2f;
		}
		else {
			vertices[i * 6 + 3] = 0.76f;
			vertices[i * 6 + 4] = 0.70f;
			vertices[i * 6 + 5] = 0.50f;
		}
	}
}

VerticeArray::VerticeArray(int height, int width, VerticeType type) {
	if (type == LowPoly) {
		this->arrayType = 6;
}
	this->vertices = new float[height * width * this->arrayType * pointVerticeAmount];
	this->worldHeight = height;
	this->worldWidth = width;
	this->verticesSize = height * width * this->arrayType * pointVerticeAmount;
	this->initializeVertices();
}

void VerticeArray::initializeVertices() {
	std::cout << getVerticesSize() << std::endl;
	for (int i = 0; i < this->getVerticesSize(); i++) {
		switch (i % 36) {
			// Bottom left corner
		case 0: vertices[i] = -0.5f; break;
		case 1: vertices[i] = -0.5f; break;
		case 2: vertices[i] = 0.0f; break;
			// Bottom right
		case 6: vertices[i] = 0.5f; break;
		case 7: vertices[i] = -0.5f; break;
		case 8: vertices[i] = 0.0f; break;
			// Top right
		case 12: vertices[i] = 0.5f; break;
		case 13: vertices[i] = 0.5f; break;
		case 14: vertices[i] = 0.0f; break;
			// Top right
		case 18: vertices[i] = 0.5f; break;
		case 19: vertices[i] = 0.5f; break;
		case 20: vertices[i] = 0.0f; break;
			// Top left
		case 24: vertices[i] = -0.5f; break;
		case 25: vertices[i] = 0.5f; break;
		case 26: vertices[i] = 0.0f; break;
			// Bottom left
		case 30: vertices[i] = -0.5f; break;
		case 31: vertices[i] = -0.5f; break;
		case 32: vertices[i] = 0.0f; break;
		}
	
	}
	for (unsigned int i = 0; i < (this->worldHeight - 1); i++) {
		for (unsigned int j = 0; j < (this->worldWidth - 1); j++) {
			vertices[j * 36 + i * (worldWidth - 1) * 36] += j;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 6] += j;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 12] += j;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 18] += j;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 24] += j;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 30] += j;

			vertices[j * 36 + i * (worldWidth - 1) * 36 + 1] -= i;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 7] -= i;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 13] -= i;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 19] -= i;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 25] -= i;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 31] -= i;
		}
	}
}

void VerticeArray::translate(int dx, int dy) {
	for (unsigned int i = 0; i < (this->worldHeight - 1); i++) {
		for (unsigned int j = 0; j < (this->worldWidth - 1); j++) {
			vertices[j * 36 + i * (worldWidth - 1) * 36] += dy;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 6] += dy;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 12] += dy;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 18] += dy;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 24] += dy;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 30] += dy;

			vertices[j * 36 + i * (worldWidth - 1) * 36 + 1] -= dx;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 7] -= dx;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 13] -= dx;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 19] -= dx;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 25] -= dx;
			vertices[j * 36 + i * (worldWidth - 1) * 36 + 31] -= dx;
		}
	}
}

void VerticeArray::noiseMap(int seed) {
	// Noise
	// ------------------------

	// Create an empty PPM image
	ppm image(this->worldHeight, this->worldWidth);
	
	// Create a PerlinNoise object with the reference permutation vector
	PerlinNoise pn(seed);
	int height = this->worldHeight;
	int width = this->worldWidth;

	unsigned int kk = 0;
	// Visit every pixel of the image and assign a color generated with Perlin noise
	for (unsigned int i = 0; i < height; ++i) {     // y
		for (unsigned int j = 0; j < width; ++j) {  // x
			double x = (double)j / ((double)width);
			double y = (double)i / ((double)height);

			// Typical Perlin noise
			double n = pn.noise(25 * x, 25 * y, 0.8);

			// Wood like structure
			//n = 20 * pn.noise(x, y, 0.8);
			//n = n - floor(n);

			// Map the values to the [0, 255] interval, for simplicity we use 
			// tones of grey
			image.r[kk] = floor(255 * n);
			image.g[kk] = floor(255 * n);
			image.b[kk] = floor(255 * n);
			kk++;

			float zn = (float)n * 10;
			if (i == 0) {
				if (j < (width - 1)) {
					vertices[36 * j + 26] = zn;
				}
				if (j > 0) {
					vertices[36 * (j - 1) + 14] = zn;
					vertices[36 * (j - 1) + 20] = zn;
				}
			}
			else if (i < (height - 1)) {
				if (j < (width - 1)) {
					vertices[(width - 1) * 36 * (i - 1) + 36 * j + 2] = zn;
					vertices[(width - 1) * 36 * (i - 1) + 36 * j + 32] = zn;
					vertices[(width - 1) * 36 * i + 36 * j + 26] = zn;
				}
				if (j > 0) {
					vertices[(width - 1) * 36 * (i - 1) + 36 * (j - 1) + 8] = zn;
					vertices[(width - 1) * 36 * i + 36 * (j - 1) + 14] = zn;
					vertices[(width - 1) * 36 * i + 36 * (j - 1) + 20] = zn;
				}
			}
			if (i == (height - 1)) {
				if (j < (width - 1)) {
					vertices[(width - 1) * 36 * (i - 1) + 36 * j + 2] = zn;
					vertices[(width - 1) * 36 * (i - 1) + 36 * j + 32] = zn;
				}
				if (j > 0) {
					vertices[(width - 1) * 36 * (i - 1) + 36 * (j - 1) + 8] = zn;
				}
			}
		}
	}

	image.write("noisemap.ppm");
}

void VerticeArray::lowPolyColor() {
	for (int i = 0; i < this->worldHeight * this->worldWidth * this->pointVerticeAmount; i++) {
		float z = vertices[i * 6 + 2] / 10.0f;
		if (z > 0.84f) {
			vertices[i * 6 + 3] = 1.0f;
			vertices[i * 6 + 4] = 1.0f;
			vertices[i * 6 + 5] = 1.0f;
		}
		else if (z > 0.72f) {
			vertices[i * 6 + 3] = -2.5f + 4.167f * z;
			vertices[i * 6 + 4] = -2.5f + 4.167f * z;
			vertices[i * 6 + 5] = -2.5f + 4.167f * z;
		}
		else if (z > 0.56f) {
			vertices[i * 6 + 3] = 0.5f;
			vertices[i * 6 + 4] = 0.5f;
			vertices[i * 6 + 5] = 0.5f;
		}
		else if (z > 0.44f) {
			vertices[i * 6 + 3] = -0.9f + 2.5f * z;
			vertices[i * 6 + 4] = 0.5f;
			vertices[i * 6 + 5] = -0.9f + 2.5f * z;
		}
		else if (z > 0.28f) {
			vertices[i * 6 + 3] = 0.2f;
			vertices[i * 6 + 4] = 0.5f;
			vertices[i * 6 + 5] = 0.2f;
		}
		else if (z > 0.16f) {
			vertices[i * 6 + 3] = 1.507f - 4.667f * z;
			vertices[i * 6 + 4] = 0.967f - 1.667f * z;
			vertices[i * 6 + 5] = 0.9f - 2.5f * z;
		}
		else {
			vertices[i * 6 + 3] = 0.76f;
			vertices[i * 6 + 4] = 0.70f;
			vertices[i * 6 + 5] = 0.50f;
		}
	}
}

void VerticeArray::addHighFreq(int seed, float freq) {
	// Noise
	// ------------------------

	// Create an empty PPM image
	ppm image(this->worldHeight, this->worldWidth);

	// Create a PerlinNoise object with the reference permutation vector
	PerlinNoise pn(seed);
	int height = this->worldHeight;
	int width = this->worldWidth;

	unsigned int kk = 0;
	// Visit every pixel of the image and assign a color generated with Perlin noise
	for (unsigned int i = 0; i < height; ++i) {     // y
		for (unsigned int j = 0; j < width; ++j) {  // x
			double x = (double)j / ((double)width);
			double y = (double)i / ((double)height);

			// Typical Perlin noise
			double n = pn.noise((double)freq * x, (double)freq * y, 0.8);

			// Wood like structure
			//n = 20 * pn.noise(x, y, 0.8);
			//n = n - floor(n);

			// Map the values to the [0, 255] interval, for simplicity we use 
			// tones of grey
			image.r[kk] = floor(255 * n);
			image.g[kk] = floor(255 * n);
			image.b[kk] = floor(255 * n);
			kk++;

			float zn = ((float)n - 0.5f) * 100.0f / (freq);
			if (i == 0) {
				if (j < (width - 1)) {
					vertices[36 * j + 26] += zn;
				}
				if (j > 0) {
					vertices[36 * (j - 1) + 14] += zn;
					vertices[36 * (j - 1) + 20] += zn;
				}
			}
			else if (i < (height - 1)) {
				if (j < (width - 1)) {
					vertices[(width - 1) * 36 * (i - 1) + 36 * j + 2] += zn;
					vertices[(width - 1) * 36 * (i - 1) + 36 * j + 32] += zn;
					vertices[(width - 1) * 36 * i + 36 * j + 26] += zn;
				}
				if (j > 0) {
					vertices[(width - 1) * 36 * (i - 1) + 36 * (j - 1) + 8] += zn;
					vertices[(width - 1) * 36 * i + 36 * (j - 1) + 14] += zn;
					vertices[(width - 1) * 36 * i + 36 * (j - 1) + 20] += zn;
				}
			}
			if (i == (height - 1)) {
				if (j < (width - 1)) {
					vertices[(width - 1) * 36 * (i - 1) + 36 * j + 2] += zn;
					vertices[(width - 1) * 36 * (i - 1) + 36 * j + 32] += zn;
				}
				if (j > 0) {
					vertices[(width - 1) * 36 * (i - 1) + 36 * (j - 1) + 8] += zn;
				}
			}
		}
	}
}

void VerticeArray::setWaterHeight(float waterHeight) {
	int height = this->worldHeight;
	int width = this->worldWidth;
	float zn = waterHeight;
	for (unsigned int i = 0; i < height; ++i) {     // y
		for (unsigned int j = 0; j < width; ++j) {  // x
			if (i == 0) {
				if (j < (width - 1)) {
					vertices[36 * j + 26] = zn;
				}
				if (j > 0) {
					vertices[36 * (j - 1) + 14] = zn;
					vertices[36 * (j - 1) + 20] = zn;
				}
			}
			else if (i < (height - 1)) {
				if (j < (width - 1)) {
					vertices[(width - 1) * 36 * (i - 1) + 36 * j + 2] = zn;
					vertices[(width - 1) * 36 * (i - 1) + 36 * j + 32] = zn;
					vertices[(width - 1) * 36 * i + 36 * j + 26] = zn;
				}
				if (j > 0) {
					vertices[(width - 1) * 36 * (i - 1) + 36 * (j - 1) + 8] = zn;
					vertices[(width - 1) * 36 * i + 36 * (j - 1) + 14] = zn;
					vertices[(width - 1) * 36 * i + 36 * (j - 1) + 20] = zn;
				}
			}
			if (i == (height - 1)) {
				if (j < (width - 1)) {
					vertices[(width - 1) * 36 * (i - 1) + 36 * j + 2] = zn;
					vertices[(width - 1) * 36 * (i - 1) + 36 * j + 32] = zn;
				}
				if (j > 0) {
					vertices[(width - 1) * 36 * (i - 1) + 36 * (j - 1) + 8] = zn;
				}
			}
		}
	}
}

void VerticeArray::setWaterColor() {
	for (int i = 0; i < this->worldHeight * this->worldWidth * this->pointVerticeAmount; i++) {
		vertices[i * 6 + 3] = 0.0f;
		vertices[i * 6 + 4] = 102.0f/255.0f;
		vertices[i * 6 + 5] = 1.0f;
	}
}

VerticeArray VerticeArray::createLake(int x,int y,int radius,int height) {
	float depth = radius / 2.0f;
	VerticeArray lake(radius*2+1, radius*2+1, LowPoly);
	lake.translate(x-radius, y-radius);
	lake.setWaterHeight(height+depth/2.0f);
	for (int i = (-1)*radius; i < radius+1; i++) {
		for (int j = (-1) * radius; j < radius+1; j++) {
			if (i == radius || j == radius || i == -1*radius || j == -1*radius) {
				this->setZatPoint(x + i, y + j, height+depth);
			}
			else {
				this->setZatPoint(x + i, y + j, height);
			}
		}
	}

	return lake;
}

void VerticeArray::createRiver(int sx, int sy, int ex, int ey, float height) {
	int lenx = ex - sx;
	int leny = ey - sy;
	float dh = height / (lenx + leny);
	for (int i = 0; i < lenx+1; i++) {
		this->setZatPoint(sx + i, sy, height);
		this->setZatPoint(sx + i, sy + 1, height + 1);
		this->setZatPoint(sx + i, sy - 1, height + 1);
		height -= dh;
	}
	this->setZatPoint(sx + lenx + 1, sy - 1, height+1);
	this->setZatPoint(sx + lenx + 1, sy, height+1);
	for (int i = 0; i < leny+1; i++) {
		this->setZatPoint(sx + lenx, sy + i, height);
		if (i > 0) {
			this->setZatPoint(sx + lenx + 1, sy + i, height + 1);
			this->setZatPoint(sx + lenx - 1, sy + i, height + 1);
		}
		height -= dh;
	}
}

void VerticeArray::setZatPoint(int x, int y, float zn) {
	int height = this->getWorldHeight();
	int width = this->getWorldWidth();
	if (x == 0) {
		if (y < (width - 1)) {
			vertices[36 * y + 26] = zn;
		}
		if (y > 0) {
			vertices[36 * (y - 1) + 14] = zn;
			vertices[36 * (y - 1) + 20] = zn;
		}
	}
	else if (x < (height - 1)) {
		if (y < (width - 1)) {
			vertices[(width - 1) * 36 * (x - 1) + 36 * y + 2] = zn;
			vertices[(width - 1) * 36 * (x - 1) + 36 * y + 32] = zn;
			vertices[(width - 1) * 36 * x + 36 * y + 26] = zn;
		}
		if (y > 0) {
			vertices[(width - 1) * 36 * (x - 1) + 36 * (y - 1) + 8] = zn;
			vertices[(width - 1) * 36 * x + 36 * (y - 1) + 14] = zn;
			vertices[(width - 1) * 36 * x + 36 * (y - 1) + 20] = zn;
		}
	}
	if (x == (height - 1)) {
		if (y < (width - 1)) {
			vertices[(width - 1) * 36 * (x - 1) + 36 * y + 2] = zn;
			vertices[(width - 1) * 36 * (x - 1) + 36 * y + 32] = zn;
		}
		if (y > 0) {
			vertices[(width - 1) * 36 * (x - 1) + 36 * (y - 1) + 8] = zn;
		}
	}
}
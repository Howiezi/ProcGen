#pragma once
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "noise.h"
#include "ppm.h"
#include "verticeArray.h"
#include "window.h"
#include "renderer.h"

#include "mesh.h"

#include <iostream>

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char *title = "ProcGen";

// camera
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int worldWidth = 256;
int worldHeight = 256;
VerticeType worldType = LowPoly;

int main()
{
	Window window(SCR_WIDTH, SCR_HEIGHT, title);
	// glfw: initialize and configure
	// ------------------------------
	
	glfwSetCursorPosCallback(window.getWindow(), mouse_callback);
	glfwSetScrollCallback(window.getWindow(), scroll_callback);

	glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// build and compile our shader program
	// ------------------------------------
	Shader ourShader("lowPoly.vert", "lowPoly.frag");
	Shader waterShader("water.vert", "water.frag");

	Mesh worldMesh(worldHeight, worldWidth);
	worldMesh.initializeAtZero();
	worldMesh.noisemap(46234);
	worldMesh.setHeight(100, 100, 8);
	//worldMesh.createMountain(10, 10);
	//worldMesh.createMountain(20, 20);
	//worldMesh.createMountain(30, 30);
	//worldMesh.createMountain(40, 40);
	//worldMesh.createMountain(50, 50);
	worldMesh.createMountain(60, 60);
	Mesh riverMesh = worldMesh.createStraightRiver(100, 100);
	Mesh riverMesh2 = worldMesh.createStraightRiver(120, 100);
	Mesh riverMesh3 = worldMesh.createStraightRiver(80, 100);
	Mesh worldColorMesh = worldMesh.createColorMesh();
	float* world = worldMesh.getvertices();
	for (int i = 0; i < 100; i++) {
		//std::cout << world[0 + i * 3] << " " << world[1 + i * 3] << " " << world[2 + i * 3] << std::endl;
	}

	float* rvv = riverMesh.getvertices();
	for (int i = 0; i < 100; i++) {
		//std::cout << rvv[0 + i * 3] << " " << rvv[1 + i * 3] << " " << rvv[2 + i * 3] << std::endl;
	}

	float* wcv = worldColorMesh.getvertices();
	for (int i = 0; i < 100; i++) {
		//std::cout << wcv[0 + i * 3] << " " << wcv[1 + i * 3] << " " << wcv[2 + i * 3] << std::endl;
	}

	Mesh fullWorld(worldMesh, worldColorMesh);

	//for (int i = worldMesh.getVerticesSize(); i < fullWorld.getVerticesSize(); i++) {
	//	std::cout << fullWorld.getvertices()[i] << std::endl;
	//}
	std::cout << fullWorld.getVerticesSize() << std::endl;

	fullWorld.bindData();
	riverMesh.bindData();
	riverMesh2.bindData();
	riverMesh3.bindData();
	
	//unsigned* ind = worldMesh.getindices();
	//for (int i = 0; i < 300; i++) {
	//	std::cout << ind[0 + i * 6] << std::endl;
	//}

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window.getWindow()))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window.getWindow());
		
		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		/*
		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);*/

		// activate shader
		ourShader.use();

		// pass projection matrix to shader (note that in this case it could change every frame)
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 150.0f);
		ourShader.setMat4("projection", projection);
		
		// camera/view transformation
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("view", view);
		
		// render boxes
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.0f * worldMesh.getLength() / 2.0f, -10.0f, 1.0f * worldMesh.getWidth() / 2.0f));
		model = glm::rotate(model, (float)glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		ourShader.setMat4("model", model);

		fullWorld.drawMesh();
		//worldMesh.drawMesh();
		waterShader.use();
		waterShader.setMat4("projection", projection);
		waterShader.setMat4("view", view);
		waterShader.setMat4("model", model);
		riverMesh.drawMesh();
		riverMesh2.drawMesh();
		riverMesh3.drawMesh();


		//glBindVertexArray(worldRenderer.getVAO());
		//glDrawArrays(GL_TRIANGLES, 0, (vertices.getWorldHeight() - 1) * (vertices.getWorldWidth() - 1) *6);
		//
		//waterShader.use();
		//waterShader.setMat4("projection", projection);
		//waterShader.setMat4("view", view);
		//waterShader.setMat4("model", model);
		//
		//glBindVertexArray(waterRenderer.getVAO());
		//glDrawArrays(GL_TRIANGLES, 0, (water.getWorldHeight() - 1) * (water.getWorldWidth() - 1) * 6);
		//
		//glBindVertexArray(lakeRenderer.getVAO());
		//glDrawArrays(GL_TRIANGLES, 0, (lake.getWorldHeight() - 1) * (lake.getWorldWidth() - 1) * 6);
		//
		//glBindVertexArray(riverRenderer.getVAO());
		//glDrawArrays(GL_TRIANGLES, 0, (river.getWorldHeight() - 1) * (river.getWorldWidth() - 1) * 6);
		/*for (unsigned int i = 0; i < 100; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			//float angle = 20.0f * i;
			//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			ourShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 6);
		}*/

		// glfw: swap buffers and pholl IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window.getWindow());
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	/*glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO2);*/
	worldMesh.deleteMeshBuffers();
	riverMesh.deleteMeshBuffers();
	worldColorMesh.deleteMeshBuffers();

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
#include <string>
#include <iostream>
#include <cDegaTime.h>
#include <cDegaShade.h>
#include <cDegaUtils.h>
#include <cDegaCamera.h>
#include <degaPredefine.h>

#define GLEW_STATIC
#include <GL/glew.h>
//#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image_aug.h>

using namespace std;
using namespace degawong;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glewInit();

	cDegaShader ourShader("./shade/box.vert", "./shade/box.frag");

	float vertices[] = {
		// positions          // colors           // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	cDegaABE abe(vertices, indices, 32, 6);

	abe.bindBuffers();
	abe.setVertexAttribute(0, 3, 8, (void*)0);
	abe.setVertexAttribute(1, 3, 8, (void*)(3 * sizeof(float)));
	abe.setVertexAttribute(2, 2, 8, (void*)(6 * sizeof(float)));
	abe.unBindBuffers();

	cDegaTexture2D text2D("./doc/left.jpg");

	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		text2D.bindTexture();
		ourShader.useProgram();

		abe.bindBuffers();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		abe.unBindBuffers();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
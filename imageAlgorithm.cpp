

#include <string>
#include <iostream>
#include <cDegaTime.h>
#include <cGUIUtils.h>
#include <cDegaUtils.h>
#include <degaPredefine.h>
#include <cInterfaceUtils.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;
using namespace degawong;

degawong::cInterfaceUtils algorithmHandel;
degawong::cWindowUtils guiUtils({ "natural" ,"studio" ,"contour" ,"stage" ,"mono" });

static void glfwErrorCallback(int error, const char* description) { std::cerr << "Glfw Error " << error << " : " << description << std::endl; }

static void renderWindowResizeCallback(GLFWwindow* window, int currWidth, int currHeight) {
	/* change the display mode */
	glViewport(0, 0, guiUtils.iRendingSize.width = currWidth, guiUtils.iRendingSize.height = currHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, currWidth, currHeight, 0.0, 0.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main() {
	try {
#ifdef DEGA_PLATFORM_WINDOW
		guiUtils.loadImage("./doc/temple.bmp");
#elif defined(DEGA_PLATFORM_LINUX)
		guiUtils.loadImage("/home/dega/Pictures/000.jpeg");
#endif
		guiUtils.checkWidthHeight();
		glfwSetErrorCallback(glfwErrorCallback);
		if (!glfwInit()) { throw cDegaException("glfwInit error!"); }
		GLFWwindow* pRenderingWindow = glfwCreateWindow(guiUtils.iRendingSize.width, guiUtils.iRendingSize.height, "Arcsoft Algorithm Demo", NULL, NULL);
		glfwMakeContextCurrent(pRenderingWindow);
		glfwSwapInterval(1);
		if (glewInit()) { throw cDegaException("glewInit error!"); }
		glfwSetWindowSizeCallback(pRenderingWindow, renderWindowResizeCallback);
		guiUtils.setWindowHandel(pRenderingWindow);
		guiUtils.imguiWindowInit();
		
		while (!glfwWindowShouldClose(pRenderingWindow)) {
			glfwPollEvents();
			guiUtils.gameLoopPollEvents();
			glfwMakeContextCurrent(pRenderingWindow);
			glfwSwapBuffers(pRenderingWindow);			
			algorithmHandel.setImageParameter(guiUtils);
			algorithmHandel.doAlgorithm();
		}
		guiUtils.destroyGUIWindow();
		glfwDestroyWindow(pRenderingWindow);
		glfwTerminate();
		return 0;
	} catch (const cDegaException& exce) {
		std::cerr << exce.what() << std::endl;
		std::cerr << "main project exception !" << std::endl;
		system("pause");
	}
}

#include <string>
#include <cDegaTime.h>
#include <cDegaUtils.h>
#include <degaPredefine.h>

#include "iostream"
#include "tchar.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl2.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


using namespace std;
using namespace degawong;

int helpWindowCorner = 1;
bool isShowHelpWindow = true;
float helpWindowBorder = 15.0f;

degawong::cDegaPara arcPara(5);
degawong::iScreenNorm i720pNorm;
degawong::cImageUtils imageUtils;

static void glfwErrorCallback(int error, const char* description) { std::cerr << "Glfw Error " << error << " : " << description << std::endl; }

static void renderWindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

static void renderWindowResizeCallback(GLFWwindow* window, int currWidth, int currHeight) {
	/* change the display mode */
	glViewport(0, 0, i720pNorm.width = currWidth, i720pNorm.height = currHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, currWidth, currHeight, 0.0, 0.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

int main() 
{
	arcPara.vPortraitList = { "natural" ,"studio" ,"contour" ,"stage" ,"stage mono" };
	try {		
		GLuint tex_id;

#ifdef DEGA_PLATFORM_WINDOW
		imageUtils.loadImage("./doc/left.jpg");
#elif defined(DEGA_PLATFORM_LINUX)
		imageUtils.loadImage("/home/dega/Pictures/000.jpeg");
#endif
		if (imageUtils.imageInfo.width > imageUtils.imageInfo.height) {
			i720pNorm.width = 1280;
			i720pNorm.height = 720;
		}
		else {
			i720pNorm.width = 576;
			i720pNorm.height = 768;
		}
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		glfwSetErrorCallback(glfwErrorCallback);
		if (!glfwInit()) {
			return 1;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		//glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* renderWindow = glfwCreateWindow(i720pNorm.width, i720pNorm.height, "Arcsoft Algorithm Demo", NULL, NULL);
		glfwMakeContextCurrent(renderWindow);
		glfwSwapInterval(1);
		glewInit();
		/* set glfw call back function */
		glfwSetKeyCallback(renderWindow, renderWindowKeyCallback);
		glfwSetWindowSizeCallback(renderWindow, renderWindowResizeCallback);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		ImGui_ImplGlfw_InitForOpenGL(renderWindow, true);
		ImGui_ImplOpenGL2_Init();
		ImGui::StyleColorsDark();

		glGenTextures(1, &tex_id);
		glBindTexture(GL_TEXTURE_2D, tex_id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glBindTexture(GL_TEXTURE_2D, 0);

		glMatrixMode(GL_PROJECTION);     // Make a simple 2D projection on the entire renderWindow
		glLoadIdentity();
		glOrtho(0.0, i720pNorm.width, i720pNorm.height, 0.0, 0.0, 100.0);
		glMatrixMode(GL_MODELVIEW);    // Set the matrix mode to object modeling
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClearDepth(0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the renderWindow

		while (!glfwWindowShouldClose(renderWindow)) {
			glfwPollEvents();
			ImGui_ImplOpenGL2_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			/* imgui key callback function */
			if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape))) {
				break;
			} else if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Space))) {
				std::cout << "press key space" << std::endl;
				// open image with defaut software
				ShellExecute(nullptr, _T("open"), _T("e://image//001.jpg"), _T(""), _T(""), SW_SHOW);
			} else if(ImGui::IsKeyPressed('s') || ImGui::IsKeyPressed('S')) {
				std::cout << "press key s(S)" << std::endl;
				// open directory
				
				ShellExecute(nullptr, "open", nullptr, nullptr, "e://image//", SW_SHOWNORMAL);
			}

			ImGuiWindowFlags window_flags = 0;
			if (false)  window_flags |= ImGuiWindowFlags_NoTitleBar;
			if (false) window_flags |= ImGuiWindowFlags_NoScrollbar;
			if (!false)    window_flags |= ImGuiWindowFlags_MenuBar;
			if (false)      window_flags |= ImGuiWindowFlags_NoMove;
			if (false)    window_flags |= ImGuiWindowFlags_NoResize;
			if (false)  window_flags |= ImGuiWindowFlags_NoCollapse;
			if (false)       window_flags |= ImGuiWindowFlags_NoNav;

			ImGui::Begin("arc parameter", NULL, window_flags);
			if (ImGui::BeginMenuBar()) {
				if (ImGui::BeginMenu("(F)ile")) {
					ImGui::MenuItem("(O)pen", NULL, &arcPara.bMenuDownFlag[0]);
					ImGui::MenuItem("(S)ave", NULL, &arcPara.bMenuDownFlag[1]);
					ImGui::MenuItem("(Q)uit", NULL, &arcPara.bMenuDownFlag[2]);
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("(V)ersion")) {
					ImGui::Text("portrait lighting _0_0_1");
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}
			if (ImGui::TreeNode("model")) {
				ImGui::RadioButton("image", &arcPara.iPortraitModel, 0);
				ImGui::SameLine();
				ImGui::RadioButton("video", &arcPara.iPortraitModel, 1);

				ImGui::TreePop();
			}
			if (ImGui::TreeNode("style")) {
				ImGui::RadioButton("natural", &arcPara.iPortraitStyle, 0);
				ImGui::RadioButton("studio", &arcPara.iPortraitStyle, 1);
				ImGui::RadioButton("contour", &arcPara.iPortraitStyle, 2);
				ImGui::RadioButton("stage", &arcPara.iPortraitStyle, 3);
				ImGui::RadioButton("stage mono", &arcPara.iPortraitStyle, 4);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("format")) {
				ImGui::RadioButton("BGR", &arcPara.iImageFormat, 0); ImGui::SameLine();
				ImGui::RadioButton("RGB", &arcPara.iImageFormat, 1);
				ImGui::RadioButton("YUV", &arcPara.iImageFormat, 2); ImGui::SameLine();
				ImGui::RadioButton("YUYV", &arcPara.iImageFormat, 3);
				ImGui::RadioButton("NV12", &arcPara.iImageFormat, 4); ImGui::SameLine();
				ImGui::RadioButton("NV21", &arcPara.iImageFormat, 5);
				ImGui::RadioButton("ABGR", &arcPara.iImageFormat, 6); ImGui::SameLine();
				ImGui::RadioButton("ARGB", &arcPara.iImageFormat, 7);
				ImGui::RadioButton("BGRA", &arcPara.iImageFormat, 8); ImGui::SameLine();
				ImGui::RadioButton("RGBA", &arcPara.iImageFormat, 9);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("intensity")) {
				int i = 0;
				for (auto ref : arcPara.vPortraitList) {
					ref += " intensity";
					auto dispPrecision = ref + " = %.3f";
					ImGui::SliderFloat(to_string(i).c_str(), &arcPara.fStyleIntensity[i++], 0.0f, 1.0f, dispPrecision.c_str());
					//ImGui::SliderFloat(" ", &fStyleIntensity[i++], 0.0f, 1.0f, dispPrecision.c_str());
					if (ImGui::IsItemActive() || ImGui::IsItemHovered()) {
						ImGui::SetTooltip("%.3f", arcPara.fStyleIntensity[i - 1]);
					}						
				}
				ImGui::TreePop();
			}

			ImVec2 window_pos = ImVec2((helpWindowCorner & 1) ? ImGui::GetIO().DisplaySize.x - helpWindowBorder : helpWindowBorder, (helpWindowCorner & 2) ? ImGui::GetIO().DisplaySize.y - helpWindowBorder : helpWindowBorder);
			ImVec2 window_pos_pivot = ImVec2((helpWindowCorner & 1) ? 1.0f : 0.0f, (helpWindowCorner & 2) ? 1.0f : 0.0f);
			if (helpWindowCorner != -1) { ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot); }
			ImGui::SetNextWindowBgAlpha(0.1f); // Transparent background
			if (ImGui::Begin("helpWindow", &isShowHelpWindow, (helpWindowCorner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav)) {
				ImGui::Text("c or C save current image.\n" "s or S save current image.\n" "space compare the ori and dst image.");
				ImGui::Separator();
				if (ImGui::IsMousePosValid()) { ImGui::Text("Mouse Position: (%.1f,%.1f)", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y); }
				else{ ImGui::Text("Mouse Position: <invalid>"); }					
				if (ImGui::BeginPopupContextWindow()) {
					if (ImGui::MenuItem("Custom", NULL, helpWindowCorner == -1)) helpWindowCorner = -1;
					if (ImGui::MenuItem("Top-left", NULL, helpWindowCorner == 0)) helpWindowCorner = 0;
					if (ImGui::MenuItem("Top-right", NULL, helpWindowCorner == 1)) helpWindowCorner = 1;
					if (ImGui::MenuItem("Bottom-left", NULL, helpWindowCorner == 2)) helpWindowCorner = 2;
					if (ImGui::MenuItem("Bottom-right", NULL, helpWindowCorner == 3)) helpWindowCorner = 3;
					//if (true && ImGui::MenuItem("Close")) * true = false;
					ImGui::EndPopup();
				}
			}
			ImGui::End();

			ImGui::Button("Time cost : ");
			if (ImGui::IsItemHovered()) {}
			ImGui::SameLine();
			ImGui::Text(" %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();

			ImGui::Render();
			glfwMakeContextCurrent(renderWindow);
			glfwGetFramebufferSize(renderWindow, &i720pNorm.width, &i720pNorm.height);
			glViewport(0, 0, i720pNorm.width, i720pNorm.height);
			glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
			glClear(GL_COLOR_BUFFER_BIT);

			glEnable(GL_TEXTURE_2D);
			GLuint imageTexture;
			glGenTextures(1, &imageTexture);
			glBindTexture(GL_TEXTURE_2D, imageTexture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			GLenum inputColourFormat = GL_BGR;
			if (1 == imageUtils.imageInfo.channel) {
				inputColourFormat = GL_LUMINANCE;
			}
			// Create the texture
			glTexImage2D(GL_TEXTURE_2D,     // Type of texture
				0,                 // Pyramid level (for mip-mapping) - 0 is the top level
				GL_RGB,            // Internal colour format to convert to
				imageUtils.imageInfo.width,          // Image width  i.e. 640 for Kinect in standard mode
				imageUtils.imageInfo.height,          // Image height i.e. 480 for Kinect in standard mode
				0,                 // Border width in pixels (can either be 1 or 0)
				inputColourFormat, // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
				GL_UNSIGNED_BYTE,  // Image data type
				imageUtils.data);        // The actual image data itself
			    glGenerateMipmap(GL_TEXTURE_2D);
			
			/* Draw a quad */
			glBegin(GL_QUADS);
			glTexCoord2i(0, 0); glVertex2i(0, 0);
			glTexCoord2i(0, 1); glVertex2i(0, i720pNorm.height);
			glTexCoord2i(1, 1); glVertex2i(i720pNorm.width, i720pNorm.height);
			glTexCoord2i(1, 0); glVertex2i(i720pNorm.width, 0);
			glEnd();

			glDeleteTextures(1, &imageTexture);
			glDisable(GL_TEXTURE_2D);

			ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

			glfwMakeContextCurrent(renderWindow);
			glfwSwapBuffers(renderWindow);
		}
		
		ImGui_ImplOpenGL2_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(renderWindow);
		glfwTerminate();				
	} catch (const cDegaException& exce) {
		std::cerr << exce.what() << std::endl;
		std::cerr << "main project exception !" << std::endl;
		throw;
	}
	return 0;
}

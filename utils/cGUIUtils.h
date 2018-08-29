#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <cDegaUtils.h>
#include <degaFormat.h>
#include <degaPredefine.h>
#include <cDegaException.h>

#ifdef DEGA_PLATFORM_WINDOW
#include <windows.h>  
#include <commdlg.h>
#elif define(DEGA_PLATFORM_LINUX)

#endif

#define GLEW_STATIC
#include <GL/glew.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl2.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image_aug.h>

namespace degawong {

static ImVec4 clearWindowColor = ImVec4(0.25f, 0.85f, 0.60f, 1.00f);

class cImageUtils {
public:
	cImageUtils() { data = nullptr; }
	cImageUtils(std::string _path2Image) : path2Image(_path2Image) {
		data = nullptr;
		stbLoadImage();
	}
	virtual ~cImageUtils() { stbi_image_free(data); };
public:
	DEGA_FORCE_INLINE void loadImage(std::string _path2Image) {
		stbi_image_free(data);
		path2Image = _path2Image;
		stbLoadImage();
	}
	DEGA_FORCE_INLINE void save2File(std::string _path2Image) {
		stbi_write_bmp(_path2Image.c_str(), imageInfo.width, imageInfo.height, imageInfo.channel, data);
	}
	DEGA_FORCE_INLINE GLenum checkImageFormat() {
		switch (imageInfo.channel) {
		case 1: { return (inputColorFormat = GL_LUMINANCE); }
		case 3: { return (inputColorFormat = GL_RGB); }
		case 4: { return (inputColorFormat = GL_RGBA); }
		default: { return (inputColorFormat = GL_RGB); }
		}
	}
public:
	DEGA_FORCE_INLINE void getOpenFilenName() {
		initWindowFrame();
#ifdef DEGA_PLATFORM_WINDOW
		if (GetOpenFileName(&windowFrame)) { path2Image = windowFrame.lpstrFile; }		
#elif define(DEGA_PLATFORM_LINUX)

#endif
	}
	DEGA_FORCE_INLINE void getSaveFilenName() {
		initWindowFrame();
#ifdef DEGA_PLATFORM_WINDOW
		if (GetSaveFileName(&windowFrame)) { path2Image = windowFrame.lpstrFile; }
#elif define(DEGA_PLATFORM_LINUX)

#endif
	}
public:
	unsigned char* data;
	cImageInfo imageInfo;	
	std::string path2Image;	
	GLenum inputColorFormat;
	TCHAR selectFileName[MAX_PATH];
public:
#ifdef DEGA_PLATFORM_WINDOW
	OPENFILENAME windowFrame;
#elif define(DEGA_PLATFORM_LINUX)

#endif
private:
	DEGA_FORCE_INLINE void stbLoadImage() {
		try {
			data = stbi_load(path2Image.c_str(), &imageInfo.width, &imageInfo.height, &imageInfo.channel, 0);
			if (nullptr == data) { throw cDegaException("unable to read image."); }
		} catch (const cDegaException& exce) {
			std::cerr << exce.what() << std::endl;
			throw;
		}
	}
private:
	DEGA_FORCE_INLINE void initWindowFrame() {
#ifdef DEGA_PLATFORM_WINDOW
		ZeroMemory(&windowFrame, sizeof(OPENFILENAME));
		windowFrame.lStructSize = sizeof(OPENFILENAME);
		windowFrame.hwndOwner = nullptr;
		windowFrame.lpstrFile = selectFileName;
		windowFrame.lpstrFile[0] = '\0';
		windowFrame.nMaxFile = sizeof(selectFileName);
		windowFrame.lpstrFilter = (LPCSTR)"all(*.*)\0*.*\0jpg(*.jpg)\0*.jpg\0bmp(*.bmp)\0*.bmp\0png(*.png)\0*.png\0jpeg(*.jpeg)\0*.jpeg\0\0";
		windowFrame.nFilterIndex = 1;
		windowFrame.lpstrFileTitle = nullptr;
		windowFrame.nMaxFileTitle = 0;
		windowFrame.lpstrInitialDir = nullptr;
		windowFrame.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		//windowFrame.lpTemplateName =  MAKEINTRESOURCE(ID_TEMP_DIALOG);    
#elif define(DEGA_PLATFORM_LINUX)

#endif
	}
};

class cWindowUtils {
public:
	cWindowUtils() { initConstructor(); };
	cWindowUtils(std::vector<std::string> _vPortraitList) { setAlgorithmName(_vPortraitList); initConstructor(); };
	virtual ~cWindowUtils() {};
public:
	DEGA_FORCE_INLINE void initConstructor() {		
		closeWindowFlag = false;
		isShowHelpWindow = true;
		switchAfterBefor = true;
		helpWindowBorder = 15.0;
		helpWindowCorner = DEGA_LOCATION_TOPRIGHT;
	}
public:
	DEGA_FORCE_INLINE void setWindowFormat(int _windowFormat) { windowFormat |= _windowFormat; }
	DEGA_FORCE_INLINE void defaultWindowFormat() { windowFormat |= ImGuiWindowFlags_MenuBar; }
	DEGA_FORCE_INLINE void noMoveWindow() { windowFormat |= ImGuiWindowFlags_NoMove; }
	DEGA_FORCE_INLINE void noTitleWindow() { windowFormat |= ImGuiWindowFlags_NoTitleBar; }
	DEGA_FORCE_INLINE void noResizeWindow() { windowFormat |= ImGuiWindowFlags_NoResize; }
	DEGA_FORCE_INLINE void noScrollbarWindow() { windowFormat |= ImGuiWindowFlags_NoScrollbar; }
	DEGA_FORCE_INLINE void enableIMGUIKeyboard() { ioHandle.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; }
	DEGA_FORCE_INLINE void setWindowHandel(GLFWwindow* _pRenderingWindow) { pRenderingWindow = _pRenderingWindow; }
public:
	DEGA_FORCE_INLINE void imguiWindowInit() { 
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ioHandle = ImGui::GetIO();
		enableIMGUIKeyboard();
		ImGui_ImplGlfw_InitForOpenGL(pRenderingWindow, true);
		ImGui_ImplOpenGL2_Init();
		ImGui::StyleColorsDark();
		setMVPMatrix();
	}
	DEGA_FORCE_INLINE void gameLoopPollEvents() {
		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		checkKeyCallBack();
		defaultWindowFormat();
		drawGUIControls();
		drawHelpWindow();
		checkMenuOpenSaveFlag();
		imguiWindowRender();
		setTextureImage();
	}
public:
	DEGA_FORCE_INLINE void checkKeyCallBack() {
		/* imgui key callback function */
		if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape))) { exit; }
		else if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Space))) { switchAfterBefor = !switchAfterBefor; }
		else if (ImGui::IsKeyPressed('c') || ImGui::IsKeyPressed('C')) { imageUtilsAfter.save2File("arcsoft_result.bmp"); }
		else if (ImGui::IsKeyPressed('s') || ImGui::IsKeyPressed('S')) { imageUtilsAfter.save2File("arcsoft_result.bmp"); }
	}
	DEGA_FORCE_INLINE void checkWidthHeight() {
		if (imageUtilsBefor.imageInfo.width > imageUtilsBefor.imageInfo.height) {
			iRendingSize.width = 1280;
			iRendingSize.height = 720;
		}
		else {
			iRendingSize.width = 576;
			iRendingSize.height = 768;
		}
	}
	DEGA_FORCE_INLINE void setMVPMatrix() {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, (iRendingSize.width), (iRendingSize.height), 0.0, 0.0, 100.0);
		glMatrixMode(GL_MODELVIEW);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClearDepth(0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	DEGA_FORCE_INLINE void textureImage() {
		if (switchAfterBefor) {
			glTexImage2D(GL_TEXTURE_2D, 
				0,            
				GL_RGB,            
				imageUtilsBefor.imageInfo.width,          
				imageUtilsBefor.imageInfo.height,         
				0,
				imageUtilsBefor.checkImageFormat(), 
				GL_UNSIGNED_BYTE,  
				imageUtilsBefor.data);
			glGenerateMipmap(GL_TEXTURE_2D);
		} 
		else {
			glTexImage2D(GL_TEXTURE_2D,    
				0,                 
				GL_RGB,            
				imageUtilsAfter.imageInfo.width,          
				imageUtilsAfter.imageInfo.height,         
				0,                 
				imageUtilsAfter.checkImageFormat(), 
				GL_UNSIGNED_BYTE,  
				imageUtilsAfter.data);        
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}
	DEGA_FORCE_INLINE void drawHelpWindow() {
		ImVec2 window_pos = ImVec2((helpWindowCorner & 1) ? ImGui::GetIO().DisplaySize.x - helpWindowBorder : helpWindowBorder, (helpWindowCorner & 2) ? ImGui::GetIO().DisplaySize.y - helpWindowBorder : helpWindowBorder);
		ImVec2 window_pos_pivot = ImVec2((helpWindowCorner & 1) ? 1.0f : 0.0f, (helpWindowCorner & 2) ? 1.0f : 0.0f);
		if (helpWindowCorner != -1) { ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot); }
		ImGui::SetNextWindowBgAlpha(0.3f);
		if (ImGui::Begin("helpWindow", &isShowHelpWindow, (helpWindowCorner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav)) {
			ImGui::Text("c or C save current image.\n" "s or S save current image.\n" "space compare the ori and dst image.");
			ImGui::Separator();
			if (ImGui::IsMousePosValid()) { ImGui::Text("Mouse Position: (%.1f,%.1f)", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y); }
			else { ImGui::Text("Mouse Position: <invalid>"); }
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
	}
	DEGA_FORCE_INLINE void drawGUIControls() {
		ImGui::Begin("arc parameter", NULL, windowFormat);
		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("(F)ile")) {
				ImGui::MenuItem("(O)pen", NULL, &arcParameter.bMenuDownFlag[0]);
				ImGui::MenuItem("(S)ave", NULL, &arcParameter.bMenuDownFlag[1]);
				ImGui::MenuItem("(Q)uit", NULL, &arcParameter.bMenuDownFlag[2]);
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("(V)ersion")) {
				ImGui::Text("dega algorithm _0_0_1");
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		if (ImGui::TreeNode("model")) {
			ImGui::RadioButton("image", &arcParameter.iAlgorithmModel, 0);
			ImGui::SameLine();
			ImGui::RadioButton("video", &arcParameter.iAlgorithmModel, 1);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("style")) {
			for (size_t i = 0; i < arcParameter.vPortraitList.size(); i++) {
				ImGui::RadioButton(arcParameter.vPortraitList[i].c_str(), &arcParameter.iAlgorithmStyle, i);
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("format")) {
			ImGui::RadioButton("BGR", &arcParameter.iImageFormat, 0); ImGui::SameLine();
			ImGui::RadioButton("RGB", &arcParameter.iImageFormat, 1);
			ImGui::RadioButton("YUV", &arcParameter.iImageFormat, 2); ImGui::SameLine();
			ImGui::RadioButton("YUYV", &arcParameter.iImageFormat, 3);
			ImGui::RadioButton("NV12", &arcParameter.iImageFormat, 4); ImGui::SameLine();
			ImGui::RadioButton("NV21", &arcParameter.iImageFormat, 5);
			ImGui::RadioButton("ABGR", &arcParameter.iImageFormat, 6); ImGui::SameLine();
			ImGui::RadioButton("ARGB", &arcParameter.iImageFormat, 7);
			ImGui::RadioButton("BGRA", &arcParameter.iImageFormat, 8); ImGui::SameLine();
			ImGui::RadioButton("RGBA", &arcParameter.iImageFormat, 9);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("intensity")) {
			size_t i = 0;
			for (auto ref : arcParameter.vPortraitList) {
				ref += " intensity";
				auto dispPrecision = ref + " = %.3f";
				ImGui::SliderFloat(std::to_string(i).c_str(), &arcParameter.fStyleIntensity[i++], 0.0f, 1.0f, dispPrecision.c_str());				
				if (ImGui::IsItemActive() || ImGui::IsItemHovered()) {
					ImGui::SetTooltip("%.3f", arcParameter.fStyleIntensity[i - 1]);
				}
			}
			ImGui::TreePop();
		}
		ImGui::Button("speed : ");
		if (ImGui::IsItemHovered()) {}
		ImGui::SameLine();
		ImGui::Text(" %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
	DEGA_FORCE_INLINE void setTextureImage() {
		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &imageTextureID);
		glBindTexture(GL_TEXTURE_2D, imageTextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		textureImage();
		glBegin(GL_QUADS);
		glTexCoord2i(0, 0); glVertex2i(0, 0);
		glTexCoord2i(0, 1); glVertex2i(0, iRendingSize.height);
		glTexCoord2i(1, 1); glVertex2i(iRendingSize.width, iRendingSize.height);
		glTexCoord2i(1, 0); glVertex2i(iRendingSize.width, 0);
		glEnd();
		glDeleteTextures(1, &imageTextureID);
		glDisable(GL_TEXTURE_2D);
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	}
	DEGA_FORCE_INLINE void imguiWindowRender() {
		ImGui::Render();
		glViewport(0, 0, iRendingSize.width, iRendingSize.height);
		glClearColor(clearWindowColor.x, clearWindowColor.y, clearWindowColor.z, clearWindowColor.w);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	DEGA_FORCE_INLINE void destroyGUIWindow() {
		ImGui_ImplOpenGL2_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
	DEGA_FORCE_INLINE void checkMenuOpenSaveFlag() {
		if (true == arcParameter.bMenuDownFlag[0]) {
			arcParameter.bMenuDownFlag[0] = false;
			imageUtilsAfter.getOpenFilenName();
			loadImage(imageUtilsAfter.path2Image);
		}
		if (true == arcParameter.bMenuDownFlag[1]) {
			arcParameter.bMenuDownFlag[1] = false;
			imageUtilsAfter.getSaveFilenName();
			imageUtilsAfter.save2File(imageUtilsAfter.path2Image);
		}
	}
public:
	DEGA_FORCE_INLINE void loadImage(std::string _path2Image) {
		imageUtilsAfter.loadImage(_path2Image);
		imageUtilsBefor.loadImage(_path2Image);
		checkWidthHeight();
	}
	DEGA_FORCE_INLINE void setAlgorithmName(std::vector<std::string> _vPortraitList) {
		arcParameter.setParameter(_vPortraitList.size());
		arcParameter.vPortraitList = _vPortraitList;
	}
public:	
	int helpWindowCorner;	
	bool closeWindowFlag;
	bool isShowHelpWindow;
	bool switchAfterBefor;
	float helpWindowBorder;
public:		
	ImGuiIO ioHandle;	
	GLuint imageTextureID;
	cDegaPara arcParameter;
	iScreenNorm iRendingSize;	
	cImageUtils imageUtilsAfter;
	cImageUtils imageUtilsBefor;
	GLFWwindow* pRenderingWindow;
	ImGuiWindowFlags windowFormat;
};

}


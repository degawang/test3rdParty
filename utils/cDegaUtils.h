#pragma once

#include <string>
#include <vector>
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image_aug.h>
#include <degaFormat.h>
#include <degaPredefine.h>
#include <cDegaException.h>

#ifdef DEGA_PLATFORM_WINDOW
#include <windows.h>  
#include <commdlg.h>
#elif define(DEGA_PLATFORM_LINUX)

#endif

namespace degawong {

class cDegaSize {
public:
	cDegaSize() : width(0), height(0) {}
	cDegaSize(int _height, int _width) : width(_width), height(_height) {}
	virtual ~cDegaSize() {}
public:
	int width;
	int height;
public:
	void clear() { width = 0; height = 0; }
};

class cImageInfo {
public:
	cImageInfo() { clear(); };
	virtual ~cImageInfo() {};
public:
	void clear() {
		width = 0;
		height = 0;
		channel = 0;
	}
public:
	int width;
	int height;
	int channel;
};

class cImageUtils {
public:
	cImageUtils() { data = nullptr; }
	cImageUtils(std::string _path2Image) : path2Image(_path2Image) {
		data = nullptr;
		stbLoadImage();
	}
	virtual ~cImageUtils() { stbi_image_free(data); };
public:
	void loadImage(std::string _path2Image) {
		stbi_image_free(data);
		path2Image = _path2Image;
		stbLoadImage();
	}
	void save2File(std::string _path2Image) {
		stbi_write_bmp(_path2Image.c_str(), imageInfo.width, imageInfo.height, imageInfo.channel, data);
	}
	GLenum checkImageFormat() {
		switch (imageInfo.channel) {
		case 1: { return (inputColorFormat = GL_LUMINANCE); }
		case 3: { return (inputColorFormat = GL_RGB); }
		case 4: { return (inputColorFormat = GL_RGBA); }
		default: { return (inputColorFormat = GL_RGB); }
		}
	}
public:
	void getOpenFilenName() {
		initWindowFrame();
#ifdef DEGA_PLATFORM_WINDOW
		if (GetOpenFileName(&windowFrame)) { path2Image = windowFrame.lpstrFile; }		
#elif define(DEGA_PLATFORM_LINUX)

#endif
		//OutputDebugString(selectFileName);
		//OutputDebugString((LPCSTR)"\r\n");
		//std::cout << selectFileName << std::endl;
	}
	void getSaveFilenName() {
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
	void stbLoadImage() {
		try {
			data = stbi_load(path2Image.c_str(), &imageInfo.width, &imageInfo.height, &imageInfo.channel, 0);
			if (nullptr == data) { throw cDegaException("unable to read image."); }
		} catch (const cDegaException& exce) {
			std::cerr << exce.what() << std::endl;
			throw;
		}
	}
private:
	void initWindowFrame() {
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

template <typename _T>
class cDegaPoint {
public:
	cDegaPoint() { clear(); }
	cDegaPoint(const cDegaPoint<_T> &_point) { 
		x = _point.x;
		y = _point.y;
		z = _point.z;
		w = _point.w;
	}
	cDegaPoint(_T _x, _T _y, int _pointFlag) : x(_x), y(_y), z(0), w(0), pointFlag(_pointFlag) {}
	cDegaPoint(_T _x, _T _y, _T _X, int _pointFlag) : pointFlag(_pointFlag) {
		switch (pointFlag) {
		case DEGA_3_POINT:
		{
			x = _x;
			y = _y;
			z = _X;
			w = 0;
			break;
		}
		case DEGA_2_HOMO_POINT:
		{
			x = _x;
			y = _y;
			z = 0;
			w = _X;
			break;
		}
		default:
			break;
		}
	}	
	cDegaPoint(_T _x, _T _y, _T _z, _T _w, int _pointFlag) : x(_x), y(_y), z(_z), w(_w), pointFlag(_pointFlag) {}
	virtual ~cDegaPoint() {}
public:
	_T x;
	_T y;
	_T z;
	_T w;
public:
	int pointFlag;
public:
	void clear() { x = 0; y = 0; z = 0; w = 0; }
};

class iScreenNorm {
public:
	iScreenNorm() : width(0), height(0) {}
	iScreenNorm(int _width, int _height) : width(_width), height(_height) {}
	~iScreenNorm() {};
public:
	int width;
	int height;
};

class cDegaPara {
public:
	cDegaPara() { bMenuDownFlag = nullptr; fStyleIntensity = nullptr; };
	cDegaPara(int _iParaNumbers) : iParaNumbers(_iParaNumbers) {
		iPortraitModel = 0;
		iPortraitStyle = 0;
		bMenuDownFlag = new bool[3] {0};
		fStyleIntensity = new float[iParaNumbers] {0};
	};
	~cDegaPara() {
		if (nullptr != bMenuDownFlag) { delete bMenuDownFlag; }
		if (nullptr != fStyleIntensity) { delete fStyleIntensity; }
	};
public:
	int iImageFormat;
	int iParaNumbers;
	int iPortraitStyle;
	int iPortraitModel;
	bool *bMenuDownFlag;
	float *fStyleIntensity;
	std::vector<std::string> vPortraitList;
};

}


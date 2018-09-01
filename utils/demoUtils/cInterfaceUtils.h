#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <cGUIUtils.h>
#include <cDemoUtils.h>
#include <degaFormat.h>
#include <degaPredefine.h>
#include <cDegaException.h>

namespace degawong {

class cInterfaceUtils {
public:
	cInterfaceUtils() { bMenuDownFlag = nullptr; fStyleIntensity = nullptr; };
	//cInterfaceUtils(cDegaPara& _arcParameter) { 
	//	iImageFormat = _arcParameter.iImageFormat;
	//	iAlgorithmModel = _arcParameter.iAlgorithmModel;
	//	iAlgorithmStyle = _arcParameter.iAlgorithmStyle;
	//	fStyleIntensity = new float[_arcParameter.iParaNumbers] {0};
	//	for (size_t i = 0; i < _arcParameter.iParaNumbers; i++) { fStyleIntensity[i] = _arcParameter.fStyleIntensity[i]; }
	//};
	virtual ~cInterfaceUtils() {
		if (nullptr != bMenuDownFlag) { delete bMenuDownFlag; }
		if (nullptr != fStyleIntensity) { delete fStyleIntensity; }
	};
public:	
	void doAlgorithm();
	void setParameter(const cDemoPara& _arcParameter) {
		iImageFormat = _arcParameter.iImageFormat;
		iAlgorithmModel = _arcParameter.iAlgorithmModel;
		iAlgorithmStyle = _arcParameter.iAlgorithmStyle;
		fStyleIntensity = new float[_arcParameter.iParaNumbers] {0};
		for (size_t i = 0; i < _arcParameter.iParaNumbers; i++) { fStyleIntensity[i] = _arcParameter.fStyleIntensity[i]; }
	}
	void setImageInfo(const cWindowUtils& _guiUtils) {		
		imageData = _guiUtils.imageUtilsAfter.data;
		imageInfo.width = _guiUtils.imageUtilsAfter.imageInfo.width;
		imageInfo.height = _guiUtils.imageUtilsAfter.imageInfo.height;
		imageInfo.channel = _guiUtils.imageUtilsAfter.imageInfo.channel;
	}
	void setImageParameter(const cWindowUtils& _guiUtils) {
		setImageInfo(_guiUtils);
		setParameter(_guiUtils.arcParameter);
	}
public:
	cImageInfo imageInfo;
public:
	int iImageFormat;
	int iParaNumbers;
	int iAlgorithmModel;
	int iAlgorithmStyle;
	bool *bMenuDownFlag;
	float *fStyleIntensity;
	unsigned char *imageData;
};

}


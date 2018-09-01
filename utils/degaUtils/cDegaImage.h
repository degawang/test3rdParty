#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <degaPredefine.h>

namespace degawong {

class cDegaImage {
public:
	cDegaImage() {}
	~cDegaImage() {}
public:

private:
	void createFromEmpty();
private:
	int width;
	int height;
	int stride;
	int channel;

private:
	uchar * data;
	int *refCount;
};


}
#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cDegaUtils.h>
#include <degaPredefine.h>

namespace degawong {

class cDegaMat {
public:
	cDegaMat();
	~cDegaMat();
public:
    cDegaMat(cDegaMat&& _mat);
    cDegaMat(const cDegaMat& _mat);
    cDegaMat(const cDegaSize& _size, const int _matType);
    cDegaMat(const int _height, const int _width, const int _matType);
	cDegaMat(const int _height, const int _width, const int _matType, void *_data);
public:

private:
	void createFromEmpty();
private:
	int width;
	int height;
	int stride;
	int channel;
    int elemSize;
private:
	uchar *data;
	int *refCount;
};


}
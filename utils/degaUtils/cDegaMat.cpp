
#include <tuple>
#include <malloc.h>
#include <cDegaMat.h>
#include <degaType.h>
#include <degaPredefine.h>
#include <stb_image_aug.h>

namespace degawong {

cDegaMat::cDegaMat() { clearAll(); }
cDegaMat::~cDegaMat() { checkForDelocate(); }
cDegaMat::cDegaMat(cDegaMat & _mat) {
	setMatData(_mat);
	setFromCstruct();
	operateAllocate();
	copyMatPoint(_mat);
}
cDegaMat::cDegaMat(cDegaMat && _mat) {
	setMatData(_mat);
	setMatPoint(_mat);
	_mat.clearAll();
}
cDegaMat::cDegaMat(const cDegaSize & _size, const int _matType) : cDegaMat(_size.height, _size.width, _matType) {}
cDegaMat::cDegaMat(std::tuple<int, int, int, int, void *> && _matParaTuple) :
	/* std::make_tuple<int height, int width, int matType, int dataFrom, uchar *data>() */
	cDegaMat(std::get<0>(_matParaTuple), 
	std::get<1>(_matParaTuple), 
	DEGA_TYPE_8UC(std::get<2>(_matParaTuple)), 
	std::get<3>(_matParaTuple), 
	std::get<4>(_matParaTuple)) {}
cDegaMat::cDegaMat(const int _height, const int _width, const int _matType) : dataFrom(DEGA_FROM_CSTRUCT) {
	width = _width;
	height = _height;
	matType = _matType;
	checkMatType();
	operateAllocate();
}
cDegaMat::cDegaMat(const int _height, const int _width, const int _matType, const int _dataFrom, void * _data) {
	width = _width;
	height = _height;
	matType = _matType;
	dataFrom = _dataFrom;
	checkMatType();
	createFromData(_data);
}

void cDegaMat::clearAll() {
	width = 0;
	height = 0;
	stride = 0;
	channel = 0;
	matType = 0;
	dataFrom = 0;
	elemSize = 0;
	dataDepth = 0;
	data = nullptr;
	refCount = nullptr;
	isSubRegion = false;
	isContinuous = false;	
}

void cDegaMat::setFromCstruct() { dataFrom = DEGA_FROM_CSTRUCT; }

void cDegaMat::setMatData(cDegaMat & _mat) {
	width = _mat.width;
	height = _mat.height;
	stride = _mat.stride;
	channel = _mat.channel;
	matType = _mat.matType;
	dataFrom = _mat.dataFrom;
	elemSize = _mat.elemSize;
	dataDepth = _mat.dataDepth;
	isSubRegion = _mat.isSubRegion;
	isContinuous = _mat.isContinuous;
}

void cDegaMat::setMatPoint(cDegaMat & _mat) {
	data = _mat.data;
	refCount = _mat.refCount;
}

void cDegaMat::copyMatPoint(cDegaMat & _mat) {
	/* copy data from data point */

}

void cDegaMat::freeAllocate() {}

void cDegaMat::freeDelocate() {}

void cDegaMat::limitAllocate() { refCount = new int(1); }

void cDegaMat::limitDelocate() { customDelocate(); delete refCount; }

void cDegaMat::customDelocate() {
	switch (dataFrom) {
	case DEGA_FROM_CLSNEW : { return clsNewDelocate(); }
	case DEGA_FROM_MALLOC : { return mallocDelocate(); }
	case DEGA_FROM_STBLOAD : { return stbLoadDelocate(); }
	}
}

void cDegaMat::clsNewDelocate() { delete[] data; }

void cDegaMat::mallocDelocate() { free(data); }

void cDegaMat::stbLoadDelocate() { stbi_image_free(data); }

void cDegaMat::checkMatType() {
	channel = getChannel();
	dataDepth = getDepth();
	elemSize = getElemSize();
	stride = width * elemSize;
}

bool cDegaMat::checkMemoFrom() { return (DEGA_FROM_CSTRUCT == dataFrom); }

bool cDegaMat::needToDelocate() { if (isSubRegion) { return false; }; return ((--(*refCount)) > 1); }

void cDegaMat::checkForDelocate() { if (needToDelocate()) {operateDelocate();} }

void cDegaMat::createFromEmpty() { freeAllocate(); }

void cDegaMat::createFromData(void *_data) { limitAllocate(); data = (uchar *)_data; }

void cDegaMat::operateAllocate() { if (checkMemoFrom()) { createFromEmpty(); } }

void cDegaMat::operateDelocate() {
	if (checkMemoFrom()) { freeDelocate(); }
	else { limitDelocate(); }
}

}




#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <degaFormat.h>
#include <degaPredefine.h>

namespace degawong {

class cDegaSize {
public:
	cDegaSize() { clear(); }
	cDegaSize(int _height, int _width) : width(_width), height(_height) {}
	virtual ~cDegaSize() {}
public:
	int width;
	int height;
public:
	void clear() { width = 0; height = 0; }
};

template <typename _T>
class cDegaScale {
public:
	cDegaScale() { b = g = r = a = 0; }
	cDegaScale(cDegaScale<_T>&& _scale) {
		b = _scale.b;
		g = _scale.g;
		r = _scale.r;
		a = _scale.a;
	}
	cDegaScale(const cDegaScale<_T>& _scale) {
		b = _scale.b;
		g = _scale.g;
		r = _scale.r;
		a = _scale.a;
	}
	cDegaScale(_T _bgr, _T _a) { b = g = r = _bgr; a = _a;}
	cDegaScale(_T _b, _T _g, _T _r, _T _a) { b = _b; g = _g; r = _r; a = _a; }
	virtual ~cDegaScale() {}
public:
	_T b;
	_T g;
	_T r;
	_T a;
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
	cDegaPoint(_T _x, _T _y, int _pointType) : x(_x), y(_y), z(0), w(0), pointType(_pointType) {}
	cDegaPoint(_T _x, _T _y, _T _X, int _pointType) : pointType(_pointType) {
		switch (pointType) {
			case DEGA_POINT_2_HOMO:
			{
				x = _x;
				y = _y;
				z = 0;
				w = _X;
				break;
			}
			case DEGA_POINT_3_USUA:
			{
				x = _x;
				y = _y;
				z = _X;
				w = 0;
				break;
			}
			default: break;
		}
	}
	cDegaPoint(_T _x, _T _y, _T _z, _T _w, int _pointType) : x(_x), y(_y), z(_z), w(_w), pointType(_pointType) {}
	virtual ~cDegaPoint() {}
public:
	_T x;
	_T y;
	_T z;
	_T w;
public:
	int pointType;
public:
	void clear() { x = 0; y = 0; z = 0; w = 0; }
};

}


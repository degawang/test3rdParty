#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <degaType.h>
#include <cDegaUtils.h>
#include <degaPredefine.h>

namespace degawong {

class cDegaMat {
public:
	cDegaMat();
	~cDegaMat();
public:    
    cDegaMat(cDegaMat & _mat);
	cDegaMat(cDegaMat && _mat);
    cDegaMat(const cDegaSize & _size, const int _matType);
	cDegaMat(std::tuple<int, int, int, int, void *>&& _matParaTuple);
	cDegaMat(const int _height, const int _width, const int _matType);	
	cDegaMat(const int _height, const int _width, const int _matType, const int _dataFrom, void *_data = nullptr);
public:
	//cDegaMat& operator ++ ();
	//cDegaMat& operator -- ();
	//cDegaMat operator ++ (int);
	//cDegaMat operator -- (int);
	//cDegaMat& operator = (const _T& _value);
	//cDegaMat operator + (const _T& _value);
	//cDegaMat operator - (const _T& _value);
	//cDegaMat operator * (const _T& _value);
	//cDegaMat operator / (const _T& _value);
	//cDegaMat& operator = (mat<_T>& _mat);
	//cDegaMat& operator = (mat<_T>&& _mat);
	//cDegaMat operator + (const mat<_T>& _mat);
	//cDegaMat operator - (const mat<_T>& _mat);
	//cDegaMat operator * (const mat<_T>& _mat);
	//cDegaMat operator / (const mat<_T>& _mat);
	//cDegaMat& operator += (const _T& _value);
	//cDegaMat& operator -= (const _T& _value);
	//cDegaMat& operator *=(const _T& _value);
	//cDegaMat& operator /=(const _T& _value);
	//cDegaMat& operator += (const cDegaMat& _mat);
	//cDegaMat& operator -= (const cDegaMat& _mat);
	//cDegaMat& operator *=(const cDegaMat& _mat);
	//cDegaMat& operator /=(const cDegaMat& _mat);
	//_T& operator()(const int& _width, const int& _height);
public:
	uchar * ptr() { return data; }
	const uchar* ptr() const { return data; }
	uchar * ptr(int _height) { return data + _height * stride; }
	const uchar* ptr(int _height) const { return data + _height * stride; }
	uchar* ptr(int _height, int _width) { return data + _height * stride + _width * getElemSize(); }
	const uchar* ptr(int _height, int _width) const { return data + _height * stride + _width * getElemSize(); }
public:
	template<typename _T> _T* ptr() { return (_T*)data; }
	template<typename _T> const _T* ptr() const { return (const _T*)data; }
	template<typename _T> _T* ptr(int _height, int _width) { return (_T*)ptr(_height, _width); }
	template<typename _T> const _T* ptr(int _height, int _width) const { return (const _T*)ptr(_height, _width); }
public:
	void clearAll();
	void setFromCstruct();
	void setMatData(cDegaMat & _mat);
	void setMatPoint(cDegaMat & _mat);
	void copyMatPoint(cDegaMat & _mat);
public:
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	int getStride() const { return stride; }
	int getMatType() const { return matType; }
	int getDepth() const { return DEGA_SPLIT_DEPTH(matType); }
	int getChannel() const { return DEGA_SPLIT_CHANEL(matType); }
	int getElemSize() const { return DEGA_GET_ELEMSIZE(matType); }
public:
	bool ifSubRegion() { return isSubRegion; }
	bool ifContinuous() { return isContinuous; }
private:
	void freeAllocate();
	void freeDelocate();
	void limitAllocate();
	void limitDelocate();
	void customDelocate();
private:
	void clsNewDelocate();
	void mallocDelocate();
	void stbLoadDelocate();
private:
	void checkMatType();
	bool checkMemoFrom();
	bool needToDelocate();
	void checkForDelocate();
private:
	void createFromEmpty();
	void createFromData(void *_data);
private:
	void operateAllocate();
	void operateDelocate();
private:
	int width;
	int height;
	int stride;
	int channel; 
	int matType;
	int dataFrom;
	int elemSize;
	int dataDepth;
private:
	bool isSubRegion;
	bool isContinuous;
private:	
	int *refCount;	
	unsigned char *data;
};


}
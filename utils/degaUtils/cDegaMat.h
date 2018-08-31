
#include <vector>
#include <string>
#include <iostream>
#include <degaPredefine.h>

namespace degawong {

class cDegaMat {
public:
	cDegaMat(){}
	~cDegaMat(){}
public:

private:
	void createFromEmpty();
private:
	int width;
	int height;
	int stride;
	int channel;

private:
	uchar *data;
	int *refCount;
};


}
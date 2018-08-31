#pragma once


namespace degawong {

/* short image data type */
#define		DEGA_TYPE_8U		0x0001
#define		DEGA_TYPE_8S		0x0002
#define		DEGA_TYPE_16U		0x0003
#define		DEGA_TYPE_16S		0x0004
#define		DEGA_TYPE_32S		0x0005
#define		DEGA_TYPE_32F		0x0006
#define		DEGA_TYPE_64F		0x0007
/* image data type */
#define		DEGA_TYPE_UCHAR8    0x0001
#define		DEGA_TYPE_SCHAR8	0x0002
#define		DEGA_TYPE_SINT16	0x0003
#define		DEGA_TYPE_USINT16	0x0004
#define		DEGA_TYPE_INT32 	0x0005
#define		DEGA_TYPE_FLOAT32	0x0006
#define		DEGA_TYPE_FLOAT64	0x0007
/* image format */
#define		DEGA_FORMAT_GRAY	0x0000
#define		DEGA_FORMAT_BGR		0x0001
#define		DEGA_FORMAT_RGB		0x0002
#define		DEGA_FORMAT_RGBA	0x0003
#define		DEGA_FORMAT_BGRA	0x0004
#define		DEGA_FORMAT_ABGR	0x0005
#define		DEGA_FORMAT_ARGB	0x0006
#define		DEGA_FORMAT_NV12	0x0007
#define		DEGA_FORMAT_NV21	0x0008
#define		DEGA_FORMAT_YUYV	0x0009
#define		DEGA_FORMAT_YVYU	0x000a
/* make intergrate parameter */
#define     DEGA_MAKE_TYPE(depth,n) ((depth << 4) + n)
/* image channel and data type */
#define		DEGA_8UC1			DEGA_MAKE_TYPE(DEGA_TYPE_8U,(1))
#define		DEGA_8UC2			DEGA_MAKE_TYPE(DEGA_TYPE_8U,(2))
#define		DEGA_8UC3			DEGA_MAKE_TYPE(DEGA_TYPE_8U,(3))
#define		DEGA_8UC(n)			DEGA_MAKE_TYPE(DEGA_TYPE_8U,(n))
/* image channel and data type */
#define		DEGA_8SUC1			DEGA_MAKE_TYPE(DEGA_TYPE_8S,(1))
#define		DEGA_8SUC2			DEGA_MAKE_TYPE(DEGA_TYPE_8S,(2))
#define		DEGA_8SUC3			DEGA_MAKE_TYPE(DEGA_TYPE_8S,(3))
#define		DEGA_8SC(n)			DEGA_MAKE_TYPE(DEGA_TYPE_8S,(n))
/* image channel and data type */
#define		DEGA_16UC1			DEGA_MAKE_TYPE(DEGA_TYPE_16U,(1))
#define		DEGA_16UC2			DEGA_MAKE_TYPE(DEGA_TYPE_16U,(2))
#define		DEGA_16UC3			DEGA_MAKE_TYPE(DEGA_TYPE_16U,(3))
#define		DEGA_16UC(n)		DEGA_MAKE_TYPE(DEGA_TYPE_16U,(n))
/* image channel and data type */
#define		DEGA_16SC1			DEGA_MAKE_TYPE(DEGA_TYPE_16S,(1))
#define		DEGA_16SC2			DEGA_MAKE_TYPE(DEGA_TYPE_16S,(2))
#define		DEGA_16SC3			DEGA_MAKE_TYPE(DEGA_TYPE_16S,(3))
#define		DEGA_16SC(n)		DEGA_MAKE_TYPE(DEGA_TYPE_16S,(n))
/* image channel and data type */
#define		DEGA_32SC1			DEGA_MAKE_TYPE(DEGA_TYPE_32S,(1))
#define		DEGA_32SC2			DEGA_MAKE_TYPE(DEGA_TYPE_32S,(2))
#define		DEGA_32SC3			DEGA_MAKE_TYPE(DEGA_TYPE_32S,(3))
#define		DEGA_32SC(n)		DEGA_MAKE_TYPE(DEGA_TYPE_32S,(n))
/* image channel and data type */
#define		DEGA_32FC1			DEGA_MAKE_TYPE(DEGA_TYPE_32F,(1))
#define		DEGA_32FC2			DEGA_MAKE_TYPE(DEGA_TYPE_32F,(2))
#define		DEGA_32FC3			DEGA_MAKE_TYPE(DEGA_TYPE_32F,(3))
#define		DEGA_32FC(n)		DEGA_MAKE_TYPE(DEGA_TYPE_32F,(n))
/* image channel and data type */
#define		DEGA_64FC1			DEGA_MAKE_TYPE(DEGA_TYPE_64F,(1))
#define		DEGA_64FC2			DEGA_MAKE_TYPE(DEGA_TYPE_64F,(2))
#define		DEGA_64FC3			DEGA_MAKE_TYPE(DEGA_TYPE_64F,(3))
#define		DEGA_64FC(n)		DEGA_MAKE_TYPE(DEGA_TYPE_64F,(n))

}
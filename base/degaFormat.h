#pragma once


namespace degawong {
	/* image data type */
	#define		DEGA_TYPE_INT8	    0X00
	#define		DEGA_TYPE_UINT8		0X01
	#define		DEGA_TYPE_INT16		0X02
	#define		DEGA_TYPE_UINT16	0X03
	#define		DEGA_TYPE_INT32 	0X04
	#define		DEGA_TYPE_FLOAT16	0X05
	#define		DEGA_TYPE_FLOAT32	0X06
	#define		DEGA_TYPE_FLOAT64	0X07
    /* image format */
	#define		DEGA_FORMAT_GRAY	0X00
	#define		DEGA_FORMAT_BGR		0X01
	#define		DEGA_FORMAT_RGB		0X02
	#define		DEGA_FORMAT_RGBA	0X03
	#define		DEGA_FORMAT_BGRA	0X04
	#define		DEGA_FORMAT_ABGR	0X05
	#define		DEGA_FORMAT_ARGB	0X06
	#define		DEGA_FORMAT_NV12	0X07
	#define		DEGA_FORMAT_NV21	0X08
	#define		DEGA_FORMAT_YUYV	0X09
    #define		DEGA_FORMAT_YVYU	0X0a
}
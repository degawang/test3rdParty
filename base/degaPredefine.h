#pragma once
namespace degawong {

/* data type */
typedef unsigned uint;
typedef signed char schar;
typedef unsigned char uchar;
typedef unsigned short ushort;
/* function parameter */
#define     DEGA_PARA_POSITIVE          0x01
#define     DEGA_PARA_NEGATIVE          0x02
/* image merge */
#define     DEGA_MERGE_HARDMIX          0x01
#define     DEGA_MERGE_OVERLAY          0x02
#define     DEGA_MERGE_PINLIGHT         0x03
#define     DEGA_MERGE_HARDLIGHT        0x04
#define     DEGA_MERGE_SOFTLIGHT        0x05
#define     DEGA_MERGE_LINERLIGHT       0x06
#define     DEGA_MERGE_VIVLDLIGHT       0x07
/* image filter */
#define     DEGA_FILTER_EDGE            0x01
#define     DEGA_FILTER_SHARP           0x02
#define     DEGA_FILTER_EMBOSS          0x03
#define     DEGA_FILTER_SKETCH          0x04
#define     DEGA_FILTER_SPHERIZE        0x05
#define     DEGA_FILTER_LIGHT           0x06
#define     DEGA_FILTER_WOODEN          0x07
#define     DEGA_FILTER_COMIC           0x08
#define     DEGA_FILTER_OILPAINT        0x09
/* image process */
#define     DEGA_PROCESS_RESIZE         0x01
/* calculate base */
#define		DEGA_CONSTANT_PI	        3.14159265358979f
/* platform base */
#ifdef     __cplusplus
#define     DEGA_EXTERN_C               extern "C"
#else
#define     DEGA_EXTERN_C
#endif
/* cpp base */
#define		DEGA_ALLIGN_NUM		        16
/* cpp base */
#define		DEGA_MAX_PATH_LENGTH		256
/* point flag */
#define     DEGA_POINT_2_USUA           0x01
#define     DEGA_POINT_2_HOMO           0x02
#define     DEGA_POINT_3_USUA           0x03
#define     DEGA_POINT_3_HOMO           0x04
/* help window location */
#define     DEGA_LOCATION_CUSTOM       -0x01
#define     DEGA_LOCATION_TOPLEFT       0x00
#define     DEGA_LOCATION_TOPRIGHT      0x01
#define     DEGA_LOCATION_BUTTOMLEFT    0x02
#define     DEGA_LOCATION_BUTTOMRIGHT   0x03

#if defined(__clang__) || (__GNUC__) || (__GNUG__)
#define     DEGA_NO_EXPORT_API          __attribute__ ((visibility ("hidden")))
#define     DEGA_EXPORT_API             DEGA_EXTERN_C __attribute__ ((visibility ("default")))
#define     DEGA_FORCE_INLINE           inline __attribute__((__always_inline__))
#elif defined(_MSC_VER) || defined(__CYGWIN__)
#define     DEGA_FORCE_INLINE           __forceinline
#define 	DEGA_EXPORT_API 	        DEGA_EXTERN_C _declspec(dllexport)
#define 	DEGA_IMPORT_API 	        DEGA_EXTERN_C _declspec(dllimport)
#else
#define 	DEGA_EXPORT_API
#define 	DEGA_IMPORT_API
#define     DEGA_FORCE_INLINE
#endif


}

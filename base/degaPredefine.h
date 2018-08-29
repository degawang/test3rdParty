#pragma once
namespace degawong {

/* function parameter */
#define     DEGA_PARA_POSITIVE          0X01
#define     DEGA_PARA_NEGATIVE          0X02
/* image merge */
#define     DEGA_MERGE_HARDMIX          0X01
#define     DEGA_MERGE_OVERLAY          0X02
#define     DEGA_MERGE_PINLIGHT         0X03
#define     DEGA_MERGE_HARDLIGHT        0X04
#define     DEGA_MERGE_SOFTLIGHT        0X05
#define     DEGA_MERGE_LINERLIGHT       0X06
#define     DEGA_MERGE_VIVLDLIGHT       0X07
/* image filter */
#define     DEGA_FILTER_EDGE            0X01
#define     DEGA_FILTER_SHARP           0X02
#define     DEGA_FILTER_EMBOSS          0X03
#define     DEGA_FILTER_SKETCH          0X04
#define     DEGA_FILTER_SPHERIZE        0X05
#define     DEGA_FILTER_LIGHT           0X06
#define     DEGA_FILTER_WOODEN          0X07
#define     DEGA_FILTER_COMIC           0X08
#define     DEGA_FILTER_OILPAINT        0X09
/* image process */
#define     DEGA_PROCESS_RESIZE         0X01
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
#define     DEGA_2_POINT                0X01
#define     DEGA_2_HOMO_POINT           0X02
#define     DEGA_3_POINT                0X03
#define     DEGA_3_HOMO_POINT           0X04
/* help window location */
#define     DEGA_LOCATION_CUSTOM       -0X01
#define     DEGA_LOCATION_TOPLEFT       0X00
#define     DEGA_LOCATION_TOPRIGHT      0X01
#define     DEGA_LOCATION_BUTTOMLEFT    0X02
#define     DEGA_LOCATION_BUTTOMRIGHT   0X03

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

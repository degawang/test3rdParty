#pragma once
namespace degawong {

/* size of data type */
#define     DEGA_SIZE_NONE          0
#define     DEGA_SIZE_INT32         sizeof(int)
#define     DEGA_SIZE_SCHAR8        sizeof(char)
#define     DEGA_SIZE_SINT16        sizeof(short)
#define     DEGA_SIZE_FLOAT32       sizeof(float)
#define     DEGA_SIZE_FLOAT64       sizeof(double)
#define     DEGA_SIZE_UCHAR8        sizeof(unsigned char)
#define     DEGA_SIZE_USINT16       sizeof(unsigned short)

const int   DATATYPE[] = { DEGA_SIZE_NONE, DEGA_SIZE_UCHAR8, DEGA_SIZE_SCHAR8, DEGA_SIZE_SINT16, DEGA_SIZE_USINT16, DEGA_SIZE_INT32, DEGA_SIZE_FLOAT32, DEGA_SIZE_FLOAT64 };

/* split intergrate parameter */
#define     DEGA_SPLIT_DEPTH(type) ((type >> 4))
#define     DEGA_SPLIT_CHANEL(type) ((type & 0X000f))
#define     DEGA_GET_ELEMSIZE(type) (DEGA_SPLIT_CHANEL(type) * DATATYPE[DEGA_SPLIT_DEPTH(type)])

}
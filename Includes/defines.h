#ifndef DEFINES_H_
#define DEFINES_H_

typedef char int8_t;
typedef int int32_t;
typedef short int16_t;

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

typedef float complex fcomplex_t;

typedef struct {
	uint16_t _cols;
	uint16_t _rows;
	fcomplex_t **_data;
}cmatrix_t;

typedef struct {
	uint16_t _cols;
	uint16_t _rows;
	int32_t **_data;
}imatrix_t;

typedef struct {
	uint16_t _cols;
	uint16_t _rows;
	uint8_t **_data;
}smatrix_t;

typedef enum {
	true,
	false
} bool_e;

typedef enum {
	PORT_0,	PORT_1,	PORT_2,	PORT_3, PORT_4,	PORT_5
} portTypes_e;

#endif /* DEFINES_H_ */

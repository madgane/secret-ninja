
#ifndef COMPLEXOPERATIONS_H_
#define COMPLEXOPERATIONS_H_

#include "lteSystem.h"

void conjMatrix(cmatrix_t *inMatrix);
void matrixMult(cmatrix_t *pMatrix, cmatrix_t *qMatrix, cmatrix_t *rMatrix);
void hermMatrix(cmatrix_t *inMatrix, cmatrix_t *outMatrix);
fcomplex_t** memalloc_2D(uint16_t,uint16_t);
void displayMatrix(cmatrix_t *cMatrix);

fcomplex_t getMatrixDet(cmatrix_t *aMatrix);
fcomplex_t detOfMatrix(uint16_t nRows,fcomplex_t **data);
void matrixCopy(cmatrix_t *aMatrix,cmatrix_t *bMatrix);
void eyeMatrix(cmatrix_t *iMatrix,uint16_t nRows);
void freeMatrix(cmatrix_t *fMatrix);
void getColOfMatrix(cmatrix_t *aMatrix,cmatrix_t *bMatrix,uint16_t refCol);
void freeVector(cvector_t *fvector);
void freeVectorf(fvector_t *fvector);
float* memalloc_1Df(uint16_t);
fcomplex_t* memalloc_1D(uint16_t);
void matrixAppend(cmatrix_t *aMatrix,cmatrix_t *bMatrix,cmatrix_t *cMatrix);
void matrixAppendOwr(cmatrix_t *aMatrix,cmatrix_t *bMatrix);
void matrixBottomAppend(cmatrix_t *aMatrix,cmatrix_t *bMatrix,cmatrix_t *cMatrix);
void matrixBottomAppendOwr(cmatrix_t *aMatrix,cmatrix_t *bMatrix);
void repMat(cmatrix_t *aMatrix,cmatrix_t *bMatrix,uint16_t xRows,uint16_t xCols);

void matrixMultInner(cmatrix_t *pMatrix, cmatrix_t *qMatrix, cmatrix_t *rMatrix);
void matrixMultOuter(cmatrix_t *pMatrix, cmatrix_t *qMatrix, cmatrix_t *rMatrix);

#endif /* COMPLEXOPERATIONS_H_ */

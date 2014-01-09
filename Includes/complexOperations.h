
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
void freeMatrix(cmatrix_t *fMatrix,uint16_t nRows);
void getColOfMatrix(cmatrix_t *aMatrix,cmatrix_t *bMatrix,uint16_t refCol);

#endif /* COMPLEXOPERATIONS_H_ */

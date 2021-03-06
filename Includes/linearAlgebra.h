/*
 * linearAlgebra.h
 *
 *  Created on: 8.1.2014
 *      Author: gvenkatr
 */

#ifndef LINEARALGEBRA_H_
#define LINEARALGEBRA_H_

#include "lteSystem.h"

void getQRDecomposition(cmatrix_t *aMatrix,cmatrix_t *qMatrix,cmatrix_t *rMatrix);
void getMatrixInverse(cmatrix_t *aMatrix,cmatrix_t *bMatrix);
void getNullMatrix(cmatrix_t *aMatrix,cmatrix_t *nMatrix);
float getNormOfVector(cmatrix_t *aMatrix);
void getSVD(cmatrix_t *xMatrix,cmatrix_t *uMatrix,cmatrix_t *dMatrix,cmatrix_t *vMatrix);
void getLeftNullMatrix(cmatrix_t *aMatrix,cmatrix_t *nMatrix);
void normalizeMatrix(cmatrix_t *aMatrix,cmatrix_t *bMatrix);

#endif /* LINEARALGEBRA_H_ */

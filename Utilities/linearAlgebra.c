
#include "lteSystem.h"
#include "linearAlgebra.h"
#include "complexOperations.h"

void getQRDecomposition(cmatrix_t *aMatrix,cmatrix_t *qMatrix,cmatrix_t *rMatrix)
{
	float nVecB;
	uint16_t iRow,iCol,nSize,xRow,xCol;
	cmatrix_t vecA,vecB,vecBH,matC,matH,matB;

	matrixCopy(aMatrix,rMatrix);
	eyeMatrix(qMatrix,aMatrix->_rows);

	nSize = MIN(aMatrix->_cols,aMatrix->_rows);
	for (iCol = 0;iCol < nSize;iCol ++)
	{
		vecA._cols = 1;
		vecA._rows = aMatrix->_rows - iCol;
		vecA._data = memalloc_2D(vecA._rows,vecA._cols);

		vecB._cols = 1;
		vecB._rows = aMatrix->_rows - iCol;
		vecB._data = memalloc_2D(vecB._rows,vecA._cols);

		eyeMatrix(&matB,aMatrix->_rows);

		nVecB = 0;
		for (iRow = iCol;iRow < aMatrix->_rows;iRow ++)
		{
			if (iRow == iCol)
			{
				vecB._data[0][0] = 1;
			}
			else
			{
				vecB._data[iRow - iCol][0] = 0;
			}
			vecA._data[iRow-iCol][0] = rMatrix->_data[iRow][iCol];
			nVecB += cabs(rMatrix->_data[iRow][iCol]) * cabs(rMatrix->_data[iRow][iCol]);
		}

		nVecB = sqrt(nVecB);
		for (iRow = 0;iRow < aMatrix->_rows-iCol;iRow ++)
		{
			vecB._data[iRow][0] *= nVecB;
		}

		for (iRow = 0;iRow < aMatrix->_rows-iCol;iRow ++)
		{
			vecB._data[iRow][0] = vecA._data[iRow][0] - vecB._data[iRow][0];
		}

		hermMatrix(&vecB,&vecBH);
		matrixMult(&vecBH,&vecA,&matC);
		getMatrixInverse(&matC,&matH);
		matrixMult(&vecB,&matH,&matC);
		matrixMult(&matC,&vecBH,&matH);

		for (xRow = 0;xRow < matH._rows;xRow ++)
		{
			for (xCol = 0;xCol < matH._cols;xCol ++)
			{
				if (xRow == xCol)
				{
					matH._data[xRow][xCol] = 1.0 - matH._data[xRow][xCol];
				}
				else
				{
					matH._data[xRow][xCol] = -matH._data[xRow][xCol];
				}
			}
		}

		if (!iCol)
		{
			matrixCopy(&matH,&matB);
		}
		else
		{
			for (xCol = iCol;xCol < matB._cols;xCol ++)
			{
				for (xRow = iCol;xRow < matB._rows;xRow ++)
				{
					matB._data[xRow][xCol] = matH._data[xRow - iCol][xCol - iCol];
				}
			}
		}

		hermMatrix(&matB,&matH);
		matrixMult(qMatrix,&matH,&matC);
		matrixCopy(&matC,qMatrix);

		matrixMult(&matB,rMatrix,&matC);
		matrixCopy(&matC,rMatrix);

		freeMatrix(&vecA);freeMatrix(&vecB);freeMatrix(&vecBH);
		freeMatrix(&matC);freeMatrix(&matB);freeMatrix(&matH);

	}
}

void getMatrixInverse(cmatrix_t *aMatrix,cmatrix_t *bMatrix)
{
	uint16_t xRow,xCol,iCol;
	fcomplex_t tempComplex;
	cmatrix_t pMatrix,*xMatrix;

	xMatrix = &pMatrix;
	xMatrix->_rows = aMatrix->_rows;
	xMatrix->_cols = aMatrix->_cols * 2;
	bMatrix->_rows = bMatrix->_cols = aMatrix->_rows;
	xMatrix->_data = memalloc_2D(xMatrix->_rows,xMatrix->_cols);
	bMatrix->_data = memalloc_2D(bMatrix->_rows,bMatrix->_cols);

	for (xRow = 0;xRow < xMatrix->_rows;xRow ++)
	{
		for (xCol = 0;xCol < aMatrix->_cols;xCol ++)
		{
			xMatrix->_data[xRow][xCol] = aMatrix->_data[xRow][xCol];
		}
		xMatrix->_data[xRow][xRow + xCol] = 1 + 0i;
	}

	for (xCol = 0;xCol < aMatrix->_cols;xCol ++)
	{
		tempComplex = xMatrix->_data[xCol][xCol];
		if (cabs(tempComplex) > 1e-6) /* to overcome precision issues of float */
		{
			for (iCol = 0;iCol < xMatrix->_cols;iCol ++)
			{
				xMatrix->_data[xCol][iCol] = xMatrix->_data[xCol][iCol] / tempComplex;
			}
			for (xRow = 0;xRow < xMatrix->_rows;xRow ++)
			{
				if (xRow == xCol) continue;
				tempComplex = xMatrix->_data[xRow][xCol];
				for (iCol = xCol;iCol < xMatrix->_cols;iCol ++)
				{
					xMatrix->_data[xRow][iCol] = xMatrix->_data[xRow][iCol] - tempComplex * xMatrix->_data[xCol][iCol];
				}
			}
		}
	}

	for (xRow = 0;xRow < bMatrix->_rows;xRow ++)
	{
		for (xCol = 0;xCol < bMatrix->_cols;xCol ++)
		{
			bMatrix->_data[xRow][xCol] = xMatrix->_data[xRow][xCol + bMatrix->_cols];
		}
	}

}

void getNullMatrix(cmatrix_t *aMatrix,cmatrix_t *nMatrix)
{
	uint16_t iRow,iCol;
	cmatrix_t pMatrix,qMatrix,iMatrix,ahMatrix;

	nMatrix->_cols = nMatrix->_rows = aMatrix->_rows;
	nMatrix->_data = memalloc_2D(nMatrix->_rows,nMatrix->_cols);

	hermMatrix(aMatrix,&ahMatrix);
	matrixMult(&ahMatrix,aMatrix,&pMatrix);
	getMatrixInverse(&pMatrix,&iMatrix);
	matrixMult(aMatrix,&iMatrix,&pMatrix);
	matrixMult(&pMatrix,&ahMatrix,&qMatrix);

	for (iRow = 0;iRow < nMatrix->_rows;iRow ++)
	{
		for (iCol = 0;iCol < nMatrix->_rows;iCol ++)
		{
			if (iRow == iCol)
			{
				nMatrix->_data[iRow][iCol] = 1 - qMatrix._data[iRow][iCol];
			}
			else
			{
				nMatrix->_data[iRow][iCol] = -qMatrix._data[iRow][iCol];
			}
		}
	}

	freeMatrix(&pMatrix);
	freeMatrix(&qMatrix);
	freeMatrix(&iMatrix);
	freeMatrix(&ahMatrix);
}

float getNormOfVector(cmatrix_t *aMatrix)
{
	uint16_t iRow;
	float normValue = 0;
	cmatrix_t *tMatrix,tempMatrix;

	if (aMatrix->_cols != 1)
	{
		tMatrix = &tempMatrix;
		hermMatrix(aMatrix,tMatrix);
	}
	else
		tMatrix = aMatrix;

	for (iRow = 0;iRow < tMatrix->_rows;iRow ++)
	{
		normValue += cabs(tMatrix->_data[iRow][0]) * cabs(tMatrix->_data[iRow][0]);
	}

	return sqrt(normValue);
}

void getSVD(cmatrix_t *xMatrix,cmatrix_t *uMatrix,cmatrix_t *dMatrix,cmatrix_t *vMatrix)
{
	uint16_t iIter = 1;
	cmatrix_t tMatrix,tR,tQ,hR,X;
	const uint16_t maxIterations = 12;

	eyeMatrix(uMatrix,xMatrix->_rows);
	eyeMatrix(vMatrix,xMatrix->_cols);

	hermMatrix(xMatrix,&X);
	getQRDecomposition(&X,&tQ,&tR);
	matrixMult(vMatrix,&tQ,&tMatrix);
	matrixCopy(&tMatrix,vMatrix);

	while (iIter < maxIterations)
	{
		hermMatrix(&tR,&hR);
		getQRDecomposition(&hR,&tQ,&tR);

		if (iIter % 2)
		{
			matrixMult(uMatrix,&tQ,&tMatrix);
			matrixCopy(&tMatrix,uMatrix);
		}
		else
		{
			matrixMult(vMatrix,&tQ,&tMatrix);
			matrixCopy(&tMatrix,vMatrix);
		}

		iIter ++;
	}

	matrixCopy(&tR,dMatrix);
	freeMatrix(&tMatrix);freeMatrix(&tR);freeMatrix(&tQ);freeMatrix(&hR);freeMatrix(&X);

}

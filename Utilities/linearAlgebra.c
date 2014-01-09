
#include "lteSystem.h"
#include "linearAlgebra.h"
#include "complexOperations.h"

void getQRDecomposition(cmatrix_t *aMatrix,cmatrix_t *qMatrix,cmatrix_t *rMatrix)
{
	float nVecB;
	uint16_t iRow,iCol,nSize;
	cmatrix_t vecA,vecB,vecC,matC,matD,matH;

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

		hermMatrix(&vecB,&vecC);
		matrixMult(&vecC,&vecA,&matC);
		matrixMult(&vecC,&vecB,&matD);
		getMatrixInverse(&matC,&matH);
		matrixMult(&matD,&matH,&matC);

		//H = I - H;

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

	freeMatrix(&pMatrix,pMatrix._rows);
	freeMatrix(&qMatrix,qMatrix._rows);
	freeMatrix(&iMatrix,iMatrix._rows);
	freeMatrix(&ahMatrix,ahMatrix._rows);
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


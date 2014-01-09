
#include "complexOperations.h"

void conjMatrix(cmatrix_t *inMatrix)
{
	uint16_t iRow,iCol;
	for (iRow = 0;iRow < inMatrix->_rows;iRow ++)
	{
		for (iCol = 0;iCol < inMatrix->_cols;iCol ++)
		{
			inMatrix->_data[iRow][iCol] = conjf(inMatrix->_data[iRow][iCol]);
		}
	}
}

void matrixMult(cmatrix_t *pMatrix, cmatrix_t *qMatrix, cmatrix_t *rMatrix)
{
	uint16_t iRow,iCol,iIndex;

	rMatrix->_cols = qMatrix->_cols;
	rMatrix->_rows = pMatrix->_rows;
	rMatrix->_data = memalloc_2D(rMatrix->_rows,rMatrix->_cols);

	for (iRow = 0;iRow < pMatrix->_rows;iRow ++)
	{
		for (iCol = 0;iCol < qMatrix->_cols;iCol ++)
		{
			for (iIndex = 0;iIndex < qMatrix->_rows;iIndex ++)
			{
				rMatrix->_data[iRow][iCol] += pMatrix->_data[iRow][iIndex] * qMatrix->_data[iIndex][iCol];
			}
		}
	}
}

void hermMatrix(cmatrix_t *inMatrix,cmatrix_t *outMatrix)
{
	uint16_t iRow,iCol;

	outMatrix->_cols = inMatrix->_rows;
	outMatrix->_rows = inMatrix->_cols;
	outMatrix->_data = memalloc_2D(outMatrix->_rows,outMatrix->_cols);

	for (iRow = 0;iRow < inMatrix->_rows;iRow ++)
	{
		for (iCol = 0;iCol < inMatrix->_cols;iCol ++)
		{
			outMatrix->_data[iCol][iRow] = conj(inMatrix->_data[iRow][iCol]);
		}
	}
}

void displayMatrix(cmatrix_t *cMatrix)
{
	uint16_t iRow,iCol;

	printf("[\n\t");
	for (iRow = 0;iRow < cMatrix->_rows;iRow ++)
	{
		for (iCol = 0;iCol < cMatrix->_cols;iCol ++)
		{
			printf("%f + %fi \t",creal(cMatrix->_data[iRow][iCol]),cimag(cMatrix->_data[iRow][iCol]));
		}
		printf(";\n\t");
	}
	printf(" \n] \n");
}

void displayOnlyMatrix(fcomplex_t **cMatrix,uint16_t nRows,uint16_t nCols)
{
	uint16_t iRow,iCol;

	printf("[\n\t");
	for (iRow = 0;iRow < nRows;iRow ++)
	{
		for (iCol = 0;iCol < nCols;iCol ++)
		{
			printf("%f + %fi \t",creal(cMatrix[iRow][iCol]),cimag(cMatrix[iRow][iCol]));
		}
		printf(";\n\t");
	}
	printf(" \n] \n");
}

fcomplex_t** memalloc_2D(uint16_t nRows,uint16_t nCols)
{
	uint16_t iRow,iCol;
	fcomplex_t **tempComplex;
	tempComplex = (fcomplex_t **) calloc(nRows,sizeof(fcomplex_t *));
	for (iRow = 0;iRow < nRows;iRow ++)
	{
		tempComplex[iRow] = (fcomplex_t *) calloc(nCols,sizeof(fcomplex_t));
		for (iCol = 0;iCol < nCols;iCol ++)
		{
			tempComplex[iRow][iCol] = 0;
		}
	}
	return tempComplex;
}

fcomplex_t getMatrixDet(cmatrix_t *aMatrix)
{
	if (aMatrix->_cols == aMatrix->_rows)
	{
		return detOfMatrix(aMatrix->_rows,aMatrix->_data);
	}
	else
	{
		return -1;
	}
}

fcomplex_t detOfMatrix(uint16_t nRows,fcomplex_t **data)
{
	fcomplex_t **tempData;
	uint16_t iRow,iCol,iiCol,iIndex;
	fcomplex_t detVal = 0;
	float indexPower;

	switch (nRows)
	{
		case (1):
			detVal = data[0][0];
			break;
		case (2):
			detVal = data[0][0] * data[1][1] - data[1][0] * data[0][1];
			break;
		default:
			for (iCol = 0;iCol < nRows;iCol ++)
			{
				tempData = memalloc_2D(nRows-1,nRows-1);
				for (iRow = 1;iRow < nRows;iRow ++)
				{
					iIndex = 0;
					for (iiCol = 0;iiCol < nRows;iiCol ++)
					{
						if (iiCol == iCol)
						{
							continue;
						}
						else
						{
							tempData[iRow - 1][iIndex ++] = data[iRow][iiCol];
						}
					}
				}
				indexPower = pow(-1.0,iCol);
				detVal += indexPower * detOfMatrix((nRows - 1),tempData) * data[0][iCol];
				for (iRow = 0;iRow < nRows-1;iRow ++) {free(tempData[iRow]);}
				free(tempData);
			}
			break;
	}

	return detVal;
}

void matrixCopy(cmatrix_t *aMatrix,cmatrix_t *bMatrix)
{
	uint16_t iRow,iCol;
	bMatrix->_rows = aMatrix->_rows;
	bMatrix->_cols = aMatrix->_cols;
	bMatrix->_data = memalloc_2D(bMatrix->_rows,bMatrix->_cols);

	for (iRow = 0;iRow < bMatrix->_rows;iRow ++)
	{
		for (iCol = 0;iCol < bMatrix->_cols;iCol ++)
		{
			bMatrix->_data[iRow][iCol] = aMatrix->_data[iRow][iCol];
		}
	}
}

void eyeMatrix(cmatrix_t *iMatrix,uint16_t nRows)
{
	uint16_t iRow;
	iMatrix->_rows = iMatrix->_cols = nRows;
	iMatrix->_data = memalloc_2D(nRows,nRows);

	for (iRow = 0;iRow < nRows;iRow ++)
	{
		iMatrix->_data[iRow][iRow] = 1 + 0i;
	}
}

void freeMatrix(cmatrix_t *fMatrix,uint16_t nRows)
{
	uint16_t iRow;
	for (iRow = 0;iRow < nRows;iRow ++)
	{
		free(fMatrix->_data[iRow]);
	}
	free(fMatrix->_data);
}

void getColOfMatrix(cmatrix_t *aMatrix,cmatrix_t *bMatrix,uint16_t refCol)
{
	uint16_t iRow;
	bMatrix->_rows = aMatrix->_rows;
	bMatrix->_cols = 1;
	bMatrix->_data = memalloc_2D(bMatrix->_rows,bMatrix->_cols);

	for (iRow = 0;iRow < bMatrix->_rows;iRow ++)
	{
		bMatrix->_data[iRow][0] = aMatrix->_data[iRow][refCol];
	}
}


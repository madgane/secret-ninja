
#include "lteSystem.h"
#include "basicAlgorithms.h"

uint16_t maxEntry(fmatrix_t *gMatrix)
{
	uint16_t iIndex,maxIndex = 0;
	float maxValue = -100;

	if (gMatrix->_cols == 1)
	{
		for (iIndex = 0;iIndex < gMatrix->_rows;iIndex ++)
		{
			if (gMatrix->_data[iIndex][0] > maxValue)
			{
				maxIndex = iIndex;
				maxValue = gMatrix->_data[iIndex][0];
			}
		}
	}
	else if (gMatrix->_rows == 1)
	{
		for (iIndex = 0;iIndex < gMatrix->_cols;iIndex ++)
		{
			if (gMatrix->_data[0][iIndex] > maxValue)
			{
				maxIndex = iIndex;
				maxValue = gMatrix->_data[0][iIndex];
			}
		}
	}
	else
	{
		printf("Input must be a vector ! \n");
	}

	return maxIndex;
}

uint16_t maxEntryv(fvector_t *gMatrix)
{
	uint16_t iIndex,maxIndex = 0;
	float maxValue = -100;

	for (iIndex = 0;iIndex < gMatrix->_rows;iIndex ++)
	{
		if (gMatrix->_data[iIndex] > maxValue)
		{
			maxIndex = iIndex;
			maxValue = gMatrix->_data[iIndex];
		}
	}

	return maxIndex;
}



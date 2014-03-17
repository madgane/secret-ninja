
#include "linearAlgebra.h"
#include "supportingFunctions.h"
#include "complexOperations.h"

fcomplex_t** cplxRandnMatrix(uint16_t nRows,uint16_t nCols)
{
	uint16_t iRow,iCol;
	fcomplex_t **randnMatrix,tempComplex;
	randnMatrix = memalloc_2D(nRows,nCols);

	for (iRow = 0;iRow < nRows;iRow ++)
	{
		for (iCol = 0;iCol < nCols;iCol ++)
		{
			__real__ tempComplex = rand() / (float)(RAND_MAX + 1);
			__imag__ tempComplex = rand() / (float)(RAND_MAX + 1);
			randnMatrix[iRow][iCol] = (tempComplex * 2 - (1 + 1j)) / sqrt(2.0);
		}
	}
	return randnMatrix;
}

userConfig_t* createDummyUser(uint16_t uID,uint16_t nRxAntenna,uint16_t backloggedPkts)
{
	uint16_t iSchBlk;
	userConfig_t *dummyUser;
	extern systemConfig_t sysConfig;

	dummyUser = (userConfig_t *) malloc(sizeof(userConfig_t));

	dummyUser->userID = uID;
	dummyUser->queuedPkts = backloggedPkts;
	dummyUser->nRxAntenna = nRxAntenna;

	for (iSchBlk = 0;iSchBlk < sysConfig.nSBs;iSchBlk ++)
	{
		dummyUser->channelMatrix[iSchBlk]._rows = nRxAntenna;
		dummyUser->channelMatrix[iSchBlk]._cols = sysConfig.nTXAntenna;
		randomizeDataMatrix(&dummyUser->channelMatrix[iSchBlk]);
	}

	return dummyUser;
}

void randomizeDataMatrix(cmatrix_t *aMatrix)
{
	uint16_t iRow,iCol;
	fcomplex_t tempComplex;
	aMatrix->_data = memalloc_2D(aMatrix->_rows,aMatrix->_cols);

	for (iRow = 0;iRow < aMatrix->_rows;iRow ++)
	{
		for (iCol = 0;iCol < aMatrix->_cols;iCol ++)
		{
			__real__ tempComplex = rand() / (float)(RAND_MAX + 1);
			__imag__ tempComplex = rand() / (float)(RAND_MAX + 1);
			aMatrix->_data[iRow][iCol] = (tempComplex * 2 - (1 + 1j)) / sqrt(2.0);
		}
	}
}

userConfig_t* createDummyUserWithKnownChannel(uint16_t uID,uint16_t nRxAntenna,uint16_t backloggedPkts,float *channelDumps)
{
	float *rPointer;
	uint16_t iSchBlk;
	userConfig_t *dummyUser;
	extern systemConfig_t sysConfig;

	dummyUser = (userConfig_t *) malloc(sizeof(userConfig_t));
	rPointer = &channelDumps[sysConfig.nSBs * nRxAntenna * sysConfig.nTXAntenna * uID * CPLX];

	dummyUser->userID = uID;
	dummyUser->queuedPkts = backloggedPkts;
	dummyUser->nRxAntenna = nRxAntenna;

	for (iSchBlk = 0;iSchBlk < sysConfig.nSBs;iSchBlk ++)
	{
		dummyUser->channelMatrix[iSchBlk]._rows = nRxAntenna;
		dummyUser->channelMatrix[iSchBlk]._cols = sysConfig.nTXAntenna;
		loadChannelMatrixFromDumps(&dummyUser->channelMatrix[iSchBlk],&rPointer[nRxAntenna * sysConfig.nTXAntenna * iSchBlk * CPLX]);
	}

	return dummyUser;
}

void loadChannelMatrixFromDumps(cmatrix_t *aMatrix,float *rPointer)
{
	uint16_t iRow,iCol,iCounter = 0;
	aMatrix->_data = memalloc_2D(aMatrix->_rows,aMatrix->_cols);

	for (iRow = 0;iRow < aMatrix->_rows;iRow ++)
	{
		for (iCol = 0;iCol < aMatrix->_cols;iCol ++)
		{
			__real__ aMatrix->_data[iRow][iCol] = rPointer[iCounter ++];
			__imag__ aMatrix->_data[iRow][iCol] = rPointer[iCounter ++];
		}
	}
}

void displayChannelMatrices(systemConfig_t *sysConfig,downlinkConfig_t *dlConfig)
{
	float norm;
	uint16_t iSB,iUser;
	for (iSB = 0;iSB < sysConfig->nSBs;iSB ++)
	{
		for (iUser = 0;iUser < dlConfig->linkedUsers;iUser ++)
		{
			printf("UserID - %d, SBlock - %d \n",dlConfig->activeUsers[iUser]->userID,iSB);
			displayMatrix(&dlConfig->activeUsers[iUser]->channelMatrix[iSB]);
			norm = getNormOfVector(&dlConfig->activeUsers[iUser]->channelMatrix[iSB]);
			printf("Channel Norm - %f \n",norm);
		}
	}
}



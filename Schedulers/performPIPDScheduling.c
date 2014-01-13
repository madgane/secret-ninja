
#include "basicAlgorithms.h"
#include "linearAlgebra.h"
#include "complexOperations.h"

void performPIPDScheduling(systemConfig_t *sysConfig,downlinkConfig_t *dlConfig)
{
	float tempProd;
	fvector_t normVector,prodVector;
	cmatrix_t gMatrix,nMatrix,tMatrix;
	uint16_t iUser,iSB,muxUsers,jUser,maxIndex,iRow;

	prodVector._rows = dlConfig->linkedUsers;
	normVector._rows = dlConfig->linkedUsers;
	normVector._data = memalloc_1Df(normVector._rows);
	prodVector._data = memalloc_1Df(normVector._rows);
	muxUsers = MIN(MIN(sysConfig->nTXAntenna,dlConfig->linkedUsers),MAX_MUX_USERS);

	for (iSB = 0;iSB < sysConfig->nSBs;iSB ++)
	{
		for (jUser = 0;jUser < dlConfig->linkedUsers;jUser ++)
		{
			normVector._data[jUser] = getNormOfVector(&dlConfig->activeUsers[jUser]->channelMatrix[iSB]);
		}

		maxIndex = maxEntryv(&normVector);
		matrixCopy(&dlConfig->activeUsers[maxIndex]->channelMatrix[iSB],&gMatrix);
		dlConfig->schedUsers[iSB][0] = dlConfig->activeUsers[maxIndex];

		for (iUser = 1;iUser < muxUsers;iUser ++)
		{
			for (jUser = 0;jUser < dlConfig->linkedUsers;jUser ++)
			{
				tempProd = 1.0;
				hermMatrix(&dlConfig->activeUsers[jUser]->channelMatrix[iSB],&tMatrix);
				matrixMult(&gMatrix,&tMatrix,&nMatrix);
				for (iRow = 0;iRow < gMatrix._rows;iRow ++)
				{
					tempProd *= (normVector._data[jUser] - cabs(nMatrix._data[iRow][0]));
				}
				prodVector._data[jUser] = tempProd;
			}

			maxIndex = maxEntryv(&prodVector);
			matrixBottomAppendOwr(&gMatrix,&dlConfig->activeUsers[maxIndex]->channelMatrix[iSB]);
			dlConfig->schedUsers[iSB][iUser] = dlConfig->activeUsers[maxIndex];
		}
	}
}

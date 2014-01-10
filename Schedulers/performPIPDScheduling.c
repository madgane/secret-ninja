
#include "basicAlgorithms.h"
#include "linearAlgebra.h"
#include "complexOperations.h"

void performPIPDScheduling(systemConfig_t *sysConfig,downlinkConfig_t *dlConfig)
{
	fvector_t normVector;
	cmatrix_t gMatrix,nMatrix,tMatrix;
	uint16_t iUser,iSB,muxUsers,jUser,maxIndex;

	normVector._rows = dlConfig->linkedUsers;
	normVector._data = memalloc_1Df(normVector._rows);
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
			getLeftNullMatrix(&gMatrix,&nMatrix);
			for (jUser = 0;jUser < dlConfig->linkedUsers;jUser ++)
			{
				matrixMult(&dlConfig->activeUsers[jUser]->channelMatrix[iSB],&nMatrix,&tMatrix);
				normVector._data[jUser] = getNormOfVector(&tMatrix);
			}

			maxIndex = maxEntryv(&normVector);
			matrixBottomAppendOwr(&gMatrix,&dlConfig->activeUsers[maxIndex]->channelMatrix[iSB]);
			dlConfig->schedUsers[iSB][iUser] = dlConfig->activeUsers[maxIndex];
		}
	}
}

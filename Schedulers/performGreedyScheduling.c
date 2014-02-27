
#include "basicAlgorithms.h"
#include "linearAlgebra.h"
#include "complexOperations.h"

void performGreedyScheduling(systemConfig_t *sysConfig,downlinkConfig_t *dlConfig)
{
	fvector_t normVector;
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

		for (iUser = 0;iUser < muxUsers;iUser ++)
		{
			maxIndex = maxEntryv(&normVector);
			dlConfig->schedUsers[iSB][iUser] = dlConfig->activeUsers[maxIndex];
			normVector._data[maxIndex] = 0.0;
		}
	}
}

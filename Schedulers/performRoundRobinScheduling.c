
#include "lteSystem.h"

void performRoundRobinScheduling(systemConfig_t *sysConfig,downlinkConfig_t *dlConfig)
{
	uint16_t iUser,iSB,muxUsers,uIndex,jUser,cUserIndex;

	muxUsers = MIN(MIN(sysConfig->nTXAntenna,dlConfig->linkedUsers),MAX_MUX_USERS);
	for (iSB = 0;iSB < sysConfig->nSBs;iSB ++)
	{
		for (iUser = 0;iUser < muxUsers;iUser ++)
		{
			uIndex = (dlConfig->frameNumber + iUser + iSB * muxUsers) % dlConfig->linkedUsers;
			for (jUser = 0;jUser < dlConfig->maxUsers;jUser ++)
			{
				cUserIndex = (jUser + uIndex) % dlConfig->maxUsers;
				if (dlConfig->activeUsers[cUserIndex] != NULL)
				{
					dlConfig->schedUsers[iSB][iUser] = dlConfig->activeUsers[cUserIndex];
					break;
				}
			}
		}
	}
}

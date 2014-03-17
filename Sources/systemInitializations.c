
#include "systemInitializations.h"
#include "complexOperations.h"

dlframe_t downlinkFrame[PING_PONG];
ulframe_t uplinkFrame[PING_PONG];

downlinkConfig_t dlConfig;
systemConfig_t sysConfig;

void initializeSystem(downlinkConfig_t *dConfig,systemConfig_t *sConfig,uint16_t cellID,uint16_t nTxAntenna,uint16_t nSchBlks)
{
	uint32_t iUser;

	dConfig->cellID = cellID;
	dConfig->maxUsers = MAX_ACTIVE_USERS;
	for (iUser = 0;iUser < dConfig->maxUsers;iUser ++)
	{
		dConfig->activeUsers[iUser] = NULL;
	}

	dConfig->frameNumber = 0;
	dConfig->linkedUsers = 0;

	sConfig->nPRBs = MAX_PRB_OVER_SF;
	sConfig->nSBs = nSchBlks;
	sConfig->nTXAntenna = nTxAntenna;
}


userConfig_t* createNewUser(uint32_t userID, cmatrix_t **chnMatrix)
{
	uint16_t schBlk;
	userConfig_t *tempUser;
	tempUser = (userConfig_t *) malloc(sizeof(userConfig_t));

	for (schBlk = 0;schBlk < sysConfig.nSBs;schBlk ++)
	{
		tempUser->channelMatrix[schBlk] = *chnMatrix[schBlk];
	}

	tempUser->userID = userID;
	updateDLConfig_User(&dlConfig,tempUser);

	return tempUser;
}

void updateDLConfig_User(downlinkConfig_t *dConfig,userConfig_t *cUser)
{
	bool_e foundUser = false;
	int16_t iUser,emptyLoc = -1;
	for (iUser = 0;iUser < dConfig->maxUsers;iUser ++)
	{
		if (dConfig->activeUsers[iUser] != NULL)
		{
			if (dConfig->activeUsers[iUser]->userID == cUser->userID)
			{
				foundUser = true;
				clearDLConfig_User(dConfig,cUser->userID);
				dConfig->activeUsers[iUser] = cUser;
			}
		}
		else
		{
			if (emptyLoc == -1)
			{
				emptyLoc = iUser;
			}
		}
	}

	if (foundUser == false)
	{
		dConfig->linkedUsers ++;
		dConfig->activeUsers[emptyLoc] = cUser;
	}
}

void clearDLConfig(downlinkConfig_t *dConfig)
{
	uint16_t iUser,iSB;
	for (iUser = 0;iUser < dConfig->maxUsers;iUser ++)
	{
		if (dConfig->activeUsers[iUser] != NULL)
		{
			freeUser(dConfig->activeUsers[iUser]);
		}
	}
	for (iSB = 0;iSB < sysConfig.nSBs;iSB ++)
	{
		free(dConfig->schedUsers[iSB]);
	}
	free(dConfig->schedUsers);
	free(dConfig);
}

void clearDLConfig_User(downlinkConfig_t *dConfig,uint32_t userID)
{
	uint16_t iUser;
	for (iUser = 0;iUser < dConfig->maxUsers;iUser ++)
	{
		if (dConfig->activeUsers[iUser] != NULL)
		{
			if (dConfig->activeUsers[iUser]->userID == userID)
			{
				dConfig->linkedUsers --;
				freeUser(dConfig->activeUsers[iUser]);
				break;
			}
		}
	}
}

void freeUser(userConfig_t *cUser)
{
	uint16_t iSB;
	for (iSB = 0;iSB < sysConfig.nSBs;iSB ++)
	{
		freeMatrix(&cUser->channelMatrix[iSB]);
		freeMatrix(&cUser->precMatrices[iSB]);
	}
	free(cUser);
}

void updateSystem(downlinkConfig_t *dlConfig,systemConfig_t *sysConfig,uint16_t frameNo)
{
	dlConfig->frameNumber = frameNo;
	dlConfig->cFrame = (dlframe_t *) &downlinkFrame[(frameNo % PING_PONG)];
}

void displayUserStructure(userConfig_t *cUser)
{
	uint16_t iCount;
	printf("Displaying user info - %d \n",cUser->userID);
	printf("Number of Rx Antennas - %d \n",cUser->nRxAntenna);
	printf("Number of Queued Pkts - %d \n",cUser->queuedPkts);
	printf("---------- End of basic user information --------- \n");
	printf("Displaying Channel Matrices - \n");
	for (iCount = 0;iCount < sysConfig.nSBs;iCount ++)
	{
		displayMatrix(&cUser->channelMatrix[iCount]);
	}
}

void displaySystemInfo()
{
	printf("Number of Tx Antenna - %d \n",sysConfig.nTXAntenna);
	printf("Number of PRBs - %d \n",sysConfig.nPRBs);
	printf("Number of Scheduling Blocks - %d \n",sysConfig.nSBs);
	printf("---------- End of system configuration information --------- \n");
}

void displayScheduledUsers(systemConfig_t *sysConfig,downlinkConfig_t *dlConfig)
{
	uint16_t iSB,iUser;
	for (iSB = 0;iSB < sysConfig->nSBs;iSB ++)
	{
		for (iUser = 0;iUser < MAX_MUX_USERS;iUser ++)
		{
			if (dlConfig->schedUsers[iSB][iUser] != NULL)
			{
				printf("%d,",dlConfig->schedUsers[iSB][iUser]->userID);
			}
		}
		printf("\t");
	}
	printf("\n");
}

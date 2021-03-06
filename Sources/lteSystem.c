
#include "lteSystem.h"

#include "systemInitializations.h"
#include "supportingFunctions.h"
#include "complexOperations.h"
#include "linearAlgebra.h"

#include "time.h"
#include "performScheduling.h"
#include "windows.h"

#define DEBUG_TIMERS (10)

float channelDumps[] = {
#include "channelDumpFile_1_base.h"
};

void testFunction();

int main()
{
	srand((unsigned int) 100);
	uint16_t cellID = 0,iFrameNo,iUser;
	const uint16_t maxFrames = 100;
	const uint16_t simUsers = 20;
	uint16_t nTransmit = 4,nReceive = 1,schBlks = 5;
	userConfig_t *cUser;

	double elapTime;
	LARGE_INTEGER frequency;
	LARGE_INTEGER ticTimes[DEBUG_TIMERS];
	LARGE_INTEGER tocTimes[DEBUG_TIMERS];

	QueryPerformanceFrequency(&frequency);

	initializeSystem(&dlConfig,&sysConfig,cellID,nTransmit,schBlks);
	updateSystem(&dlConfig,&sysConfig,0);

	sysConfig.schedType = PIPD;

	for (iUser = 0;iUser < simUsers;iUser ++)
	{
		cUser = createDummyUser(iUser,nReceive,10);
		//cUser = createDummyUserWithKnownChannel(iUser,nReceive,10,channelDumps);
		updateDLConfig_User(&dlConfig,cUser);
	}

	for (iFrameNo = 0;iFrameNo < maxFrames;iFrameNo ++)
	{
		updateSystem(&dlConfig,&sysConfig,iFrameNo);

		QueryPerformanceCounter(&ticTimes[0]);
		performUserScheduling(&sysConfig,&dlConfig);
		QueryPerformanceCounter(&tocTimes[0]);

		displayScheduledUsers(&sysConfig,&dlConfig);

		elapTime = (float) tocTimes[0].QuadPart - (float) ticTimes[0].QuadPart;
		printf("Total Cycles involved - %f Clocks and Time in msec - %f. \n ",(double)frequency.QuadPart,(elapTime * 1e3 / frequency.QuadPart));
	}

	//displayChannelMatrices(&sysConfig,&dlConfig);

	return (true);
}

void testFunction()
{
	uint16_t cellID = 0,iFrameNo;
	const uint16_t maxFrames = 10;
	const uint16_t simUsers = 100;
	uint16_t nTransmit = 4,nReceive = 4,schBlks = 1;
	uint16_t iSB,iUser;
	userConfig_t *cUser;
	fcomplex_t detVal;

	cmatrix_t aMatrix,bMatrix,cMatrix;
	cmatrix_t uMatrix,dMatrix,vMatrix;

	double elapTime;
	LARGE_INTEGER frequency;
	LARGE_INTEGER ticTimes[DEBUG_TIMERS];
	LARGE_INTEGER tocTimes[DEBUG_TIMERS];

	QueryPerformanceFrequency(&frequency);

	initializeSystem(&dlConfig,&sysConfig,cellID,nTransmit,schBlks);
	updateSystem(&dlConfig,&sysConfig,0);

	for (iUser = 0;iUser < simUsers;iUser ++)
	{
		cUser = createDummyUser(iUser,nReceive,10);
		updateDLConfig_User(&dlConfig,cUser);
	}

	QueryPerformanceCounter(&ticTimes[0]);
	for (iSB = 0;iSB < sysConfig.nSBs;iSB ++)
	{
		for (iUser = 0;iUser < dlConfig.linkedUsers;iUser ++)
		{
			getSVD(&dlConfig.activeUsers[iUser]->channelMatrix[iSB],&uMatrix,&dMatrix,&vMatrix);
		}
	}
	QueryPerformanceCounter(&tocTimes[0]);

	elapTime = (float) tocTimes[0].QuadPart - (float) ticTimes[0].QuadPart;
	printf("Total Cycles involved - %f Clocks and Time in msec - %f. \n ",(double)frequency.QuadPart,(elapTime * 1e3 / frequency.QuadPart));





	aMatrix._rows = 2;aMatrix._cols = 4;
	bMatrix._rows = 2;bMatrix._cols = 4;

	randomizeDataMatrix(&aMatrix);
	randomizeDataMatrix(&bMatrix);

	hermMatrix(&bMatrix,&uMatrix);

	matrixMultInner(&aMatrix,&bMatrix,&cMatrix);

	displayMatrix(&aMatrix);displayMatrix(&bMatrix);
	displayMatrix(&cMatrix);


//
//	displayMatrix(&aMatrix);
//	getLeftNullMatrix(&aMatrix,&cMatrix);
//	matrixMult(&aMatrix,&cMatrix,&bMatrix);
//
//	displayMatrix(&bMatrix);
//
//	getQRDecomposition(&aMatrix,&bMatrix,&cMatrix);
//
//	getSVD(&aMatrix,&uMatrix,&dMatrix,&vMatrix);
//
//	printf("%f",getNormOfVector(&aMatrix));

	//matrixAppendOwr(&aMatrix,&bMatrix);
	//displayMatrix(&aMatrix);

	//hermMatrix(&bMatrix,&cMatrix);

	//displayMatrix(&cMatrix);

	//matrixMult(&aMatrix,&cMatrix,&bMatrix);

	//displayMatrix(&bMatrix);

	//detVal = getMatrixDet(&aMatrix);

	//displayMatrix(&aMatrix);
	//printf("%f,%f \n",crealf(detVal),cimagf(detVal));

	//t = clock();
	//getMatrixInverse(&aMatrix,&bMatrix);
	//t = clock() - t;
	//printf("%d clicks, %f seconds \n\n",(int)t,((float) t)/CLOCKS_PER_SEC);

	//displayMatrix(&aMatrix);
	//getNullMatrix(&aMatrix,&bMatrix);

	//displayMatrix(&bMatrix);

	//matrixMult(&bMatrix,&aMatrix,&cMatrix);

	//displayMatrix(&cMatrix);


	//t = clock();
	//getSVD(&aMatrix,&uMatrix,&dMatrix,&vMatrix);
	//t = clock() - t;

	//printf("%d clicks, %f seconds \n\n",(int)t,((float) t)/CLOCKS_PER_SEC);

	//displayMatrix(&uMatrix);
	//displayMatrix(&dMatrix);
	//displayMatrix(&vMatrix);

	exit(true);
}

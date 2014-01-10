
#include "lteSystem.h"

#include "systemInitializations.h"
#include "supportingFunctions.h"
#include "complexOperations.h"
#include "linearAlgebra.h"

#include "time.h"
#include "performScheduling.h"

#define DEBUG_TIMERS (10)

void testFunction();

int main()
{

	uint16_t cellID = 0,iFrameNo,iUser;
	const uint16_t maxFrames = 1;
	const uint16_t simUsers = 100;
	uint16_t nTransmit = 4,nReceive = 1;
	userConfig_t *cUser;
	clock_t ticTimes[DEBUG_TIMERS];
	clock_t tocTimes[DEBUG_TIMERS];
	float elapTime;

	initializeSystem(&dlConfig,&sysConfig,cellID,nTransmit);
	updateSystem(&dlConfig,&sysConfig,0);

	sysConfig.schedType = SUCCPROJ;

	for (iUser = 0;iUser < simUsers;iUser ++)
	{
		cUser = createDummyUser(iUser,nReceive,10);
		updateDLConfig_User(&dlConfig,cUser);
	}

	/* displayChannelMatrices(&sysConfig,&dlConfig); */

	for (iFrameNo = 0;iFrameNo < maxFrames;iFrameNo ++)
	{
		updateSystem(&dlConfig,&sysConfig,iFrameNo);

		ticTimes[0] = clock();
		performUserScheduling(&sysConfig,&dlConfig);
		tocTimes[0] = clock();

		displayScheduledUsers(&sysConfig,&dlConfig);

		elapTime = (float) tocTimes[0];
		printf("Total Cycles involved - %f Clocks and Time in sec - %f. \n ",elapTime,(elapTime / (float)CLOCKS_PER_SEC));
	}

	return (success);
}



void testFunction()
{
	uint16_t cellID = 0,iFrameNo,iUser;
	const uint16_t maxFrames = 100;
	const uint16_t simUsers = 10;
	userConfig_t *cUser;
	fcomplex_t detVal;

	clock_t t;

	cmatrix_t aMatrix,bMatrix,cMatrix;
	cmatrix_t uMatrix,dMatrix,vMatrix;

	aMatrix._rows = 4;aMatrix._cols = 2;
	bMatrix._rows = 3;bMatrix._cols = 1;

	randomizeDataMatrix(&aMatrix);
	randomizeDataMatrix(&bMatrix);

	displayMatrix(&aMatrix);
	getLeftNullMatrix(&aMatrix,&cMatrix);
	matrixMult(&aMatrix,&cMatrix,&bMatrix);

	displayMatrix(&bMatrix);

	printf("%f",getNormOfVector(&aMatrix));

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

	exit(success);
}

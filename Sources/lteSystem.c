
#include "lteSystem.h"

#include "systemInitializations.h"
#include "supportingFunctions.h"
#include "complexOperations.h"
#include "linearAlgebra.h"

#include "time.h"

int main()
{
	uint16_t cellID = 0,iFrameNo,iUser;
	const uint16_t maxFrames = 100;
	const uint16_t simUsers = 10;
	userConfig_t *cUser;
	fcomplex_t detVal;

	clock_t t;

	cmatrix_t aMatrix,bMatrix,cMatrix;
	cmatrix_t uMatrix,dMatrix,vMatrix;

	initializeSystem(&dlConfig,&sysConfig,cellID,4);
	updateSystem(&dlConfig,&sysConfig,0);

	for (iUser = 0;iUser < simUsers;iUser ++)
	{
		cUser = createDummyUser(iUser,1,10);
		updateDLConfig_User(&dlConfig,cUser);
	}

	for (iFrameNo = 0;iFrameNo < maxFrames;iFrameNo ++)
	{
		updateSystem(&dlConfig,&sysConfig,iFrameNo);
	}

	displaySystemInfo();

	aMatrix._rows = 5;aMatrix._cols = 5;
	//bMatrix._rows = 4;bMatrix._cols = 4;

	randomizeDataMatrix(&aMatrix);
	//randomizeDataMatrix(&bMatrix);

	displayMatrix(&aMatrix);
	//displayMatrix(&bMatrix);

	//hermMatrix(&bMatrix,&cMatrix);

	//displayMatrix(&cMatrix);

	//matrixMult(&aMatrix,&cMatrix,&bMatrix);

	//displayMatrix(&bMatrix);

	//detVal = getMatrixDet(&aMatrix);

	//displayMatrix(&aMatrix);
	//printf("%f,%f \n",crealf(detVal),cimagf(detVal));

	t = clock();
	getMatrixInverse(&aMatrix,&bMatrix);
	t = clock() - t;
	printf("%d clicks, %f seconds \n\n",(int)t,((float) t)/CLOCKS_PER_SEC);

	//displayMatrix(&aMatrix);
	//getNullMatrix(&aMatrix,&bMatrix);

	displayMatrix(&bMatrix);

	//matrixMult(&bMatrix,&aMatrix,&cMatrix);

	//displayMatrix(&cMatrix);


	t = clock();
	getSVD(&aMatrix,&uMatrix,&dMatrix,&vMatrix);
	t = clock() - t;

	printf("%d clicks, %f seconds \n\n",(int)t,((float) t)/CLOCKS_PER_SEC);

	displayMatrix(&uMatrix);
	displayMatrix(&dMatrix);
	displayMatrix(&vMatrix);

	return 1;
}

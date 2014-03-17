
#ifndef SUPPORTINGFUNCTIONS_H_
#define SUPPORTINGFUNCTIONS_H_

#include "lteSystem.h"

fcomplex_t** cplxRandnMatrix(uint16_t,uint16_t);
userConfig_t* createDummyUser(uint16_t,uint16_t,uint16_t);
void randomizeDataMatrix(cmatrix_t *aMatrix);
void displayChannelMatrices(systemConfig_t *sysConfig,downlinkConfig_t *dlConfig);
userConfig_t* createDummyUserWithKnownChannel(uint16_t uID,uint16_t nRxAntenna,uint16_t backloggedPkts,float *rPointer);
void loadChannelMatrixFromDumps(cmatrix_t *aMatrix,float *rPointer);

#endif /* SUPPORTINGFUNCTIONS_H_ */

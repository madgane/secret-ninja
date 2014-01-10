
#ifndef SUPPORTINGFUNCTIONS_H_
#define SUPPORTINGFUNCTIONS_H_

#include "lteSystem.h"

fcomplex_t** cplxRandnMatrix(uint16_t,uint16_t);
userConfig_t* createDummyUser(uint16_t,uint16_t,uint16_t);
void randomizeDataMatrix(cmatrix_t *aMatrix);
void displayChannelMatrices(systemConfig_t *sysConfig,downlinkConfig_t *dlConfig);

#endif /* SUPPORTINGFUNCTIONS_H_ */

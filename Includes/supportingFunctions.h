
#ifndef SUPPORTINGFUNCTIONS_H_
#define SUPPORTINGFUNCTIONS_H_

#include "lteSystem.h"

fcomplex_t** cplxRandnMatrix(uint16_t,uint16_t);
userConfig_t* createDummyUser(uint16_t,uint16_t,uint16_t);
void randomizeDataMatrix(cmatrix_t *aMatrix);

#endif /* SUPPORTINGFUNCTIONS_H_ */

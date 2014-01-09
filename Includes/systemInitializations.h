
#ifndef SYSTEMINITIALIZATIONS_H_
#define SYSTEMINITIALIZATIONS_H_

#include "lteSystem.h"

extern downlinkConfig_t dlConfig;
extern systemConfig_t sysConfig;

void initializeSystem(downlinkConfig_t *,systemConfig_t *,uint16_t,uint16_t);
userConfig_t* createNewUser(uint32_t, cmatrix_t **);
void updateDLConfig_User(downlinkConfig_t *,userConfig_t *);
void clearDLConfig(downlinkConfig_t *);
void clearDLConfig_User(downlinkConfig_t*,uint32_t);
void updateSystem(downlinkConfig_t *,systemConfig_t *,uint16_t);
void displayUserStructure(userConfig_t *cUser);
void displaySystemInfo();

#endif /* SYSTEMINITIALIZATIONS_H_ */

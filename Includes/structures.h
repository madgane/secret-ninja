
#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include "frame.h"

typedef struct {
	uint8_t nTXAntenna;

	uint8_t nPRBs;
	uint8_t nSBs;
	schedType_e schedType;

}systemConfig_t;

typedef struct {
	uint16_t userID;

	cmatrix_t channelMatrix[N_SCHBLK_OVER_SF];
	cmatrix_t precMatrices[N_SCHBLK_OVER_SF];

	uint32_t queuedPkts;
	uint8_t *userBits;
	uint16_t nRxAntenna;

}userConfig_t;

typedef struct {
	uint16_t cellID;
	uint16_t frameNumber;
	userConfig_t *activeUsers[MAX_ACTIVE_USERS];

	uint16_t linkedUsers;
	uint16_t maxUsers;
	dlframe_t *cFrame;

	userConfig_t *schedUsers[N_SCHBLK_OVER_SF][MAX_MUX_USERS];

}downlinkConfig_t;

#endif /* STRUCTURES_H_ */

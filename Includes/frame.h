
#ifndef FRAME_H_
#define FRAME_H_

#include "macros.h"

typedef struct {
	portTypes_e portsPresent[MAX_PORTS_OVER_PRB];
	int32_t dataRE[N_SC_OVER_PRB][N_SYM_OVER_PRB];
}phyRB_t;

typedef struct {
	phyRB_t prbElements[N_PRB_OVER_SF];
}dlframe_t;

typedef struct {
	phyRB_t prbElements[N_PRB_OVER_SF];
}ulframe_t;

#endif /* FRAME_H_ */

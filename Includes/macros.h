
#ifndef MACROS_H_
#define MACROS_H_

/* LTE constants */

#define N_SC_OVER_PRB (12)
#define N_SYM_OVER_PRB	(14)

/* System configurations */

#define N_FFT (1024)
#define N_FFT_USED (600)
#define N_PRB_OVER_SCHBLK (5)

/* System Limitations */

#define MAX_PORTS_OVER_PRB (2)

#define MAX_SYSTEM_USERS (100)
#define MAX_ACTIVE_USERS (100)
#define PING_PONG (2)

/* Derived definitions */

#define MAX_MUX_USERS (4)
#define N_PRB_OVER_SF (N_FFT_USED / N_SC_OVER_PRB)
#define N_SCHBLK_OVER_SF (N_PRB_OVER_SF / N_PRB_OVER_SCHBLK)

#define MIN(X,Y) ((X)<(Y))?(X):(Y)
#define MAX(X,Y) ((X)>(Y))?(X):(Y)

#endif /* MACROS_H_ */

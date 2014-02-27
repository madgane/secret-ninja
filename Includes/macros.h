
#ifndef MACROS_H_
#define MACROS_H_

/* Generals */

#define CPLX (2)

/* LTE constants */

#define N_SC_OVER_PRB (12)
#define N_SYM_OVER_PRB	(14)

/* System configurations */

#define N_FFT (1024)
#define N_FFT_USED (600)
#define N_PRB_OVER_SCHBLK (50)

/* System Limitations */

#define MAX_PORTS_OVER_PRB (2)

#define MAX_ACTIVE_USERS (400)
#define PING_PONG (2)

/* Derived definitions */

#define MAX_MUX_USERS (8)
#define N_PRB_OVER_SF (N_FFT_USED / N_SC_OVER_PRB)
#define N_SCHBLK_OVER_SF (N_PRB_OVER_SF / N_PRB_OVER_SCHBLK)

#define MIN(X,Y) ((X)<(Y))?(X):(Y)
#define MAX(X,Y) ((X)>(Y))?(X):(Y)

#endif /* MACROS_H_ */

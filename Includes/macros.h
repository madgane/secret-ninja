
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

/* System Limitations */

#define MAX_PORTS_OVER_PRB (2)

#define MAX_ACTIVE_USERS (400)
#define PING_PONG (2)
#define MAX_MUX_USERS (8)

#ifdef _MHZ_10
	#define MAX_SCHBLK_OVER_SF (10)
	#define MAX_PRB_OVER_SF	(50)
#elif _MHZ_20
	#define MAX_SCHBLK_OVER_SF (20)
	#define MAX_PRB_OVER_SF	(100)
#endif

#define MIN(X,Y) ((X)<(Y))?(X):(Y)
#define MAX(X,Y) ((X)>(Y))?(X):(Y)

#endif /* MACROS_H_ */

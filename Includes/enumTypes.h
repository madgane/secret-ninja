/*
 * enumTypes.h
 *
 *  Created on: Jan 10, 2014
 *      Author: Ganesh
 */

#ifndef ENUMTYPES_H_
#define ENUMTYPES_H_

typedef enum {
	true,
	false
} bool_e;

typedef enum {
	PORT_0,	PORT_1,	PORT_2,	PORT_3, PORT_4,	PORT_5
} portType_e;

typedef enum {
	ROUNDROBIN, GREEDY, SUCCPROJ, PIPD
} schedType_e;

#endif /* ENUMTYPES_H_ */

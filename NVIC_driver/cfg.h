/*
 * cfg.h
 *
 *  Created on: May 29, 2023
 *      Author: hp
 */

#ifndef NVIC_DRIVER_CFG_H_
#define NVIC_DRIVER_CFG_H_

#include"stdint.h"

/*
 *
*PRIGROUP_16G0S   0b011
*PRIGROUP_8G2S    0b100
*PRIGROUP_4G4S    0b101
*PRIGROUP_2G8S    0b110
*PRIGROUP_0G16S   0b111
 *
 */

//post build case
#define PRIGROUP_16G0S   0b011
#define PRIGROUP_8G2S    0b100
#define PRIGROUP_4G4S    0b101
#define PRIGROUP_2G8S    0b110
#define PRIGROUP_0G16S   0b111

#define GROUPING_STATUS  	PRIGROUP_2G8S


#endif /* NVIC_DRIVER_CFG_H_ */

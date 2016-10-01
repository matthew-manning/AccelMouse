/*Matthew Manning
 *started 01/10/2016 
 *
 *sets up coms with a copmuter and transfers mouse data
 *will have extra coms functions later
 *computer dials mouse 
 */

#ifndef _TRANSFER_LIB_H_
#define _TRANSFER_LIB_H_

#include "pseudomouse.h"

int waitForHost(int port);
int sendMouseData(int ConHandle, struct pseudomouse Mouse, int CycleTime);


#endif

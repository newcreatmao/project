#ifndef __PID_H__
#define __PID_H__

#include "stm32f10x.h"                  // Device header
#include <math.h>
#include <stdlib.h>

void PID_init(void);
float LPID_realize(float speed,float Actual);
float RPID_realize(float speed,float Actual);

#endif

#ifndef __SYS_H
#define __SYS_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "stm32f10x.h"                  // Device header
#include "I2C.h"
#include "stdio.h"
#include "freertos.h"
#include "Delay.h"


#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "mpu6050.h"

#include "OLED.h"
#include "task.h"
#include "HC-SR04.h"
#include "adc.h"
#include "BEEP.h"

#endif

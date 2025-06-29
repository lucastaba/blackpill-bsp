/******************************************************************************
 * @file     vio.c
 * @brief    Virtual I/O implementation template
 * @version  V1.0.0
 * @date     24. May 2023
 ******************************************************************************/
/*
 * Copyright (c) 2019-2023 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <string.h>
#include "Driver_GPIO.h"
#include "cmsis_vio.h"

#include "RTE_Components.h"                 // Component selection
#include CMSIS_device_header

#if !defined CMSIS_VOUT || !defined CMSIS_VIN
// Add user includes here:
#include "GPIO_STM32.h"
#endif

// VIO input, output definitions
#define VIO_VALUE_NUM           5U          // Number of values

// VIO input, output variables
__USED uint32_t vioSignalIn;                // Memory for incoming signal
__USED uint32_t vioSignalOut;               // Memory for outgoing signal
__USED int32_t  vioValue[VIO_VALUE_NUM];    // Memory for value used in vioGetValue/vioSetValue

#if !defined CMSIS_VOUT || !defined CMSIS_VIN

extern ARM_DRIVER_GPIO Driver_GPIO0;
static ARM_DRIVER_GPIO* pGPIOdrv = &Driver_GPIO0;

typedef enum {
  VIO_ACTIVE_LOW,
  VIO_ACTIVE_HIGH,
} VIO_ACTIVE_STATE;

typedef struct {
  ARM_GPIO_Pin_t pin;
  uint32_t mask;
  ARM_GPIO_DIRECTION direction;
  ARM_GPIO_OUTPUT_MODE mode;
  ARM_GPIO_PULL_RESISTOR resitor;
  VIO_ACTIVE_STATE activeState;
  ARM_GPIO_SignalEvent_t eventCb;
} VIO_pinCfg_t;

#define USER_LED (0U)

#if !defined CMSIS_VOUT
// Add global user types, variables, functions here:
const VIO_pinCfg_t outputPinCfg[] = {
  {GPIO_PIN_ID_PORTC(13), vioLED3, ARM_GPIO_OUTPUT, ARM_GPIO_PUSH_PULL, ARM_GPIO_PULL_NONE, VIO_ACTIVE_LOW, NULL},
};
#endif

#if !defined CMSIS_VIN
// Add global user types, variables, functions here:

#endif
#endif

// Initialize test input, output.
void vioInit (void) {
#if !defined CMSIS_VOUT
// Add user variables here:
  int i;
#endif
#if !defined CMSIS_VIN
// Add user variables here:

#endif

  vioSignalIn  = 0U;
  vioSignalOut = 0U;

  memset(vioValue, 0, sizeof(vioValue));

#if !defined CMSIS_VOUT
// Add user code here:
  for (i = 0; i < sizeof(outputPinCfg)/sizeof(*outputPinCfg); i++) {
    pGPIOdrv->Setup(outputPinCfg[i].pin, outputPinCfg[i].eventCb);
    pGPIOdrv->SetDirection(outputPinCfg[i].pin, outputPinCfg[i].direction);
    pGPIOdrv->SetOutputMode(outputPinCfg[i].pin, outputPinCfg[i].mode);
    pGPIOdrv->SetPullResistor(outputPinCfg[i].pin, outputPinCfg[i].resitor);
    vioSetSignal(outputPinCfg[i].pin, 0U);
  }
#endif

#if !defined CMSIS_VIN
// Add user code here:

#endif
}

// Set signal output.
void vioSetSignal (uint32_t mask, uint32_t signal) {
#if !defined CMSIS_VOUT
// Add user variables here:
  int i;
  uint32_t pinValue;
#endif

  vioSignalOut &= ~mask;
  vioSignalOut |=  mask & signal;

#if !defined CMSIS_VOUT
// Add user code here:
  for (i = 0; i < sizeof(outputPinCfg)/sizeof(*outputPinCfg); i++) {
    if ((outputPinCfg[i].mask & mask) != 0) {
      if ((signal & outputPinCfg[i].mask) != 0) {
        pinValue = 1;
      } else {
        pinValue = 0;
      }
      if (outputPinCfg[i].activeState == pinValue) {
        pGPIOdrv->SetOutput(outputPinCfg[i].pin, 1);
      } else {
        pGPIOdrv->SetOutput(outputPinCfg[i].pin, 0);
      }
    }
  }
#endif
}

// Get signal input.
uint32_t vioGetSignal (uint32_t mask) {
  uint32_t signal;
#if !defined CMSIS_VIN
// Add user variables here:

#endif

#if !defined CMSIS_VIN
// Add user code here:

//   vioSignalIn = ...;
#endif

  signal = vioSignalIn & mask;

  return signal;
}

// Set value output.
void vioSetValue (uint32_t id, int32_t value) {
  uint32_t index = id;
#if !defined CMSIS_VOUT
// Add user variables here:

#endif

  if (index >= VIO_VALUE_NUM) {
    return;                             /* return in case of out-of-range index */
  }

  vioValue[index] = value;

#if !defined CMSIS_VOUT
// Add user code here:

#endif
}

// Get value input.
int32_t vioGetValue (uint32_t id) {
  uint32_t index = id;
  int32_t  value = 0;
#if !defined CMSIS_VIN
// Add user variables here:

#endif

  if (index >= VIO_VALUE_NUM) {
    return value;                       /* return default in case of out-of-range index */
  }

#if !defined CMSIS_VIN
// Add user code here:

//   vioValue[index] = ...;
#endif

  value = vioValue[index];

  return value;
}
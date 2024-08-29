/*
 * can.h
 *
 *  Created on: 25 sie 2024
 *      Author: barto
 */

#ifndef INC_CAN_H_
#define INC_CAN_H_
#include "main.h"

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);
void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan);
void MX_CAN_Init(void);

#endif /* INC_CAN_H_ */

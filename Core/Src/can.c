/*
 * can.c
 *
 *  Created on: 25 sie 2024
 *      Author: barto
 */

#include "can.h"
CAN_HandleTypeDef hcan;
CAN_TxHeaderTypeDef   TxHeader;
uint8_t               TxData[8];
uint32_t              TxMailbox;
CAN_RxHeaderTypeDef   RxHeader;
uint8_t               RxData[8];
int step=0;
 float speed=680;
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
  {
    Error_Handler();
  }

  if (RxHeader.StdId == 197)
  	{
	  step=RxData[0];
	  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);


  	}
  if (RxHeader.StdId == 198)
    	{
	  if(RxData[0]>=0 && RxData[0]<=100)
  	  {speed=4.51*RxData[0]+451;//magiczne liczby, za długo wyjasniac poprostu nie zmieniac

  	  }
	  else
	  {
	speed=0;
	  }
  	  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    	}

}
void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan) {

	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &RxHeader, RxData);
}

void MX_CAN_Init(void)
{
	CAN_FilterTypeDef  sFilterConfig;
	  hcan.Instance = CAN1;
	  hcan.Init.Prescaler = 4;//4
	  hcan.Init.Mode = CAN_MODE_NORMAL;
	  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
	  hcan.Init.TimeSeg1 = CAN_BS1_9TQ;//9
	  hcan.Init.TimeSeg2 = CAN_BS2_8TQ;//8
	  hcan.Init.TimeTriggeredMode = DISABLE;
	  hcan.Init.AutoBusOff = DISABLE;
	  hcan.Init.AutoWakeUp = DISABLE;
	  hcan.Init.AutoRetransmission = ENABLE;
	  hcan.Init.ReceiveFifoLocked = DISABLE;
	  hcan.Init.TransmitFifoPriority = DISABLE;
	  if (HAL_CAN_Init(&hcan) != HAL_OK)
	  {
	    Error_Handler();
	  }



	  sFilterConfig.FilterBank = 0;
		    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
		    sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
		    sFilterConfig.FilterIdHigh = 0x0000;
		    sFilterConfig.FilterIdLow = 0x0000;
		    sFilterConfig.FilterMaskIdHigh = 0x0000;
		    sFilterConfig.FilterMaskIdLow = 0x0000;
		    sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
		    sFilterConfig.FilterActivation = ENABLE;
		    sFilterConfig.SlaveStartFilterBank = 0;

		    if (HAL_CAN_ConfigFilter(&hcan, &sFilterConfig) != HAL_OK)
		    {
		      /* Filter configuration Error */
		      Error_Handler();
		    }
			if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING)!=HAL_OK)
			  {
				  Error_Handler();
			  }
			if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO1_MSG_PENDING)!=HAL_OK)
						  {
							  Error_Handler();
						  }



		  HAL_CAN_Start(&hcan);
}





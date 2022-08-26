/*!
 * @file        bsp_usart.c
 *
 * @brief       Usart board support package body
 *
 * @version     V1.0.0
 *
 * @date        2022-04-24
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#include "bsp_usart.h"
#include <stdio.h>

/*!
 * @brief       Redirect printf function
 *
 * @param       ch:  The characters that need to be send.
 *
 * @param       *f:  pointer to a FILE that can recording all information
 *              needed to control a stream
 *
 * @retval      The characters that need to be send.
 *
 */
int fputc(int ch, FILE* f)
{
    /** send a byte of data to the serial port */
    USART_TxData(DEBUG_USART, (uint8_t)ch);

    /** wait for the data to be send  */
    while (USART_ReadStatusFlag(DEBUG_USART, USART_FLAG_TXBE) == RESET);

    return (ch);
}

/*!
 * @brief       USART Init
 *
 * @param       baudRate
 *
 * @retval      None
 *
 * @note
 */
void USART_Init(uint32_t baudRate)
{
    GPIO_Config_T gpioConfig;
    USART_Config_T usartConfigStruct;

    /** Enable GPIO clock */
    RCM_EnableAHBPeriphClock(DEBUG_USART_TX_CLK);
    RCM_EnableAHBPeriphClock(DEBUG_USART_RX_CLK);

    /** Enable USART clock */
    RCM_EnableAPB2PeriphClock(DEBUG_USART_CLK);

    /** Connect PXx to USARTx_Tx */
    GPIO_ConfigPinAF(DEBUG_USART_TX_PORT, DEUBG_USART_TX_SOURCE, DEBUG_USART_TX_AF);

    /** Connect PXx to USARTx_Rx */
    GPIO_ConfigPinAF(DEBUG_USART_RX_PORT, DEUBG_USART_RX_SOURCE, DEBUG_USART_RX_AF);

    /** Configure USART Tx as alternate function push-pull */
    gpioConfig.mode = GPIO_MODE_AF;
    gpioConfig.pin = DEBUG_USART_TX_PIN;
    gpioConfig.speed = GPIO_SPEED_50MHz;
    gpioConfig.outtype = GPIO_OUT_TYPE_PP;
    gpioConfig.pupd = GPIO_PUPD_PU;
    GPIO_Config(DEBUG_USART_TX_PORT, &gpioConfig);

    /** Configure USART Rx as input floating */
    gpioConfig.pin = DEBUG_USART_RX_PIN;
    GPIO_Config(DEBUG_USART_RX_PORT, &gpioConfig);

    /**
    * MINI_USARTs configured as follow:
    * BaudRate = baudRate
    * Word Length = 8 Bits
    * One Stop Bit
    * No parity
    * Hardware flow control disabled (RTS and CTS signals)
    * Receive and transmit enabled
    */
    usartConfigStruct.baudRate = baudRate;
    usartConfigStruct.mode     = USART_MODE_TX_RX;
    usartConfigStruct.hardwareFlowCtrl = USART_FLOW_CTRL_NONE;
    usartConfigStruct.parity   = USART_PARITY_NONE;
    usartConfigStruct.stopBits =  USART_STOP_BIT_1;
    usartConfigStruct.wordLength = USART_WORD_LEN_8B;
    USART_Config(DEBUG_USART, &usartConfigStruct);

    /** Enable USART */
    USART_Enable(DEBUG_USART);
}

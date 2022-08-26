/*!
 * @file        bsp_flash.h
 *
 * @brief       Header for bsp_flash.c module
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

#ifndef __BSP_FLASH_H
#define __BSP_FLASH_H

#include "main.h"

/*!
 * @brief    APP type define
 */
typedef enum
{
  APP1 = 0,
  APP2 = 1,
	APP3 = 2
} APP_TypeDef;

#define FLASH_BASE                  (uint32_t)0x08000000

/* 1 Kbytes */
#define FLASH_PAGE_SIZE             (uint32_t)0x400

#define Bootloader_ADDRESS     			(uint32_t)0x1FFFD800		
//Bootloader 030 address is :0x1FFFEC00		//091 address is : 0x1FFFD800

#define USER_APP1_ADDRESS           (uint32_t)0x08002000
/* 8 KBytes */
#define USER_APP1_END_ADDRESS       (uint32_t)0x08004000
#define USER_APP1_FLASH_SIZE        (USER_APP1_END_ADDRESS - USER_APP1_ADDRESS + 1)

#define USER_APP2_ADDRESS           (uint32_t)0x08004000
/* 8 KBytes */
#define USER_APP2_END_ADDRESS       (uint32_t)0x08006000
#define USER_APP2_FLASH_SIZE        (USER_APP2_END_ADDRESS - USER_APP2_ADDRESS + 1)

#define USER_FLASH_SIZE             (USER_APP2_END_ADDRESS - USER_APP1_ADDRESS + 1)

/** function declaration*/
void FLASH_IAP_Init(void);
uint32_t FLASH_IAP_Erase(APP_TypeDef Application);
uint32_t FLASH_IAP_Write(__IO uint32_t* address, uint32_t* data, uint16_t length, APP_TypeDef Application);

#endif

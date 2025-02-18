/* add user code begin Header */
/**
  **************************************************************************
  * @file     main.c
  * @brief    main program
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */
/* add user code end Header */

/* Includes ------------------------------------------------------------------*/
#include "at32f421_wk_config.h"
#include "wk_usart.h"
#include "wk_wdt.h"
#include "wk_gpio.h"
#include "wk_system.h"

/* private includes ----------------------------------------------------------*/
/* add user code begin private includes */
#include "lcd.h"
/* add user code end private includes */

/* private typedef -----------------------------------------------------------*/
/* add user code begin private typedef */

/* add user code end private typedef */

/* private define ------------------------------------------------------------*/
/* add user code begin private define */

/* add user code end private define */

/* private macro -------------------------------------------------------------*/
/* add user code begin private macro */

/* add user code end private macro */

/* private variables ---------------------------------------------------------*/
/* add user code begin private variables */
uint32_t FPS = 0;
uint32_t FPS_Count = 0;
/* add user code end private variables */

/* private function prototypes --------------------------------------------*/
/* add user code begin function prototypes */
void LCD_Test(void);
/* add user code end function prototypes */

/* private user code ---------------------------------------------------------*/
/* add user code begin 0 */

/* add user code end 0 */

/**
  * @brief main function.
  * @param  none
  * @retval none
  */
int main(void)
{
    /* add user code begin 1 */
    /* add user code end 1 */
    /* system clock config. */
    wk_system_clock_config();
    /* config periph clock. */
    wk_periph_clock_config();
    /* nvic config. */
    wk_nvic_config();
    /* timebase config. */
    wk_timebase_init();
    /* init usart1 function. */
    wk_usart1_init();
    /* init wdt function. */
    wk_wdt_init();
    /* init gpio function. */
    wk_gpio_config();
    /* add user code begin 2 */
    usart_data_transmit(USART1, 0xAA);
    LCD_Init();
    /* add user code end 2 */

    while (1)
    {
        /* add user code begin 3 */
        LCD_ShowString(0, 0, "ABCD", RED, WHITE, 32, 1);
        //LCD_DrawLine(0,0,0,0,BLACK);
        //LCD_Test();
        /* add user code end 3 */
    }
}

/* add user code begin 4 */
void LCD_Test(void)
{
    ++FPS_Count;
    LCD_Clear(YELLOW);
    LCD_ShowIntNum(0, 0, FPS, 3, BLUE, WHITE, 32);
}

/* add user code end 4 */

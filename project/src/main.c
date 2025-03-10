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
#include "wk_spi.h"
#include "wk_usart.h"
#include "wk_wdt.h"
#include "wk_dma.h"
#include "wk_gpio.h"
#include "wk_system.h"

/* private includes ----------------------------------------------------------*/
/* add user code begin private includes */
#include <string.h>
#include "lcd.h"
#include "at32_spiflash.h"
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
uint32_t id = 0;
extern const unsigned char gImage_1[336];
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
    __IO uint32_t index = 0;
    __IO uint32_t flash_id_index = 0;
    /* add user code end 1 */
    /* system clock config. */
    wk_system_clock_config();
    /* config periph clock. */
    wk_periph_clock_config();
    /* nvic config. */
    wk_nvic_config();
    /* timebase config. */
    wk_timebase_init();
    /* init dma1 channel1 */
    wk_dma1_channel1_init();
    /* config dma channel transfer parameter */
    /* user need to modify define values DMAx_CHANNELy_XXX_BASE_ADDR and DMAx_CHANNELy_BUFFER_SIZE in at32xxx_wk_config.h */
    wk_dma_channel_config(DMA1_CHANNEL1,
                          DMA1_CHANNEL1_PERIPHERAL_BASE_ADDR,
                          DMA1_CHANNEL1_MEMORY_BASE_ADDR,
                          DMA1_CHANNEL1_BUFFER_SIZE);
    dma_channel_enable(DMA1_CHANNEL1, TRUE);
    /* init usart1 function. */
    wk_usart1_init();
    /* init spi1 function. */
    //wk_spi1_init();
    /* init wdt function. */
    wk_wdt_init();
    /* init gpio function. */
    wk_gpio_config();
    /* add user code begin 2 */
    usart_data_transmit(USART1, 0xAA);
    spiflash_init();
    flash_id_index = spiflash_read_id();
    LCD_Init();
    TranferPicturetoTFT_LCD(2);
    uint8_t a = 10;
    uint8_t test_flag = 0;

    /* add user code end 2 */
    while (1)
    {
        /* add user code begin 3 */
        for (uint8_t i = 0; i < 10; i++)
        {
            LCD_ShowChar1(150, 150, i, WHITE, 0x2104, 64, 0);
            DrawProgressBar(35, 80, 45, 208, a, RED);
            wk_delay_ms(200);

            if (test_flag == 0)
            {
                a++;
                if (a >= 100)
                {
                    test_flag = 1;
                }
            }
            else
            {
                a--;
                if (a <= 10)
                {
                    test_flag = 0;
                }
            }
        }

        /* add user code end 3 */
    }
}

/* add user code begin 4 */
void LCD_Test(void)
{
    ++FPS_Count;
    TranferPicturetoTFT_LCD(3);
    //LCD_Clear(WHITE);
    //LCD_ShowIntNum(0, 180, FPS, 3, BLUE, WHITE, 32);
}

/* add user code end 4 */

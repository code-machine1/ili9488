 /******************************************************************************
   * 测试硬件：立创开发板·GD32E230C8T6    使用主频72Mhz    晶振8Mhz
   * 版 本 号: V1.0
   * 修改作者: www.lckfb.com
   * 修改日期: 2023年11月02日
   * 功能介绍:      
   *****************************************************************************
   * 梁山派软硬件资料与相关扩展板软硬件资料官网全部开源  
   * 开发板官网：www.lckfb.com   
   * 技术支持常驻论坛，任何技术问题欢迎随时交流学习  
   * 立创论坛：club.szlcsc.com   
   * 其余模块移植手册：【立创·GD32E230C8T6开发板】模块移植手册
   * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
   * 不靠卖板赚钱，以培养中国工程师为己任
  ******************************************************************************/
#include "gd32e23x.h"
#include "systick.h"
#include "LCD.h"
#include "test.h"

int main(void)
{
    float t = 0;
	systick_config();//滴答定时器初始化 1ms
	
    LCD_Init();
    LCD_Fill(0,0,320,480,YELLOW);
    while(1)
    {
        main_test();
        Test_Color();
        Test_FillRec();
        Test_Circle();
        English_Font_test();
        Chinese_Font_test();
        Pic_test();
    }
}

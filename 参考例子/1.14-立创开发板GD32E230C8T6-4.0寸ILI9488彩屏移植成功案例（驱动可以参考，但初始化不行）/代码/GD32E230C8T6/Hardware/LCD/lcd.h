#ifndef __LCD_H
#define __LCD_H		
#include "gd32e23x.h"	 
#include "stdlib.h" 
#include "systick.h"
#include "bsp_usart.h"

#ifndef u8
#define u8 uint8_t
#endif

#ifndef u16
#define u16 uint16_t
#endif

#ifndef u32
#define u32 uint32_t
#endif

#define DFT_SCAN_DIR  L2R_U2D  //默认的扫描方向
#define LCD_USE8BIT_MODEL   0  //8位16位切换，1：8位
                               //             0:16位

//扫描方向定义
#define L2R_U2D  0x00 //从左到右,从上到下（正向,0度）
#define L2R_D2U  0x80 //从左到右,从下到上
#define R2L_U2D  0x40 //从右到左,从上到下
#define R2L_D2U  0xc0 //从右到左,从下到上（旋转180度）

#define U2D_L2R  0x20 //从上到下,从左到右
#define U2D_R2L  0x60 //从上到下,从右到左（旋转90度）
#define D2U_L2R  0xa0 //从下到上,从左到右（旋转270度）
#define D2U_R2L  0xe0 //从下到上,从右到左

//LCD重要参数集
typedef struct  
{										    
	u16 width;			//LCD 宽度
	u16 height;			//LCD 高度
	u16 id;				  //LCD ID
}_lcd_dev; 	  

//LCD参数
extern _lcd_dev lcddev;	//管理LCD重要参数

//////////////////////////////////////////////////////////////////////////////////	 
//-----------------LCD端口移植---------------- 
#define RCU_LCD_RD     RCU_GPIOA//RD
#define PORT_LCD_RD    GPIOA
#define GPIO_LCD_RD    GPIO_PIN_0

#define RCU_LCD_WR     RCU_GPIOB//WR
#define PORT_LCD_WR    GPIOB
#define GPIO_LCD_WR    GPIO_PIN_15

#define RCU_LCD_CS      RCU_GPIOC//CS
#define PORT_LCD_CS     GPIOC
#define GPIO_LCD_CS     GPIO_PIN_13

#define RCU_LCD_DC      RCU_GPIOB //DC/RS
#define PORT_LCD_DC     GPIOB
#define GPIO_LCD_DC     GPIO_PIN_14


#define RCU_LCD_RES     RCU_GPIOA//RES
#define PORT_LCD_RES    GPIOA
#define GPIO_LCD_RES    GPIO_PIN_1

#define RCU_LCD_BLK     RCU_GPIOB//BLK/BL
#define PORT_LCD_BLK    GPIOB
#define GPIO_LCD_BLK    GPIO_PIN_12

#define RCU_LCD_DB0     RCU_GPIOA//DB0
#define PORT_LCD_DB0    GPIOA
#define GPIO_LCD_DB0    GPIO_PIN_2

#define RCU_LCD_DB1     RCU_GPIOA//DB1
#define PORT_LCD_DB1    GPIOA
#define GPIO_LCD_DB1    GPIO_PIN_3

#define RCU_LCD_DB2     RCU_GPIOA//DB2
#define PORT_LCD_DB2    GPIOA
#define GPIO_LCD_DB2    GPIO_PIN_4

#define RCU_LCD_DB3     RCU_GPIOA//DB3
#define PORT_LCD_DB3    GPIOA
#define GPIO_LCD_DB3    GPIO_PIN_5

#define RCU_LCD_DB4     RCU_GPIOA//DB4
#define PORT_LCD_DB4    GPIOA
#define GPIO_LCD_DB4    GPIO_PIN_6

#define RCU_LCD_DB5     RCU_GPIOA//DB5
#define PORT_LCD_DB5    GPIOA
#define GPIO_LCD_DB5    GPIO_PIN_7

#define RCU_LCD_DB6     RCU_GPIOB//DB6
#define PORT_LCD_DB6    GPIOB
#define GPIO_LCD_DB6    GPIO_PIN_0

#define RCU_LCD_DB7     RCU_GPIOB//DB7
#define PORT_LCD_DB7    GPIOB
#define GPIO_LCD_DB7    GPIO_PIN_1

#define RCU_LCD_DB8     RCU_GPIOB//DB8
#define PORT_LCD_DB8    GPIOB
#define GPIO_LCD_DB8    GPIO_PIN_10

#define RCU_LCD_DB9     RCU_GPIOB//DB9
#define PORT_LCD_DB9    GPIOB
#define GPIO_LCD_DB9   GPIO_PIN_11

#define RCU_LCD_DB10     RCU_GPIOB//DB10
#define PORT_LCD_DB10    GPIOB
#define GPIO_LCD_DB10    GPIO_PIN_3

#define RCU_LCD_DB11     RCU_GPIOB//DB11
#define PORT_LCD_DB11    GPIOB
#define GPIO_LCD_DB11    GPIO_PIN_4

#define RCU_LCD_DB12     RCU_GPIOB//DB12
#define PORT_LCD_DB12    GPIOB
#define GPIO_LCD_DB12    GPIO_PIN_5

#define RCU_LCD_DB13     RCU_GPIOB//DB13
#define PORT_LCD_DB13    GPIOB
#define GPIO_LCD_DB13    GPIO_PIN_6

#define RCU_LCD_DB14     RCU_GPIOB//DB14
#define PORT_LCD_DB14    GPIOB
#define GPIO_LCD_DB14    GPIO_PIN_7

#define RCU_LCD_DB15     RCU_GPIOB//DB15
#define PORT_LCD_DB15    GPIOB
#define GPIO_LCD_DB15    GPIO_PIN_8

//-----------------LCD端口定义---------------- 
//#define	LCD_LED PAout(5) //LCD背光  PA5

#define	LCD_CS_SET  gpio_bit_write(PORT_LCD_CS, GPIO_LCD_CS, SET)//CS// GPIOA->BSRR=1<<0    //片选端口  PA0
#define	LCD_RS_SET	gpio_bit_write(PORT_LCD_DC, GPIO_LCD_DC, SET)//DC //GPIOA->BSRR=1<<1    //数据/命令 PA1
#define	LCD_WR_SET	gpio_bit_write(PORT_LCD_WR, GPIO_LCD_WR, SET)//WR//GPIOA->BSRR=1<<2    //写数据		PA2
#define	LCD_RD_SET	gpio_bit_write(PORT_LCD_RD, GPIO_LCD_RD, SET)//RD//GPIOA->BSRR=1<<3    //读数据		PA3
#define	LCD_RST_SET	gpio_bit_write(PORT_LCD_RES, GPIO_LCD_RES, SET)//RES  //GPIOA->BSRR=1<<4    //复位			PA4
								    
#define	LCD_CS_CLR  gpio_bit_write(PORT_LCD_CS, GPIO_LCD_CS, RESET)//CSGPIOA->BRR=1<<0     //片选端口  PA0
#define	LCD_RS_CLR	gpio_bit_write(PORT_LCD_DC, GPIO_LCD_DC, RESET)//DCGPIOA->BRR=1<<1     //数据/命令 PA1
#define	LCD_WR_CLR	gpio_bit_write(PORT_LCD_WR, GPIO_LCD_WR, RESET)//WRGPIOA->BRR=1<<2     //写数据		PA2
#define	LCD_RD_CLR	gpio_bit_write(PORT_LCD_RD, GPIO_LCD_RD, RESET)//RDGPIOA->BRR=1<<3     //读数据		PA3
#define	LCD_RST_CLR	gpio_bit_write(PORT_LCD_RES, GPIO_LCD_RES, RESET)//RES GPIOA->BRR=1<<4     //复位			PA4

//#define LCD_DATA_OUT() {GPIOB->CRH=0X33333333;GPIOB->CRL=0X33333333;}
//#define LCD_DATA_IN()  {GPIOB->CRH=0X88888888;GPIOB->CRL=0X88888888;}

//// x ? 置1 : 置0                                      
#define PIN_HIGH_OR_LOW(port,gpio,x)  {((x) ? (GPIO_OCTL(port)|=(uint32_t)(gpio)) : (GPIO_OCTL(port)&=~(uint32_t)(gpio)));}

//                  先清除该位，空出位置                                    根据x判断是设置位还是清除位 
#define BIT_DB15(x) { GPIO_OCTL(PORT_LCD_DB15) &= ((uint32_t)~(GPIO_LCD_DB15)); PIN_HIGH_OR_LOW( PORT_LCD_DB15, GPIO_LCD_DB15, x) }
#define BIT_DB14(x) { GPIO_OCTL(PORT_LCD_DB14) &= ((uint32_t)~(GPIO_LCD_DB14)); PIN_HIGH_OR_LOW( PORT_LCD_DB14, GPIO_LCD_DB14, x) }
#define BIT_DB13(x) { GPIO_OCTL(PORT_LCD_DB13) &= ((uint32_t)~(GPIO_LCD_DB13)); PIN_HIGH_OR_LOW( PORT_LCD_DB13, GPIO_LCD_DB13, x) }
#define BIT_DB12(x) { GPIO_OCTL(PORT_LCD_DB12) &= ((uint32_t)~(GPIO_LCD_DB12)); PIN_HIGH_OR_LOW( PORT_LCD_DB12, GPIO_LCD_DB12, x) }
#define BIT_DB11(x) { GPIO_OCTL(PORT_LCD_DB11) &= ((uint32_t)~(GPIO_LCD_DB11)); PIN_HIGH_OR_LOW( PORT_LCD_DB11, GPIO_LCD_DB11, x) }
#define BIT_DB10(x) { GPIO_OCTL(PORT_LCD_DB10) &= ((uint32_t)~(GPIO_LCD_DB10)); PIN_HIGH_OR_LOW( PORT_LCD_DB10, GPIO_LCD_DB10, x) }
#define BIT_DB9(x) { GPIO_OCTL(PORT_LCD_DB9) &= ((uint32_t)~(GPIO_LCD_DB9)); PIN_HIGH_OR_LOW( PORT_LCD_DB9, GPIO_LCD_DB9, x) }
#define BIT_DB8(x) { GPIO_OCTL(PORT_LCD_DB8) &= ((uint32_t)~(GPIO_LCD_DB8)); PIN_HIGH_OR_LOW( PORT_LCD_DB8, GPIO_LCD_DB8, x) }

#define BIT_DB7(x) { GPIO_OCTL(PORT_LCD_DB7) &= ((uint32_t)~(GPIO_LCD_DB7)); PIN_HIGH_OR_LOW( PORT_LCD_DB7, GPIO_LCD_DB7, x) }
#define BIT_DB6(x) { GPIO_OCTL(PORT_LCD_DB6) &= ((uint32_t)~(GPIO_LCD_DB6)); PIN_HIGH_OR_LOW( PORT_LCD_DB6, GPIO_LCD_DB6, x) }
#define BIT_DB5(x) { GPIO_OCTL(PORT_LCD_DB5) &= ((uint32_t)~(GPIO_LCD_DB5)); PIN_HIGH_OR_LOW( PORT_LCD_DB5, GPIO_LCD_DB5, x) }
#define BIT_DB4(x) { GPIO_OCTL(PORT_LCD_DB4) &= ((uint32_t)~(GPIO_LCD_DB4)); PIN_HIGH_OR_LOW( PORT_LCD_DB4, GPIO_LCD_DB4, x) }
#define BIT_DB3(x) { GPIO_OCTL(PORT_LCD_DB3) &= ((uint32_t)~(GPIO_LCD_DB3)); PIN_HIGH_OR_LOW( PORT_LCD_DB3, GPIO_LCD_DB3, x) }
#define BIT_DB2(x) { GPIO_OCTL(PORT_LCD_DB2) &= ((uint32_t)~(GPIO_LCD_DB2)); PIN_HIGH_OR_LOW( PORT_LCD_DB2, GPIO_LCD_DB2, x) }
#define BIT_DB1(x) { GPIO_OCTL(PORT_LCD_DB1) &= ((uint32_t)~(GPIO_LCD_DB1)); PIN_HIGH_OR_LOW( PORT_LCD_DB1, GPIO_LCD_DB1, x) }
#define BIT_DB0(x) { GPIO_OCTL(PORT_LCD_DB0) &= ((uint32_t)~(GPIO_LCD_DB0)); PIN_HIGH_OR_LOW( PORT_LCD_DB0, GPIO_LCD_DB0, x) }
#define DATAOUT(dat){\
		BIT_DB15( (dat>>15)&0x01 );\
        BIT_DB14( (dat>>14)&0x01 );\
        BIT_DB13( (dat>>13)&0x01 );\
        BIT_DB12( (dat>>12)&0x01 );\
        BIT_DB11( (dat>>11)&0x01 );\
        BIT_DB10( (dat>>10)&0x01 );\
        BIT_DB9( (dat>>9)&0x01 );\
        BIT_DB8( (dat>>8)&0x01 );\
		BIT_DB7( (dat>>7)&0x01 );\
        BIT_DB6( (dat>>6)&0x01 );\
        BIT_DB5( (dat>>5)&0x01 );\
        BIT_DB4( (dat>>4)&0x01 );\
        BIT_DB3( (dat>>3)&0x01 );\
        BIT_DB2( (dat>>2)&0x01 );\
        BIT_DB1( (dat>>1)&0x01 );\
        BIT_DB0( (dat>>0)&0x01 );\
}




//#define DATAOUT(x)  GPIOB->ODR=x;       //数据输出
//#define DATAIN      GPIOB->IDR;         //数据输入

//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
//#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)
	    				

void LCD_WR_REG(u16 reg);//写寄存器
void LCD_WR_data(u16 data);//写数据
void LCD_WR_DATA(u16 data);//写数据
u16 LCD_RD_DATA(void);//读点
u16 LCD_ReadReg(u16 LCD_Reg);//读寄存器
void LCD_SetCursor(u16 x,u16 y);//设置光标位置
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//设置坐标函数
void LCD_DisplayOn(void);//开显示
void LCD_DisplayOff(void);//关显示
u16 LCD_ReadPoint(u16 x,u16 y);//读点函数
void LCD_Clear(u16 color);//清屏函数
	
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);//指定区域填充颜色
void LCD_DrawPoint(u16 x,u16 y,u16 color);//在指定位置画一个点
void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);//在指定位置画一条线
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);//在指定位置画一个矩形
void Draw_Circle(u16 x0,u16 y0,u8 r,u16 color);//在指定位置画一个圆

void LCD_ShowChinese(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode);//显示汉字串
void LCD_ShowChinese12x12(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode);//显示单个12x12汉字
void LCD_ShowChinese16x16(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode);//显示单个16x16汉字
void LCD_ShowChinese24x24(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode);//显示单个24x24汉字
void LCD_ShowChinese32x32(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode);//显示单个32x32汉字

void LCD_ShowChar(u16 x,u16 y,u8 num,u16 fc,u16 bc,u8 sizey,u8 mode);//显示一个字符
void LCD_ShowString(u16 x,u16 y,const u8 *p,u16 fc,u16 bc,u8 sizey,u8 mode);//显示字符串
u32 mypow(u8 m,u8 n);//求幂
void LCD_ShowIntNum(u16 x,u16 y,u16 num,u8 len,u16 fc,u16 bc,u8 sizey);//显示整数变量
void LCD_ShowFloatNum1(u16 x,u16 y,float num,u8 len,u16 fc,u16 bc,u8 sizey);//显示两位小数变量

void LCD_ShowPicture(u16 x,u16 y,u16 length,u16 width,const u8 pic[]);//显示图片

void Set_Dir(u8 dir);
void LCD_Init(void);													   	//初始化
				   						   																			 

#endif  
	 
	 




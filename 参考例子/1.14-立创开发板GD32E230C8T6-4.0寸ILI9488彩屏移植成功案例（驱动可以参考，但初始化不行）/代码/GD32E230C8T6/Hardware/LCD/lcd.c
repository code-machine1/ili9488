#include "lcd.h"
#include "stdlib.h"
#include "lcdfont.h"


//管理LCD重要参数
//默认为竖屏
_lcd_dev lcddev;


void send_data(u16 data)
{
	gpio_bit_write(PORT_LCD_DB15, GPIO_LCD_DB15, (data>>15)&0x01 );
	gpio_bit_write(PORT_LCD_DB14, GPIO_LCD_DB14, (data>>14)&0x01 );
	gpio_bit_write(PORT_LCD_DB13, GPIO_LCD_DB13, (data>>13)&0x01 );
	gpio_bit_write(PORT_LCD_DB12, GPIO_LCD_DB12, (data>>12)&0x01 );
	gpio_bit_write(PORT_LCD_DB11, GPIO_LCD_DB11, (data>>11)&0x01 );
	gpio_bit_write(PORT_LCD_DB10, GPIO_LCD_DB10, (data>>10)&0x01 );
	gpio_bit_write(PORT_LCD_DB9, GPIO_LCD_DB9, (data>>9)&0x01 );
	gpio_bit_write(PORT_LCD_DB8, GPIO_LCD_DB8, (data>>8)&0x01 );
	gpio_bit_write(PORT_LCD_DB7, GPIO_LCD_DB7, (data>>7)&0x01 );
	gpio_bit_write(PORT_LCD_DB6, GPIO_LCD_DB6, (data>>6)&0x01 );
	gpio_bit_write(PORT_LCD_DB5, GPIO_LCD_DB5, (data>>5)&0x01 );
	gpio_bit_write(PORT_LCD_DB4, GPIO_LCD_DB4, (data>>4)&0x01 );
	gpio_bit_write(PORT_LCD_DB3, GPIO_LCD_DB3, (data>>3)&0x01 );
	gpio_bit_write(PORT_LCD_DB2, GPIO_LCD_DB2, (data>>2)&0x01 );
	gpio_bit_write(PORT_LCD_DB1, GPIO_LCD_DB1, (data>>1)&0x01 );
	gpio_bit_write(PORT_LCD_DB0, GPIO_LCD_DB0, (data>>0)&0x01 );

}



//写寄存器函数
//regval:寄存器值
void LCD_WR_REG(u16 reg)
{
//#if LCD_USE8BIT_MODEL==1//使用8位并行数据总线模式
//	LCD_RS_CLR;
//	LCD_CS_CLR;
//	send_data(reg);
//	LCD_WR_CLR;
//	LCD_WR_SET;
//	LCD_CS_SET;
//	LCD_RS_SET;
//#else   //使用16位并行数据总线模式
	LCD_RS_CLR;
	LCD_CS_CLR;
	DATAOUT(reg);
	LCD_WR_CLR;
	LCD_WR_SET;
	LCD_RS_SET;
	LCD_CS_SET;
//#endif	 
}
//写LCD数据
//data:要写入的值
void LCD_WR_data(u16 data)
{	 
//#if LCD_USE8BIT_MODEL==1//使用8位并行数据总线模式
//	LCD_CS_CLR;
//	send_data(data);
//	LCD_WR_CLR;
//	LCD_WR_SET;
//	LCD_CS_SET;
//#else  //使用16位并行数据总线模式
	LCD_CS_CLR;
	DATAOUT(data);
	LCD_WR_CLR;
	LCD_WR_SET;
	LCD_CS_SET;
//#endif
}

//写LCD数据
//data:要写入的值
void LCD_WR_DATA(u16 data)
{
//#if LCD_USE8BIT_MODEL==1//使用8位并行数据总线模式
//	LCD_CS_CLR;
//	send_data(data>>8);
//	LCD_WR_CLR;
//	LCD_WR_SET;	 
//	send_data(data);	
//	LCD_WR_CLR;
//	LCD_WR_SET;	 
//	LCD_CS_SET;
//#else   //使用16位并行数据总线模式
	LCD_CS_CLR;
	DATAOUT(data);
	LCD_WR_CLR;
	LCD_WR_SET;
	LCD_CS_SET;
//#endif	 
}
//读LCD数据
//返回值:读到的值
//u16 LCD_RD_DATA(void)
//{
//	u16 data=0,data0=0;
//	LCD_DATA_IN();
//#if LCD_USE8BIT_MODEL==1//使用8位并行数据总线模式
//	LCD_CS_CLR;
//	LCD_RD_CLR;
//	data=DATAIN;
//	LCD_RD_SET;
//	LCD_RD_CLR;
//	data0=DATAIN;
//	LCD_RD_SET;
//	LCD_CS_SET;
//	data&=0xff;
//	data=data0|data<<8;
//#else //使用16位并行数据总线模式
//	LCD_CS_CLR;
//	LCD_RD_CLR;
//	data=DATAIN;
//	LCD_RD_SET;
//	LCD_CS_SET;
//#endif
//	LCD_DATA_OUT();
//	return data;
//}


/******************************************************************************
      函数说明：设置起始和结束地址
      入口数据：x1,x2 设置列的起始和结束地址
                y1,y2 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2)
{
	LCD_WR_REG(0x2a);//列地址设置
	LCD_WR_data(x1>>8);
	LCD_WR_data(x1&0xff);
	LCD_WR_data(x2>>8);
	LCD_WR_data(x2&0xff);
	LCD_WR_REG(0x2b);//行地址设置
	LCD_WR_data(y1>>8);
	LCD_WR_data(y1&0xff);
	LCD_WR_data(y2>>8);
	LCD_WR_data(y2&0xff);
//	LCD_WR_REG(0x2c);//储存器写
}

/******************************************************************************
      函数说明：设置光标位置
      入口数据：x,y 光标位置
      返回值：  无
******************************************************************************/
void LCD_SetCursor(u16 x,u16 y)
{
	LCD_WR_REG(0x2a);//列地址设置
	LCD_WR_data(x>>8);
	LCD_WR_data(x&0xff);
	LCD_WR_REG(0x2b);//行地址设置
	LCD_WR_data(y>>8);
	LCD_WR_data(y&0xff);
}

//LCD开启显示
void LCD_DisplayOn(void)
{
	LCD_WR_REG(0X29);	//开启显示
}	 
//LCD关闭显示
void LCD_DisplayOff(void)
{
	LCD_WR_REG(0X28);	//关闭显示
}  


//读取个某点的颜色值	 
//x,y:坐标
//返回值:此点的颜色
//u16 LCD_ReadPoint(u16 x,u16 y)
//{
// 	u16 rgb;
//	LCD_SetCursor(x,y);
//	LCD_WR_REG(0X2E);
//#if LCD_USE8BIT_MODEL==1//使用8位并行数据总线模式
//	LCD_DATA_IN();
//	LCD_RS_SET;
//	LCD_CS_CLR;
//	LCD_RD_CLR;
//	rgb=DATAIN;
//	LCD_RD_SET;
//	LCD_RD_CLR;
//#else //使用16位并行数据总线模式
//	rgb=LCD_RD_DATA();//dummy read
//#endif
//	rgb=LCD_RD_DATA();//实际坐标颜色
//	return rgb;
//}


void LCD_Clear(u16 color)
{          
	u16 i,j; 
	LCD_Address_Set(0,0,lcddev.width-1,lcddev.height-1);//设置显示范围
	for(i=0;i<lcddev.width;i++)
	{													   	 	
		for(j=0;j<lcddev.height;j++)
		{
			LCD_WR_DATA(color);
		}
	} 					  	    
}

/******************************************************************************
      函数说明：在指定区域填充颜色
      入口数据：xsta,ysta   起始坐标
                xend,yend   终止坐标
								color       要填充的颜色
      返回值：  无
******************************************************************************/
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)
{          
	u16 i,j; 
	LCD_Address_Set(xsta,ysta,xend-1,yend-1);//设置显示范围
	for(i=ysta;i<yend;i++)
	{													   	 	
		for(j=xsta;j<xend;j++)
		{
			LCD_WR_DATA(color);
		}
	} 					  	    
}

/******************************************************************************
      函数说明：在指定位置画点
      入口数据：x,y 画点坐标
                color 点的颜色
      返回值：  无
******************************************************************************/
void LCD_DrawPoint(u16 x,u16 y,u16 color)
{
	LCD_Address_Set(x,y,x,y);//设置光标位置 
	LCD_WR_DATA(color);
} 


/******************************************************************************
      函数说明：画线
      入口数据：x1,y1   起始坐标
                x2,y2   终止坐标
                color   线的颜色
      返回值：  无
******************************************************************************/
void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1;
	uRow=x1;//画线起点坐标
	uCol=y1;
	if(delta_x>0)incx=1; //设置单步方向 
	else if (delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if (delta_y==0)incy=0;//水平线 
	else {incy=-1;delta_y=-delta_y;}
	if(delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y;
	for(t=0;t<distance+1;t++)
	{
		LCD_DrawPoint(uRow,uCol,color);//画点
		xerr+=delta_x;
		yerr+=delta_y;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}


/******************************************************************************
      函数说明：画矩形
      入口数据：x1,y1   起始坐标
                x2,y2   终止坐标
                color   矩形的颜色
      返回值：  无
******************************************************************************/
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
	LCD_DrawLine(x1,y1,x2,y1,color);
	LCD_DrawLine(x1,y1,x1,y2,color);
	LCD_DrawLine(x1,y2,x2,y2,color);
	LCD_DrawLine(x2,y1,x2,y2,color);
}


/******************************************************************************
      函数说明：画圆
      入口数据：x0,y0   圆心坐标
                r       半径
                color   圆的颜色
      返回值：  无
******************************************************************************/
void Draw_Circle(u16 x0,u16 y0,u8 r,u16 color)
{
	int a,b;
	a=0;b=r;	  
	while(a<=b)
	{
		LCD_DrawPoint(x0-b,y0-a,color);             //3           
		LCD_DrawPoint(x0+b,y0-a,color);             //0           
		LCD_DrawPoint(x0-a,y0+b,color);             //1                
		LCD_DrawPoint(x0-a,y0-b,color);             //2             
		LCD_DrawPoint(x0+b,y0+a,color);             //4               
		LCD_DrawPoint(x0+a,y0-b,color);             //5
		LCD_DrawPoint(x0+a,y0+b,color);             //6 
		LCD_DrawPoint(x0-b,y0+a,color);             //7
		a++;
		if((a*a+b*b)>(r*r))//判断要画的点是否过远
		{
			b--;
		}
	}
}

/******************************************************************************
      函数说明：显示汉字串
      入口数据：x,y显示坐标
                *s 要显示的汉字串
                fc 字的颜色
                bc 字的背景色
                sizey 字号 可选 16 24 32
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChinese(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode)
{
	while(*s!=0)
	{
		if(sizey==12) LCD_ShowChinese12x12(x,y,s,fc,bc,sizey,mode);
		else if(sizey==16) LCD_ShowChinese16x16(x,y,s,fc,bc,sizey,mode);
		else if(sizey==24) LCD_ShowChinese24x24(x,y,s,fc,bc,sizey,mode);
		else if(sizey==32) LCD_ShowChinese32x32(x,y,s,fc,bc,sizey,mode);
		else return;
		s+=2;
		x+=sizey;
	}
}

/******************************************************************************
      函数说明：显示单个12x12汉字
      入口数据：x,y显示坐标
                *s 要显示的汉字
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChinese12x12(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode)
{
	u8 i,j,m=0;
	u16 k;
	u16 HZnum;//汉字数目
	u16 TypefaceNum;//一个字符所占字节大小
	u16 x0=x;
	TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
	                         
	HZnum=sizeof(tfont12)/sizeof(typFNT_GB12);	//统计汉字数目
	for(k=0;k<HZnum;k++) 
	{
		if((tfont12[k].Index[0]==*(s))&&(tfont12[k].Index[1]==*(s+1)))
		{ 	
			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
			for(i=0;i<TypefaceNum;i++)
			{
				for(j=0;j<8;j++)
				{	
					if(!mode)//非叠加方式
					{
						if(tfont12[k].Msk[i]&(0x01<<j))LCD_WR_DATA(fc);
						else LCD_WR_DATA(bc);
						m++;
						if(m%sizey==0)
						{
							m=0;
							break;
						}
					}
					else//叠加方式
					{
						if(tfont12[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,fc);//画一个点
						x++;
						if((x-x0)==sizey)
						{
							x=x0;
							y++;
							break;
						}
					}
				}
			}
		}				  	
		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
	}
} 

/******************************************************************************
      函数说明：显示单个16x16汉字
      入口数据：x,y显示坐标
                *s 要显示的汉字
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChinese16x16(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode)
{
	u8 i,j,m=0;
	u16 k;
	u16 HZnum;//汉字数目
	u16 TypefaceNum;//一个字符所占字节大小
	u16 x0=x;
  TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
	HZnum=sizeof(tfont16)/sizeof(typFNT_GB16);	//统计汉字数目
	for(k=0;k<HZnum;k++) 
	{
		if ((tfont16[k].Index[0]==*(s))&&(tfont16[k].Index[1]==*(s+1)))
		{ 	
			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
			for(i=0;i<TypefaceNum;i++)
			{
				for(j=0;j<8;j++)
				{	
					if(!mode)//非叠加方式
					{
						if(tfont16[k].Msk[i]&(0x01<<j))LCD_WR_DATA(fc);
						else LCD_WR_DATA(bc);
						m++;
						if(m%sizey==0)
						{
							m=0;
							break;
						}
					}
					else//叠加方式
					{
						if(tfont16[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,fc);//画一个点
						x++;
						if((x-x0)==sizey)
						{
							x=x0;
							y++;
							break;
						}
					}
				}
			}
		}				  	
		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
	}
} 


/******************************************************************************
      函数说明：显示单个24x24汉字
      入口数据：x,y显示坐标
                *s 要显示的汉字
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChinese24x24(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode)
{
	u8 i,j,m=0;
	u16 k;
	u16 HZnum;//汉字数目
	u16 TypefaceNum;//一个字符所占字节大小
	u16 x0=x;
	TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
	HZnum=sizeof(tfont24)/sizeof(typFNT_GB24);	//统计汉字数目
	for(k=0;k<HZnum;k++) 
	{
		if ((tfont24[k].Index[0]==*(s))&&(tfont24[k].Index[1]==*(s+1)))
		{ 	
			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
			for(i=0;i<TypefaceNum;i++)
			{
				for(j=0;j<8;j++)
				{	
					if(!mode)//非叠加方式
					{
						if(tfont24[k].Msk[i]&(0x01<<j))LCD_WR_DATA(fc);
						else LCD_WR_DATA(bc);
						m++;
						if(m%sizey==0)
						{
							m=0;
							break;
						}
					}
					else//叠加方式
					{
						if(tfont24[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,fc);//画一个点
						x++;
						if((x-x0)==sizey)
						{
							x=x0;
							y++;
							break;
						}
					}
				}
			}
		}				  	
		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
	}
} 

/******************************************************************************
      函数说明：显示单个32x32汉字
      入口数据：x,y显示坐标
                *s 要显示的汉字
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChinese32x32(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode)
{
	u8 i,j,m=0;
	u16 k;
	u16 HZnum;//汉字数目
	u16 TypefaceNum;//一个字符所占字节大小
	u16 x0=x;
	TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
	HZnum=sizeof(tfont32)/sizeof(typFNT_GB32);	//统计汉字数目
	for(k=0;k<HZnum;k++) 
	{
		if ((tfont32[k].Index[0]==*(s))&&(tfont32[k].Index[1]==*(s+1)))
		{ 	
			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
			for(i=0;i<TypefaceNum;i++)
			{
				for(j=0;j<8;j++)
				{	
					if(!mode)//非叠加方式
					{
						if(tfont32[k].Msk[i]&(0x01<<j))LCD_WR_DATA(fc);
						else LCD_WR_DATA(bc);
						m++;
						if(m%sizey==0)
						{
							m=0;
							break;
						}
					}
					else//叠加方式
					{
						if(tfont32[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,fc);//画一个点
						x++;
						if((x-x0)==sizey)
						{
							x=x0;
							y++;
							break;
						}
					}
				}
			}
		}				  	
		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
	}
}


/******************************************************************************
      函数说明：显示单个字符
      入口数据：x,y显示坐标
                num 要显示的字符
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
/******************************************************************************
      函数说明：显示单个字符
      入口数据：x,y显示坐标
                num 要显示的字符
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChar(u16 x,u16 y,u8 num,u16 fc,u16 bc,u8 sizey,u8 mode)
{
	u8 temp,sizex,t,m=0;
	u16 i,TypefaceNum;//一个字符所占字节大小
	u16 x0=x;
	sizex=sizey/2;
	TypefaceNum=(sizex/8+((sizex%8)?1:0))*sizey;
	num=num-' ';    //得到偏移后的值
	LCD_Address_Set(x,y,x+sizex-1,y+sizey-1);  //设置光标位置 
	for(i=0;i<TypefaceNum;i++)
	{ 
		if(sizey==12)temp=ascii_1206[num][i];		       //调用6x12字体
		else if(sizey==16)temp=ascii_1608[num][i];		 //调用8x16字体
		else if(sizey==24)temp=ascii_2412[num][i];		 //调用12x24字体
		else if(sizey==32)temp=ascii_3216[num][i];		 //调用16x32字体
		else return;
		for(t=0;t<8;t++)
		{
			if(!mode)//非叠加模式
			{
				if(temp&(0x01<<t))LCD_WR_DATA(fc);
				else LCD_WR_DATA(bc);
				m++;
				if(m%sizex==0)
				{
					m=0;
					break;
				}
			}
			else//叠加模式
			{
				if(temp&(0x01<<t))LCD_DrawPoint(x,y,fc);//画一个点
				x++;
				if((x-x0)==sizex)
				{
					x=x0;
					y++;
					break;
				}
			}
		}
	}   	 	  
}


/******************************************************************************
      函数说明：显示字符串
      入口数据：x,y显示坐标
                *p 要显示的字符串
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowString(u16 x,u16 y,const u8 *p,u16 fc,u16 bc,u8 sizey,u8 mode)
{         
	while(*p!='\0')
	{       
		LCD_ShowChar(x,y,*p,fc,bc,sizey,mode);
		x+=sizey/2;
		p++;
	}  
}


/******************************************************************************
      函数说明：显示数字
      入口数据：m底数，n指数
      返回值：  无
******************************************************************************/
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;
	return result;
}


/******************************************************************************
      函数说明：显示整数变量
      入口数据：x,y显示坐标
                num 要显示整数变量
                len 要显示的位数
                fc 字的颜色
                bc 字的背景色
                sizey 字号
      返回值：  无
******************************************************************************/
void LCD_ShowIntNum(u16 x,u16 y,u16 num,u8 len,u16 fc,u16 bc,u8 sizey)
{         	
	u8 t,temp;
	u8 enshow=0;
	u8 sizex=sizey/2;
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+t*sizex,y,' ',fc,bc,sizey,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
} 


/******************************************************************************
      函数说明：显示两位小数变量
      入口数据：x,y显示坐标
                num 要显示小数变量
                len 要显示的位数
                fc 字的颜色
                bc 字的背景色
                sizey 字号
      返回值：  无
******************************************************************************/
void LCD_ShowFloatNum1(u16 x,u16 y,float num,u8 len,u16 fc,u16 bc,u8 sizey)
{         	
	u8 t,temp,sizex;
	u16 num1;
	sizex=sizey/2;
	num1=num*100;
	for(t=0;t<len;t++)
	{
		temp=(num1/mypow(10,len-t-1))%10;
		if(t==(len-2))
		{
			LCD_ShowChar(x+(len-2)*sizex,y,'.',fc,bc,sizey,0);
			t++;
			len+=1;
		}
	 	LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
}


/******************************************************************************
      函数说明：显示图片
      入口数据：x,y起点坐标
                length 图片长度
                width  图片宽度
                pic[]  图片数组    
      返回值：  无
******************************************************************************/
void LCD_ShowPicture(u16 x,u16 y,u16 length,u16 width,const u8 pic[])
{
	u8 picH,picL;
	u16 i,j;
	u32 k=0;
	LCD_Address_Set(x,y,x+length-1,y+width-1);
	for(i=0;i<length;i++)
	{
		for(j=0;j<width;j++)
		{
			picH=pic[k*2];
			picL=pic[k*2+1];
			LCD_WR_DATA(picH<<8|picL);
			k++;
		}
	}			
}


void Set_Dir(u8 dir)
{
	if((dir>>4)%4)
	{
		lcddev.width=480;
		lcddev.height=320;
	}else
	{
		lcddev.width=320;
		lcddev.height=480;
	}
}

void LCD_GPIO_Init(void)
{

		rcu_periph_clock_enable(RCU_GPIOA);
		rcu_periph_clock_enable(RCU_GPIOB);
		rcu_periph_clock_enable(RCU_GPIOC);

                 /* 配置RD */
        gpio_mode_set(PORT_LCD_RD,GPIO_MODE_OUTPUT,GPIO_PUPD_PULLUP,GPIO_LCD_RD);
        gpio_output_options_set(PORT_LCD_RD,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_LCD_RD);
        gpio_bit_write(PORT_LCD_RD, GPIO_LCD_RD, SET);
        
                 /* 配置WR */
        gpio_mode_set(PORT_LCD_WR,GPIO_MODE_OUTPUT,GPIO_PUPD_PULLUP,GPIO_LCD_WR);
        gpio_output_options_set(PORT_LCD_WR,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_LCD_WR);
        gpio_bit_write(PORT_LCD_WR, GPIO_LCD_WR, SET);
        
                 /* 配置DC */
        gpio_mode_set(PORT_LCD_DC,GPIO_MODE_OUTPUT,GPIO_PUPD_PULLUP,GPIO_LCD_DC);
        gpio_output_options_set(PORT_LCD_DC,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_LCD_DC);
        gpio_bit_write(PORT_LCD_DC, GPIO_LCD_DC, SET);

                 /* 配置CS */
        gpio_mode_set(PORT_LCD_CS,GPIO_MODE_OUTPUT,GPIO_PUPD_PULLUP,GPIO_LCD_CS);
        gpio_output_options_set(PORT_LCD_CS,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_LCD_CS);
        gpio_bit_write(PORT_LCD_CS, GPIO_LCD_CS, SET);
        
                 /* 配置RES */
        gpio_mode_set(PORT_LCD_RES,GPIO_MODE_OUTPUT,GPIO_PUPD_PULLUP,GPIO_LCD_RES);
        gpio_output_options_set(PORT_LCD_RES,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_LCD_RES);
        gpio_bit_write(PORT_LCD_RES, GPIO_LCD_RES, SET);

                 /* 配置BLK */
        gpio_mode_set(PORT_LCD_BLK, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_LCD_BLK);
        gpio_output_options_set(PORT_LCD_BLK, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_LCD_BLK);
        gpio_bit_write(PORT_LCD_BLK, GPIO_LCD_BLK, SET);


                 /* 配置DB0 */
        gpio_mode_set(PORT_LCD_DB0, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_LCD_DB0);
        gpio_output_options_set(PORT_LCD_DB0, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_LCD_DB0);
        gpio_bit_write(PORT_LCD_DB0, GPIO_LCD_DB0, SET);

                 /* 配置DB1 */
        gpio_mode_set(PORT_LCD_DB1, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_LCD_DB1);
        gpio_output_options_set(PORT_LCD_DB1, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_LCD_DB1);
        gpio_bit_write(PORT_LCD_DB1, GPIO_LCD_DB1, SET);
        
                 /* 配置DB2 */
        gpio_mode_set(PORT_LCD_DB2, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_LCD_DB2);
        gpio_output_options_set(PORT_LCD_DB2, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_LCD_DB2);
        gpio_bit_write(PORT_LCD_DB2, GPIO_LCD_DB2, SET);
        
                 /* 配置DB3 */
        gpio_mode_set(PORT_LCD_DB3, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_LCD_DB3);
        gpio_output_options_set(PORT_LCD_DB3, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_LCD_DB3);
        gpio_bit_write(PORT_LCD_DB3, GPIO_LCD_DB3, SET);

                 /* 配置DB4 */
        gpio_mode_set(PORT_LCD_DB4, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_LCD_DB4);
        gpio_output_options_set(PORT_LCD_DB4, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_LCD_DB4);
        gpio_bit_write(PORT_LCD_DB4, GPIO_LCD_DB4, SET);
        
                 /* 配置DB5 */
        gpio_mode_set(PORT_LCD_DB5, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_LCD_DB5);
        gpio_output_options_set(PORT_LCD_DB5, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_LCD_DB5);
        gpio_bit_write(PORT_LCD_DB5, GPIO_LCD_DB5, SET);
        
                 /* 配置DB6 */
        gpio_mode_set(PORT_LCD_DB6, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_LCD_DB6);
        gpio_output_options_set(PORT_LCD_DB6, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_LCD_DB6);
        gpio_bit_write(PORT_LCD_DB6, GPIO_LCD_DB6, SET);
        
                 /* 配置DB7 */
        gpio_mode_set(PORT_LCD_DB7, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_LCD_DB7);
        gpio_output_options_set(PORT_LCD_DB7, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_LCD_DB7);
        gpio_bit_write(PORT_LCD_DB7, GPIO_LCD_DB7, SET);

		                 /* 配置DB8 */
        gpio_mode_set(PORT_LCD_DB8, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_LCD_DB8);
        gpio_output_options_set(PORT_LCD_DB8, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_LCD_DB8);
        gpio_bit_write(PORT_LCD_DB8, GPIO_LCD_DB8, SET);

                 /* 配置DB9 */
        gpio_mode_set(PORT_LCD_DB9, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_LCD_DB9);
        gpio_output_options_set(PORT_LCD_DB9, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_LCD_DB9);
        gpio_bit_write(PORT_LCD_DB9, GPIO_LCD_DB9, SET);

                 /* 配置DB10 */
        gpio_mode_set(PORT_LCD_DB10, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_LCD_DB10);
        gpio_output_options_set(PORT_LCD_DB10, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_LCD_DB10);
        gpio_bit_write(PORT_LCD_DB10, GPIO_LCD_DB10, SET);

                 /* 配置DB11 */
        gpio_mode_set(PORT_LCD_DB11, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_LCD_DB11);
        gpio_output_options_set(PORT_LCD_DB11, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_LCD_DB11);
        gpio_bit_write(PORT_LCD_DB11, GPIO_LCD_DB11, SET);

                 /* 配置DB12 */
        gpio_mode_set(PORT_LCD_DB12, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_LCD_DB12);
        gpio_output_options_set(PORT_LCD_DB12, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_LCD_DB12);
        gpio_bit_write(PORT_LCD_DB12, GPIO_LCD_DB12, SET);

                 /* 配置DB13 */
        gpio_mode_set(PORT_LCD_DB13, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_LCD_DB13);
        gpio_output_options_set(PORT_LCD_DB13, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_LCD_DB13);
        gpio_bit_write(PORT_LCD_DB13, GPIO_LCD_DB13, SET);

                 /* 配置DB14 */
        gpio_mode_set(PORT_LCD_DB14, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_LCD_DB14);
        gpio_output_options_set(PORT_LCD_DB14, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_LCD_DB14);
        gpio_bit_write(PORT_LCD_DB14, GPIO_LCD_DB14, SET);

                 /* 配置DB15 */
        gpio_mode_set(PORT_LCD_DB15, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_LCD_DB15);
        gpio_output_options_set(PORT_LCD_DB15, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_LCD_DB15);
        gpio_bit_write(PORT_LCD_DB15, GPIO_LCD_DB15, SET);

}


//初始化lcd
void LCD_Init(void)
{
	//引脚初始化
	LCD_GPIO_Init();

//	GPIO_InitTypeDef GPIO_InitStructure;

// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE); 
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure); //GPIOA	
//	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);


//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOB,GPIO_Pin_All);
//	
	LCD_RST_CLR;
	delay_ms(200); 					// delay 50 ms 
	LCD_RST_SET;
	
	delay_ms(50); 					// delay 50 ms 
	Set_Dir(DFT_SCAN_DIR);
	LCD_WR_REG(0xE0); 
	LCD_WR_DATA(0x00); 
	LCD_WR_DATA(0x07); 
	LCD_WR_DATA(0x0f); 
	LCD_WR_DATA(0x0D); 
	LCD_WR_DATA(0x1B); 
	LCD_WR_DATA(0x0A); 
	LCD_WR_DATA(0x3c); 
	LCD_WR_DATA(0x78); 
	LCD_WR_DATA(0x4A); 
	LCD_WR_DATA(0x07); 
	LCD_WR_DATA(0x0E); 
	LCD_WR_DATA(0x09); 
	LCD_WR_DATA(0x1B); 
	LCD_WR_DATA(0x1e); 
	LCD_WR_DATA(0x0f);  
	
	LCD_WR_REG(0xE1); 
	LCD_WR_DATA(0x00); 
	LCD_WR_DATA(0x22); 
	LCD_WR_DATA(0x24); 
	LCD_WR_DATA(0x06); 
	LCD_WR_DATA(0x12); 
	LCD_WR_DATA(0x07); 
	LCD_WR_DATA(0x36); 
	LCD_WR_DATA(0x47); 
	LCD_WR_DATA(0x47); 
	LCD_WR_DATA(0x06); 
	LCD_WR_DATA(0x0a); 
	LCD_WR_DATA(0x07); 
	LCD_WR_DATA(0x30); 
	LCD_WR_DATA(0x37); 
	LCD_WR_DATA(0x0f); 
	
	LCD_WR_REG(0xC0); 
	LCD_WR_DATA(0x10); 
	LCD_WR_DATA(0x10); 
	
	LCD_WR_REG(0xC1); 
	LCD_WR_DATA(0x41); 
	
	LCD_WR_REG(0xC5); 
	LCD_WR_DATA(0x00); 
	LCD_WR_DATA(0x22); 
	LCD_WR_DATA(0x80); 
	
	LCD_WR_REG(0x36);    // Memory Access Control 
	if(DFT_SCAN_DIR==L2R_U2D)LCD_WR_DATA(0x48);
	else if(DFT_SCAN_DIR==R2L_D2U)LCD_WR_DATA(0x88);
	else if(DFT_SCAN_DIR==U2D_R2L)LCD_WR_DATA(0x28);
	else LCD_WR_DATA(0xE8);

	
	LCD_WR_REG(0x3A); //Interface Mode Control，
	LCD_WR_DATA(0x55);
		
	LCD_WR_REG(0XB0);  //Interface Mode Control  
	LCD_WR_DATA(0x00); 
	LCD_WR_REG(0xB1);   //Frame rate 70HZ  
	LCD_WR_DATA(0xB0); 
	LCD_WR_DATA(0x11); 
	LCD_WR_REG(0xB4); 
	LCD_WR_DATA(0x02);   
	LCD_WR_REG(0xB6); //RGB/MCU Interface Control
	LCD_WR_DATA(0x02); 
	LCD_WR_DATA(0x02); 
	
	LCD_WR_REG(0xB7); 
	LCD_WR_DATA(0xC6); 
	LCD_WR_REG(0xE9); 
	LCD_WR_DATA(0x00);
	
	LCD_WR_REG(0XF7);    
	LCD_WR_DATA(0xA9); 
	LCD_WR_DATA(0x51); 
	LCD_WR_DATA(0x2C); 
	LCD_WR_DATA(0x82);
	
	LCD_WR_REG(0x11); 
//	delay_ms(120); 
	LCD_WR_REG(0x29);
//	LCD_LED=1;
//usart_send_string("run this 1");
    gpio_bit_write(PORT_LCD_RES, GPIO_LCD_RES, SET);
//	usart_send_string("run this 2");
}






#ifndef __GUI_H__
#define __GUI_H__
#include "gd32e23x.h"
#include "systick.h"

#ifndef u8
#define u8 uint8_t
#endif

#ifndef u16
#define u16 uint16_t
#endif

#ifndef u32
#define u32 uint32_t
#endif


void GUI_DrawPoint(u16 x,u16 y,u16 color);
void _draw_circle_8(int xc, int yc, int x, int y, u16 c);
void gui_circle(int xc, int yc,u16 c,int r, int fill);
void Show_Str(u16 x, u16 y,u8 *str,u16 fc, u16 bc,u8 sizey,u8 mode);
void Gui_StrCenter(u16 x, u16 y,u8 *str,u16 fc,u16 bc,u8 sizey,u8 mode);
#endif


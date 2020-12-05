#ifndef __LIB_FB_H
#define __LIB_FB_H

#include<sys/types.h>
#include<sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <stdlib.h>

typedef unsigned           char uint8_t;
typedef unsigned short     int uint16_t;                                     
typedef unsigned           int uint32_t;
typedef uint32_t  u32;
typedef uint16_t u16; 
typedef uint8_t u8;

void LCD_DrawPoint(unsigned int x, unsigned int y,struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *pfb);
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *pfb);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *pfb);
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r,struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *fpb);
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p,struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *fbp);
void LCD_DrawPixel(unsigned int x, unsigned int y,unsigned char *RGB,struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *pfb);

#endif

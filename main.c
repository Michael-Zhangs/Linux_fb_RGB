#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>

#include "libfb.h"

extern unsigned char white[4];
extern unsigned char black[4];
unsigned long int screensize;
int main()
{
        int fbfd = 0;
        struct fb_var_screeninfo vinfo;
        struct fb_fix_screeninfo finfo;
        char *fbp = 0;
        int x = 0, y = 0;
        long int location = 0;
       int sav=0;
        /* open device*/
        fbfd = open("/dev/fb0", O_RDWR);
        if (!fbfd) {
                printf("Error: cannot open framebuffer device.\n");
                exit(1);
        }
        printf("The framebuffer device was opened successfully.\n");

        /* Get fixed screen information */
        if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
                printf("Error reading fixed information.\n");
                exit(2);
        }

        /* Get variable screen information */
        if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
                printf("Error reading variable information.\n");
                exit(3);
        }

        /* show these information*/
        printf("vinfo.xres_virtual : %d , vinfo.yres_virtual : %d\n",vinfo.xres_virtual, vinfo.yres_virtual);
        printf("vinfo.xres=%d\n",vinfo.xres);
        printf("vinfo.yres=%d\n",vinfo.yres);
        printf("vinfo.bits_per_bits=%d\n",vinfo.bits_per_pixel);
        printf("vinfo.xoffset=%d\n",vinfo.xoffset);
        printf("vinfo.yoffset=%d\n",vinfo.yoffset);
        printf("finfo.line_length=%d\n",finfo.line_length);

        /* Figure out the size of the screen in bytes */
        screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

        printf("screensize : %ld ,  : %d\n",screensize, finfo.smem_len);

        /* Map the device to memory */
        fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,
                fbfd, 0);
        if ((int)fbp == -1)
        {
            printf("Error: failed to map framebuffer device to memory.\n"); exit(4);
        }
        printf("The framebuffer device was mapped to memory successfully.\n");

        memset(fbp,0,screensize);
            /* Where we are going to put the pixel */

        unsigned int  index;
        const unsigned char *pLog = NULL;
        pLog=black;
        for(x=0;x<vinfo.xres;x++)
            for(y=0;y<vinfo.yres;y++)
            {
                location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                 (y+vinfo.yoffset) * finfo.line_length;

                *(fbp + location) = pLog[index]; /*  blue */
                *(fbp + location + 1) = pLog[index+1];
                *(fbp + location + 2) = pLog[index+2]; /*  blue */
                *(fbp + location + 3) = pLog[index+3];
            }
//        LCD_DrawPoint(10, 10, finfo, vinfo, fbp);
//        LCD_DrawPoint(20, 20, finfo, vinfo, fbp);
        FILE *obj;
        obj = fopen("image.bin","r");
        unsigned char rgbtmp[4] = {0xff,0xff,0xff,0x00};
        for(int y=0;y<299;y++)
        {
                for(int x=0;x<450;x++)
                {
                        rgbtmp[0]=fgetc(obj);
                        rgbtmp[1]=fgetc(obj);
                        rgbtmp[2]=fgetc(obj);
                        LCD_DrawPixel(x,y,&rgbtmp,finfo,vinfo,fbp);
                }
        }
        //LCD_ShowChar(20, 20, 'y',32,finfo, vinfo, fbp);
        //LCD_ShowString(0,0,200,32,32,"asdfhlkjsfadkhjsdfljkljkh",finfo, vinfo,fbp);
        //LCD_Draw_Circle(400,400,200,finfo, vinfo, fbp);
        //LCD_DrawLine(60, 60, 90,90,finfo, vinfo, fbp);
        munmap(fbp, screensize);  /* release the memory */
        close(fbfd);

    return 0;
}

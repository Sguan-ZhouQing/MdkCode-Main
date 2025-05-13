/*
 * @Author: ???Sguan
 * @Date: 2025-04-27 22:11:04
 * @LastEditors: ???Sguan|3464647102@qq.com
 * @LastEditTime: 2025-04-29 21:50:31
 * @FilePath: \test_SPIscreen\GUI\test.c
 * @Description: [???]test????
 * 
 * Copyright (c) 2025 by $JUST, All Rights Reserved. 
 */
#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include "delay.h"
#include "GUI.h"
#include "test.h"
#include "touch.h"
#include "pic.h"
#include "ft6336.h"

uint16_t ColorTab[5]={RED,GREEN,BLUE,YELLOW,BRED};
uint16_t ColornTab[8]={RED,MAGENTA,GREEN,DARKBLUE,BLUE,BLACK,LIGHTGREEN};
const uint16_t POINT_COLOR_TBL = RED;
 
void DrawTestPage(uint8_t *str)
{
	LCD_Clear(WHITE);
	LCD_Fill(0,0,lcddev.width,20,BLUE);
	LCD_Fill(0,lcddev.height-20,lcddev.width,lcddev.height,BLUE);
	POINT_COLOR=WHITE;
	Gui_StrCenter(0,2,WHITE,BLUE,str,16,1);
}

void main_test(void)
{
	DrawTestPage("È«¶¯µç×Ó×ÛºÏ²âÊÔ³ÌÐò");	
	Gui_StrCenter(0,30,RED,BLUE,"È«¶¯µç×Ó",16,1);
	Gui_StrCenter(0,60,RED,BLUE,"×ÛºÏ²âÊÔ³ÌÐò",16,1);
	Gui_StrCenter(0,90,BRED,BLUE,"3.5\" IPS ST7796 320X480",16,1);
	Gui_StrCenter(0,120,BLUE,BLUE,"xiaoFeng@QDtech 2022-12-20",16,1);
	delay_ms(1500);		
	delay_ms(1500);
}

void Test_Color(void)
{
	LCD_Fill(0,0,lcddev.width,lcddev.height,WHITE);
	Show_Str(20,30,BLACK,YELLOW,"WHITE",16,1);delay_ms(800);
	LCD_Fill(0,0,lcddev.width,lcddev.height,BLACK);
	Show_Str(20,30,WHITE,YELLOW,"BLACK",16,1);delay_ms(800);
	LCD_Fill(0,0,lcddev.width,lcddev.height,RED);
	Show_Str(20,30,BLUE,YELLOW,"RED ",16,1);delay_ms(800);
	LCD_Fill(0,0,lcddev.width,lcddev.height,GREEN);
	Show_Str(20,30,BLUE,YELLOW,"GREEN ",16,1);delay_ms(800);
	LCD_Fill(0,0,lcddev.width,lcddev.height,BLUE);
	Show_Str(20,30,RED,YELLOW,"BLUE ",16,1);delay_ms(800);
	LCD_Fill(0,0,lcddev.width,lcddev.height,GRAY);
	Show_Str(20,30,MAGENTA,YELLOW,"GRAY",16,1);delay_ms(800);
}

void Test_FillRec(void)
{
	uint8_t i=0;
	DrawTestPage("²âÊÔ3:GUI¾ØÐÎÌî³ä²âÊÔ");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
	for (i=0; i<5; i++) 
	{
		POINT_COLOR=ColorTab[i];
		LCD_DrawRectangle(lcddev.width/2-80+(i*15),lcddev.height/2-80+(i*15),lcddev.width/2-80+(i*15)+60,lcddev.height/2-80+(i*15)+60); 
	}
	delay_ms(1500);	
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE); 
	for (i=0; i<5; i++) 
	{
		POINT_COLOR=ColorTab[i];
		LCD_DrawFillRectangle(lcddev.width/2-80+(i*15),lcddev.height/2-80+(i*15),lcddev.width/2-80+(i*15)+60,lcddev.height/2-80+(i*15)+60); 
	}
	delay_ms(1500);
}

void Test_Circle(void)
{
	uint8_t i=0;
	DrawTestPage("²âÊÔ4:GUI»­Ô²Ìî³ä²âÊÔ");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
	for (i=0; i<5; i++)  
		gui_circle(lcddev.width/2-80+(i*25),lcddev.height/2-50+(i*25),ColorTab[i],30,0);
	delay_ms(1500);	
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE); 
	for (i=0; i<5; i++) 
	  	gui_circle(lcddev.width/2-80+(i*25),lcddev.height/2-50+(i*25),ColorTab[i],30,1);
	delay_ms(1500);
}

void English_Font_test(void)
{
	DrawTestPage("²âÊÔ6:Ó¢ÎÄÏÔÊ¾²âÊÔ");
	Show_Str(10,30,BLUE,YELLOW,"6X12:abcdefghijklmnopqrstuvwxyz0123456789",12,0);
	Show_Str(10,45,BLUE,YELLOW,"6X12:ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",12,1);
	Show_Str(10,60,BLUE,YELLOW,"6X12:~!@#$%^&*()_+{}:<>?/|-+.",12,0);
	Show_Str(10,80,BLUE,YELLOW,"8X16:abcdefghijklmnopqrstuvwxyz0123456789",16,0);
	Show_Str(10,100,BLUE,YELLOW,"8X16:ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",16,1);
	Show_Str(10,120,BLUE,YELLOW,"8X16:~!@#$%^&*()_+{}:<>?/|-+.",16,0); 
	delay_ms(1200);
}

void Test_Triangle(void)
{
	uint8_t i=0;
	DrawTestPage("²âÊÔ5:GUI TriangleÌî³ä²âÊÔ");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
	for(i=0;i<5;i++)
	{
		POINT_COLOR=ColorTab[i];
		Draw_Triangel(lcddev.width/2-80+(i*20),lcddev.height/2-20+(i*15),lcddev.width/2-50-1+(i*20),lcddev.height/2-20-52-1+(i*15),lcddev.width/2-20-1+(i*20),lcddev.height/2-20+(i*15));
	}
	delay_ms(1500);	
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE); 
	for(i=0;i<5;i++)
	{
		POINT_COLOR=ColorTab[i];
		Fill_Triangel(lcddev.width/2-80+(i*20),lcddev.height/2-20+(i*15),lcddev.width/2-50-1+(i*20),lcddev.height/2-20-52-1+(i*15),lcddev.width/2-20-1+(i*20),lcddev.height/2-20+(i*15));
	}
	delay_ms(1500);
}

void Chinese_Font_test(void)
{	
	DrawTestPage("²âÊÔ7:ÖÐÎÄÏÔÊ¾²âÊÔ");
	Show_Str(10,30,BLUE,YELLOW,"16X16:È«¶¯µç×Ó¼¼ÊõÓÐÏÞ¹«Ë¾»¶Ó­Äú",16,0);
	Show_Str(10,50,BLUE,YELLOW,"16X16:WelcomeÈ«¶¯µç×Ó",16,0);
	Show_Str(10,70,BLUE,YELLOW,"24X24:ÉîÛÚÊÐÖÐÎÄ²âÊÔ",24,1);
	Show_Str(10,100,BLUE,YELLOW,"32X32:×ÖÌå²âÊÔ",32,1);
	delay_ms(1200);
}

void Pic_test(void)
{
	DrawTestPage("²âÊÔ8:Í¼Æ¬ÏÔÊ¾²âÊÔ");
	
	Gui_Drawbmp16(30,30,gImage_qq);
	Show_Str(30+12,75,BLUE,YELLOW,"QQ",16,1);
	Gui_Drawbmp16(90,30,gImage_qq);
	Show_Str(90+12,75,BLUE,YELLOW,"QQ",16,1);
	Gui_Drawbmp16(150,30,gImage_qq);
	Show_Str(150+12,75,BLUE,YELLOW,"QQ",16,1);
	delay_ms(1200);
}

void Rotate_Test(void)
{
	uint8_t i=0;
	uint8_t *Direction[4]={"Rotation:0","Rotation:90","Rotation:180","Rotation:270"};
	
	for(i=0;i<4;i++)
	{
	LCD_direction(i);
	DrawTestPage("²âÊÔ10:ÆÁÄ»Ðý×ª²âÊÔ");
	Show_Str(20,30,BLUE,YELLOW,Direction[i],16,1);
	Gui_Drawbmp16(30,50,gImage_qq);
	delay_ms(1000);delay_ms(1000);
	}
	LCD_direction(USE_HORIZONTAL);
}

void Touch_Pen_Test(void)
{
 	uint16_t lastpos[2];		
	DrawTestPage("²âÊÔ12:´¥ÃþPEN²âÊÔ");
	LCD_ShowString(lcddev.width-32,2,16,"RST",1);
	POINT_COLOR=RED;
	while(1)
	{
		tp_dev.scan();
		if((tp_dev.sta)&(1<<0))
		{
			if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
			{
				if(lastpos[0]==0XFFFF)
				{
					lastpos[0] = tp_dev.x[0];
					lastpos[1] = tp_dev.y[0];
				}
				if(tp_dev.x[0]>(lcddev.width-32)&&tp_dev.y[0]<18)
				{
					tp_dev.x[0]=0xFFFF;
					tp_dev.x[0]=0xFFFF;
					DrawTestPage("²âÊÔ12:´¥ÃþPEN²âÊÔ");
					LCD_ShowString(lcddev.width-32,2,16,"RST",1);
					POINT_COLOR=RED;
				}
				else
				{
					LCD_DrawLine2(lastpos[0],lastpos[1],tp_dev.x[0],tp_dev.y[0],2,POINT_COLOR_TBL);
				}
				lastpos[0]=tp_dev.x[0];
				lastpos[1]=tp_dev.y[0];
			}
		}else lastpos[0]=0XFFFF;
	} 
}

void Touch_Button_Test(void)
{  
	DrawTestPage("²âÊÔ11:´¥Ãþ°´¼ü²âÊÔ");
	POINT_COLOR = BLACK;
	LCD_DrawRectangle(lcddev.width/2-50, 40, lcddev.width/2+50, 90);
	POINT_COLOR = RED;
	LCD_DrawFillRectangle(lcddev.width/2-49, 41, lcddev.width/2-1, 89);
	POINT_COLOR = BLUE;
	LCD_DrawFillRectangle(lcddev.width/2, 41, lcddev.width/2+49, 89);
	POINT_COLOR = WHITE;
	LCD_ShowString(lcddev.width/2-32,57,16,"ON",1);	
	POINT_COLOR = GRAY;
	LCD_FillRoundRectangle(lcddev.width/2-110, 150, lcddev.width/2+110, 169,10);
	POINT_COLOR = BRED;
	LCD_FillRoundRectangle(lcddev.width/2-110, 150, lcddev.width/2+10, 169,10);
	gui_circle(lcddev.width/2, 160,DARKBLUE,10, 1);
	POINT_COLOR = BLACK;
	LCD_ShowString(lcddev.width/2-125,152,16,"0",1);
	LCD_ShowString(lcddev.width/2+115,152,16,"100",1);
	POINT_COLOR = RED;
	LCD_ShowNum(lcddev.width/2-12,125,50,3,16);
	POINT_COLOR = BLACK;
	LCD_DrawRoundRectangle(lcddev.width/2-30, 220, lcddev.width/2+30, 250,8); 
	POINT_COLOR = LGRAYBLUE;
	LCD_FillRoundRectangle(lcddev.width/2-29, 221, lcddev.width/2+29, 248,7);
	POINT_COLOR = MAGENTA;
	LCD_ShowString(lcddev.width/2-15,227,16,"EXIT",1);
	Show_Str(lcddev.width/2-47,195,RED,WHITE,"°´EXIT¼üÍË³ö",16,1);
	while(1)
	{
		tp_dev.scan();
		if((tp_dev.sta)&(1<<0))
		{
			if((tp_dev.y[0]>40)&&(tp_dev.y[0]<90))
			{
				if((tp_dev.x[0]>(lcddev.width/2-50))&&(tp_dev.x[0]<(lcddev.width/2-1)))
				{
						POINT_COLOR = RED;
						LCD_DrawFillRectangle(lcddev.width/2-49, 41, lcddev.width/2-1, 89);
						POINT_COLOR = BLUE;
						LCD_DrawFillRectangle(lcddev.width/2, 41, lcddev.width/2+49, 89);
						POINT_COLOR = WHITE;
						LCD_ShowString(lcddev.width/2-32,57,16,"ON",1);	
				}
				if((tp_dev.x[0]>(lcddev.width/2))&&(tp_dev.x[0]<(lcddev.width/2+50)))
				{
						POINT_COLOR = BLUE;
						LCD_DrawFillRectangle(lcddev.width/2-49, 41, lcddev.width/2-1, 89);
						POINT_COLOR = RED;
						LCD_DrawFillRectangle(lcddev.width/2, 41, lcddev.width/2+49, 89);
						POINT_COLOR = WHITE;
						LCD_ShowString(lcddev.width/2+13,57,16,"OFF",1);	
				}
			}	
			if((tp_dev.x[0]>=(lcddev.width/2-100))&&(tp_dev.x[0]<=(lcddev.width/2+100))&&(tp_dev.y[0]>150)&&(tp_dev.y[0]<169))
			{
					POINT_COLOR = GRAY;
					LCD_FillRoundRectangle(tp_dev.x[0]-10, 150, lcddev.width/2+110, 169,10);
					POINT_COLOR = BRED;
					LCD_FillRoundRectangle(lcddev.width/2-110, 150, tp_dev.x[0]+10, 169,10);
					gui_circle(tp_dev.x[0], 160,DARKBLUE,10, 1);
					POINT_COLOR = RED;
					LCD_ShowNum(lcddev.width/2-12,125,(tp_dev.x[0]-(lcddev.width/2-100))/2,3,16);
			}
			if((tp_dev.x[0]>=(lcddev.width/2-30))&&(tp_dev.x[0]<=(lcddev.width/2+30))&&(tp_dev.y[0]>220)&&(tp_dev.y[0]<250))
			{
				POINT_COLOR = WHITE;
				LCD_DrawRoundRectangle(lcddev.width/2-30, 220, lcddev.width/2+30, 250,8); 
				POINT_COLOR = LBBLUE;
				LCD_FillRoundRectangle(lcddev.width/2-29, 221, lcddev.width/2+29, 248,7);
				POINT_COLOR = LIGHTGREEN;
				LCD_ShowString(lcddev.width/2-15,227,16,"EXIT",1);
				tp_dev.x[0]=0xFFFF;
				break;
			}
		}
	} 
}

void Touch_Test(void)
{
	if(tp_dev.init())
	{
		return;
	}
	Touch_Button_Test();
	Touch_Pen_Test();
}

void Test_Read(void)
{
	uint16_t lcd_id,color;
	uint8_t buf[10] = {0},i;
	uint8_t cbuf[35] = {0};
	DrawTestPage("²âÊÔ2:¶ÁIDºÍÑÕÉ«Öµ²âÊÔ");
	lcd_id = LCD_Read_ID();
	sprintf((char *)buf,"ID:0x%x",lcd_id);
	Show_Str(50,25,BLUE,YELLOW,buf,16,1);
	for (i=0; i<7; i++) 
	{
		POINT_COLOR=ColornTab[i];
		LCD_DrawFillRectangle(20-10,55+i*25-10,20+10,55+i*25+10);
		color = LCD_ReadPoint(20,55+i*25);
		if(POINT_COLOR==color)
		{
			strcpy((char*)buf, "OK");
		}
		else
		{
			strcpy((char*)buf, "ERROR");
		}
		sprintf((char *)cbuf,"read color:0x%04X  %s",color, buf);
		Show_Str(20+20,55+i*25-8,POINT_COLOR,YELLOW,cbuf,16,1);
	}
	delay_ms(1500);
}

void Test_Dynamic_Num(void)
{
		uint8_t i;
	DrawTestPage("²âÊÔ9:¶¯Ì¬Êý×ÖÏÔÊ¾");
	POINT_COLOR=BLUE;
	srand(123456);
	LCD_ShowString(15,50,16, " HCHO:           ug/m3",1);
	LCD_ShowString(15,70,16, "  CO2:           ppm",1);
	LCD_ShowString(15,90,16, " TVOC:           ug/m3",1);
	LCD_ShowString(15,110,16,"PM2.5:           ug/m3",1);
	LCD_ShowString(15,130,16," PM10:           ug/m3",1);
	LCD_ShowString(15,150,16,"  TEP:           C",1);
	LCD_ShowString(15,170,16,"  HUM:           %",1);
	POINT_COLOR=RED;
	for(i=0;i<15;i++)
	{
		LCD_ShowNum(100,50,rand()%10000,5,16);
		LCD_ShowNum(100,70,rand()%10000,5,16);
		LCD_ShowNum(100,90,rand()%10000,5,16);
		LCD_ShowNum(100,110,rand()%10000,5,16);
		LCD_ShowNum(100,130,rand()%10000,5,16);
		LCD_ShowNum(100,150,rand()%50,5,16);
		LCD_ShowNum(100,170,rand()%100,5,16);
		delay_ms(500);
	}
}

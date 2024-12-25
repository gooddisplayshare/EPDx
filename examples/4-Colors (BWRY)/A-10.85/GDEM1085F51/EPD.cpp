#include "EPD_SPI3.h" //E-paper 3-wire SPI 
#include "EPD.h"

//Delay Functions
void delay_xms(unsigned int xms)
{
   delay(xms);
}

////////////////////////////////////E-paper demo//////////////////////////////////////////////////////////
void lcd_chkstatus(void)
{
  while(isEPD_W21_BUSY==0);
                   
}

void EPD_init(void)
{
	delay_xms(100);//At least 100ms delay 	
	EPD_W21_RST_0;		// Module reset
	delay_xms(50);//At least 50ms delay 
	EPD_W21_RST_1;
	delay_xms(50);//At least 50ms delay 
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
		
	EPD_W21_WriteCMD(0x4D);
  EPD_W21_WriteDATA(0x78);	
	
	EPD_W21_WriteCMD(0x00);	//0x00
	EPD_W21_WriteDATA(0x2F);	
	EPD_W21_WriteDATA(0x29);	

	EPD_W21_WriteCMD(0x06);//47uH
  EPD_W21_WriteDATA(0x0d);
  EPD_W21_WriteDATA(0x12);
  EPD_W21_WriteDATA(0x30);
	EPD_W21_WriteDATA(0x20);
  EPD_W21_WriteDATA(0x19);
  EPD_W21_WriteDATA(0x3D);
	EPD_W21_WriteDATA(0x0C);
	
	EPD_W21_WriteCMD(0x06);	//0x06
  EPD_W21_WriteDATA(0x0d);
  EPD_W21_WriteDATA(0x12);
  EPD_W21_WriteDATA(0x30);
	EPD_W21_WriteDATA(0x20);
  EPD_W21_WriteDATA(0x19);
  EPD_W21_WriteDATA(0x3D);
	EPD_W21_WriteDATA(0x0C);
	
	EPD_W21_WriteCMD(0x50);	//0x50
	EPD_W21_WriteDATA(0x37);	

	EPD_W21_WriteCMD(0x61);//0x61	
	EPD_W21_WriteDATA(Source_BITS/256);	
	EPD_W21_WriteDATA(Source_BITS%256);	
	EPD_W21_WriteDATA(Gate_BITS/256);	
	EPD_W21_WriteDATA(Gate_BITS%256);	

	EPD_W21_WriteCMD(0x65);	//0x65
	EPD_W21_WriteDATA(0x00);	
	EPD_W21_WriteDATA(0x00);	
	EPD_W21_WriteDATA(0x00);	
	EPD_W21_WriteDATA(0x00);	

	EPD_W21_WriteCMD(0xE0);
  EPD_W21_WriteDATA(0x01);

  EPD_W21_WriteCMD(0xE3);
  EPD_W21_WriteDATA(0x08);  
	
  EPD_W21_WriteCMD(0xE5);
  EPD_W21_WriteDATA(0x08); 
	
  EPD_W21_WriteCMD(0xE9);
  EPD_W21_WriteDATA(0x01);   

  EPD_W21_WriteCMD(0x04); //Power on
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
	
}
	
void EPD_sleep(void)
{  	
	EPD_W21_WriteCMD(0X02);  	//power off
	EPD_W21_WriteDATA(0x00);
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal

	EPD_W21_WriteCMD(0X07);  	//deep sleep
	EPD_W21_WriteDATA(0xA5);
}
void EPD_update(void)
{   
  EPD_W21_WriteCMD(0x12); //Display Update Control
	EPD_W21_WriteDATA(0x00);
  lcd_chkstatus();   
}

void Display_All_Black(void)
{
  unsigned long i; 

  EPD_W21_WriteCMD(0x10);
	for(i=0;i<ALLSCREEN_BYTES;i++)
	{
		EPD_W21_WriteDATA(0x00);
	}   
  EPD_update();	
	
}

void Display_All_White(void)
{
  unsigned long i;
 
  EPD_W21_WriteCMD(0x10);
	for(i=0;i<ALLSCREEN_BYTES;i++)
	{
		EPD_W21_WriteDATA(0x55);
	}
  	
	 EPD_update();	
}

void Display_All_Yellow(void)
{
  unsigned long i;
 
  EPD_W21_WriteCMD(0x10);  
	for(i=0;i<ALLSCREEN_BYTES;i++)
	{
		EPD_W21_WriteDATA(0xaa);
	}
	 EPD_update();	
}


void Display_All_Red(void)
{
  unsigned long i;
 
  EPD_W21_WriteCMD(0x10);
	for(i=0;i<ALLSCREEN_BYTES;i++)
	{
		EPD_W21_WriteDATA(0xff);
	} 	
	 EPD_update();	
}



unsigned char Color_get(unsigned char color)
{
	unsigned datas;
	switch(color)
	{
		case 0x00:
			datas=white;	
      break;		
		case 0x01:
			datas=yellow;
		  break;
		case 0x02:
			datas=red;
		  break;		
		case 0x03:
			datas=black;
		  break;			
    default:
      break;			
	}
	 return datas;
}

void PIC_display(const unsigned char* picData)
{
  unsigned int i,j; 
	unsigned char temp1;
	unsigned char data_H1,data_H2,data_L1,data_L2,data;
		//Master
		EPD_W21_WriteCMD1(0x10);	       //Transfer old data
		for(j=0;j<480;j++)
		for(i=0;i<170;i++){	  		
			temp1=picData[340*j+i];
			data_H1=Color_get(temp1>>6&0x03)<<6;			
			data_H2=Color_get(temp1>>4&0x03)<<4;
			data_L1=Color_get(temp1>>2&0x03)<<2;
			data_L2=Color_get(temp1&0x03);			
			data=data_H1|data_H2|data_L1|data_L2;			
      EPD_W21_WriteDATA1(data);			
		} 				
		//Slave
		EPD_W21_WriteCMD2(0x10);	       //Transfer old data
		for(j=0;j<480;j++)
		for(i=170;i<340;i++){	  
			temp1=picData[340*j+i];
			data_H1=Color_get(temp1>>6&0x03)<<6;			
			data_H2=Color_get(temp1>>4&0x03)<<4;
			data_L1=Color_get(temp1>>2&0x03)<<2;
			data_L2=Color_get(temp1&0x03);			
			data=data_H1|data_H2|data_L1|data_L2;			
      EPD_W21_WriteDATA2(data);		
		}			
	 //update
    EPD_update();	
}



/***********************************************************
            end file
***********************************************************/

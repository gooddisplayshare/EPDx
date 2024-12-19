#include<ESP32epdx.h> //E-paper SPI etc
//EPD
#include"EPD.h"  //E-paper driver
#include"IMAGE.h" //E-paper image data

unsigned char BlackImage[EPD_ARRAY];//Define canvas space

void setup() {
 /* ESP32-WROOM-32D (Using hardware SPI)
  BUSY——GPIO13  RES——GPIO12  DC——GPIO14  CS——GPIO27  SCK—GPIO18  SDIN—GPIO23  */
   pinMode(13, INPUT);  //BUSY
   pinMode(12, OUTPUT); //RES 
   pinMode(14, OUTPUT); //DC   
   pinMode(27, OUTPUT); //CS   
   //SPI
   SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0)); 
   SPI.begin ();  
}

//Tips//
/*
1.Flickering is normal when EPD is performing a full screen update to clear ghosting from the previous image so to ensure better clarity and legibility for the new image.
2.There will be no flicker when EPD performs a partial update.
3.Please make sue that EPD enters sleep mode when update is completed and always leave the sleep mode command. Otherwise, this may result in a reduced lifespan of EPD.
4.Please refrain from inserting EPD to the FPC socket or unplugging it when the MCU is being powered to prevent potential damage.)
5.Re-initialization is required for every full screen update.
6.When porting the program, set the BUSY pin to input mode and other pins to output mode.
*/
void loop() {
    unsigned char i;
 
 #if 0 //Full screen update, fast update, and partial update demostration.
			EPD_Init(); //Full screen update initialization.
			EPD_WhiteScreen_ALL(gImage_BW2,gImage_RW2); //To Display one image using full screen update.
			EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
			delay(3000); //Delay for 2s.
			
			/************Fast update mode(12s)*******************/
	#if 0 //Fast update demostration.	
			EPD_Init_Fast(); //Fast update initialization.
			EPD_WhiteScreen_ALL(gImage_BW2,gImage_RW2); //To Display one image using full screen update.
			EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
			delay(3000); //Delay for 2s.
	#endif				
	#if 1 //Partial update demostration.
	//Partial update demo support displaying a clock at 5 locations with 00:00.  
	//After 5 partial updates, implement a full screen update to clear the ghosting caused by partial updatees.
	//////////////////////Partial update time demo/////////////////////////////////////
			EPD_Init(); //Electronic paper initialization.	
			EPD_SetRAMValue_BaseMap(gImage_BW1,gImage_RW1); //Please do not delete the background color function, otherwise it will cause unstable display during partial update.
			EPD_Init_Part(); //Part update initialization.
			EPD_Dis_Part_TwoData(376,24,Num[2],Num[5],2,104,48,1); //x,y,DATA-A~E,Resolution 48*104      
			EPD_Dis_Part_TwoData(376+48*4+24,24,Num[5],Num[0],2,104,48,1); //x,y,DATA-A~E,Resolution 48*104     
	
			EPD_Dis_Part_TwoData(376,24,Num[2],Num[6],2,104,48,0); //x,y,DATA-A~E,Resolution 48*104      
			EPD_Dis_Part_TwoData(376+48*4+24,24,Num[5],Num[1],2,104,48,0); //x,y,DATA-A~E,Resolution 48*104     
				
			EPD_Dis_Part_TwoData(376,24,Num[2],Num[7],2,104,48,0); //x,y,DATA-A~E,Resolution 48*104      
			EPD_Dis_Part_TwoData(376+48*4+24,24,Num[4],Num[9],2,104,48,0); //x,y,DATA-A~E,Resolution 48*104     
				
			EPD_Dis_Part_TwoData(376,24,Num[2],Num[8],2,104,48,0); //x,y,DATA-A~E,Resolution 48*104      
			EPD_Dis_Part_TwoData(376+48*4+24,24,Num[5],Num[2],2,104,48,0); //x,y,DATA-A~E,Resolution 48*104     

			EPD_Dis_Part_TwoData(376,24,Num[2],Num[9],2,104,48,0); //x,y,DATA-A~E,Resolution 48*104      
			EPD_Dis_Part_TwoData(376+48*4+24,24,Num[5],Num[3],2,104,48,0); //x,y,DATA-A~E,Resolution 48*104  			
			EPD_DeepSleep();  //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
			delay(3000); //Delay for 2s.
	#endif	
	
	#if 0 //Demonstration of full screen update with 180-degree rotation, to enable this feature, please change 0 to 1.
			/************Full display(180)*******************/
			EPD_Init_180(); //Full screen update initialization.
		  EPD_WhiteScreen_ALL(gImage_BW1,gImage_RW1); //To Display one image using full screen update.
		  EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
			delay(3000); //Delay for 2s.
	#endif			
	
#endif


 #if 1 //GUI Demo(GUI examples can display points, lines, rectangles, circles, letters, numbers, etc).
   //Data initialization settings.
    Paint_NewImage(BlackImage, EPD_WIDTH, EPD_HEIGHT, 0, WHITE); //Set canvas parameters, GUI image rotation, please change 270 to 0/90/180/270.
    Paint_SelectImage(BlackImage); //Select current settings.

    /**************Drawing demonstration**********************/   
		Paint_Clear(WHITE); //Clear canvas.
		//Point.   
    Paint_DrawPoint(5, 10, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT); //point 1x1.
    Paint_DrawPoint(5, 25, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT); //point 2x2.
    Paint_DrawPoint(5, 40, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT); //point 3x3.
    Paint_DrawPoint(5, 55, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT); //point 4x4.
		//Line.
    Paint_DrawLine(20, 10, 70, 60, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1); //1x1line 1.
    Paint_DrawLine(70, 10, 20, 60, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1); //1x1line 2.
    EPD_Init(); //Full screen refresh initialization.
    EPD_Display_BW(BlackImage); //Display GUI image.

    Paint_Clear(WHITE); //Clear canvas.
		//Rectangle.
    Paint_DrawRectangle(20, 10, 70, 60, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1); //Hollow rectangle 1.
    Paint_DrawRectangle(85, 10, 130, 60, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1); //Hollow rectangle 2.
    //Circle.
		Paint_DrawCircle(150, 90, 30, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1); //Hollow circle.
    Paint_DrawCircle(200, 90, 30, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1); //solid circle.
    EPD_Display_RW(BlackImage); //Display GUI image.
		EPD_DeepSleep();//EPD_DeepSleep,Sleep instruction is necessary, please do not delete!!!
    delay(3000); //Delay for 3s.
    /***********Letter demo***************************/
		//Black and white images/////////////////////////////
		Paint_SelectImage(BlackImage);//Set the virtual canvas data storage location
    Paint_Clear(WHITE);
    Paint_DrawString_EN(0, 0, "Good Display", &Font8, WHITE, BLACK);  //5*8.
		Paint_DrawString_EN(0, 10, "Good Display", &Font12, WHITE, BLACK); //7*12.
		Paint_DrawString_EN(0, 25, "Good Display", &Font16, WHITE, BLACK); //11*16.
		EPD_Init(); //Full screen refresh initialization.
    EPD_Display_BW(BlackImage);//display black and white images
		//Red and white images///////////////////////
		Paint_Clear(WHITE);				
		Paint_DrawNum(0, 45, 123456789, &Font20, WHITE, BLACK); //14*20.
		Paint_DrawNum(0, 70, 123456789, &Font24, WHITE, BLACK); //17*24. 
    EPD_Display_RW(BlackImage);//display red and white images
		EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
		delay(3000); //Delay for 3s.
	
#endif
    //Clear
    EPD_Init(); //Full screen update initialization.
    EPD_WhiteScreen_White(); //Clear screen function.
    EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
    delay(3000); //Delay for 3s.

  while(1); // The program stops here
  
} 

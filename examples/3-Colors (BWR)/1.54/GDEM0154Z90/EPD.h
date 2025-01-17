#ifndef _EPD_H_
#define _EPD_H_


#define EPD_WIDTH   200
#define EPD_HEIGHT  200
#define EPD_ARRAY  EPD_WIDTH*EPD_HEIGHT/8  


//Full screen update display
void EPD_HW_Init(void); 
void EPD_HW_Init_180(void);  
void EPD_WhiteScreen_ALL(const unsigned char* datasBW,const unsigned char* datasRW);
void EPD_WhiteScreen_White(void);
void EPD_WhiteScreen_Black(void);
void EPD_DeepSleep(void);										 

//GUI display					 
void EPD_HW_Init_GUI(void); 
void EPD_Display(unsigned char *datasBW,unsigned char *datasRW);  
												 
#endif




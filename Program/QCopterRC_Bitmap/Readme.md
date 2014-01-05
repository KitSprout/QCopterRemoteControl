QCopterRC SDIO Example
========
* Author  : [Hom](https://github.com/Hom19910422)
* Update  : 2014/01/01

Description
========
QCopterRC SDIO 搭配 FatFs 的範例程式，從一開始的 SD 卡初始化、SD 卡資訊、讀取資料夾目錄、寫檔案、讀檔案的整體測試，直接透過 3.5 吋螢幕做顯示。

Hardware
========
* LED  
PC13 - LED_B  
PC14 - LED_G  
PC15 - LED_R  

* KEY  
PA0　- KEY_LL  
PA1　- KEY_LP  
PA8　- KEY_RP  
PB2　- KEY_LR  
PD3　- KEY_RL  
PD6　- KEY_RR  
PE0　- KEY_PR  
PE1　- KEY_PP  
PE2　- KEY_PL  
PE3　- KEY_S1  
PE4　- KEY_S2  
PE5　- KEY_S3  

* SDIO  
PD8　- SDIO D0  
PD9　- SDIO D1  
PD10 - SDIO D2  
PD11 - SDIO D3  
PD12 - SDIO CK  
PD2　- SDIO CMD  

* FSMC  
PC6　- LCD_LIG  
PC7　- LCD_RST  
PD0　- LCD_D2  
PD1　- LCD_D3  
PD4　- LCD_RD  
PD5　- LCD_WR  
PD7　- LCD_CS  
PD8　- LCD_D13  
PD9　- LCD_D14  
PD10 - LCD_D15  
PD11 - LCD_RS  
PD14 - LCD_D0  
PD15 - LCD_D1  
PE7　- LCD_D4  
PE8　- LCD_D5  
PE9　- LCD_D6  
PE10 - LCD_D7  
PE11 - LCD_D8  
PE12 - LCD_D9  
PE13 - LCD_D10  
PE14 - LCD_D11  
PE15 - LCD_D12  

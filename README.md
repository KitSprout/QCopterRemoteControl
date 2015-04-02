[QCopterRC](https://github.com/QCopter/QCopterRemoteControl)
========
* Author  : [Hom](https://github.com/Hom-Wang)
* Version : v1.1
* Update  : 2015/04/03

Description
========
QCopteRC 是一個遙控器，用來與 QCopterFC 溝通、控制，是四軸飛行器的控制裝置，搭載感測器，有體感功能，板子上外接 3.5 吋螢幕，可以將四軸上的回傳回來的資訊顯示出來，並且建立操作介面。

License
========
* 硬體(Hardware)採用 [CC BY-SA 3.0 TW](http://creativecommons.org/licenses/by-sa/3.0/tw/deed.zh_TW) 方式授權 
  
　　<a rel="license" href="http://creativecommons.org/licenses/by-sa/3.0/tw/"><img alt="創用 CC 授權條款" style="border-width:0" src="http://i.creativecommons.org/l/by-sa/3.0/tw/80x15.png" /></a>  
　　<span xmlns:dct="http://purl.org/dc/terms/" property="dct:title"> QCopterRemoteControl </span>由<a xmlns:cc="http://creativecommons.org/ns#" href="https://plus.google.com/u/0/112822505513154783828/posts" property="cc:attributionName" rel="cc:attributionURL"> Hom </a>製作，以<a rel="license" href="http://creativecommons.org/licenses/by-sa/3.0/tw/deed.zh_TW"> 創用CC 姓名標示-相同方式分享 3.0 台灣 授權條款 </a>釋出。  

* 軟體(Software)採用 [MIT License](http://opensource.org/licenses/MIT) 方式授權  

Hardware
========
* 控制器　 : [STM32F407V](http://www.st.com/web/catalog/mmc/FM141/SC1169/SS1577/LN11/PF252140) 100Pin 168MHz DSP FPU
* 顯示器　 : [TFT_3.5-inch](https://github.com/Hom19910422/TFT_3.5-inch) ( 3.5" 480*320 )，使用 FSMC 操作
* 感測器　 : [IMU 6-DOF](https://github.com/OpenPCB/IMU_10-DOF) ( [MPU-6050](http://www.invensense.com/mems/gyro/mpu6050.html) )
* 儲存紀錄 : SD 卡，使用 SDIO 操作
* 無線傳輸 : [nRF24L01P](http://www.nordicsemi.com/eng/Products/2.4GHz-RF/nRF24L01P) + PA + LNA
* 乙太網路 : [W5500](http://www.wiznet.co.kr/Sub_Modules/en/product/Product_Detail.asp?cate1=&cate2=&cate3=&pid=1193)，使用 SPI 操作
* 外接介面 : 1*SPI ( FFC16 ) 、1*USB ( Micro ) 、1*UART、1*I2C/CAN
* PCB 尺寸 : 155 * 60mm
* 設計軟體 [Altium Designer 13](http://www.altium.com/en/products/altium-designer) ( PcbLib use AD [PcbLib v0.2](https://github.com/OpenPCB/AltiumDesigner_PcbLibrary) )

*** 目前 W5500 尚未完成測試 ...

QCopterRC v2.0 預計修改 ( 尚未決定改版時間 )：  
>1. 微控制器改為 LQFP1100 的 STM32F42xV 或 STM32F43xV，增加運算速度。  
>2．無線傳輸部分改用 [nRF51422](https://www.nordicsemi.com/eng/Products/ANT/nRF51422) 傳輸，以相容 BLE & ANT+  
>3. 改成使用 4 吋 800*480 螢幕，增加解析度及畫質。  
>4. 由於改成 4 吋螢幕，所以會修改整體位置，並增減部分輸入裝置功能或數量，像是按鍵數等。  
>5. 去除乙太網路功能。  

<img src="https://lh3.googleusercontent.com/-r6Nh2HrxldA/UrWXRap8O-I/AAAAAAAAFwo/pbTsi6B34RU/s800/QCopterRC_System.png" width="800" />

Related Documents
========
* [Update Records - Hackpad](https://hom.hackpad.com/QCopterRC-FWmRgT70cZ3)
* [Datasheet & BOM - Google Drive](https://drive.google.com/folderview?id=0BzL2wwAot6oPWm5BdGdBbk5lRzg&usp=sharing)

Program
========
QCopterRC RemoteControl ( 已完成基本遙控功能，介面完善中... )  
QCopterRC WaveForm ( 示波器功能 )  
QCopterRC Bitmap ( Bitmap 檔案讀取 )  

Example
========
* QCopterRC ADC
* QCopterRC FFCSPI-TFT2.2 ( use [TFT_2.2-inch](https://github.com/QCopter/TFT_2.2-inch) )
* QCopterRC FFCSPI-MPU9250 ( use [SmartIMU](https://github.com/Hom-Wang/SmartIMU) )
* QCopterRC FLASH
* QCopterRC FSMC ( Use [TFT_3.5-inch](https://github.com/QCopter/TFT_3.5-inch) )
* QCopterRC KeyBoard
* [QCopterRC LED](https://github.com/QCopter/QCopterRemoteControl/tree/master/Program/TEST_QCopterRC_LED)
* QCopterRC NRF
* [QCopterRC SDIO](https://github.com/QCopter/QCopterRemoteControl/tree/master/Program/TEST_QCopterRC_SDIO) ( Use [Fatfs](http://elm-chan.org/fsw/ff/00index_e.html) 0.10 )
* QCopterRC IMU ( 尚未實際燒錄測試 )
* QCopterRC UART

View
========
<img src="https://lh6.googleusercontent.com/-AQUZyXwInaM/UrcvK1A35xI/AAAAAAAAF6k/2eTzKeHJpbI/s800/DSC_1833.jpg" width="800" />
<img src="https://lh4.googleusercontent.com/-A6pGim8IKBA/UrcvLityKFI/AAAAAAAAF7Q/EN3v33-LZH8/s800/DSC_1838.jpg" width="800" />
<img src="https://lh3.googleusercontent.com/-i2jI-RmPKf4/Usrnp9OxfLI/AAAAAAAAGKs/qWmk2hAYP6o/s800/DSC_1919.jpg" width="800" />
<img src="https://lh5.googleusercontent.com/-IaevGzKqz3w/Usrnq6NHzVI/AAAAAAAAGK8/JWCgRssayyI/s800/DSC_1940.jpg" width="800" />
<img src="https://lh6.googleusercontent.com/-1GhxOp8Odig/UrcvJOf2yGI/AAAAAAAAF6A/DydFt1GlMtc/s800/DSC_1804.jpg" width="800" />
<img src="https://lh4.googleusercontent.com/-deRcVLpT0XQ/UrcvKjl6h_I/AAAAAAAAF6Y/J-30F-g-q60/s800/DSC_1828.jpg" width="800" />
<img src="https://lh4.googleusercontent.com/-3XqjPx65wiw/UrcvKvSGUSI/AAAAAAAAF6c/gBzTH2sirxQ/s800/DSC_1820.jpg" width="800" />
<img src="https://lh4.googleusercontent.com/-4TkxysD7Ot4/UrcvJ_Tlu9I/AAAAAAAAF6M/iOD2lAik7kE/s800/DSC_1813.jpg" width="800" />
<img src="https://lh4.googleusercontent.com/-nApnkzk6IK0/UrcvMN4k6nI/AAAAAAAAF64/sYbOPJUFbyA/s800/DSC_1864.jpg" width="800" />
<br />
更多圖片 [Google+ albums](https://plus.google.com/u/0/photos/+文宏王Hom/albums/5930573467560028593)

Config
========
<img src="https://lh3.googleusercontent.com/-iZeoe4lx8wU/Usl9gZgsuZI/AAAAAAAAGKA/TYhudVKkLHo/s1600/RC_CONF.png" width="800" />
<img src="https://lh5.googleusercontent.com/-vNn1p6Z6Y7s/UrczaR9EPkI/AAAAAAAAF9M/80ux41UU7Ac/s1600/QCopterRC_Config_PIN.png" width="800" />
<img src="https://lh4.googleusercontent.com/-dkd0YtkochY/UrczaIU0xXI/AAAAAAAAF9E/m6ET7IX6QPM/s1600/QCopterRC_Config_AF.png"  width="800" />
<img src="https://lh6.googleusercontent.com/-8CqkUnWzeiY/UrczaFQCg1I/AAAAAAAAF9A/zu0XXFit_L0/s1600/QCopterRC_Config_DMA.png" width="800" />

*** 傳輸資料格式  
QFC_TO_QRC  
<img src="https://lh3.googleusercontent.com/-eIh5NvuE0aw/UrsPnzmAcZI/AAAAAAAAGDc/mu5YwwC-S1s/s1600/QFC_TO_QRC.png" width="800" />
QRC_TO_QFC  
<img src="https://lh4.googleusercontent.com/-U3WhNPhTxHo/UsgUPnOV6bI/AAAAAAAAGJE/AayjWFXOgPI/s1600/QRC_TO_QFC.png" width="800" />

Schematic
========
<img src="https://lh4.googleusercontent.com/-XJrP5jj4uVc/Urhxxdme28I/AAAAAAAAF_Y/r3ew48ok084/s1600/QCopterRC_Sch_MAIN.png" width="800" />
<br>＊STM32F407V<br>
<img src="https://lh3.googleusercontent.com/-SxaNTLV6tpo/Urhxxwy7hRI/AAAAAAAAF_c/SHcH6ecnMIs/s800/QCopterRC_Sch_MCU.png" width="591" />
<br>＊SW<br>
<img src="https://lh6.googleusercontent.com/-Ab_ii-lINjc/UrhxzJTdqrI/AAAAAAAAF_g/XK3r09ch1YY/s800/QCopterRC_Sch_SWD.png" width="142" />
<br>＊POWER<br>
<img src="https://lh4.googleusercontent.com/-t6zbRQSs670/Urhxy66k_qI/AAAAAAAAF_w/aY_S796HfGE/s800/QCopterRC_Sch_POWER.png" width="330" />
<br>＊LED<br>
<img src="https://lh6.googleusercontent.com/-dNle7SRrhxk/Urhxw0rm02I/AAAAAAAAF-8/eYzahldl1vo/s800/QCopterRC_Sch_LED.png" width="233" />
<br>＊KEY<br>
<img src="https://lh6.googleusercontent.com/-hX6X6MF3RnY/UrhxwSmUAQI/AAAAAAAAF_A/yOrXEpzLoks/s800/QCopterRC_Sch_KEY.png" width="800" />
<br>＊NRF<br>
<img src="https://lh5.googleusercontent.com/-CSlGL5D3Npk/UrhxyDFwxFI/AAAAAAAAF_Q/OsRn1dDF1PM/s800/QCopterRC_Sch_NRF.png" width="172" />
<br>＊IMU<br>
<img src="https://lh3.googleusercontent.com/-OD69VuptCW8/UrhxwP06e2I/AAAAAAAAF-s/A5RKLNDV_n4/s800/QCopterRC_Sch_IMU.png" width="166" />
<br>＊EXT<br>
<img src="https://lh6.googleusercontent.com/-AyW2FcYtiOI/Urhxvldj77I/AAAAAAAAF-Y/P7spzFB-VeU/s800/QCopterRC_Sch_EXT.png" width="251" />
<br>＊FFCSPI<br>
<img src="https://lh5.googleusercontent.com/-a2MLB5qE-zc/UrhxvjxS9YI/AAAAAAAAF-g/ItJLxbqZsa8/s800/QCopterRC_Sch_FFCSPI.png" width="152" />
<br>＊LCD<br>
<img src="https://lh5.googleusercontent.com/-TQ0qQbi0F4k/UrhxwuK6l-I/AAAAAAAAF-4/lC83gfkhJGM/s800/QCopterRC_Sch_LCD.png" width="771" />
<br>＊USB<br>
<img src="https://lh4.googleusercontent.com/-GG_1xZfw4Cs/UrhxzV2CI9I/AAAAAAAAF_s/YF6jB9EE4F0/s800/QCopterRC_Sch_USB.png" width="239" />
<br>＊ETH<br>
<img src="https://lh5.googleusercontent.com/-s6iejk9BC9g/Urhxvm461nI/AAAAAAAAF-k/jwPnLcUFrGs/s1600/QCopterRC_Sch_ETH.png" width="800" />

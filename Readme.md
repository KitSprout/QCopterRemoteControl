[QCopterRC](https://github.com/Hom19910422/QCopterRemoteControl)
========
* Author  : [Hom](https://github.com/Hom19910422)
* Version : v0.0
* Update  : 2013/12/17

Description
========
QCopteRC 是一個遙控器，用來與 QCopterFC 溝通、控制，是四軸飛行器的控制裝置，  
板子上建有 3.5 吋螢幕，可以將四軸上的回傳回來的資訊顯示出來。

Hardware
========
* 控制器　 : [STM32F407V](http://www.st.com/web/catalog/mmc/FM141/SC1169/SS1577/LN11/PF252140) 100Pin 168MHz DSP FPU
* 顯示器　 : [TFT_3.5-inch](https://github.com/Hom19910422/TFT_3.5-inch) ( 3.5" 480*320 )，使用 FSMC 操作
* 感測器　 : [IMU 6-DOF](https://github.com/Hom19910422/IMU_10-DOF) ( [MPU-6050](http://www.invensense.com/mems/gyro/mpu6050.html) )
* 儲存紀錄 : SD 卡，使用 SDIO 操作
* 無線傳輸 : [nRF24L01P](http://www.nordicsemi.com/eng/Products/2.4GHz-RF/nRF24L01P) + PA + LNA
* 乙太網路 : [W5500](http://www.wiznet.co.kr/Sub_Modules/en/product/Product_Detail.asp?cate1=&cate2=&cate3=&pid=1193)，使用 SPI 操作
* 外接介面 : 1*SPI ( FFC16 ) 、1*USB ( micro ) 、1*UART
* PCB 尺寸 : 155 * 60mm
* 設計軟體 [Altium Designer 13](http://www.altium.com/en/products/altium-designer) ( [PcbLib](https://github.com/CYACAcademic/AltiumDesigner_PcbLibrary) use AD PcbLib v0.1 )

Program
========

Test
========

Related Documents
========
* [Google Drive](https://drive.google.com/folderview?id=0BzL2wwAot6oPWm5BdGdBbk5lRzg&usp=sharing)

View
========
<img src="https://lh5.googleusercontent.com/-54YnRyrZJSg/Uq8ca2uChwI/AAAAAAAAFWk/lqvL_L71pnQ/s800/RC_Top3D1_v1.0.png" height="317" width="800" />
<img src="https://lh5.googleusercontent.com/-p9rxwdCPN0E/Uq8cYh2LKjI/AAAAAAAAFV4/D2___PPIYdw/s800/RC_Bottom3D1_v1.0.png" height="334" width="800" />
<br />
更多圖片 [Google+ albums](https://plus.google.com/u/0/photos/+文宏王Hom/albums/5930573467560028593)

Config
========
<img src="https://lh4.googleusercontent.com/-cw0Fm1Ns6YE/Uq8swvYOgXI/AAAAAAAAFY4/0MDGJfJ2_2Y/s800/QCopterRC_Config_PIN.png" height="332" width="800" />
<img src="https://lh4.googleusercontent.com/-ZR7rreKls4g/Uq8swjjCkuI/AAAAAAAAFZE/02-HMPcusxQ/s1600/QCopterRC_Config_AF.png" width="800" />
<img src="https://lh6.googleusercontent.com/-K6xmewD5tEU/Uq8swhN4jiI/AAAAAAAAFY0/_UgIbHUlUf4/s800/QCopterRC_Config_DMA.png" height="492" width="800" />

Schematic
========

<br />
<br />
<a href="http://www.oshwa.org/">
<img src="https://lh5.googleusercontent.com/-nIBTA3RL8Hk/Ug8wr_ly3-I/AAAAAAAADFY/hAfv5LAzHag/s144/oshw-logo-800-px.png">
<br />
<br />
<a rel="license" href="http://creativecommons.org/licenses/by-sa/3.0/tw/deed.zh_TW"><img alt="創用 CC 授權條款" style="border-width:0" src="http://i.creativecommons.org/l/by-sa/3.0/tw/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title"> QCopterRemoteControl </span>由<a xmlns:cc="http://creativecommons.org/ns#" href="https://plus.google.com/u/0/112822505513154783828/posts" property="cc:attributionName" rel="cc:attributionURL"> Hom </a>製作，以<a rel="license" href="http://creativecommons.org/licenses/by-sa/3.0/tw/deed.zh_TW">創用CC 姓名標示-相同方式分享 3.0 台灣 授權條款</a>釋出。<br />此作品衍生自<a xmlns:dct="http://purl.org/dc/terms/" href="https://github.com/Hom19910422" rel="dct:source"> Hom-GitHub </a>

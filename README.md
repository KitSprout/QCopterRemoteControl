QCopterRC
========
[![GitHub version](https://img.shields.io/badge/QRC%20version-v1.1-brightgreen.svg)](https://github.com/KitSprout/QCopterRemoteControl/tree/QCopterRC)
[![GitHub version](https://img.shields.io/badge/QRCs%20version-v1.0-brightgreen.svg)](https://github.com/KitSprout/QCopterRemoteControl)
[![GitHub license](https://img.shields.io/badge/license-%20MIT%20%2F%20CC%20BY--SA%204.0-blue.svg)](https://github.com/KitSprout/QCopterRemoteControl/blob/master/LICENSE)
[![GitHub pcb library](https://img.shields.io/badge/pcb%20library-%20v2.16-yellow.svg)](https://github.com/KitSprout/AltiumDesigner_PcbLibrary/releases/tag/v2.16)


QCopterRemoteControl 是一個遙控器開板，四軸飛行器的控制裝置，用來與 QCopterFlightControl 溝通、控制，板上搭載搖桿與感測器，並外接顯示螢幕，可以將四軸上的回傳回來的資訊顯示出來，螢幕建立了簡單的操作介面，方便使用者設定、觀察飛控板，目前遙控器有 QCopterRC 與 QCopterRCs 兩種版本，前者使用芯片效能較高、功能多，帶高解析度的螢幕，後者功能較為簡潔，製作成本比較低。目前開發著重於 QCopterRCs，想了解 QCopterRC 的可以進入該分支 [branche](https://github.com/KitSprout/QCopterRemoteControl/tree/QCopterRC)

Hardware
========
* 控制器　 : [STM32F411CE](http://www.st.com/en/microcontrollers/stm32f411ce.html) 48Pin 100MHz DSP FPU
* 顯示器　 : [OLED_1.5-inch]() ( SSD1351 1.5" 128*128 )，使用 SPI 操作
* 感測器　 : [MPU9250](https://www.invensense.com/products/motion-tracking/9-axis/mpu-9250/)
* 無線傳輸 : [nRF24L01P](http://www.nordicsemi.com/eng/Products/2.4GHz-RF/nRF24L01P) + PA + LNA
* 設計軟體 [Altium Designer 17](http://www.altium.com/en/products/altium-designer) ( PcbLib use AD [PcbLib v2.16](https://github.com/KitSprout/AltiumDesigner_PcbLibrary/releases/tag/v2.16) )

<img src="" />

View
========
<img src="" />

<br />
[more photo...](https://goo.gl/photos/wA4TmWAdz5D3ZGH7A)

Config
========
<img src="" />

Schematic
========
<img src="" />

Get it
========
Ruten Shop

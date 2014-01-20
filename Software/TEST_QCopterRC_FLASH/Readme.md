QCopterRC Flash Example
========
* Author  : [Hom](https://github.com/Hom19910422)
* Update  : 2013/12/29

Description
========
QCopterRC FLASH 測試程式，分別將三種變數型態陣列 unsigned char、unsigned short、
unsigned int 寫入至 STM32F407VG 的 FLASH 中，並且依照三種型態讀出，比較是否正確，
若正確會看到 LED 燈依序亮起 ( R → G → B)，最後做閃做的動作，若失敗只會看到 LED 閃爍。


這個 IO EXT 程式是使用 Keil C 與 8051 設計的，

主要是控制 NXP PCA9555 晶片做 IO 延伸控制使用，

為了增加 GPIO 不夠用的問題，一顆中有兩組 IO PORT，

可以搭配 EXT INT 外部中斷 PIN 控制進入 ISR 做動作， 


程式部份參考說明：

===================================================

為什麼要用那個 marco ... 其實這裡的程式是這樣：

我們使用一顆 pca9555，有兩組的 io ext 就是 16 bit

也就是說外部的資料中多了兩 port 的 gpio

那麼我們在內部就定義出兩個 byte 的資料設為 p0 與 p1

當我們要寫入 io ext (pca9555) 時，我們就先呼叫一下 macro

LED_NTSC1(ON),LED_NTSC2(OFF),LED_PAL1(OFF);
LED_PALN(OFF),LED_PAL2(OFF),LED_PALM(OFF);

其實這裡的巨集只是把 pn_data_port 的某一個 bit 設為 |= 0x01 或是 &~=0x01

就是舉起或是落下而已，為什麼要這樣寫，因為多半用這類 io ext 都是這樣設計，這樣你要點亮那一顆 led 或是關那一顆 led

只要在送 write 前先: LED_NTSC1(ON);

這樣

temp[1]=PCA9555_LED_PORT.p0;
temp[2]=PCA9555_LED_PORT.p1;

的資料就會被設定好了，
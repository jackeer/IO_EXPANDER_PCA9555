
這個 IO EXT 程式是使用 Keil C 與 8051 設計的，

主要是控制 NXP PCA9555 晶片做 IO 延伸控制使用，

為了增加 GPIO 不夠用的問題，一顆中有兩組 IO PORT，

可以搭配 EXT INT 外部中斷 PIN 控制進入 ISR 做動作， 
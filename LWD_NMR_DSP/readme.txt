下载的参数表：表头+内容
1.刻度模式参数表 19个字 起始地址：0x8001
2.测井模式参数表 57个字

中控传来的参数表，主控板原封不动下发。到底是自己内部设计一套比较好，还是用中控的通信协议。

实际发射频率需要自己根据温度公式得出。

工作频率并不是中心频率。

RefAmp 参考幅值为0x294

SCIA时钟初始化

套管检测时参数设置问题

SW_ACQ1=1 SW_ACQ2=0时，通道选择ECHO

在CCS10.0下，不要动使用了IQmath函数的文件，否则会报错。解决办法是删除工程，然后再添加进来（import project）。

Relaease版本是FLASH下载版本程序
Debug版本是RAM版本程序

cmd文件不能轻易改动，很容易导致FLASH版本程序出问题
L1RAM在RAM版本下不能使用，要不然程序无法运行；而且L1RAM只能被设置为PAGE=1，要不然程序无法运行。
c_int_0函数要在H0RAM中才行

在写代码之前，编译器优化选项一定要关闭。否则FPGA和一些延时函数都无法正常工作。
voliate关键字

LWD_NMR_DSP RAM版和FALSH版本分别对应DEBUG和Release选项，需要在Mydefine.h中选择是否屏蔽#define DEBUG


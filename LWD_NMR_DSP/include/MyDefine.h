#define DEBUG       // 用来控制RAM和FALSH版本程序

// 参数表相关宏
#define CAL_TABLE_LEN 	 	20  	// 刻度模式参数表长度
#define WELL_TABLE_LEN 	 	57  	// 测井模式参数表长度
#define TUNING_TABLE_LEN 	69	 	// 刻度参数表，主要用来调谐，使用参数并不多
#define CONFIG_TABLE_LEN 	19  	// 仪器配置参数表

#define ADDR_CAL_TABLE_START	(Uint16 *)0x8002
#define ADDR_WELL_TABLE_START	(Uint16 *)0x8018
#define ADDR_TUNING_TABLE_START	(Uint16 *)0x8057
#define ADDR_CONFIG_TABLE_START	(Uint16 *)0x80A2

// 计算Q值的系数，Q=2*c*sqrt(log(sqrt(2))) Q_factor=2*sqrt(log(sqrt(2)))
#define Q_FACTOR		0.775925	

//Address macro definations
// TODO
#define TABLE_START			0x8000    //参数表0x8000+78
//#define WORK_MODE_ADDR		0x8001
//#define FREQ_STR_ADDR		0x8002
//#define FREQ_SEL_WORDS_ADDR	0x800A
//#define WIDTH_STR_ADDR		0x800C
//#define STEP_FREQ_ADDR		0x8015
//#define SIGNAL_ACQ_PERIOD_NUM_ADDR		0x8016
//#define SIGNAL_ACQ_FREQ_TIMES_ADDR		0x8017
//#define NOISE_ACQ_TIME_ADDR	0x8018
//#define NOISE_ACQ_FREQ_ADDR	0x8019
//#define MAT_PARA_STR_ADDR	0x801C
//#define SCALE_TE_ADDR		0x801F

#define DDS_FREQ_ADDR		0x80B9 //gai

#define SCANTABLE_START			0x120000		//扫频上传数据表首地址
#define SCALETABLE_START		0x120000		//刻度数据表首地址
#define HOLETABLE_START			0x120000		//孔隙度数据表首地址
#define PLUSETABLE_START		0x120000		//发射信号波形采集检测表首地址
#define DECPMGTABLE_START		0x120000		//DeCpmg表首地址
#define PAPSTABLE_START	        0x140000

// mode for LWD NMR
#define PPM_TABLE_START         0x120000
#define PPDIF_TABLE_START		0x120000
#define PPT1_TABLE_START        0x120000
#define PPOFTW_TABLE_START      0x120000
#define PPShort_TABLE_START     0x120000
#define CASING_TABLE_START 		0x120000

#define MINITABLE_START		0x008100		//the start address of mini scan data store zone

//Parameter macro definations
#define USER_DISABLE		0x0002
#define USER_ENABLE			0x0001
#define SET					0x0001
#define CLEAR				0x0000

#define POSITIVE			0x0001
#define NEGATIVE			0x0000

#define TABLE_TOTAL_NUM     83
#define BAND_NUM			9

#define SHIFT				10           //格式转换
#define NOISE_STRIP			8           //噪声舍去点数

#define SHAKE_NUM			4			//起振次数
#define IN_BRI_WIDTH		100			//内桥脉宽
#define OUT_BRI_WIDTH		200			//外桥脉宽
#define SHORT_DUMP_TIME		100			//短泄放时间
#define LONG_DUMP_TIME		2000		//长泄放时间
#define WAIT_DUMP_TIME		280			//短泄放间隔时间

#define PLUSE_STRIP  		10           //激励舍去点数

#define SOFT_DUMP_TIME		8000
#define TE_ADD				1
#define T_N					10   //90°和180°之间减少的周期数
#define FPGA_COUNT			100      //fpga对应1us计数值（10ns单位
#define HV_ON				0x0001
#define HV_OFF				0x0002

#define	P_PLUSE_T1			120
#define	P_PLUSE_T2			603		
#define	P_PLUSE_T3			120
#define	P_PLUSE_T4			201

#define	SD_SACQ_T1			120	
#define	SD_SACQ_T2			613	

#define SCALE_REPAIR1		813    //scale状态机用于稳定，复位等操作的时间计数值（10ns单位）
#define SCALE_REPAIR2		920    //scale状态机用于稳定，复位等操作的时间计数值（10ns单位）
#define SWITCH_REPAIR		200    //ADG1404稳定时间计数值（10ns单位）
#define PP3_REPAIR1			3
#define PPoil_REPAIR1		4
#define PPoil_REPAIR2		2
#define PPoil_REPAIR3		9
#define PPgas_REPAIR1		5
#define PPgas_REPAIR2		10
#define PPgas_REPAIR3		9
#define PP6_REPAIR1			3		//此时间需要根据做实验调整
#define PP6_REPAIR2			9

#define T2D_REPAIR1			11		//this parameters should be adjusted
#define T2D_REPAIR2			4		//this parameters should be adjusted
#define T1T2_REPAIR1		10		//this parameters should be adjusted
#define T1T2_REPAIR2		4		//this parameters should be adjusted
#define T12D_REPAIR1		10		//this parameters should be adjusted
#define T12D_REPAIR2		4		//this parameters should be adjusted

#define MINI_TEST			53		//the time of mini scan is 7.6ms
#define FPGA_BC				5


//Interface with FPGA macro definations
//外部地址区域2（0x080000---0x100000）
#define  DSP_NS_CTRL_EN		*(Uint16 *) 0x80004       //噪声or信号控制选择（选择噪声数据通道）
#define  DSP_NS_CTRL_DIS	*(Uint16 *) 0x80005      //选择信号数据通道           

#define  SCAN_RST_EN		*(Uint16 *) 0x80008       //扫频复位（上升沿高有效）
#define  SCAN_RST_DIS		*(Uint16 *) 0x80009   
#define  SCAN_START_EN		*(Uint16 *) 0x8000A       //扫频启动
#define  SCAN_START_DIS		*(Uint16 *) 0x8000B 

#define  NOISE_RST_EN		*(Uint16 *) 0x8000C       //噪声复位（上升沿高有效）
#define  NOISE_RST_DIS		*(Uint16 *) 0x8000D
#define  NOISE_START_EN		*(Uint16 *) 0x8000E       //噪声启动（上升沿高有效）
#define  NOISE_START_DIS	*(Uint16 *) 0x8000F

#define  DDS_CONFDATA		*(Uint16 *) 0x80015         //dds频率字
#define  DDS_DATALOAD_EN	*(Uint16 *) 0x80016    //dds频率字装载（上升沿高有效）
#define  DDS_DATALOAD_DIS	*(Uint16 *) 0x80017   
#define  DDS_DATACHOICE_EN	*(Uint16 *) 0x80018   //dds频率字高低位（高位）
#define  DDS_DATACHOICE_DIS	*(Uint16 *) 0x80019   //低位

#define  CAL_DIVDATA		*(Uint16 *) 0x8001A          //cal分频字（按分频数翻转）
#define  CAL_DATALOAD_EN	*(Uint16 *) 0x8001B     //cal分频字装载（上升沿高有效）
#define  CAL_DATALOAD_DIS	*(Uint16 *) 0x8001C

#define  NRAM_RST_EN		*(Uint16 *) 0x8001D         //noise_ram读复位（上升沿高有效）
#define  NRAM_RST_DIS		*(Uint16 *) 0x8001E 
#define  NRAM_RD_EN			*(Uint16 *) 0x8001F          //noise_ram读使能（高有效）
#define  NRAM_RD_DIS		*(Uint16 *) 0x80020

/*
#define  NRAM_RST_EN  *(Uint16 *) 0x2000         //noise_ram读复位（上升沿高有效）
#define  NRAM_RST_DIS *(Uint16 *) 0x2001
#define  NRAM_RD_EN  *(Uint16 *) 0x2009          //noise_ram读使能（高有效）
#define  NRAM_RD_DIS *(Uint16 *) 0x2008 
*/

#define  NRAM_LOAD_EN		*(Uint16 *) 0x80021        //noise相关寄存器装载（上升沿高有效）
#define  NRAM_LOAD_DIS		*(Uint16 *) 0x80022 
#define  NRAM_ACQNUM		*(Uint16 *) 0x80023         //noise采集数据个数
#define  NRAM_DIVNUM		*(Uint16 *) 0x80024          //noise采集时钟分频数（10位数据，按照高5位和低5位分频）

#define  SIGNAL_ACQNUM		*(Uint16 *) 0x80025        //信号采集点数
#define  SIGNAL_PERIODNUM	*(Uint16 *) 0x80026     //信号周期采样率
//#define  SIGNAL_PERIODNUM *(Uint16 *) 0x2011     //信号周期采样率
#define  SIGNAL_LOAD_EN		*(Uint16 *) 0x80027       //signal相关寄存器装载（上升沿高有效）
#define  SIGNAL_LOAD_DIS	*(Uint16 *) 0x80028

#define  DATACHOICE			*(Uint16 *) 0x80029                //加法器结果16位通道选择 
//#define  DATACHOICE *(Uint16 *) 0x2010  

#define  STATE1MS_RST_EN	*(Uint16 *) 0x80031         //1ms状态机复位
#define  STATE1MS_RST_DIS	*(Uint16 *) 0x80032         
#define  STATE1MS_START_DIS	*(Uint16 *) 0x80033         //1ms状态机启动（相关信号输出选择）
#define  STATE1MS_START_EN	*(Uint16 *) 0x80034
#define  STATE1MS_LOAD_DIS	*(Uint16 *) 0x80035         //1ms状态机LOAD信号清零
#define  STATE1MS_LOAD_EN	*(Uint16 *) 0x80036          //1ms状态机LOAD信号有效
#define  STATE1MS_CHOICE	*(Uint16 *) 0x80037         //1ms状态机参数选择
#define  STATE1MS_DATA		*(Uint16 *) 0x80038        //1ms状态机参数

#define  RELAY_ON   		*((Uint16 *)0x80040)         // 开启继电器，写入低十位[9:0]来控制继电器端口高低电平输出
#define  RELAY_CLOSE        *((Uint16 *)0x80041)        // 关闭继电器，写入低十位[9:0]来控制继电器端口高低电平输出

#define  CTRL_CHOICE		*(Uint16 *) 0x80060          //控制通路选择（为0扫频，噪声，为1刻度）

#define  SCALE_RST_EN		*(Uint16 *) 0x80061        //刻度复位
#define  SCALE_RST_DIS		*(Uint16 *) 0x80062       
#define  SCALE_START_EN		*(Uint16 *) 0x80063      //刻度启动
#define  SCALE_START_DIS	*(Uint16 *) 0x80064       
#define  SCALE_LOAD_EN		*(Uint16 *) 0x80065       //刻度数据装载
#define  SCALE_LOAD_DIS		*(Uint16 *) 0x80066 
#define  SCALE_DATA			*(Uint16 *) 0x8006D         //scale状态机数据
#define  SCALE_CHOICE		*(Uint16 *) 0x8006E         //scale状态机数据选择

#define  POSI_NEGE_EN		*(Uint16 *) 0x8006B        //正反相激励选择
#define  POSI_NEGE_DIS		*(Uint16 *) 0x8006C

#define  BRIDGE_LOAD_EN		*(Uint16 *) 0x80067      //内外桥数据装载
#define  BRIDGE_LOAD_DIS	*(Uint16 *) 0x80068
#define  BRIDGE_DATA		*(Uint16 *) 0x8006F         //bridge宽度数据  
    
#define  HALF_DATA			*(Uint16 *) 0x80070         //半激励数据

#define  DUMP_LOAD_EN		*(Uint16 *) 0x80069        //泄放数据
#define  DUMP_LOAD_DIS		*(Uint16 *) 0x8006A 
#define  DUMP_CHOICE		*(Uint16 *) 0x80071         //dump数据选择
#define  DUMP_DATA			*(Uint16 *) 0x80072         //dump数据   
    
#define  SCALE_DDSDIV		*(Uint16 *) 0x80073         //scaledds分频数据

#define	 SD_SACQ_CHOICE		*(Uint16 *)	0x80074			
#define	 SD_SACQ_DATA		*(Uint16 *)	0x80075			
#define	 SD_SACQ_LOAD_EN	*(Uint16 *)	0x80076			
#define	 SD_SACQ_LOAD_DIS	*(Uint16 *)	0x80077

#define  PLUSE_NOISE_EN		*(Uint16 *) 0x80080        //pluse_noise采样选择
#define  PLUSE_NOISE_DIS	*(Uint16 *) 0x80081
   
#define  PLUSE_SCALE_EN		*(Uint16 *) 0x80082        //pluse_scale激励泄放控制选择
#define  PLUSE_SCALE_DIS	*(Uint16 *) 0x80083 

#define  PLUSE_START_EN		*(Uint16 *) 0x80084        //pluse激励启动
#define  PLUSE_START_DIS	*(Uint16 *) 0x80085
#define  PLUSE_RST_EN		*(Uint16 *) 0x80086        //pluse激励复位
#define  PLUSE_RST_DIS		*(Uint16 *) 0x80087
#define  PLUSE_LOAD_EN		*(Uint16 *) 0x80088        //pluse激励数据装载
#define  PLUSE_LOAD_DIS		*(Uint16 *) 0x80089
#define  PLUSE_LCHOICE_EN	*(Uint16 *) 0x8008A        //pluse激励数据装载选择
#define  PLUSE_LCHOICE_DIS	*(Uint16 *) 0x8008B
#define  PLUSE_DATA			*(Uint16 *) 0x8008C        //pluse激励数据

#define  TIMER_DATA			*(Uint16 *) 0x80090        //定时器数据
#define  TIMER_START		*(Uint16 *) 0x80091        //定时器启动
#define  TIMER_STOP			*(Uint16 *) 0x80092

#define  SCAN_CHOICE_EN		*(Uint16 *) 0x80093        //扫频状态机数据选择
#define  SCAN_CHOICE_DIS	*(Uint16 *) 0x80094        
#define  SCAN_LOAD_EN		*(Uint16 *) 0x80095        //扫频状态机数据装载
#define  SCAN_LOAD_DIS		*(Uint16 *) 0x80096        
#define  SCAN_DATA			*(Uint16 *) 0x80097        //扫频状态机数据

#define  NSTATE_CHOICE_EN	*(Uint16 *) 0x80098        //noise状态机数据选择
#define  NSTATE_CHOICE_DIS	*(Uint16 *) 0x80099       
#define  NSTATE_LOAD_EN		*(Uint16 *) 0x8009A        //noise状态机数据装载
#define  NSTATE_LOAD_DIS	*(Uint16 *) 0x8009B      
#define  NSTATE_DATA		*(Uint16 *) 0x8009C        //noise状态机数据

#define  ACQCLK_EN			*(Uint16 *) 0x8009D        
#define  ACQCLK_DIS			*(Uint16 *) 0x8009E

#define  K1_EN				*(Uint16 *) 0x800A0        
#define  K1_DIS				*(Uint16 *) 0x800A1 
#define  K2_EN				*(Uint16 *) 0x800A2        
#define  K2_DIS				*(Uint16 *) 0x800A3

#define  PD_PLUSE_CHOICE	*(Uint16 *) 0x800A4 
#define  PD_PLUSE_DATA		*(Uint16 *) 0x800A5
#define  PD_PLUSE_LOAD_EN	*(Uint16 *) 0x800A6        
#define  PD_PLUSE_LOAD_DIS	*(Uint16 *) 0x800A7

#define  DUMP_SUSTAIN_EN	*(Uint16 *) 0x800A8
#define  DUMP_SUSTAIN_DIS	*(Uint16 *) 0x800A9
#define  DUMP_SUSTAIN_DATA  *(Uint16 *) 0x800AA

#define  INV_TURN_EN		*(Uint16 *) 0x800AB
#define  INV_TURN_DIS		*(Uint16 *) 0x800AC

#define  READ_NOISE			*(Uint16 *) 0x81000           
#define  RDDATA				*(Uint16 *) 0x82000 

#define MODE_CHOICE    		11
/*
#define  READ_NOISE *(Uint16 *) 0x2100           
#define  RDDATA *(Uint16 *) 0x2200
*/

// 从机标识
#define EVENT_BOARD_ID      0x55AA

// RS485延时
#define RS485_DELAY         25

// 主控板下发数据帧帧头定义，F means Frame
#define DATA_DOWN_TABLE_F   0x1328  // 参数表下载指令
#define DATA_UP_TABLE_F     0x1428  // 参数表上传指令
#define DATA_INQUIRE_F      0x9991  // 查询状态指令
#define DATA_OPERATION_F    0x9992  // 启动工作指令
#define DATA_CASING_F       0x9993  // 套管检测指令
#define DATA_UP_MODE_F      0x9994  // 模式数据上传指令
#define DATA_MODE_CONFIRM_F 0x9995  // 模式数据确认指令
#define DATA_K1K2_EN_F      0x9996  // 储能短节K1K2控制指令
#define DATA_K1K2_DIS_F     0x9997  // 储能短节断开指令（暂时未用）
#define DATA_HVState_F      0x9998  // 储能短节状态判断指令
#define DATA_SysCheck_F     0x9999  // 系统自检测指令
#define DATA_PAPS_F         0x999A  // PAPS数据上传指令
#define DATA_Parameter_F    0x99A0  // 重要参数下发指令

// 事件板回复帧帧头定义，F means Frame
#define REPLY_STATE_F       0x9981  // 查询状态指令回复
#define REPLY_DOWN_TABLE_F  0x9982  // 参数表下载指令回复
#define REPLY_UP_TABLE_F    0x9983  // 参数表上传指令回复
#define REPLY_CASING_F      0x9984  // 套管检测数据回复
#define REPLY_MODE_DATA_F   0x9985  // 刻度/测井模式数据回复
#define REPLY_CASING_ERR_F  0x9986  // 套管检测异常帧
#define REPLY_Parameter_F   0x9987  // 重要参数下发指令回复
#define REPLY_PAPS_F        0x9988  // PAPS数据上传指令回复

// 频率温度转换公式 f = -0.2516 * T + 568.0064
#define f_T_k -2.516f          // 公式斜率
#define f_T_b 5680.064f         // 公式截距

//// 继电器对应的频率转换公式，10个继电器则有十位，从0到1023，对应440kHz-580kHz
//#define RELAY_f_k -7.31f        // 公式斜率
//#define RELAY_f_b 4238.0f       // 公式截距

